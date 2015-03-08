#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

void addStrings(vector<string> &v,int left, int right, char s[], int count){

    // left holds the number of I remaining (as in how many balls can we stil put in)
    // right holds number of O remaining
    if(left < 0 || right < left) return;
     /* left < 0 is needed since we cannot construct if no left balls are there*/
     /* at any given time in the string, the number of I must be bigger
     or equal than the number of O's hence right < left*/
    if(left == 0 && right == 0) {
       string s_copy(s);
       v.push_back(s_copy);
    } else {
      // as long as we have balls to put in
      if(left > 0) {
       s[count] = 'I';
       s[count+1] = '\0';
       addStrings(v, left-1, right, s, count+1);
      }
      // as long as the number of O's is bigger than the number if I's
      if(right > left){
       s[count] = 'O';
       s[count+1] = '\0';
       addStrings(v, left, right-1, s, count+1);
      }

    }
}

int main()
{
    int n;
    cout<<"Enter number n: ";
    cin>>n;

    vector<string> vec;

    char str[2*n+1];
    addStrings(vec,n,n,str,0);

    vector<string>::iterator it;
    for(it = vec.begin(); it != vec.end(); it++){
        cout << *it << "\n";
    }

    cout<<"Number of strings: "<<vec.size()<<"\n";

    return 0;
}

/** The number of such sequences C_n could have computed by realizing
that for each n, the number of sequences is the catalan number
at index n. C_n = (2*n)!/(n!*(n+1)!) closed formula for the catalan number,
example C_3 = 5

The complexity of the algorithm above is O(n^2) because be have a recursion
given by S(l,r) = S(l-1,r) + S(l,r-1) which it translates into an nxn table

*/
