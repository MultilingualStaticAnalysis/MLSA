/*
 * C++ Program to Implement Sparse Matrix
 */
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;  
 
/*
 * Class List Declaration
 */
class List
{
    private: 
        int index;
        int value;
        List *nextindex;
    public: 
        List(int index)
        {
            this->index = index;
            nextindex = NULL;
            value = NULL;
        }
        List()
        {
            index = -1;
            value = NULL;
            nextindex = NULL;
        }
        void store(int index, int value)
        {
            List *current = this;
            List *previous = NULL;
            List *node = new List(index);
            node->value = value;
            while (current != NULL && current->index < index)
            {
                previous = current;
                current = current->nextindex;
            }
            if (current == NULL)
            {
                previous->nextindex = node;
            } 
            else
            {
                if (current->index == index)
                {
                    cout<<"DUPLICATE INDEX"<<endl;
                    return;
                }
                previous->nextindex = node;
                node->nextindex = current;
            }
            return;
        }
 
        int fetch(int index)
        {
            List *current = this;
            int value = NULL;
            while (current != NULL && current->index != index)
            {
                current = current->nextindex;
            }
            if (current != NULL)
            {
                value = current->value;
            } 
            else
            {
                value = NULL;
            }
            return value;
        }
 
        int elementCount()
        {
            int elementCount = 0;
            List *current = this->nextindex;
            for ( ; (current != NULL); current = current->nextindex)
            {
                elementCount++;
            }
            return elementCount;
        }
};
/*
 * Class SpareArray Declaration
 */
class SparseArray
{
    private:
        List *start;
        int index;
    public:
        SparseArray(int index)
        {
            start = new List();
            this->index = index;
        }
        void store(int index, int value)
        {
            if (index >= 0 && index < this->index)
            {
                if (value != NULL)
                    start->store(index, value);
            } 
            else
            {
                cout<<"INDEX OUT OF BOUNDS"<<endl;
            }
        }
        int fetch(int index)
        {
            if (index >= 0 && index < this->index)
                return start->fetch(index);
            else 
            {
                cout<<"INDEX OUT OF BOUNDS"<<endl;
                return NULL;
            }
        }
        int elementCount()
        {
            return start->elementCount();
        }
};
/*
 * Class SparseMatrix Declaration
 */
class SparseMatrix
{
    private:
        int N;
        SparseArray **sparsearray;
    public: 
        SparseMatrix(int N)
        {
            this->N = N;
            sparsearray = new SparseArray* [N];
            for (int index = 0; index < N; index++)
            {
                sparsearray[index] = new SparseArray(N);
            }
        }
        void store(int rowindex, int colindex, int value)
        {
            if (rowindex < 0 || rowindex > N)
            {
                cout<<"row index out of bounds"<<endl;
                return;
            }
            if (colindex < 0 || colindex > N)
            {
                cout<<"col index out of bounds"<<endl;
                return;
            }
            sparsearray[rowindex]->store(colindex, value);
        }
 
        int get(int rowindex, int colindex)
        {
            if (rowindex < 0 || colindex > N)
            {
                cout<<"row index out of bounds"<<endl;
                return 0;
            }
            if (rowindex < 0 || colindex > N)
            {
                cout<<"col index out of bounds"<<endl;
                return 0;
            }
            return (sparsearray[rowindex]->fetch(colindex));
        }
        int elementCount()
        {
            int count = 0;
            for (int index = 0; index < N; index++)
            {
                count += sparsearray[index]->elementCount();
            }
            return count;
        }
};
/*
 * Main
 */
int main()
{
    int iarray[3][3];
    iarray[0][0] = 1;
    iarray[0][1] = NULL;
    iarray[0][2] = 2;
    iarray[1][0] = NULL;
    iarray[1][1] = 3;
    iarray[1][2] = NULL;
    iarray[2][0] = 4;
    iarray[2][1] = 6;
    iarray[2][2] = NULL;
    SparseMatrix sparseMatrix(3);
    for (int rowindex = 0; rowindex < 3; rowindex++)
    {
        for (int colindex = 0; colindex < 3; colindex++)
        {
            sparseMatrix.store(rowindex, colindex, iarray[rowindex][colindex]);
        }
    }
 
    cout<<"the sparse Matrix is: "<<endl;
    for (int rowindex = 0; rowindex < 3; rowindex++)
    {
        for (int colindex = 0; colindex < 3; colindex++)
        {
            if (sparseMatrix.get(rowindex, colindex) == NULL)
                cout<<"NULL"<< "\t";
            else
                cout<<sparseMatrix.get(rowindex, colindex) << "\t";
        }
        cout<<endl;
    }
    cout<<"The Size of Sparse Matrix is "<<sparseMatrix.elementCount()<<endl;
 
}