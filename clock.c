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

volatile int tack;
void eguneratuD();
void prozAld();

void *clock_f(){
	
	while(1){
		//sem_post(&sinc);
		pthread_mutex_lock(&mutex);
		//printf("Tack %d\n", tack);
		tack++;
		prozAld();
		pthread_mutex_unlock(&mutex);

		//sem_wait(&sinc2);

		
	}
}


/*
Prozesuak iraungo duen denbora programak berak ezartzen du.
Hariak duen ziklo kontagailuarekin alderatuko da prozesuaren denbora.
Behin prozesua bere amaierara iristen denean prozesua haritik atera, 
haria erabilgarri jarri eta hariaren ziklo kopurua hasieratuko da.
*/

void prozAld(){
	int i, j;
	for (i = 0; i < CORE; i++)
	{
		for ( j = 0; j < HARI; j++){
			//Lehendabizi begiratu ea haria exekuzioan dagoen ala ez (0 libre, 1 exekuzioan)
			if (prozesagailu.corekop[i].harikop[j].erabilgarri == 1){
				//Begiratu ea prozesua bere ziklo kopurura iritsi den
				if(prozesagailu.corekop[i].harikop[j].exekDenb == prozesagailu.corekop[i].harikop[j].prozesua.iraupena){
					//Egoera exekutatura aldatu
					prozesagailu.corekop[i].harikop[j].prozesua.egoera = 4;
					//Haria erabilgarri jarri
					prozesagailu.corekop[i].harikop[j].erabilgarri = 0;
					//Hariaren zikloak hasieratu
					prozesagailu.corekop[i].harikop[j].exekDenb = 0;
					printf("%d hariko prozesuaren exekuzioa amaitu da\n", j);
				//Exekuzioak quantum-a pasaz gero
				}
			}			
		}
	}
	
}