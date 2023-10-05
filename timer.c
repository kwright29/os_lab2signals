#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int x = 0;
int times_ran = 0;
int total_time = 0;
clock_t clock(void);
clock_t start_t, end_t;

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  x+=1;
}

void quit_handler(int signum) {
  //signal handler for when CTRL C is pressed 
	end_t = clock();
	total_time = (end_t - start_t)/1000000;
  printf("Alarms Occured: %d Seconds program was executed: %d seconds\n", times_ran
    , total_time);
  exit(1);
}

int main(int argc, char * argv[])
{
  while(1) {
		signal(SIGINT,quit_handler);
    signal(SIGALRM,handler); //register handler to handle SIGALRM
    alarm(1); //Schedule a SIGALRM for 1 second
    while(x==0);
    printf("Turing was right!\n");
    times_ran += 1;
		x = 0;
  } //busy wait for signal to be delivered 
  return 0; //never reached
}