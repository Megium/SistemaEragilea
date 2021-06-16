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

struct queue ilara;
void gorde(int core, struct pcb proz);

void *generateProcess_f(){
    //prozesuak sortzeko ausazko denboren hazia
	time_t t;
    srand((unsigned) time(&t));
    
    //Ilara objetua sortu eta hasieratu.
    
	ilara.indizea = 0;
    //Ilararen tamaina aldakorra izango denez, ilara dinamiko bat sortu behar da.
    ilara.buff = malloc(MAX*sizeof(struct pcb));
	

    int i = 1;
	int d, l, c, k, j, m, p;
	int kont=0;
	char fitxategia[64];
	k=0;
	j=0;

	for (p = 0; p < MAX; p++)
	{
		ilara.buff[p].erabilera = 1;
		ilara.buff[p].pid = 0;
	}

	while(1){
		d = rand();
		//d = rand() % (MAIZT%7);
		l = rand() % POSIZIO;
		c = rand() % 100000;
        //Sorturiko denbora 0 bada salto, erroreak ekiditeko

        
		if(d!=0){

			sleep(d%2);
            
			struct pcb prozesu;			//Prozesu berri bat sortu, pcb motakoa

			prozesu.pid = i;			//Prozesu berriari pid bat esleitu
			
			prozesu.lehentasuna = l;	//prozesuari lehentasun bat esleitu ausaz
			prozesu.egoera = 1;			//prozesua zai egoeran jarri
			prozesu.erabilera = 0;		//prozesua ez dago exekuzio ilara batean

			if (d%50 < 10){
				sprintf(fitxategia, "Programak/prog00%d.elf", d%50);
			}else{
				sprintf(fitxategia, "Programak/prog0%d.elf", d%50);
			}

			irakurriFitxategitik(prozesu, fitxategia);		//sortutako prozesuan programa bat kargatu eta dagozkio eremuak bete
															//memoriari dagozkion pgb, text eta data

            //bufferrean(ilara nagusian) sartu beharreko prozesua sortzeko deia egin
            while(k==0){

				pthread_mutex_lock(&mutex2);
            	if (ilara.buff[j%MAX].erabilera == 1){
					ilara.buff[j%MAX] = prozesu;
            		gorde(j%CORE, prozesu);
					ilara.indizea++;
            		k=1;
					//printf("Errore[1]\n");
				}else{
            		j++;
            	}if(ilara.indizea == MAX){
					ilara.indizea = 0;
					//printf("Errore[2]\n");
				}else{
					ilara.indizea++;
					//printf("Errore[3]\n");
				}
				pthread_mutex_unlock(&mutex2);
            }
			k=0;


			j++;
			i++;
		}	
	}
}

void gorde(int core, struct pcb proz){

	if(proz.pid != 0){
		if (prozesagailu.corekop[core].zein == 1){
			if (proz.lehentasuna > prozesagailu.corekop[core].nun){
				proz.erabilera = 1;
				
				prozesagailu.corekop[core].wait1[proz.lehentasuna].zerrenda[prozesagailu.corekop[core].wait1[proz.lehentasuna].zenbat] = proz;
				prozesagailu.corekop[core].wait1[proz.lehentasuna].zenbat++;
				printf("PID %d. prozesua %d. corean sartu da %d lehentasunarekin. \n", proz.pid, core, proz.lehentasuna);
			}else{
				proz.erabilera = 1;
				
				prozesagailu.corekop[core].wait2[proz.lehentasuna].zerrenda[prozesagailu.corekop[core].wait2[proz.lehentasuna].zenbat] = proz;
				prozesagailu.corekop[core].wait2[proz.lehentasuna].zenbat++;
				printf("PID %d. prozesua %d. corean sartu da %d lehentasunarekin. \n", proz.pid, core, proz.lehentasuna);
			}

		}else{
			if (proz.lehentasuna > prozesagailu.corekop[core].nun){
				proz.erabilera = 1;
				
				prozesagailu.corekop[core].wait2[proz.lehentasuna].zerrenda[prozesagailu.corekop[core].wait2[proz.lehentasuna].zenbat] = proz;
				prozesagailu.corekop[core].wait2[proz.lehentasuna].zenbat++;
				printf("PID %d. prozesua %d. corean sartu da %d lehentasunarekin. \n", proz.pid, core, proz.lehentasuna);
			}else{
				proz.erabilera = 1;
				
				prozesagailu.corekop[core].wait1[proz.lehentasuna].zerrenda[prozesagailu.corekop[core].wait1[proz.lehentasuna].zenbat] = proz;
				prozesagailu.corekop[core].wait1[proz.lehentasuna].zenbat++;
				printf("PID %d. prozesua %d. corean sartu da %d lehentasunarekin. \n", proz.pid, core, proz.lehentasuna);
			}
		}
	}
	
}



