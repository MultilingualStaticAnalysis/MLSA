//Quadratic Equation

#include <math.h>
#include <iostream>
using namespace std;
struct graphPoint{
	double x, y;
	};
class QuadraticEquation{
	public:
	QuadraticEquation(double A = 0.0, double B = 0.0, double C = 0.0) : a(A), b(B), c(C){
		xintercepts[0].x = 0.0;
		xintercepts[0].y = 0.0;
		xintercepts[1].x = 0.0;
		xintercepts[1].y = 0.0;
	}
	~QuadraticEquation(){}


	int getxintercepts(){


		double temp = (b * b) - (4 * a * c);
		if(temp < 0){
			cout << "##-Square Root Error:\n"
			     << " ##- SquareRoot ( " << temp << " )\n";
			return 1;
		}

		temp = sqrt ( temp );

		xintercepts[0].x = (b * -1) - temp;
		xintercepts[0].x = xintercepts[0].x / (2 * a);

		xintercepts[1].x  = (b * -1) + temp;
		xintercepts[1].x = xintercepts[1].x / (2 * a);
		return 0;
	}

	void displayequation(){
		if(a != 0){
			cout << a;
			cout << "x^2";}
		if(b >= 1 & a != 0)
			cout << "+";
		if(b != 0)
			cout << b << "x";
		if(c > 0)
			cout << "+";
		if(c != 0)
			cout << c;
		if(a == 0 & b == 0 & c == 0)
			cout << 0;
		cout << "=0" << endl;
	}

	double a, b, c;
	graphPoint xintercepts[2];
	};







void creditsHelp();
void wierdGetch();



int main(int argc, char *argv[]){
	cout << "@-Quadratic Equation Solver\n"
    	 << " @-Karlan Mitchell karlanmitchell-at-comcast-dot-net\n"
    	 << " @-For Credits/Help enter 0 for A\n";

	double a,b,c;

	cout << "Enter in values for equation\n";
	for(;;){
		cout << "A: ";
		cin >> a;
		if(a == 0.0){
			creditsHelp();
			continue;
		}
		break;
	}
	cout << "B: ";
	cin >> b;
	cout << "C: ";
	cin >> c;

	QuadraticEquation test(a,b,c);//create the class

	test.displayequation();//display the equation with the class function

	switch(test.getxintercepts()){/* I am using a switch here instead of
                               * an if because I constanly add/remove
			       * error messages to this function*/
		case 1:
			cout << "!!-Equation not possible\n"
				<< " !!-If you know that it is possible, please contact me about a bug\n";
			exit(1);
			break;
	}

	cout << "x = " << test.xintercepts[0].x << " | " << test.xintercepts[1].x << endl;
	cout << "(" << test.xintercepts[0].x << ", 0) & (" << test.xintercepts[1].x << ", 0)\n";


	wierdGetch();
	return 0;
}
void creditsHelp(){

	cout << "\nThis program was created by me to make my math homework easier\n\n"

	     << "What it does:\n"
	     << "It takes in the 'a', 'b', and 'c' values for a quadratic equation\n"
	     << "which equals zero.\n"
	     << "EX: \"x^2 - 3x + 2 = 0\" is equal to \"(x - 2)(x - 1) = 0\"\n"
	     << "    ax^2 + bx + c = 0\n"
	     << "    The 'a','b', and 'c' values for the equation would be 1, -3, and 2\n"
	     << "    The x intercepts for this would be (2, 0) and (1, 0)\n"
	     << "    2^2 - 3(2) + 2 = 0 and 1^2 - 3(1) + 2 = 0\n\n"

	     << "Why would I use this:\n"
	     << "1) You are in Algebra I/II or Geometry\n"
	     << "2) Your too lazy to do the quadratic equation on your own which is:\n"
	     << "   x=( -b +/- sqrt(bb - 4ac) ) / (2a)\n";
	wierdGetch();
	exit(0);
}
void wierdGetch(){
	cout << "Press enter to exit...";
	getchar();getchar();//Why do I need, two?  The world may never know
}