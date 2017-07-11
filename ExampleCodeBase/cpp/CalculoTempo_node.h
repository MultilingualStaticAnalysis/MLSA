//Interface da classe node
#include <math.h>
//#define TAMANHO 4

#ifndef Node_H
#define Node_H
class Node
{
	private:
		int xPos, yPos;
		float G;
		float H;
		float F;
	public:
		int tamanho;
		int id;
		Node *parent;
		//Override no construtor
		Node() : parent(0) {}
		/*Node(int x,int y,Node *_parent = 0) : xPos(x),yPos(y),
			parent(_parent), id(y*TAMANHO+x), G(0), H(0) {};*/
		Node(int x,int y,Node *_parent = 0,int t= 0): xPos(x),yPos(y),G(0),H(0),tamanho(t),id(y*tamanho+x),parent(_parent){};
		//getters
		int getxPos() const;
		int getyPos() const;
		float getG() const;
		float getH() const;
		float getF() const;
		Node* getParent() const;
		//setters
		void setxPos(int);
		void setyPos(int);
		void setG(float);
		void setH(Node* meta);
		void setF(float);
		void setParent(Node*);
		void calculaF();
};
#endif
/*
class Node
{
	private:
		int xPos;
		int yPos;
		int distancia;
		int prioridade;
	public:
		Node (int,int,int,int);
		int getxPos() const;
		int getyPos() const;
		int getPrioridade() const;
		void atualizarPrioridade(const int & xDest, const int & yDest);
		void atualizarDistancia();
		const int& distanciaHeuristica(const int&, const int&) const;

};
*/
/*
struct Node
{
	public:
		int xPos, yPos;
		int id;
		Node *parent;
		float G;
		float H;
		float F;

		Node() : parent(0) {}
		Node(int x,int y,Node *_parent = 0) : xPos(x),yPos(y),
			parent(_parent), id(y*TAMANHO+x), G(0), H(0) {};

		float getF() { return G+H; }
		float distanciaPontos(Node* nodeMeta)
		{
			float dist = (float) (sqrt((float)((nodeMeta->xPos-this->xPos)*(nodeMeta->xPos-this->xPos))+((noteMeta->yPos-this->yPos)*(nodeMeta->yPos-this->yPos))));
			return dist;

		}
};
*/
