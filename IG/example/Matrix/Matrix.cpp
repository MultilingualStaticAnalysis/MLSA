/**
C++ - Program with Matrices by codebind.com
*/
 
#include<iostream>
#include<cmath>
 
using namespace std;
 
 
void swapcol(int a[50][50], int r, int c, int b);
void swaprow(int a[50][50], int r, int c,int b);
int swapmx(int arr[50][50],int m,int n,int a ,int b );
void arrey(int arr1[50][50],int arr2[50][50], int sizemx1, int p,int q);
 
 
 
int main()
{
  //-------defining variables and initializing them-------------
  int e,flag=0,i,j,flag1=0;
  int arrey1[50][50],arrey2[50][50],arrey3[50][50],arrey4[50][50],arrey5[50][50],arrey6[50][50],arrey7[50][50],arrey8[50][50];
  int k,sizemx1,p,q,r,x,y,temp=0;
  int m, n,a,b,l;
  char operation,redo;
  //--------Printing my name on screen----------------
  cout<<"Welcome to the  program 2.1 written by Your Name"<<endl;
  cout<<"***************************************************************"<<endl;
  cout<<endl<<endl<<endl;
 
  cout<<"The instruction menu:"<<endl<<endl<<endl;
  cout<<"    1. Initialize Matrices"<<endl;
  cout<<"    2. Print Matrices"<<endl;
  cout<<"    3. Multiply Matrices"<<endl;
  cout<<"    4. Transpose of 2nd Matrix"<<endl;
  cout<<"    5. Move Row and Column of 2nd Matrix"<<endl;
  cout<<"    6. Quit"<<endl<<endl;
 
  //--here do loop is used so that the program can be used more then one time
  //without exiting the run screen---------------------------
  do
  {
    do
    {
 
 
      cout<<"Please enter your requested instruction (1..6)?=  ";
      while(!(cin>>operation))  //Reciving vaiables from input : is it no/character ?
      {
        cout << "Please  enter a number!  Try again: ";
        cin.clear ();
        cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars,
        // whichever comes first.
      }
      //cin>>operation ;
      cout<<endl;
 
 
 
 
      //---used switch function so thet the operater can be decided------------
      switch (operation)
      {
      //------calculating the requested equation for inputs-------------
      //-------at the same time printing the results on screen-----------
      case'1':
        cout<<"Enter the Size of 1st square Matrix"<<endl;
        cout<<"Row & Column=";
        while(!(cin>>sizemx1))  //Reciving vaiables from input : is it no/character ?
        {
          cout << "Please  enter a number!  Try again: ";
          cin.clear ();
          cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars,
          // whichever comes first.
        }
        //cin>>sizemx1;
        if (sizeof(sizemx1)<4){
          cout<<"unknown command"<<endl;
        }
        cout<<"Enter the  of 2nd Matrix"<<endl;
        cout<<"Row=";
        while(!(cin>>p))  //Reciving vaiables from input : is it no/character ?
        {
          cout << "Please  enter a number!  Try again: ";
          cin.clear ();
          cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars,
          // whichever comes first.
        }
 
        //cin>>p;
 
        cout<<"Column=";
        while(!(cin>>q))  //Reciving vaiables from input : is it no/character ?
        {
          cout << "Please  enter a number!  Try again: ";
          cin.clear ();
          cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars,
          // whichever comes first.
        }
        //cin>>q;
        flag=flag+1;
        //cout<<"flag="<<flag<<endl;
 
 
        break;
      case'2': //2. Print Matrices
        //cout<<"flag="<<flag<<endl;
        //cout<<"flag1="<<flag1<<endl;
 
        if(flag<1){
          cout<<"flag="<<flag<<endl;
          cout<<"Please perforform operation no.1 firest"<<endl;
        }
        if(flag>=1){
          cout<<"flag="<<flag<<endl;
          // arrey( arrey1,arrey2, sizemx1, p,q);
          /*cout<<"Enter the elements in the 1st Array"<<endl;
for(i=0;i<sizemx1;i++)
{
for(j=0;j<sizemx1;j++)
{
cin>>arrey1[i][j];
}
}
cout<<"Enter the elements in the 2nd Array"<<endl;
for(i=0;i<p;i++)
{
for(j=0;j<q;j++)
{
cin>>arrey2[i][j];
}
}*/
 
 
 
 
          cout<<"\nDisplaying the 1st Array"<<endl;
          for(i=0;i<sizemx1;i++)
          {
            for(j=0;j<sizemx1;j++)
            {
              arrey1[i][j] = 50+rand() %(100-50+1);
 
              cout<<arrey1[i][j]<<"\t";
 
            }
            cout<<endl;
          }
          cout<<"\nDisplaying the 2nd Array"<<endl;
          for(i=0;i<p;i++)
          {
            for(j=0;j<q;j++)
            {
              arrey2[i][j] = 50+rand() %(100-50+1);
 
              cout<<arrey2[i][j]<<"\t";
            }
            cout<<endl;
          }
          flag1=flag1+1;
        }
        arrey2[10][10]=arrey4[10][10];
 
        for(i=0;i<p;i++)
        {
          for(j=0;j<q;j++)
          {
            arrey5[i][j]=arrey2[i][j];
            arrey6[i][j]=arrey2[i][j];
          }
        }
 
        break;
      case'3':      //3. Multiply Matrices
        //cout<<"flag1="<<flag1<<endl;
        if(flag1<1){
          cout<<"Please perforform operation no.1 and no.2 firest"<<endl;
        }else{
          if(sizemx1!=p){
            cout<<"Multiplication is not possible"<<endl;
          }
          if(sizemx1==p)
          {
            for(i=0;i<sizemx1;i++)
            {
              for(j=0;j<q;j++)
              {
                arrey3[i][j]=0;
                for(k=0;k<p;k++)
                {
                  arrey3[i][j]=arrey3[i][j]+arrey1[i][k]*arrey2[k][j];
                }
              }
            }
            cout<<"\nDisplaying the array elements after multiplication"<<endl;
            for(i=0;i<sizemx1;i++)
            {
              for(j=0;j<q;j++)
              {
                cout<<arrey3[i][j]<<"\t";
              }
              cout<<endl;
            }
          }
        }
        break;
      case'4':   //4. Transpose of 2nd Matrix
 
        if(flag1<1){
          cout<<"Please perforform operation no.1 and no.2 firest"<<endl;
        }
        else{
          for(i=0;i<p;i++)
          {
            for(j=0;j<q;j++)
            {
              arrey7[i][j]=arrey6[i][j];
 
            }
          }
          cout<<"\nDisplaying trannspose the 2nd Matrix"<<endl;
 
          for(i=0;i<=q-1;i++)
          {
            for(j=0;j<=p-1;j++)
            {
              temp=arrey7[j][i];
              arrey7[j][i]=arrey4[i][j];
              arrey4[i][j]=temp;
 
              //cout<<i<<j;
              cout<<temp<<"\t";
            }
            cout<<endl;
          }
        }
 
        break;
      case'5': //5. Move Row and Column of 2nd Matrix
 
        if(flag1<1){
          cout<<"Please perforform operation no.1 and no.2 firest"<<endl;
        }    else{
 
          cout <<"enter the row number you want to swap:"<<endl;
          // cin>>x>>y;
 
          while(!(cin>>x))  //Reciving vaiables from input : is it no/character ?
          {
            cout << "Please  enter a number!  Try again: ";
            cin.clear ();
            cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars,
            // whichever comes first.
          }
          cout<<endl;
          cout <<"enter the column number you want to swap:"<<endl;
          while(!(cin>>y))  //Reciving vaiables from input : is it no/character ?
          {
            cout << "Please  enter a number!  Try again: ";
            cin.clear ();
            cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars,
            // whichever comes first.
          }
          cout<<endl;
 
          for(i=0;i<p;i++)
          {
            for(j=0;j<q;j++)
            {
              arrey8[i][j]=arrey5[i][j];
 
            }
          }
          cout<<"The original matrix is"<<endl;
          cout<< endl;
 
          for(i=0;i<p;i++)
          {
            for(j=0;j<q;j++)
            {
 
 
              cout<<arrey8[i][j]<<"\t";
            }
            cout<< endl;
          }
 
          swapmx(arrey8,p,q,x,y);
          cout<< endl;
 
        }
        break;
      case'6':  //  6. Quit
        cout<<"Thanks do u want to start again:";
        cout<<endl<<endl;
        goto label;
        break;
      default:
        cout<<"unknown command"<<endl;
 
      }
    }
    while(operation=='1'||operation=='2'||operation=='3'||operation=='4'||operation=='5'||operation=='6');
 
 
    //----now once again the program will ask the user if want to continue or not
    cout<<"enter y or Y to continue:";
    cin>>redo;
    cout<<endl<<endl;
  }
  while(redo=='y'||redo=='Y');
label:
 
  system("pause");
  return 0;
 
}
void arrey(int arr1[50][50],int arr2[50][50], int sizemx1, int p,int q)
{
 
  cout<<"Enter the elements in the 1st Array"<<endl;
  for(int i=0;i<sizemx1;i++)
  {
    for(int j=0;j<sizemx1;j++)
    {
      //cin>>arr1[i][j];
      while(!(cin>>arr1[i][j]))  //Reciving vaiables from input : is it no/character ?
      {
        cout << "Please  enter a number!  Try again: ";
        cin.clear ();
        cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars,
        // whichever comes first.
      }
 
    }
  }
  cout<<"Enter the elements in the 2nd Array"<<endl;
  for(int i=0;i<p;i++)
  {
    for(int j=0;j<q;j++)
    {
      //cin>>arr2[i][j];
      while(!(cin>>arr2[i][j]))  //Reciving vaiables from input : is it no/character ?
      {
        cout << "Please  enter a number!  Try again: ";
        cin.clear ();
        cin.ignore (1000, '\n');  // Skip to next newline or 1000 chars,
        // whichever comes first.
      }
    }
  }
}
void swapcol(int a[50][50], int r, int c,int b)
// r -> row, c ->col
{
  int t,s;
  while(b < (c-1))
  {
    for(int i=0; i<r; i++)
    {
      t = a[i][b];
      a[i][b] = a[i][b+1];
      a[i][b+1] = t;
    }
    b++;
  }
 
 
}
void swaprow(int a[50][50], int r, int c,int b)
// r -> row, c ->col
{
  int t;
  while(b < (r-1))
  {
    for(int i=0; i<c; i++)
    {
      t = a[b][i];
      a[b][i] = a[b+1][i];
      a[b+1][i] = t;
    }
    b++;
  }
 
  /*for(int i = 0; i< c ; i++)
{
t = a[b-1][i];
a[b-1][i] = a[r-1][i];
a[r-1][i] = t;
}*/
}
int swapmx(int arr[50][50],int m,int n,int a ,int b )
{
 
  int  i, j,k,l;
 
  //for( l = 0; l <=a-1; l ++){
  /* Swap function call */
  cout<<"The matrix after shifting row"<<endl;
  swaprow(arr, m, n, a-1);
  for( i = 0; i < m ; i ++)
  { cout<< endl;
    for (  j = 0; j < n ; j ++)
 
      cout << arr[i][j] <<"\t";
  }
  cout<< endl;
  cout<< endl;
 
 
  //}
  cout<<endl<<endl;
  cout<<"The matrix after shifting column"<<endl;
  //for( k = 0; k <=b ; k ++){
 
 
  swapcol(arr, m, n, b-1);
  //cout<<"k="<<k<<endl;
  /* Display Array in Matrix form */
  //}
  for( i = 0; i < m ; i ++)
  { cout<< endl;
    for (  j = 0; j < n ; j ++)
      cout << arr[i][j] <<"\t";
  }
  cout<< endl;
  return 1;
}
 
 
/*
OUTPUT:
Welcome to the  program 2.1 written by Your Name
***************************************************************
 
 
 
The instruction menu:
 
 
    1. Initialize Matrices
    2. Print Matrices
    3. Multiply Matrices
    4. Transpose of 2nd Matrix
    5. Move Row and Column of 2nd Matrix
    6. Quit
 
Please enter your requested instruction (1..6)?=  1
 
Enter the Size of 1st square Matrix
Row & Column=3
Enter the  of 2nd Matrix
Row=3
Column=3
Please enter your requested instruction (1..6)?=  2
 
flag=1
 
Displaying the 1st Array
91      55      60
81      94      66
53      83      84
 
Displaying the 2nd Array
85      94      94
75      98      66
82      87      58
Please enter your requested instruction (1..6)?=
*/