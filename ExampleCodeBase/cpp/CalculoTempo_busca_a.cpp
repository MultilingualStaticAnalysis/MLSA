#include "CalculoTempo_busca_a.h"
#include <iostream>
#include <algorithm>


Busca_a::Busca_a(void)
{
	inicializaBusca = false;
	foundMeta = false;
}
Busca_a::~Busca_a(void)
{
}

/* Testa se já foi inicializada a busca
 * Caso negativo ele limpa as listas, inicializa os nós
 * e começa a busca
 * A entrada é do tipo Vector2 = new Vector2(x,y)
 */
void Busca_a::findCaminho(Vector2 posicaoInicial, Vector2 posicaoMeta, int** matrizpeso, int tamanhomapa)
{
	if(!inicializaBusca)
	{
		for(unsigned int i=0;i<listaAbertos.size();i++)
		{
			delete listaAbertos[i];
		}
		listaAbertos.clear();

		for(unsigned int i=0;i<listaVisitados.size();i++)
		{
			delete listaVisitados[i];
		}
		listaVisitados.clear();
		for(unsigned int i = 0;i<caminhoMeta.size();i++)
		{
			delete caminhoMeta[i];
		}
		caminhoMeta.clear();
		for(unsigned int i = 0;i<caminhoVolta.size();i++)
		{
			delete caminhoVolta[i];
		}
		caminhoVolta.clear();

		//Inicialização do nó inicio
		Node inicio;
		inicio.setxPos(posicaoInicial.x);
		inicio.setyPos(posicaoInicial.y);

		//Inicialização do nó Meta
		Node meta;
		meta.setxPos(posicaoMeta.x);
		meta.setyPos(posicaoMeta.y);
		
		peso = 0;
		inicializaLista(inicio,meta,tamanhomapa);
		inicializaBusca = true;
	}
	if(inicializaBusca)
	{
		continuePath(matrizpeso,tamanhomapa);
	}
}
/* Inicializa o algoritmo
* É criado o nó inicial e o nó meta.
* É atribuido a lista de abertos o nó inicial
* É inicializada a lista de fechados
*/
void Busca_a::inicializaLista(Node inicio,Node meta,int tamanhomapa)
{
	//Inicializa os nós
	noInicio = new Node(inicio.getxPos(), inicio.getyPos(), NULL,tamanhomapa);
	noMeta = new Node(meta.getxPos(),meta.getyPos(),&meta,tamanhomapa);
	
	noInicio->setG(0);
	noInicio->setH(noMeta);
	noInicio->calculaF();
	noInicio->setParent(0);
	
	//Adiciona o nó inicial na lista de abertos
	listaAbertos.push_back(noInicio);
}

/*Antigo
void Busca_a::setInicioeFim(Node inicio,Node meta)
{
	nodeInicio = new Node(inicio.xPos, inicio.yPos, NULL);
	nodeMeta = new Node(meta.xPos, meta.yPos, &meta);

	nodeInicio->G = 0;
	nodeInicio->H = nodeInicio->distanciaPontos(nodeMeta);
	nodeInicio->parent = 0;

	listaAbertos.push_back(nodeInicio);
}
*/

void Busca_a::continuePath(int** matrizpeso,int tamanhomapa)
{
	int newpeso;
	//Se não houver elementos aberto, retorna (erro na busca)
	if(listaAbertos.empty())
	{
		return;
	}
	//Pega o nodo com menor valor de f na lista de abertos
	Node* nodeAtual = getNextNode();
	//Teste se o nó em que estou é o nó meta
	if(nodeAtual->id == noMeta->id)
	{
		noMeta->parent = nodeAtual->parent;
		noMeta->setG(matrizpeso[noMeta->getyPos()][noMeta->getxPos()] + noMeta->parent->getG());
			
		//Retornando o caminho completo que vai ser percorrido
		Node* getPath;
		for(getPath = noMeta; getPath !=NULL;getPath = getPath->parent)
		{
			if(getPath == noMeta)
				peso+=getPath->getG();
			caminhoMeta.push_back(new Vector2(getPath->getxPos(),getPath->getyPos())); //Ida
			caminhoVolta.push_back(new Vector2(getPath->getxPos(),getPath->getyPos())); //Volta
		}
		std::reverse(caminhoMeta.begin(),caminhoMeta.end());
		foundMeta = true;
		return;
	}
	//Caso não for encontrado o meta, começa a busca em horizontal e vertical
	else
	{
		//Lado Direito
		if(nodeAtual->getxPos()+1 <tamanhomapa)
		{
			newpeso=matrizpeso[nodeAtual->getyPos()][nodeAtual->getxPos()+1];
			pathOpened(nodeAtual->getxPos()+1,nodeAtual->getyPos(),nodeAtual->getG()+newpeso,nodeAtual,tamanhomapa);
		}
		//Lado Esquerdo
		if(nodeAtual->getxPos()-1 >= 0){
			newpeso=matrizpeso[nodeAtual->getyPos()][nodeAtual->getxPos()-1];
			pathOpened(nodeAtual->getxPos()-1,nodeAtual->getyPos(),nodeAtual->getG()+newpeso,nodeAtual,tamanhomapa);
		}
		//Baixo
		if(nodeAtual->getyPos()+1 <tamanhomapa)
		{
			newpeso=matrizpeso[nodeAtual->getyPos()+1][nodeAtual->getxPos()];
			pathOpened(nodeAtual->getxPos(),nodeAtual->getyPos()+1,nodeAtual->getG()+newpeso,nodeAtual,tamanhomapa);
		}
		//Cima
		
		if(nodeAtual->getyPos()-1 >=0){
			newpeso=matrizpeso[nodeAtual->getyPos()-1][nodeAtual->getxPos()];
			pathOpened(nodeAtual->getxPos(),nodeAtual->getyPos()-1,nodeAtual->getG()+newpeso,nodeAtual,tamanhomapa);
		}
		//Testa se o nó aberto já estava na lista de abertos, caso positivo, apaga ele.
		for(unsigned int i=0;i<listaAbertos.size();i++)
		{
			if(nodeAtual->id == listaAbertos[i]->id)
			{
				listaAbertos.erase(listaAbertos.begin() + i);
			}
		}
	}		
}
/*Função getNextNode
 * Retorna o nodo na lista de aberto que tiver o F
 * com o menor valor
 */
Node* Busca_a::getNextNode()
{
	//Para garantir o melhor valor, inicializa-se melhorF como algo grande
	float melhorF = 999999.0f;
	int nodeIndex = -1;
	Node* proximoNode = NULL;
	
	for(unsigned int i=0;i<listaAbertos.size();i++)
	{
		if(listaAbertos[i]->getF() < melhorF)
		{
			melhorF = listaAbertos[i]->getF();
			nodeIndex = i;		
		}
	}
	if(nodeIndex >= 0)
	{
		proximoNode = listaAbertos[nodeIndex];
		listaVisitados.push_back(proximoNode);
		listaAbertos.erase(listaAbertos.begin() + nodeIndex);
	}
	return proximoNode;
}
/* Função pathOpened
 * Abre os caminhos em que o algoritmo pode seguir
 * 
 */
void Busca_a::pathOpened(int x,int y, float newCost, Node* parent, int tamanhomapa)
{	
	int id = y* tamanhomapa + x;
	//Caso já esteja na lista de fechados
	for(unsigned int i =0;i<listaVisitados.size();i++)
	{
		if(id == listaVisitados[i]->id)
		{
			return;
		}
	}
	

	Node* novoNode = new Node(x,y,parent,tamanhomapa);
	novoNode->setG(newCost);
	novoNode->setH(noMeta);
	novoNode->calculaF();
	//novoNode->H = parent->distanciaPontos(nodeMeta);

	for(unsigned int i=0;i<listaAbertos.size();i++)
	{
		if(id == listaAbertos[i]->id)
		{
			float novoF = novoNode->getG() + newCost + listaAbertos[i]->getH();

			if(listaAbertos[i]->getF() > novoF)
			{
				listaAbertos[i]->setG(novoNode->getG() + newCost);
				listaAbertos[i]->parent = novoNode;
			}
			else //se o novo F não é melhor que o antigo
			{
				delete novoNode;
				return;
			}
		}
	}

	listaAbertos.push_back(novoNode);
}
Vector2 Busca_a::getVnoMeta()
{
	Vector2 aux(noMeta->getxPos(),noMeta->getyPos());
	return 	aux;
}

/*
Vector3 Busca_a::nextPathPos()//Colocar o que vai receber a IA 
{
	int index = 1;
	
	Vector3 proximaPos;
	proximaPos.x = caminhoMeta[caminhoMeta.size() - index]->x
	proximaPos.y = caminhoMeta[caminhoMeta.size() - index]->y

	Vector3 distancia = proximaPos - pos; //Posicao da IA

	if(index < caminhoMeta.size())
	{
		if(distance.Lenght() < radius) //Radius da IA
		{
			caminhoMeta.erase(caminhoMeta.end() - index);
		}
	}

	return proximaPos
}
*/
/*
using namespace std;
int main(){
	int **matrizteste;
	matrizteste = (int**) malloc(4*sizeof(int*));
	for(int i=0;i<4;i++){
		matrizteste[i] = (int*) malloc(4*sizeof(int));
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			matrizteste[i][j] = 5;
		}
	}
	matrizteste[3][1] = 2;
	matrizteste[2][1] = 2;
	
	Busca_a* busca = new Busca_a();
	Vector2 inicio(0,3);
	Vector2 fim(1,1);
	while(!busca->foundMeta)
	{
		busca->findCaminho(inicio,fim,matrizteste,4);
	}
	std::reverse(busca->caminhoMeta.begin(),busca->caminhoMeta.end());
	cout<<"tamanho:"<<busca->caminhoMeta.size() <<endl;
	for(unsigned int i=0;i<busca->caminhoMeta.size();i++){
		printf("Elemento %d: (%d,%d)",i,busca->caminhoMeta[i]->x,busca->caminhoMeta[i]->y);
	}
	return 0;
}
*/
