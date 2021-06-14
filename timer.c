#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include "clock.h"
#include "timer.h"
#include "global.h"
#include "loader.h"
#include "scheduler.h"

void *timer_f(){
	
	while(1){
		//sem_wait(&sinc2);
		if(tack >= MAIZT){
			pthread_mutex_lock(&mutex);
			printf("Ziklo bat pasa da\n");
			tack = 0;
			pthread_mutex_unlock(&mutex);
			
			sem_post(&sche);

		}
		
		//sem_post(&sinc);
	}
}