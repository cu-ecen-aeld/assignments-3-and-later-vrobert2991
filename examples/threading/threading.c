#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
    struct thread_data * thread_func_args = (struct thread_data *) thread_param;
   
    usleep(thread_func_args->wait_to_obtain);
    pthread_mutex_lock(thread_func_args->mutex);
    usleep(thread_func_args->wait_to_release);
    pthread_mutex_unlock(thread_func_args->mutex);
    pthread_exit(thread_func_args);

}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{

    struct thread_data * thread_param = (struct thread_data *) malloc(sizeof(struct thread_data)); 

    thread_param->wait_to_obtain = wait_to_obtain_ms*1000;
    thread_param->wait_to_release = wait_to_release_ms*1000;
    thread_param->mutex = mutex; 
    thread_param->thread_complete_success = false;
    
    int rc = pthread_create(thread, NULL, threadfunc, thread_param);
    if (rc != 0)
    {
        thread_param->thread_complete_success = false;
    
    } else {
        
        thread_param->thread_complete_success = true;
    
    }
        
    return thread_param->thread_complete_success;
}

