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
#include "memoria.h"

sem_t sinc;
sem_t sinc2;
sem_t sche;

pthread_mutex_t mutex;
pthread_mutex_t mutex2;
int MAIZT;
int MAX;			//kanpotik hasieratu behar da.
int POSIZIO;
int CORE;
int HARI;
int QUAN;

struct cpu prozesagailu;


int main(int argc, char const *argv[]){
	
	pthread_t clock_hari, timer_hari, process_hari, scheduler_hari;
	
	//kanpotik sartutako balioak
	MAIZT = atoi(argv[1]);
	MAX = atoi(argv[2]);
	CORE = atoi(argv[3]);
	HARI = atoi(argv[4]);
	POSIZIO = 10;

	pthread_mutex_init(&mutex, 0);
	pthread_mutex_init(&mutex2, 0);
	sem_init(&sche, 1, 1);
	sem_init(&sinc, 1, 1);
	sem_init(&sinc2, 1, 0);

	prozesagailu.corekop = malloc(CORE*sizeof(struct core));

	for (int i = 0; i < CORE; i++)
	{
		prozesagailu.corekop[i].coreID = i;
		prozesagailu.corekop[i].zein = 1;
		prozesagailu.corekop[i].nun = 0;
		prozesagailu.corekop[i].harikop = malloc(HARI*sizeof(struct haria));

		for (int j = 0; j < HARI; j++)
		{
			prozesagailu.corekop[i].harikop[j].hariID = j;
			prozesagailu.corekop[i].harikop[j].erabilgarri = 0;
			prozesagailu.corekop[i].harikop[j].exekDenb = 0;
		}
		for (int k = 0; k < 10; k++)
		{
			prozesagailu.corekop[i].wait1[k].zenbat = 0;
			prozesagailu.corekop[i].wait1[k].une = 0;
			prozesagailu.corekop[i].wait2[k].zenbat = 0;
			prozesagailu.corekop[i].wait2[k].une = 0;
			for (int m = 0; m < 20; m++)
			{
				prozesagailu.corekop[i].wait1[k].zerrenda[m].pid = 0;
				prozesagailu.corekop[i].wait1[k].zerrenda[m].egoera = 4;
			}
		}
	}


	pthread_create(&clock_hari, NULL, clock_f,NULL);
	pthread_create(&timer_hari, NULL, timer_f,NULL);
	pthread_create(&process_hari, NULL, generateProcess_f, NULL);
	pthread_create(&scheduler_hari, NULL, scheduler_f, NULL);

	
	
	pthread_join(clock_hari, NULL);
	pthread_join(timer_hari, NULL);
	pthread_join(process_hari, NULL);
	pthread_join(scheduler_hari, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&mutex2);
	sem_destroy(&sche);
	sem_destroy(&sinc);
	sem_destroy(&sinc2);
}
