#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>

typedef struct node * Tpointer;
typedef float Titem;
typedef Tpointer Tlist;

typedef struct node
{
    Titem value;
    Tpointer next;
}Tnode;

void initializelist(Tlist*);
void insert_to_end(Tlist*, Titem);
void print_list(Tlist);
void find_max(Tlist);
void find_min(Tlist);
void find_average(Tlist);

int main(void)
{
    int fd;
    char bufferRead[8];
    float value;
    Tlist list;
	
    initializelist(&list);
	
	/*
		Opening the result.txt file that contains all elapsed 
		time for reading sensor value during processing 
	*/
	if((fd = open("result.txt", O_RDONLY)) < 0)
		perror("open file error");
		
	/*
		We read the file until the EOF is reach, we read 
		8 bytes each times because we don't have put separator, we've 
		just used fixed length for timing
	*/
	while(read(fd, bufferRead, sizeof(bufferRead)))
	{
		value = atof(bufferRead);											/* Converting the "string" to float */
		insert_to_end(&list, value);										/* Add the readed time to the list of timing for further processing */
	}	
	
	/*
		Here we are looking for maximum, minimum and average 
		elapsed time in the previous created & filled list 
	*/
	find_max(list);
	find_min(list);
	find_average(list);
	
	exit(0);
}

void initializelist(Tlist *list)
{
    *list = NULL;
}

/*
	Inserting to the end of the Tlist the specified Titem
*/
void insert_to_end(Tlist *list, Titem item)
{
    Tpointer newnode;
    newnode = (Tpointer)malloc(sizeof(Tnode));
    newnode->value = item;
    newnode->next = NULL;
	
    if(*list == NULL)
        *list = newnode;
    else    
	{
        Tpointer node = *list;
		
        while(node->next != NULL)
            node = node->next;
			
        node->next = newnode;
    }
}

/*
	Just parsing the Tlist element by element to 
	printf there value only to the screen
*/
void print_list(Tlist list)
{
    Tpointer node = list;
	
    while(node != NULL)
	{
        printf("%f", node->value);
        node = node->next;
    }
}

/*
	Retrieve the maximum elapsed time in list argument by 
	parsing it while we don't reach the final node. When 
	parsing is done we just printed to the screen the 
	maximum finded value
*/
void find_max(Tlist list)
{
    Tpointer node = list;
    float max = 0;
	
    while(node != NULL)
	{
		if(node->value > max)
			max = node->value;
			
        node = node->next;
    }
    printf("The maxmium time is %f\n", max);
}

/*
	Retrieve the minimum elapsed time in list argument by 
	parsing it while we don't reach the final node. When 
	parsing is done we just printed to the screen the 
	minimum finded value
*/
void find_min(Tlist list)
{
    Tpointer node = list;
    float min = 10;
	
    while(node != NULL)
	{
		if(node->value < min)
            min = node->value;
			
        node = node->next;
    }
    printf("The minmium time is %f\n", min);
}

/*
	Calculate the average elapsed time in list argument by 
	parsing it while we don't reach the final node. When 
	parsing is done we just printed to the screen the 
	calculate average elapsed time to interprate it
*/
void find_average(Tlist list)
{
	Tpointer node = list;
    float total = 0;
    int count = 0;
	
    while(node != NULL)
	{
        total = node->value + total;
        node = node->next;
        count++;
    }
    printf("The average time is %f\n", total / count);
}
