
#include "CalculoTempo_node.h"
//Construtor
/*
Node::Node(int x,int y, int d,int p)
{
	xPos = x;
	yPos = y;
	distancia = d;
	prioridade = p; //Quanto menor o F= distancia + heuristica, maior a prioridade
}

//Getters

int Node::getxPos() const
{
	return xPos;
}

int Node::getyPos() const
{
	return yPos;
}

int Node::getPrioridade() const
{
	return prioridade;
}

//Upgrade Functions

void Node::atualizarPrioridade(const int & xDest, const int & yDest) //Recebe os endereços de destino como entrada
{
	prioridade = distancia + distanciaHeuristica(xDest,yDest)*10;
}

void Node::atualizarDistancia(){
	distancia +=10;
}

const int &Node::distanciaHeuristica(const int & xDest, const int & yDest) const
{
	static int xDistancia,yDistancia,distanciaTotal;
	xDistancia = xDest-xPos;
	yDistancia = yDest-yPos;

	distanciaTotal=abs(xDistancia)+abs(yDistancia);

	return (distanciaTotal);
}

//Overloading no operador <
bool operator<(const Node& a, const Node & b)
{
	return a.getPrioridade() > b.getPrioridade();
}
*/
//Getters
int Node::getxPos() const
{
	return this->xPos;
}
int Node::getyPos() const
{
	return this->yPos;
}
float Node::getG() const
{
	return this->G; 
}
float Node::getH() const
{
	return this->H;
}
float Node::getF() const
{
	return this->F;
}
Node* Node::getParent() const
{
	return this->parent;
}
//Setters
void Node::setxPos(int x)
{
	this->xPos = x;
}
void Node::setyPos(int y)
{
	this->yPos = y;
}
void Node::setG(float G)
{
	this->G = G;
}
void Node::setH(Node* meta)
{
	this->H = (sqrt(((meta->getxPos()-this->xPos)*(meta->getxPos()-this->xPos))+((meta->getyPos()-this->yPos)*(meta->getyPos()-this->yPos))));
}
void Node::setF(float F)
{
	this->F = F;
}
void Node::setParent(Node* parent)
{
	this->parent = parent;
}
void Node::calculaF()
{
	this->F = this->G + this->H;
}
