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

void exek();
void exekuzioanJarri();
void programaExek(struct pcb proz, int pageT);
int helbideaLortu(char reg[8]);
void store(int zenb, int helb);


void *scheduler_f(){
	int desp;

	while(1){

		sem_wait(&sche);
		printf("-----------------\n-   Scheduler   -\n-----------------\n");
		//Ilarako prozesuak prozesadoreetan banatu
		pthread_mutex_lock(&mutex2);
			exekuzioanJarri();
		pthread_mutex_unlock(&mutex2);
	}


}



//prozesuak exekuzioan jarri.
void exekuzioanJarri(){
	int i, j, k, l;
	int buk = 0;

	for (i = 0; i < CORE; ++i)
	{
		//printf("Core: %d\n", i);
		buk = 0;
		for(j = 0; j < HARI; j++){
			buk = 0;
			//printf("Haria: %d\n", j);
			if(prozesagailu.corekop[i].harikop[j].erabilgarri == 1){
				//haria ez badago erabilgarri hurrengo harira pasa.
				//printf("Haria ez dago erabilgarri\n");
				break;
			}else{
				if(prozesagailu.corekop[i].zein == 1){
					//lana errazteko aldagaiak eskuratu.
					int uneko = prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une; //lehentasun barruan zenbatgarren prozesuan doan.
					int nunD = prozesagailu.corekop[i].nun;  //wait ilarako zein lehentasunean doan.
					
					//Lehentasun ilara korritu prozesu erabigarri bat bilatu arte.
					for(k = 0; k < 10; k++){
						//lehentasun honen barruan ez badago prozesurik salto.
						if(prozesagailu.corekop[i].wait1[k].zenbat == 0){
							//printf("Lehentasun %d hutsa dago\n", k);
							//break;
						}else{
							//Lehentasuneko prozesuak korritu erabilgarri bat bilatu arte.
							for(l = 0; l < prozesagailu.corekop[i].wait1[k].zenbat; l++){
								//printf("Prozesuen bila 1\n");
								//begiratu ea prozesua erabilgarri ala exekutatzen dagoen
								if(prozesagailu.corekop[i].wait1[k].zerrenda[l].egoera == 1 ){
									prozesagailu.corekop[i].wait1[k].zerrenda[l].egoera = 2;
									prozesagailu.corekop[i].wait1[prozesagailu.corekop[i].nun].une = l;
									prozesagailu.corekop[i].nun = k;
									prozesagailu.corekop[i].harikop[j].erabilgarri = 1;
									prozesagailu.corekop[i].harikop[j].prozesua = prozesagailu.corekop[i].wait1[k].zerrenda[l];
									prozesagailu.corekop[i].harikop[j].ptbr = prozesagailu.corekop[i].wait1[k].zerrenda[l].mm.pgb;
									programaExek(prozesagailu.corekop[i].harikop[j].prozesua, prozesagailu.corekop[i].harikop[j].ptbr);
									buk = 1;
									printf("%d prozesua exekuziora, %d coreko %d harian\n", prozesagailu.corekop[i].wait1[k].zerrenda[l].pid, i, j);
									break;
								}
							}
							if(buk == 1){
								break;
							}
						}	
					}
					if(k == 10){
						prozesagailu.corekop[i].zein = 2;
						prozesagailu.corekop[i].nun = 0;
					}
					if(buk == 1){
						break;
					}
////////////////////////////////////////////////////////////////////////////////////////////////////////////					
				}else{
					int uneko = prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].une; //lehentasun barruan zenbatgarren prozesuan doan.
					int nunD = prozesagailu.corekop[i].nun;  //wait ilarako zein lehentasunean doan.
					
					//Lehentasun ilara korritu prozesu erabigarri bat bilatu arte.
					for(k = 0; k < 10; k++){
						//lehentasun honen barruan ez badago prozesurik salto.
						if(prozesagailu.corekop[i].wait2[k].zenbat == 0){
							//printf("Lehentasun %d hutsa dago\n", k);
							//break;
						}else{
							for(l = 0; l < prozesagailu.corekop[i].wait2[k].zenbat; l++){
								//printf("Prozesuen bila 2\n");
								//begiratu ea prozesua erabilgarri ala exekutatzen dagoen
								if(prozesagailu.corekop[i].wait2[k].zerrenda[l].egoera == 1 ){
									prozesagailu.corekop[i].wait2[k].zerrenda[l].egoera = 2;
									prozesagailu.corekop[i].wait2[prozesagailu.corekop[i].nun].une = l;
									prozesagailu.corekop[i].nun = k;
									prozesagailu.corekop[i].harikop[j].erabilgarri = 1;
									prozesagailu.corekop[i].harikop[j].prozesua = prozesagailu.corekop[i].wait2[k].zerrenda[l];
									prozesagailu.corekop[i].harikop[j].ptbr = prozesagailu.corekop[i].wait2[k].zerrenda[l].mm.pgb;
									programaExek(prozesagailu.corekop[i].harikop[j].prozesua, prozesagailu.corekop[i].harikop[j].ptbr);
									buk = 1;
									printf("%d prozesua exekuziora, %d coreko %d harian\n", prozesagailu.corekop[i].wait2[k].zerrenda[l].pid, i, j);
									break;
								}
							}
							if(buk == 1){
								break;
							}
						}
						//Lehentasuneko prozesuak korritu erabilgarri bat bilatu arte.
					}
					if(k == 10){
						prozesagailu.corekop[i].zein = 1;
						prozesagailu.corekop[i].nun = 0;
					}
					if(buk == 1){
						break;
					}
				}
			}
		}
	}
}

/*
	Aginduak:
	- 0 hasten bada ld
	- 1 hasten bada st
	- 2 hasten bada add
	- F hasten bada exit
	--------------------
	ld edo st:
	1. bita zein erregistrotan gorde edo kargatu
	Gainontzeko bitak zenbatgarren datua
	--------------------
	add:
	1.bita eragiketa
	2.bitak zein erregistrotan gordeko den emaitza(0 tik F arte)
	3 eta 4.bitak zein erregistrotako datuak batu behar diren(0 tik F arte)

	Exekuzio denborak:
	- ld: ziklo 1
	- st: 2 ziklo
	- add: 4ziklo

	Exekuzioa simulatzeko ziklo bakoitzak denbora bat izango du 
	non denbora hori clock-ak kontrolatu
*/

void programaExek(struct pcb proz, int pageT){

	int Erreg[16];
	int jauzi = 2;
	int lag = proz.mm.data / 10;
	jauzi = jauzi + 4*lag;
	int helb = MemNag[pageT].orriT[0];
	char agindu[64];
	int i;
	int buk = 0;
	int reg1, reg2, reg3;
	int desplaz;
	int denbora = 0;


	for(i = 0; i < jauzi; i++){
		agindu = MemNag[helb+i].hitza;

		switch(agindu[0]){
			case '0':		//load
				reg1 = strtol(&agindu[1], NULL, 16);			//zein erregistro erabili behar den lortu
				desplaz = helbideaLortu(agindu);			//datuaren helbidea lortu
				Erreg[reg1] = strtol(&MemNag[helb + desplaz], NULL, 16);			//datua erregistroan gorde
				denbora = denbora + 1;
				break;
			case '1':		//store
				reg1 = strtol(&agindu[1], NULL, 16);			//zein erregistro erabili behar den lortu
				desplaz = helbideaLortu(agindu);			//zein helbidatan gorde behar den lortu
				store(Erreg[reg1], helb + desplaz);			//store funtzioaren laguntzaz datu hamartarra 
															//hamaseitar karaktere kate bat bilakatu eta dagokion helbidean gorde
				denbora = denbora + 2; 
				break;
			case '2':		//add
				reg1 = strtol(&agindu[1], NULL, 16);			//zein erregistron gorde behar den lortu
				reg2 = strtol(&agindu[2], NULL, 16);			//lehen datua lortu
				reg3 = strtol(&agindu[3], NULL, 16);			//bigarren datua lortu
				Erreg[reg1] = Erreg[reg2] + Erreg[reg3];	//batuketa egin eta erregistroan gorde
				denbora = denbora + 4;
				break;
			case 'F':		//bukatu
				buk = 1;
				break;
		}
		if(buk == 1){
			proz.iraupena = denbora;
			break;
		}


	}

}

int helbideaLortu(char reg[8]){
	int i;
	int desplaz;
	char erreg[100];
	for(i = 2; i < 8; i++){						//agindu erregistrotik eragiketa eta erregistroaren datuak kendu
		erreg[i-2] = reg[i];
	}
	desplaz = strtol(&erreg, NULL, 16);			//zenbat desplazatu behar den atera
	return desplaz / 4;							
}

void store(int zenb, int helb){					//jasotako datu hamartarra hamaseitarrean bilakatu
	long remainder;
    int i, j = 0;
    char hexadecimalnum[8];
 
    while (zenb != 0)
    {
        remainder = zenb % 16;
        if (remainder < 10)
            hexadecimalnum[j++] = 48 + remainder;
        else
            hexadecimalnum[j++] = 55 + remainder;
        zenb = zenb / 16;
    }
    MemNag[helb].hitza = hexadecimalnum;				//karaktere katea datu hamaseitarrarekin memoriako helbide egokian gorde
}