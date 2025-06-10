#include <stdio.h>
#include <pthread.h>

void *th_run_process(void *args)
{
	printf("%lu thread_number", pthread_self());
}
int main(){
int i;
pthread_t pt1[5];

	for (i = 0; i < 5; i++) {
		pthread_create(&pt1[i], NULL, th_run_process, NULL);
	}

	for (i = 0; i < 5; i++) {
		pthread_join(pt1[i], NULL);
	}

	printf("threadz\n");
}
