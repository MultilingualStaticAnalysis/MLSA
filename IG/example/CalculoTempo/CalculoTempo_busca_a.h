#include "CalculoTempo_node.h"
//#include "node.cpp"
#include <stdlib.h>
#include <stdio.h>
#include "CalculoTempo_vector2.h"
#include <vector>


#ifndef Busca_a_H
#define Busca_a_H
class Busca_a
{
	public:
		Busca_a(void);
		~Busca_a(void);

		void findCaminho(Vector2 posicaoInicial, Vector2 posicaoMeta, int** matrizpeso, int tamanhomapa);
		//Vector3 nextPathPos();
		void clearOpenList() { listaAbertos.clear();}
		void clearVisitedList() { listaVisitados.clear(); }
		void clearPathToGoal() { caminhoMeta.clear(); }
		void clearVolta() { caminhoVolta.clear();}
		bool inicializaBusca;
		bool foundMeta;
		std::vector<Vector2*> caminhoMeta;
		std::vector<Vector2*> caminhoVolta;
		float peso;
		Vector2 getVnoMeta();
	private:
		void inicializaLista(Node inicio,Node meta,int tamanhomapa);
		void pathOpened(int x,int y, float newCost, Node* parent,int tamanhomapa); //Checa se a celula atual está na lsita de abertos
		Node* getNextNode();
		void continuePath(int** matrizpeso,int tamanhomapa);

		Node *noInicio;
		Node *noMeta;
		std::vector<Node*> listaAbertos;
		std::vector<Node*> listaVisitados;
};
#endif

