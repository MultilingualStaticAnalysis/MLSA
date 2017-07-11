//Interface da classe node
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


struct Vector2
{
	public:
		int x,y;
		Vector2(){}
		Vector2(int x,int y){this->x = x; this->y = y;}
		void setX(int x){this->x = x;}
		void setY(int y){this->y = y;}
};

