#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cmath>

using namespace std;

typedef struct{ int ru,rd,cu,cd;} corners;
typedef int mat[100][100];

//initialize the values of the matrix with random
//values between 1 and 10 just to make it
//easier for testing
void initializeMatrixRand(int A[][100], int n)
{

    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        A[i][j] = (int) (rand()%10+1);
}

// reading matrix
void readMatrix(int a[][100],int n)
{
   for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
       cin>>a[i][j];
}


//return the sum of 2 matrices as result
void sum(int A[][100], int B[][100],int C[][100], corners a, corners b, corners c)
{
    int r = a.rd - a.ru;
    int col = a.cd - a.cu;
    for(int i = 0;i<r;i++)
      for(int j= 0;j<col;j++)
        C[i+c.ru][j+c.cu] = A[i+a.ru][j+a.cu] + B[i+b.ru][j+b.cu];

}

//return the difference of 2 matrices as result
void diff(int A[][100], int B[][100],int C[][100], corners a, corners b, corners c)
{
    int r = a.rd - a.ru;
    int col = a.cd - a.cu;
    for(int i = 0;i<r;i++)
      for(int j= 0;j<col;j++)
        C[i+c.ru][j+c.cu] = A[i+a.ru][j+a.cu] - B[i+b.ru][j+b.cu];

}

//reset the values of a matrix to a particular value
void reset(int X[][100], corners x, int k)
{
   for(int i = x.ru;i<x.rd;i++)
    for(int j = x.cu;j<x.cd;j++)
      X[i][j] = k;
}

void strassen(int A[][100], int B[][100], int C[][100], corners aa, corners bb, corners cc)
{

    mat P[7],M,N;

    if((aa.cd-aa.cu) == 1) {
     C[cc.ru][cc.cu] += A[aa.ru][aa.cu]*B[bb.ru][bb.cu];
     return;
    }
    //set the corners for each n/2 matrix in A
    corners a = {aa.ru, aa.ru+(aa.rd-aa.ru)/2,aa.cu,aa.cu+(aa.cd-aa.cu)/2};
    corners b = {aa.ru, aa.ru+(aa.rd-aa.ru)/2,aa.cu+(aa.cd-aa.cu)/2,aa.cd};
    corners c = {aa.ru+(aa.rd-aa.ru)/2,aa.rd,aa.cu,aa.cu+(aa.cd-aa.cu)/2};
    corners d = {aa.ru+(aa.rd-aa.ru)/2,aa.rd,aa.cu+(aa.cd-aa.cu)/2,aa.cd};

    //set the corners for each n/2 matrix in B
    corners e = {bb.ru, bb.ru+(bb.rd-bb.ru)/2,bb.cu,bb.cu+(bb.cd-bb.cu)/2};
    corners f = {bb.ru, bb.ru+(bb.rd-bb.ru)/2,bb.cu+(bb.cd-bb.cu)/2,bb.cd};
    corners g = {bb.ru+(bb.rd-bb.ru)/2,bb.rd,bb.cu,bb.cu+(bb.cd-bb.cu)/2};
    corners h = {bb.ru+(bb.rd-bb.ru)/2,bb.rd,bb.cu+(bb.cd-bb.cu)/2,bb.cd};

    //set the corners for each n/2 matrix in C
    corners x = {cc.ru, cc.ru+(cc.rd-cc.ru)/2,cc.cu,cc.cu+(cc.cd-cc.cu)/2};
    corners y = {cc.ru, cc.ru+(cc.rd-cc.ru)/2,cc.cu+(cc.cd-cc.cu)/2,cc.cd};
    corners z = {cc.ru+(cc.rd-cc.ru)/2,cc.rd,cc.cu,cc.cu+(cc.cd-cc.cu)/2};
    corners t = {cc.ru+(cc.rd-cc.ru)/2,cc.rd,cc.cu+(cc.cd-cc.cu)/2,cc.cd};


    int m = aa.rd-aa.ru;
    corners p ={0,m/2,0,m/2};
    for(int i=0;i<7;i++)
     reset(P[i],p,0);
    reset(M,p,0);
    reset(N,p,0);

    //P0
    diff(B,B,M,f,h,p);
    strassen(A,M,P[0],a,p,p);
    reset(M,p,0);
    reset(N,p,0);

    //P1
    sum(A,A,M,a,b,p);
    strassen(M,B,P[1],p,h,p);
    reset(M,p,0);
    reset(N,p,0);

    //P2
    sum(A,A,M,c,d,p);
    strassen(M,B,P[2],p,e,p);
    reset(M,p,0);
    reset(N,p,0);

    //P3
    diff(B,B,M,g,e,p);
    strassen(A,M,P[3],d,p,p);
    reset(M,p,0);
    reset(N,p,0);

    //P4
    sum(A,A,M,a,d,p);
    sum(B,B,N,e,h,p);
    strassen(M,N,P[4],p,p,p);
    reset(M,p,0);
    reset(N,p,0);

    //P5
    diff(A,A,M,b,d,p);
    sum(B,B,N,g,h,p);
    strassen(M,N,P[5],p,p,p);
    reset(M,p,0);
    reset(N,p,0);

    //P6
    diff(A,A,M,a,c,p);
    sum(B,B,N,e,f,p);
    strassen(M,N,P[6],p,p,p);
    reset(M,p,0);
    reset(N,p,0);

    //C00
    sum(P[4],P[3],M,p,p,p);
    diff(M,P[1],N,p,p,p);
    sum(N,P[5],C,p,p,x);
    reset(M,p,0);
    reset(N,p,0);

    //C01
    sum(P[0],P[1],C,p,p,y);

    //C10
    sum(P[2],P[3],C,p,p,z);

    //C11
    sum(P[4],P[0],M,p,p,p);
    diff(M,P[2],N,p,p,p);
    diff(N,P[6],C,p,p,t);
    reset(M,p,0);
    reset(N,p,0);

}


void printMatrix(int A[][100],corners a)
{
    for(int i=a.ru;i<a.rd;i++)
    { for(int j=a.cu;j<a.cd;j++)
       cout<<A[i][j]<<" ";
      cout<<"\n";
    }
}


int main(int argc, char* argv[])
{   //matrix size
    int n;
    cout<<"n = ";
    cin>>n;
    cout<<"\n";

    //finding the nearest upper power of 2 for n
    int upper2power = 1;
    while(upper2power < n) upper2power*=2;


    int A[100][100],B[100][100],C[100][100];
    corners a = {0,n,0,n};
    corners b = {0,n,0,n};
    corners c = {0,n,0,n};

    srand(time(0));
    //with this tiny modification we can use any nxn matrix multiplications
    if(upper2power > n)
    {
     a.ru = 0; a.rd = upper2power; a.cu = 0; a.cd = upper2power;
     b.ru = 0; b.rd = upper2power; b.cu = 0; b.cd = upper2power;
     c.ru = 0; c.rd = upper2power; c.cu = 0; c.cd = upper2power;
     reset(A,a,0);
     reset(B,b,0);
    }

    //read matrices from keyboard
    // readMatrix(A,n);
    // readMatrix(B,n);

    //random value inputs for matrices
    initializeMatrixRand(A,n);
    initializeMatrixRand(B,n);

    //testing
    printMatrix(A,a);
    cout<<"\n";
    printMatrix(B,b);
    cout<<"\n";

    strassen(A,B,C,a,b,c);
    c.ru=0; c.rd = n; c.cu = 0; c.cd = n;
    printMatrix(C,c);
    cout<<"\n";

    /*
    sum(A,B,C,a,b,c);
    printMatrix(C,c);
    cout<<"\n";

    diff(A,B,C,a,b,c);
    printMatrix(C,c);
    cout<<"\n";
    */
    return 0;
}
