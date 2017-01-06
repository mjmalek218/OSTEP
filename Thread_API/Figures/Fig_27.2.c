/* RECALL WHAT I WANTED TO CONFIRM IN THIS EXAMPLE: HOW EXACLTY
   IS A THREAD, CREATED WITH PTHREAD_CREATE, ENDED??? */



#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>


/* Note what this is: just two integers. They have to be packaged
   into one struct, however, due to the nature of C (can't overload
   on arguments). */
typedef struct __myarg_t
{
  int a;
  int b;
} myarg_t;


/* Again just two integers, but this is supposed to be the return type. */
typedef struct __myret_t
{
  int x;
  int y;
} myret_t;

void *mythread(void *arg)
{
 
  myarg_t *m = (myarg_t *) arg;               // casting
  printf("%d %d\n", m->a, m->b);    
  myret_t *r = Malloc(sizeof(myret_t));       // allocates memory for r in mutually accessible
                                              // heap. If it were allocated on the call stack
                                              // it would no longer be accessible once the 
                                              // thread returns

  r->x = 1;                                   // then just sets it to...1 and 2? pretty boring
  r->y = 2;
  return (void *) r;
}

int
main(int argc, char *argv[])
{

  /* Code starts by defining these values*/
  int rc;
  pthread_t p; // the thread
  myret_t *m;  // presumably the return value for the thread

  myarg_t args;  //arguments to the child thread's starting function
  args.a = 10;   
  args.b = 20;
  Pthread_create(&p, NULL, mythread, &args);
  Pthread_join(p, (void **) &m);             
  printf("returned %d %d\n", m->x, m->y);
  return 0;
} 



/* So it seems as though looking at the question, that the way a child thread returns
   is by the original function called returning.

   Another side note: *never* return a pointer which refers to something allocated
   on the child thread's call stack. Once the thread returns the memory from the 
   call stack is collected and the value will be wiped out. 

   The nice thing is though if your code exhibits the above error, gcc is likely to 
   throw a warning/error. 
 */

