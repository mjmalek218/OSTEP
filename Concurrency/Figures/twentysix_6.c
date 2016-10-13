#include <stdio.h>
#include <pthread.h>
#include "mythreads.h"


// WHAT THE HELL DOES VOLATILE MEAN???? KEEP MEANING TO LOOK THIS UP.
// NEED TO LOOK IT UP 
static volatile int counter = 0;


/* 

mythread()

Simply adds 1 to counter repeatedly, in a loop.
No, this is not how you would add 10,000,000 to
a counter, but it shows the problem nicely.

*/

/* On this first iteration I can tell this is quite poorly conjoined. 
   The amount the threads will increment counter is completely unpredictable. 
 */

void *
mythread(void *arg)
{
  /* First prints the argument, whatever the hell that is */
  printf("%s: begin\n", (char *) arg);

  int i;

  /* INTERESTING...didn't know you could use scientific notation 
     like this in C. */
  for (i = 0; i < 1e7; i++)
    {
      counter = counter + 1;
    }

  printf("%s: done\n", (char *) arg);
  return NULL;
}

/* main()

   Just launches two threads (pthread_create)
   and then waits for them (pthread_join)

*/

int main(int argc, char *argv[])
{
  pthread_t p1, p2;
  printf("main: begin counter = %d)\n", counter);

  /* A and B are the arguments here. Note they are both strings. */
  Pthread_create(&p1, NULL, mythread, "A"); // note the capital indicates an error wrapper 
  Pthread_create(&p2, NULL, mythread, "B");

  // join waits for the threads to finish 
  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);
  printf("main: done with both (counter = %d)\n", counter); // prints out counter at the end
  return 0; //recall 0 represents proper termination
  
}
