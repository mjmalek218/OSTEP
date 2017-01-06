#include <stdio.h>


/* This function will simply pass a void* pointer because we want to be able to pass in 
   any arbitrary type. */

/* First recall how functions use pointers to get return values:

   Let's say we have a functions returning two values:

   1. int for error code
   2. int for its actual output (say the result of some computation)

   Then one way we could get both is to create a struct type and
   have it return that struct. 

   Another way is to exploit pointers, or virtual memory addresses. 
   We could have it return the error the normal way (int return type)
   and then pass in a pointer to an int, or a virtual memory address 
   of an int location in the calling functions stack (or memory heap tbh,
   just a memory location the original function had access to) 

*/

int two_output_example(int *garbage_example)
{
  

}


/* Next recall how void* pointers work. The idea is since all pointers are just 
   virtual memory addresses, they are all the same length on a given machine. 
   This means if we have a situation where we could have multiple data types pass
   in or out of a function, we could just use void* as the type and then cast it 
   later (note: void* prior to casting is very limited. can't dereference or 
   do pointer arithmetic with it. 

   So the way the pthread_join code is declared is the following:

   int pthread_join(pthread_t thread, void **value_ptr);

   Because the routine (the thread that was originally created, essentially)
   can return anything, since the function that was called isn't even 
   necessarily the function that ends the thread (need to confirm this in
   the example) it returns a pointer to a memory location 

   The way it therefore works currently is that a pointer *to* a void pointer
   is currently passed into pthread_join, which is ostensibly memory that the
   joining procedure has access to, and then pthread_join deliberately de-references
   the void double pointer (which, presumably, is valid since the compiler *knows*
   what a double pointer of *any* type points to: just another pointer) and then 
   sets the memory address void** points to equal to whatever void* the thread
   is supposed to return. 

   Now the question is: why have a double pointer? Why not just have a single 
   void pointer, pass this void* into pthread_join, and then have pthread_join 
   update the referenced variable??

   The answer is because pthread_join does not *know* what the value returned 
   will be, and therefore *cannot* dereference it correctly to change the memory
   location. If we pass in void* to pthread_join, what we are saying is: "this is 
   a pointer to a memory location we, the calling procedure, have access to, and we 
   want you to place the desired value at *this* memory location. The problem is,
   of course, is that in order to do so pthread_join would have to first dereference
   its void*, which it cannot do since the creators of that function natrually do 
   not have access to the desired data type by the posix user.

   So the calling thread dereferences a pointer to a pointer, because it *knows* the
   result of the dereference will simply be a word (4 bytes for 32 bit system, 8 bytes
   for 64 bit) 
   
*/
