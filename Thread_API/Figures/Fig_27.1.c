#include <pthread.h>

/* Notice the arguments here:

   1. pthread_t thread is the thread to wait for until execution of current 
      thread is resumed.

   2. value_ptr represents a pointer to the value returned by the thread. 
      The value returned could be anything, and so void* is indicative 
      of this. 
*/

 
int pthread_join(pthread_t thread, void **value_ptr);

typedef struct __myarg_T
{
  int a;
  int b;
} myarg_t;


