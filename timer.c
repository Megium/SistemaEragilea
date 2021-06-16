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
			eguneratuD();
			pthread_mutex_unlock(&mutex);
			
			sem_post(&sche);

		}
		
		//sem_post(&sinc);
	}
}

void eguneratuD(){
	int i, j;
	for (i = 0; i < CORE; i++)
	{
		for ( j = 0; j < HARI; j++)
		{
			if(prozesagailu.corekop[i].harikop[j].erabilgarri == 1){
				prozesagailu.corekop[i].harikop[j].exekDenb++;			//harian dagoen denbora eguneratu.
			}			
		}
	}
	
}