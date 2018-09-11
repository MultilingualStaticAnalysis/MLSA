#include "CalculoTempo_maincalculo.h"



using namespace std;
int 
main(int argc, char**argv)
{
	//Estruturas para calculo do tempo	
	double global_time = 0.0;
	double global_time2 = 0.0;
	double global_time3 = 0.0;
	double global_timeaux = 0.0;
	Tile **mapa_dungeon1; //Matriz tile para desenhar Dungeon1
	Tile **mapa_dungeon2; //Matriz tile para desenhar Dungeon2
	Tile **mapa_dungeon3; //Matriz tile para desenhar Dungeon3
	Tile **mapa_fora; //Matriz tile para desenhar mapa de fora

	int controleFora = 0;
	int dun[3];

	//Gerar as matrizes de tiles para os mapas
	//Dungeon1
	char file[100] = "dungeon1.txt";
	mapa_dungeon1 = gera_mapa(file,1);
	//desenha_mapa(mapa_dungeon1,1);
	//Dungeon2
	char file2[100] = "dungeon2.txt";
	mapa_dungeon2 = gera_mapa(file2,1);
	//desenha_mapa(mapa_dungeon2,1);
	//Dungeon3
	char file3[100] = "dungeon3.txt";
	mapa_dungeon3 = gera_mapa(file3,1);
	//desenha_mapa(mapa_dungeon2,1);
	//Mapafora
	char file4[100] = "mapa_fora.txt";
	mapa_fora = gera_mapa(file4,0);
	//Buscando no mapa de fora qual a primeira porta que vai ser entrada
	Busca_a* fora_1a = new Busca_a(); 
	Busca_a* fora_1b = new Busca_a();
	Busca_a* fora_1c = new Busca_a();
	Vector2 posInicial(24,27);
	Vector2 porta1(5,32);
	Vector2 porta2(39,17);
	Vector2 porta3(24,1);
	//Buscando dentro das dungeons
	Busca_a* busca_d1 = new Busca_a();
	Vector2 iniciod1(14,26);
	Vector2 fimd1(13,3);
	Busca_a* busca_d2 = new Busca_a();
	Vector2 iniciod2(13,25);
	Vector2 fimd2(13,2);
	Busca_a* busca_d3 = new Busca_a();
	Vector2 iniciod3(14,25);
	Vector2 fimd3(15,19);
	#pragma omp parallel num_threads(6)
	{
		if(omp_get_thread_num() == 0){
			encontra_caminhodungeon(fora_1a,posInicial,porta1,getPesoTile(mapa_fora,0),42,&global_time);
		}
		if(omp_get_thread_num() == 1){
			encontra_caminhodungeon(fora_1b,posInicial,porta2,getPesoTile(mapa_fora,0),42,&global_time);			
		}
		if(omp_get_thread_num() == 2){
			encontra_caminhodungeon(fora_1c,posInicial,porta3,getPesoTile(mapa_fora,0),42,&global_time);			
		}
		if(omp_get_thread_num() == 3){
			encontra_caminhodungeon(busca_d1,iniciod1,fimd1,getPesoTile(mapa_dungeon1,1),28,&global_time);
		}
		if(omp_get_thread_num() == 4){
			encontra_caminhodungeon(busca_d2,iniciod2,fimd2,getPesoTile(mapa_dungeon2,1),28,&global_time);
		}
		if(omp_get_thread_num() == 5){
			encontra_caminhodungeon(busca_d3,iniciod3,fimd3,getPesoTile(mapa_dungeon3,1),28,&global_time);
		}
	}
	Busca_a* fora_1real;
	if(fora_1a->peso < fora_1b->peso && fora_1a->peso < fora_1c->peso){
		fora_1real = fora_1a;
		dun[0] = 1;
		controleFora = 1; //se Inicial = porta1
	}
	else if(fora_1b->peso < fora_1c->peso){
		fora_1real = fora_1b;
		controleFora = 2; // se Inicial = porta2
		dun[0] = 2;
	}
	else{
		fora_1real = fora_1c; 
		controleFora = 3; //se Inicial = porta3
		dun[0] = 3;
	}
	
	Busca_a* fora_2a = new Busca_a();
	Busca_a* fora_2b = new Busca_a();
	Vector2 posInicio2(0,0);
	Vector2 portaA(0,0);
	Vector2 portaB(0,0);

	if(controleFora ==1){//Dungeon 1
		posInicio2.setX(5);
		posInicio2.setY(32);
		portaA.setX(39);
		portaA.setY(17);
		portaB.setX(24);
		portaB.setY(1);
	}
	else if(controleFora == 2){//Dungeon 2
		posInicio2.setX(39);
		posInicio2.setY(17);
		portaA.setX(5);
		portaA.setY(32);
		portaB.setX(24);
		portaB.setY(1);
	}
	else if(controleFora == 3){ //Dungeon 3
		posInicio2.setX(24);
		posInicio2.setY(1);
		portaA.setX(5);
		portaA.setY(32);
		portaB.setX(39);
		portaB.setY(17);
	}

	#pragma omp parallel num_threads(2)
	{
		if(omp_get_thread_num() == 0){
			encontra_caminhodungeon(fora_2a,posInicio2,portaA,getPesoTile(mapa_fora,0),42,&global_time2);
		}
		if(omp_get_thread_num() == 1){
			encontra_caminhodungeon(fora_2b,posInicio2,portaB,getPesoTile(mapa_fora,0),42,&global_time2);			
		}
	
	}
	Busca_a* fora_2real;
	if(fora_2a->peso < fora_2b->peso){
		fora_2real = fora_2a;
		controleFora = 4;
		if(dun[0] == 1){
			dun[1] = 2;
			dun[2] = 3;
		}
		if(dun[0] == 2){
			dun[1] = 1;
			dun[2] = 3;
		}
		if(dun[0] == 3){
			dun[1] = 1;
			dun[2] = 2;
		}
	}
	else{
		fora_2real = fora_2b;
		controleFora = 5;
		if(dun[0] == 1){
			dun[1] = 3;
			dun[2] = 2;
		}
		if(dun[0] == 2){
			dun[1] = 3;
			dun[2] = 1;
		}
		if(dun[0] == 3){
			dun[1] = 2;
			dun[2] = 1;
		}
	}
	Busca_a* fora_3real = new Busca_a();
	Busca_a* lost_wood = new Busca_a();
	Busca_a* espada = new Busca_a();
	Vector2  posLostWood(6,5);
	Vector2 posEspada(2,1);
	double tempoSerial1 = omp_get_wtime();
	if(controleFora == 4){
		encontra_caminhodungeon(fora_3real,portaA,portaB,getPesoTile(mapa_fora,0),42,&global_timeaux);
	}
	else if(controleFora == 5){
		encontra_caminhodungeon(fora_3real,portaB,portaA,getPesoTile(mapa_fora,0),42,&global_timeaux);
	}
	double tempoSerial2 = omp_get_wtime();
	double tempoSerial = tempoSerial2-tempoSerial1;
	#pragma omp parallel num_threads(2)
	{	
		if(omp_get_thread_num() == 0){			
			encontra_caminhodungeon(lost_wood,fora_3real->getVnoMeta(),posLostWood,getPesoTile(mapa_fora,0),42,&global_time3);
		}
		if(omp_get_thread_num() == 1){	
			encontra_caminhodungeon(espada,posLostWood,posEspada,getPesoTile(mapa_fora,0),42,&global_time3);
		}
	}	
	printf("Tempo gasto: %lf/s\n", global_time+global_time2+global_time3+tempoSerial); //Soma de todas as buscas feitas em todas as threads
   	exit(0);
}

void
encontra_caminhodungeon(Busca_a * busca, Vector2 ini, Vector2 fim,int**tile,int tam,double *global_time)
{
	double time_init = omp_get_wtime();
	while(!busca->foundMeta){
		busca->findCaminho(ini,fim,tile,tam);
	}
	double time_final = omp_get_wtime();
	double time_exec = time_final - time_init;
#	pragma omp critical
		*global_time = time_exec > *global_time ? time_exec : *global_time;
}
