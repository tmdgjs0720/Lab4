#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *cancel_thread(void *arg)
{
	int i, state;
	
	for(i=0; ; i++){
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &state);
		printf("Tread: cancel state disabled \n");
		sleep(1);
		
		pthread_setcancelstate(state, &state);
		printf("Tread: cancel state restored \n");
		
		if(i %4 ==0)
			pthread_testcancel();
		}
		return arg;
}

int main(int argc, char*argv[]){
	pthread_t tid;
	int arg, status;
	void *result;
	
	if(argc < 2){
		fprintf(stderr, "Usage: cancelthread time(sec) \n");
		exit(1);
	}
	
	status = pthread_create(&tid, NULL, cancel_thread, NULL);
	
	if(status != 0){
		fprintf(stderr, "Create thread: %d", status);
		exit(1);
	}
	
	arg = atoi(argv[1]);
	sleep(arg);
	
	status = pthread_cancel (tid);
	if(status !=0){
		fprintf(stderr, "Cancel thread: %d", status);
		exit(1);
	}
	status = pthread_join (tid, &result);
	if(status !=0){
		fprintf(stderr, "Join thread: %d", status);
		exit(1);
	}
	
	return (int) result;
}
