struct tile
{
	float x;
	float y;
	int peso;
};

typedef struct tile Tile;

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
			M -> monhtanha -> +150;
			G -> Agua -> +180;
	Dungeons -> flag = 1:
		Casos de leitura:
		B -> Bloqueio;
		C -> Caminháel -> +10;

	Recebe o nome do arquivo que será lido e a flag que dirá se é dungeon ou mapa;
	*Caso file_name == null gera aleatóriamente? ---- Em teste... depois...;

	Retorna uma matriz de inteiros contendo os pesos de cada área como descrito acima.
*/
Tile **
gera_mapa(char *file_name,int flag);

/*
	getPesoTile
	----------------
	Recebe uma matriz de Tile, e um flag que sinaliza se 1(dungeon) e 0 (map_fora)
	retorna uma matriz de peso referente aos tiles em que o personagem irá passar(para uso da IA).
*/
int**
getPesoTile(Tile **map, int flag);

/*
	libera_memoria
	-------------
	Recebe matriz de tiles e a libera
*/
void
libera_memoria(Tile **map, int flag);
