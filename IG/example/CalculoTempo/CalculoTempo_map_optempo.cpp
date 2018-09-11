#include "CalculoTempo_map_optempo.h"
/*
	gera_mapa
	-------------
	Esta função gera a matriz que representa o mapa ou a dungeon onde o personagem pode realizar ações.
	Essa matriz é gerada a partir de um arquivo que deve ter as seguintes propriedades:
	Controle de linhas/colunas:
		depende de qual tipo foi escolhido, mas esse controle será feito no código(não precisa ser no arquivo).
	MAPAS -> Flag = 0:
		Casos de leitura:
			G -> Grama -> + 10;
			A -> Areia -> + 20;
			F -> floresta -> +100;
			M -> montanha -> +150;
			W -> Agua -> +180;
	Dungeons -> flag = 1:
		Casos de leitura:
		B -> Bloqueio;
		C -> Caminháel -> +10;

	Recebe o nome do arquivo que será lido e a flag que dirá se é dungeon ou mapa;
	*Caso file_name == null gera aleatóriamente? ---- Em teste... depois...;

	Retorna uma matriz de TILES contendo os pesos de cada área como descrito acima.
	também contém posição x e y da tile e sua imagem.
*/
Tile **
gera_mapa(char *file_name, int flag)
{


	int i, j;
	float x=0.0,y=0.0;
	char tipo;
	FILE *map;
	Tile **mat_mapa;
	if(flag == 1) //Cria Dungeon -> começa matriz com 0 em tudo;
	{
		//Inicializa Tiles para Dungeon.

		//Inicialização da matriz de tiles
		mat_mapa =(Tile**) calloc(28,sizeof(Tile*));
		for(i = 0;i<28;i++)
   		{	
			mat_mapa[i] =(Tile*) calloc(28,sizeof(Tile));
   		}

	}

	else//Cria mapa -> começa matriz com 0 em tudo;
	{
		//Inicializa tiles para mapa.

		//Inicialização da matriz de Tiles
		mat_mapa =(Tile**) calloc(42,sizeof(Tile*));
		for(i = 0;i<42;i++)
   		{	
			mat_mapa[i] =(Tile*) calloc(42,sizeof(Tile));
   		}
	}

	if(file_name != NULL)//verifica se é para gerar randomicamente ou em cima de arquivo.
	{
	map = fopen (file_name , "r"); //abertura arquivo de leitura
		//Operações no caso de sucesso de abertura do arquivo
		if(map != NULL)
		{
			if(flag == 1) //Gera Dungeon por arquivo
			{
				for(i = 0; i < 28; i++)
				{
					
					if(i > 0)
						tipo = fgetc(map);
					for(j = 0; j < 28; j++)
					{
						tipo = fgetc(map);
						if(x >= 1008) //Controla o X e Y para dungeon
						{
							x = 0;
							y += 27;
						}
						switch(tipo)
						{
							case 'B':
								mat_mapa[i][j].peso = 1000;
								mat_mapa[i][j].x = x;
								mat_mapa[i][j].y = y;
								x += 36;
								break;
							case 'C':			
								mat_mapa[i][j].peso = 10;
								mat_mapa[i][j].x = x;
								mat_mapa[i][j].y = y;
								x += 36;
								break;
							default:
								break;
						}
					}

				}

			}
			else // Gera mapa por arquivo
			{
				for(i = 0; i < 42; i++)
				{

					if(i > 0)
						tipo = fgetc(map);
					for(j = 0; j < 42; j++)
					{
						tipo = fgetc(map);
						if(x >= 1008) //Controla o X e Y para mapa
						{
							x = 0;
							y += 18;
						}
						//Controle do tipo no arquivo
						switch(tipo)
						{
							case 'A':
								mat_mapa[i][j].peso = 20;
								mat_mapa[i][j].x = x;
								mat_mapa[i][j].y = y;
								x += 24;
								break;
							case 'G':
								mat_mapa[i][j].peso = 10;
								mat_mapa[i][j].x = x;
								mat_mapa[i][j].y = y;
								x += 24;							
								break;
							case 'F':
								mat_mapa[i][j].peso = 100;
								mat_mapa[i][j].x = x;
								mat_mapa[i][j].y = y;
								x += 24;							
								break;
							case 'M':
								mat_mapa[i][j].peso = 150;
								mat_mapa[i][j].x = x;
								mat_mapa[i][j].y = y;
								x += 24;
								break;
							case 'W':
								mat_mapa[i][j].peso = 180;
								mat_mapa[i][j].x = x;
								mat_mapa[i][j].y = y;
								x += 24;
								break;
							default:	
								break;

						}
					}
				}
			}
		}
		else
			printf("Error"); // Retorna matriz = {0}
	}

	else//Gera aleatorio;
	{
		printf("Gerando aleatoriamente....");
		if(flag == 1)
		{
			printf("Gera dungeon aleatorio");
		}
		else
		{
			printf("Gera mapa aleatorio");	
		}
	}
	return mat_mapa;

}

/*
	getPesoTile
	----------------
	Recebe uma matriz de Tile, e um flag que sinaliza se 1(dungeon) e 0 (map_fora)
	retorna uma matriz de peso referente aos tiles em que o personagem irá passar(para uso da IA).
*/
int**
getPesoTile(Tile **map, int flag)
{
	int i,j;
	int ** mat_peso = NULL;
	if(flag == 1){
		mat_peso =(int**) calloc(28,sizeof(int*));
		for(i = 0;i<28;i++)
   		{	
			mat_peso[i] =(int*) calloc(28,sizeof(int));
   		}
   		for(i = 0;i<28;i++){
			for(j=0;j<28;j++){
				mat_peso[i][j] = map[i][j].peso;
			}
		}

   	}else{
		mat_peso =(int**) calloc(42,sizeof(int*));
		for(i = 0;i<42;i++)
   		{	
			mat_peso[i] =(int*) calloc(42,sizeof(int));
   		}
   		for(i = 0;i<42;i++){
			for(j=0;j<42;j++){
				mat_peso[i][j] = map[i][j].peso;
			}
		}

   	}

	return mat_peso;
}

/*
	libera_memoria
	-------------
	Recebe matriz de tiles e a libera
	retorna NULL
*/
void
libera_memoria(Tile **map, int flag)
{
	int i,j;
	if(flag == 1)
	{
		for(i = 0;i<28;i++){
				free(map[i]);
		}
		free(map);
	}
	else
	{
		for(i = 0;i<42;i++){
				free(map[i]);
		}
		free(map);
	}
}
