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

void Memoria(){

}


/*
	- Memoria fisikoko hasiera helbidea gorde
	- Datuak segidan sartu memorian, memoriako blokeak ez daudela libre adierazi
	- Orri taulan gorde helbidea
	- PCB ko pgb aldagaian orri taulako helbidea gorde.
*/
void irakurriFitxategitik(pcb proz, unsigned char fitx[64]){

int buff_luz = 255;
char buffer[buff_luz];			// datuak fitxategitik ateratzean gordetzeko
int libre;						// memorian libre dagoen blokea gordetzeko
int kont;						// datu blokeak kontatzeko

for(i = KERNEL_BUK + 1; i < MEM_BUK; i++){

	if(MemNag[i].libre == 0){			//memoriako blokea libre dago
		MemNag[i].libre = 1;
		kont = i - 1;
		break;
	}
}

//fitxategia zabaldu eta irakurtzeko moduan jarri
FILE* FP;
FP = fopen(fitx, "r");

//lehen bi lerroetatik text eta data balioak atera eta int balio bezala jarri
if (fgets(buffer, buff_luz, FP))
		proz.mm.text = atoi(buffer);
if (fgets(buffer, buff_luz, FP))
		proz.mm.data = atoi(buffer);


while (fgets(buffer, buff_luz, FP)) {
	kont++;
	MemNag[kont].hitza = buffer;
	MemNag[kont].libre = 1;
}

fclose(FP);


/* 
Behin fitxategitik programa irakurri eta gorde dela datuen erreferentzia orri taulan
gordeko da eta erreferentzia prozesuaren pgb an ere bai.
*/
int j;
for(j = ORRI_TAULA; j < KERNEL_BUK; j++){
	if(MemNag[j].libre == 0){
		MemNag[j].orriT[0] = i;
		MemNag[j].orriT[0] = kont;
		MemNag[j].libre = 1;

		proz.mm.pgb = j;
	}
}

}