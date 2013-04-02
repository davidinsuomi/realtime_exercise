#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>

// Prototype of the signal handler
void rt_handler(int signo, siginfo_t *info, void* p ) {
	  printf(" Timer %d  seconds expired \n",info->si_value.sival_int);
}
int main(void) {
	timer_t timerid,timerid3;
	struct sigevent sevent,sevent3;
	struct sigaction sa;
	struct itimerspec timerstruct,timerstruct3;
	int i;


        	// Install real time signal handler
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = rt_handler;
	sigaction(SIGRTMAX, &sa, NULL);
	// Construct a structure that specifies what signal is generated
	// and how signal handler is called



	sevent.sigev_notify = SIGEV_SIGNAL;
	sevent.sigev_signo = SIGRTMAX;
	sevent.sigev_value.sival_int = 1; // integer parameter
         // Create a timer instance
 	timer_create(CLOCK_REALTIME, &sevent,  &timerid);
  	// Set the times for a timer
	timerstruct.it_value.tv_sec = 1;       // First time after 1 secs
	timerstruct.it_value.tv_nsec = 0;
	timerstruct.it_interval.tv_sec = 1;   // Do not repeat
	timerstruct.it_interval.tv_nsec = 0;  // Do not repeat
	timer_settime(timerid, 0, &timerstruct, NULL);
    	// Do what ever






	// Construct a structure that specifies what signal is generated
	// and how signal handler is called
	sevent3.sigev_notify = SIGEV_SIGNAL;
	sevent3.sigev_signo = SIGRTMAX;
	sevent3.sigev_value.sival_int = 3; // integer parameter
         // Create a timer instance
 	timer_create(CLOCK_REALTIME, &sevent3,  &timerid3);
  	// Set the times for a timer
	timerstruct3.it_value.tv_sec = 3;       // First time after 3 secs
	timerstruct3.it_value.tv_nsec = 0;
	timerstruct3.it_interval.tv_sec = 3;   // Do not repeat
	timerstruct3.it_interval.tv_nsec = 0;  // Do not repeat
	timer_settime(timerid3, 0, &timerstruct3, NULL);
    	// Do what ever





    	while(1) {
		sleep(1);
	}

}


