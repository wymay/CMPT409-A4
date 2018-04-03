//Constrained Circular Permutations

#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

void swap(int& a, int& b)
{ int x=a;
  a=b;
  b=x;
}

void countPermutations(vector<int>& vec, int next, int& count, int triSum)
{ if (next==vec.size())
  { 
    if(vec[vec.size()-1]+vec[0]<=triSum-1)
        count++;
    return;
  }
  for (int i=next; i<vec.size(); i++)
  { swap(vec[i], vec[next]);
    if(next>=2 && next < vec.size() && (vec[next]+vec[next-1]+vec[next-2] > triSum)){
        swap(vec[i], vec[next]);
        continue;
    }
    countPermutations(vec, next+1, count, triSum);
    swap(vec[i], vec[next]);
  }
}

int main(){
    int n;
    cin >> n;
    while(n--){
        int pSize, triSum;
        cin >> pSize >> triSum;

        int count = 0;
        vector<int> perm;
        for(int i = 2; i <= pSize; i++){
            perm.push_back(i);
        }
        countPermutations(perm, 0, count, triSum);
        printf("Permutation size:    %d\n", pSize);
        printf("Maximum triplet sum: %d\n", triSum);
        printf("Valid permutations:  %d\n", count/2);
        if(n!=0) cout << endl;
        }
}
