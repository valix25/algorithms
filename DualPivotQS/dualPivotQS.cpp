#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;


/** see explanation for b) at the end comments */

class QuickDualPivot{

private:
    void sorting(int* , int, int);
    void exchange(int*, int, int);
public:
    void sorty(int*, int);
};

inline void QuickDualPivot::sorty(int a[], int n)
{
   sorting(a,0,n-1);
}

inline void QuickDualPivot::exchange(int a[], int i, int j)
{
   int temp = a[i];
   a[i] = a[j];
   a[j] = temp;
}

inline void QuickDualPivot::sorting(int a[], int lo, int hi)
{
   if(hi <= lo) return;
   srand(time(0));

   int mid = (hi-lo)/2 + lo;
   int x = (int) (rand()%(mid-lo+1)) + lo; //choose pivot between lo and mid
   int y = (int) (rand()%(hi-mid+1)) + mid; //choose second pivot between midŜ and hi
   while(x == y)
      y = (int) (rand()%(hi-mid+1)) + mid;
   //cout<<x<<" "<<y<<"\n";

   if(a[x] <= a[y])
      {
         exchange(a,x,lo);
         if(y == lo)
            exchange(a,x,hi);
         else
         exchange(a,y,hi);
      }
   else
      {
          exchange(a,y,lo);
          if(x == lo)
           exchange(a,y,hi);
         else
          exchange(a,x,hi);
      }
   // now we are done setting the random pivots at the beginning and at the end

   int lt = lo + 1;
   int gt = hi - 1;
   int i = lt;

   while(i <= gt)
   {
     if(a[i] < a[lo])
        {
          exchange(a,i,lt);
          i++;
          lt++;
        }
     else if(a[hi] < a[i])
        {
          exchange(a,i,gt);
          gt--;
        }
     else i++;
   }

   lt--;
   exchange(a,lo,lt);

   gt++;
   exchange(a,hi,gt);

   sorting(a,lo,lt-1);
   if(a[lt] < a[gt]) sorting(a,lt+1,gt-1);
   sorting(a,gt+1,hi);


}

void print_array(int a[], int n)
{
   for(int i = 0; i < n; i++)
     cout<<a[i]<<" ";
   cout<<"\n";
}


int main(int argc, char* argv[])
{
    int n;
    cout<<"Enter number of elements: ";
    cin>>n;

    int *a = new int[n];
    /*
    for(int i = 0; i < n; i++)
      cin>>a[i];*/
    srand(time(0));
    for(int i=0; i < n; i++)
      a[i] = rand()%50 + 1;

    print_array(a,n);

    QuickDualPivot q;
    q.sorty(a,n);

    print_array(a,n);

    delete[] a;
    return 0;
}

/**
Run the program for various inputs and it worked for all
my test, if there are inputs/tests
for which it might not work it would probably be because of how the pivots
were chosen. I run into a few bugs because them and I think I solved them all.

For b)

The worst possible inputs for a standard Quicksort with one pivot is when the
input sequence is ordered or if all the elements are the same. In these cases
the complexity is given by (n-1)*(n-2).... or O(n^2) since the partition doesn't
do anything and it goes till the end of the sequence and the subarray is n-1, and
then it repeats.

This is also relevant for the dual pivot Quicksort which also has these cases
as the worst possible cases, only that by using 2 pivots, the sorting in the
worst case would go like this: (n-2)*(n-4)*... also O(n^2) but twice as faster
than the standard Quicksort. Roughly n(n-2)/4 for DP QS and n(n-1)/2 for standard
QS. This seems to be supported by the following results. 55 vs 100 in time for
the DV QS(page 7 in the source publication's pdf).

http://iaroslavski.narod.ru/quicksort/DualPivotQuicksort.pdf

for the compact implementation:
http://algs4.cs.princeton.edu/23quicksort/QuickDualPivot.java.html

*/

