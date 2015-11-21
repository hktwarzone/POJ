/*
Connected Graph

An undirected graph is a set V of vertices and a set of E∈{V*V} edges.An undirected graph is connected if and only i
f for every pair (u,v) of vertices,u is reachable from v. 
You are to write a program that tries to calculate the number of different connected undirected graph with n vertices. 

Sample Input

1
2
3
4
0
Sample Output

1
1
4
38
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
   long long numConnected(int n) {
       vector<long long> f;
       f.push_back(1);
       f.push_back(1);
       f.push_back(1);
       for (int i = 3; i <= n; i++) {
           long long sum = 0;
           for (int j = 1; j < i - 1; j++) {
               sum += comb(i - 1, j - 1) * f[j] * pow(2, comb(i - j, 2));
           }
           sum += comb(i - 1, i - 2) * f[i - 1];
           f.push_back(pow(2, comb(i, 2)) - sum);
       }
       return f[n];
   }
   long long pow(int n, int k) {
       if (k == 0) return 1;
       if (k == 1) return n;
       if (k % 2 == 0) return pow(n, k / 2) * pow(n, k / 2);
       return pow(n, k / 2) * pow(n, k / 2) * n;
   }

   long long comb(int n, int k) {
       if (k == 0) return 1;
       long long top = 1;
       long long down = 1;
       while (k > 0) {
           top *= n--;
           down *= k--;
       }
       return (top / down);
   }
};

int main() {
	// your code goes here
	Solution s;
    for (int k = 1; k <= 10; k++) {
        cout << s.numConnected(k) << endl;
    }
	return 0;
}
