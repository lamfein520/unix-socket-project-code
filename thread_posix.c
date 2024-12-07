#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <utils/Log.h>
 void *thread_posix_function(void *arg) {
  (void*)arg;
  int i;
  for ( i=0; i<30; i++) {
    printf("hello thread i = %d\n",i);
    ALOGD("hello thread i = %d\n",i);
    sleep(1);
  }
  return NULL;
}
int main(void) {
  pthread_t mythread;
  
  if ( pthread_create( &mythread, NULL, thread_posix_function, NULL) ) {
    ALOGD("error creating thread.");
    abort();
  }
  if ( pthread_join ( mythread, NULL ) ) {
    ALOGD("error joining thread.");
    abort();
  }
  ALOGD("hello thread has run end exit\n");
  exit(0);
}
