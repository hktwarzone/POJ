/*
An old Stone Game

There is an old stone game.At the beginning of the game the player picks n(1<=n<=50000) piles of stones in a line. 
The goal is to merge the stones in one pile observing the following rules: 
At each step of the game,the player can merge two adjoining piles to a new pile.The score is the number of stones 
in the new pile. 
You are to write a program to determine the minimum of the total score. 

Sample Input

1
100
3
3 4 3
4
1 1 1 1
0
Sample Output

0
17
8

*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int stoneGame(vector<int>& stones) {
        int n = stones.size();
        vector<vector<int>> partial(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            partial[i][i] = stones[i];
            for (int j = i + 1; j < n; j++) {
                partial[i][j] = partial[i][j - 1] + stones[j];
            }
        }
        vector<vector<int>> f(n, vector<int>(n, 0));
        for (int gap = 1; gap < n; gap++) {
            for (int i = 0; i + gap < n; i++) {
                int j = i + gap;
                f[i][j] = INT_MAX;
                for (int k = i; k < j; k++) {
                    f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + partial[i][j]);
                }
            }
        }
        return f[0][n - 1];
    }
};

int main() {
	// your code goes here
	vector<int> stones = {1,1,1,1};
	Solution s;
	cout << s.stoneGame(stones) << endl;
	return 0;
}
