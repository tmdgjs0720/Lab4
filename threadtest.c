#include <stdio.h>
#include <pthread.h>
#include <stddef.h>

void *test_thread(void *arg){
	printf("Thread: Hello, World Test\n");
	return arg;
}

void main(){
	pthread_t tid;
	int status;
	
	status = pthread_create(&tid, NULL, test_thread, NULL);
	if(status != 0)
		perror("Create thread");
	pthread_exit(NULL);
}


