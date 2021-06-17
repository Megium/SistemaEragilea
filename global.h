extern volatile int tack;
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


//Memori management, programaren datuak memorian non dauden esango digun datu egitura.
struct memoriManagement
{
	int pgb;
	int text;
	int data;
};

//Prozesuaren informazioa gordetzeko
struct pcb
{
int pid;				//Prozesuaren identifikatzailea
int lehentasuna;		//Exekutatzerako garaian prozesuak izango duen lehentasuna
int egoera;				//1=zai, 2=exekuzioan, 3=Blokeatuta, 4=Exekutatua
int erabilera;			//Prozesua core-ren batean dagoen ala ez. 0 = erabili gabe; 1 = core baten barruan
int iraupena;			//Programaren iraupena, aldkorra programaren arabera.
struct memoriManagement mm ;  //Memoria kudeatzeko balioak
};
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

struct mmuStruct
{
	int TLB;//TLB taula bat sartu hemen barnean.
};

//Prozesagailearen egitura.
struct haria
{
	int hariID;
	int erabilgarri;
	struct pcb prozesua;
	int exekDenb;			//Harian dagoen programaren exekuzio denbora kontrolatzeko.
	int pc;					//program counter
	int ir;					//instruction register
	int ptbr;				//memoria nagusian orri taula non jasoa dagoen esaten du.
	struct mmuStruct mmu;
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

struct Nagusia
{
	char hitza[8];				//informazio hitzak.
	int orriT[2];				//Orri taularen kasuan lehen zatian, aginduan non hasten dire eta bigarrengoan non bukatzen diren.
	int libre;					//blokea libre dagoen ala ez jakiteko. 0 libre, 1 erabiltzen.
};
//Memoria nagusia, 24 biteko helbide busarekin.
extern struct Nagusia MemNag[16777216];		//0xFFFFFF-0x000000







