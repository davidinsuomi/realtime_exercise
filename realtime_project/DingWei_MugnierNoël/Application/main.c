#include "MultiSensorSimulator.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>

#define MAX_TEMPERATURE 350															/* Defining the max temperature for sensor */

/*
	Calculate delta time between Tmeas measurement time (second argument)
	got when reading sensor descriptor and the time get after execution of 
	the reading (clock_gettime() function, third argument) it return the 
	interval in the first structure argument
*/
int delta_t(struct timespec*, struct timespec*, struct timespec*);
/*
	event handler for signal SIGRTMAX, it's called when sensor MAX_TEMPERATURE
	is overtaked, it just display a warning to user before returning
*/
void rt_handler(int, siginfo_t*, void*);

void main(void)
{
    int noOfSensors, sensorDescriptors[50], fd, i = 0;
	int const VALUES_PER_DESC = 5;
    char bufferRead[8];
	pid_t child1, child2, pid;
	
	struct sigevent sevent;
	struct sigaction sa;
    union sigval value;	
	
	/*
		Reading from opened sensor descriptor return Tmeas structure 
		describe as below we use it to get the sensor value !
		
		typedef struct {
			 struct timespec moment;
			 int value;
		} Tmeas;
	*/
	Tmeas measurement;	

	/*
		Create and initialize signal mask to handle the SIGRTMAX 
		Signal with our rt_handler handler
	*/
    sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = rt_handler;
	sigaction(SIGRTMAX, &sa, NULL);
	
	sevent.sigev_notify = SIGEV_SIGNAL;
	sevent.sigev_signo = SIGRTMAX;
	sevent.sigev_value.sival_int = 1;

	/* 
		Start the sensor simulator. StartSimulator return 
		the number of opened sensors, it's always 50
	*/
    noOfSensors = StartSimulator(sensorDescriptors, VALUES_PER_DESC);
	
    for(i; i < noOfSensors; i++)													/* Forking 50 child process one per sensor */
	{		
		/* 
			Fake child2's parent process it's destroyed immediatly 
			when child2 is created 
		*/
		child1 = fork();															
		
		if (child1 < 0) 
		{
			perror("Child1 creation failed");
			exit(1);
		}

		if(child1 == 0)
		{   
			/*
				We are in the "temporary" parent of the child2, now we need 
				to kill child1 to avoid the main parent process don't block 
				to create other process 
			*/
			child2 = fork();
			
			if (child2 < 0) 
			{
				perror("Child2 creation failed");
				exit(1);
			}			
			/* 
				We need double forking to avoid blocking wait in parent. When Child1
				terminates Child2 get startup process as parent 
			*/
			if(child2 > 0)																
				exit(0);  																		

			int result, ret;			
			struct timespec now, interval;   										/* structure needed to calculate and store the elapsed time */
			double zt = 0;
			
			while(1)																/* Reading until EOF (when result == 0) */
			{
				/* 
					Read descriptor[i] and get its information in dedicated 
					measurement structure 
				*/
				result = read(sensorDescriptors[i], &measurement, sizeof(Tmeas));	
				
				/* 
					Read the actual time after send for further processing using 
					the CLOCK_REALTIME (because it's cross-process each can read same time
				*/
				if (clock_gettime(CLOCK_REALTIME, &now) != 0)    					
					fprintf(stderr, "error: clock_gettime now\n");

				if(result > 0)
				{
					printf("The sensor NO. %d, Measurement value was %d\n", i, measurement.value);
					/* 
						Calculate elapsed measurement time to know if we 
						are in Real time or not
					*/	
					ret = delta_t(&interval, &measurement.moment, &now); 			
					zt = (interval.tv_sec + interval.tv_nsec) / 1000000000.0;
					printf("Elapsed time(%d) = %10.6f\n", ret, zt);					/* Print the elapsed time */
					
					/*
						We need to store the elapsed time in a dedicated file for 
						further processing (maximum, minimum and average elapsed time)
					*/
					if((fd = open("result.txt", O_CREAT|O_RDWR|O_APPEND, 0777)) < 0)
						perror("result.txt file opening error");
					else
					{
						sprintf(bufferRead, "%f", zt);
						/*
							We don't need to prevent conccurent writing here because 
							we've used the O_APPEND flag to ensure that we always 
							write at the end of the file
						*/
						write(fd, bufferRead, sizeof(bufferRead));			
					}

					if(measurement.value > MAX_TEMPERATURE) 						/* The temperature is over the maximum */
					{
						/* 
							Notify our process to add an signal event (SIGRTMAX) 
							to the signal queue to be processed by our rt_handler
						*/
						if(sigqueue(getpid(), SIGRTMAX, value) < 0)
							perror("sigqueue failed");
					}
				}					
				else if(result == 0)
					exit(0);     													/* End of File (EOF) received we can close the child */
				else if(result == -1 && errno != EAGAIN)
					perror("reading descriptor failed");
			}			
        }
																					/* We are in parent execution here */
	}	
	/* 
		Parent wait all process without blocking because 
		of double forking implemented in child 
	*/
	while((pid = waitpid(-1, NULL, 0)) > 0); 										
	exit(0);	
}

int delta_t(struct timespec *interval, struct timespec *begin, struct timespec *now)
{
	interval->tv_nsec = now->tv_nsec - begin->tv_nsec; 								/* Subtract 'decimal fraction' first */
	
	if(interval->tv_nsec < 0 )
	{
		interval->tv_nsec += 1000000000; 											/* Borrow 1sec from 'tv_sec' if subtraction -ve */
		interval->tv_sec = now->tv_sec - begin->tv_sec - 1; 						/* Subtract whole number of seconds and return 1 */
		return (1);
	}
	else
	{
		interval->tv_sec = now->tv_sec - begin->tv_sec; 							/* Subtract whole number of seconds and return 0 */
		return (0);
	}
} 

void rt_handler(int signo, siginfo_t *info, void* p) 
{
    printf("Caution! over the range!\n");
	return;
}
