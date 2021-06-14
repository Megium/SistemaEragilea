8extern volatile int tack;
extern int MAIZT;
extern int MAX;
extern int POSIZIO;
extern int CORE;
extern int HARI;
extern int QUAN;
extern pthread_mutex_t mutex;
extern pthread_mutex_t mutex2;
extern sem_t sche;
extern sem_t sinc;
extern sem_t sinc2;
extern struct queue ilara;
extern struct cpu prozesagailu;


//Prozesuaren informazioa gordetzeko
struct pcb
{
int pid;				//Prozesuaren identifikatzailea
int lehentasuna;		//Exekutatzerako garaian prozesuak izango duen lehentasuna
int egoera;				//1=zai, 2=exekuzioan, 3=Blokeatuta, 4=Exekutatua
int erabilera;			//Prozesua core-ren batean dagoen ala ez. 0 = erabili gabe; 1 = core baten barruan
memorimManagement mm ;  //Memoria kudeatzeko balioak
}
//Prozesuak sartzeko ilara, bertan buffer bat prozesuen informazioekin eta sorturiko prozesu kopuruarekin.
struct queue
{
	struct pcb *buff;
	int indizea;
};

struct priority
{
	//Lehentasun maila honetan zenbat prozesu dauden
	int zenbat;
	//Une honetan uneko lehentasunean zenbatgarren prozesuan doan
	int une;
	//Lehentasun bakoitzeko prozesu zerrenda, prozesuen id-ak gordeko ditu
	struct pcb zerrenda[20];
};


//Prozesagailearen egitura.
struct haria
{
	int hariID;
	int erabilgarri;
	struct pcb prozesua;
	//int quantum;	//3.zatian prozesu bakoitzaren luzera exekutatu beharreko programak adieraziko du.

	//program counter
	int pc;
	//instruction register
	int ir;
	//Page table base register
	char ptbr;	//memoria nagusian orri taula non jasoa dagoen esaten du.
	struct MMU;
};
struct core
{
	int coreID;
	struct haria *harikop;
	struct priority wait1[10];
	struct priority wait2[10];
	//zein azpi ilara erabiltzen ari den une honetan
	int zein;
	//azpi ilarako zenbatgarren "lehentasun" posizioan dagoen
	int nun;
};
struct cpu
{
	struct core *corekop;
};
//////////////////
//3.zatiko datuegiturak
//////////////////

//Memori management, programaren datuak memorian non dauden esango digun datu egitura.
struct memorimManagement
{
	int pgb;
	int text;
	int data;
};
struct MMU
{
	//TLB taula bat sartu hemen barnean.
};

struct Nagusia
{
	int hitza[2];				//4 byteko(32 bit) hitza.
								//Orri taularen kasuan lehen zatian, aginduan non hasten dire eta bigarrengoan non bukatzen diren.
	int libre;					//blokea libre dagoen ala ez jakiteko. 0 libre, 1 erabiltzen.
}

//Memoria nagusia, 24 biteko helbide busarekin.
Nagusia MemNag[16777216];		//0xFFFFFF-0x000000








