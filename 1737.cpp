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

Solution: https://oeis.org/A001187/b001187.txt
*/

#include <iostream>
#include <climits>
#include <vector>

using namespace std;

class BigInt {
public:
    string num;
    BigInt() { num = "0"; }
    BigInt(int i) { num = to_string(i); }
    BigInt(string s) {
        num = s;
        int i = 0;
        while(num[i] == '0') { i++; }
        num = num.substr(i);
    }
    BigInt operator=(const int i) {
        num = to_string(i);
        return *this;
    }
    BigInt operator=(const BigInt &b) {
        num = b.num;
        return *this;
    }
    friend BigInt operator+(const BigInt &a, const BigInt &b);
    friend BigInt operator-(const BigInt &a, const BigInt &b); 
    friend BigInt operator*(const BigInt &a, const BigInt &b);
};

BigInt operator+(const BigInt &a, const BigInt &b) {
    int n = a.num.size();
    int m = b.num.size();
    int c = 0;
    int sum = 0;
    string res;
    while (n > 0 || m > 0 || c > 0) {
        sum = c;
        if (n > 0) sum += (a.num[--n] - '0');
        if (m > 0) sum += (b.num[--m] - '0');
        c = sum / 10;
        res = (char)(sum % 10 + '0') + res;
    }
    return BigInt(res);
}

BigInt operator-(const BigInt &a, const BigInt &b) {
    int n = a.num.size();
    int m = b.num.size();
    int c = 0;
    int sum = 0;
    string res;
    while (n > 0 || m > 0 || c > 0) {
        sum = -c;
        if (n > 0) sum += (a.num[--n] - '0');
        if (m > 0) sum -= (b.num[--m] - '0');
        if (sum < 0) {
            sum += 10;
            c = 1;
        }
        else c = 0;
        res = (char)(sum + '0') + res;
    }
    return BigInt(res);
}
    
BigInt operator*(const BigInt &a, const BigInt &b) {
    int n = a.num.size();
    int m = b.num.size();
    string res(n + m, '0');
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            int sum = (res[i + j + 1] - '0') + (a.num[i] - '0') * (b.num[j] - '0');
            int c = sum / 10;
            if (c > 0) {
                res[i + j] = (char)(((int)(res[i + j] - '0') + c) + '0');
            }
            res[i + j + 1] = (char)(sum % 10 + '0');
        }
    }
    return BigInt(res);
}

class Solution {
public:
   Solution() {
       pow2 = vector<BigInt>(1250, BigInt());
       pow2[0] = 1;
       combt = vector<vector<BigInt>>(50, vector<BigInt>(50, BigInt()));
   }
   void numConnected(int n) {
       vector<BigInt> f(n + 1, BigInt());
       for (int i = 0; i <= 2; i++) {
           f[i] = 1;
           cout << i << " " << f[i].num << endl;
       }
       for (int i = 3; i <= n; i++) {
           BigInt sum = 0;
           for (int j = 1; j < i - 1; j++) {
               sum = sum + f[j] * comb(i - 1, j - 1) * getPow(combi(i - j, 2));
           }
           sum = sum + f[i - 1] * comb(i - 1, i - 2);
           f[i] = getPow(combi(i, 2)) - sum;
           cout << i << " " << f[i].num << endl;
       }
   }
   
   BigInt getPow(int index) {
       if (pow2[index].num != "0") return pow2[index];
       BigInt res;
       if (index % 2 == 0) res = getPow(index / 2) * getPow(index / 2);
       else res = getPow(index / 2) * getPow(index / 2) * 2;
       pow2[index] = res;
       return res;
   }
   
   int combi(int n, int k) {
       if (k == 0 || k == n) return 1;
       return combi(n - 1, k) + combi(n - 1, k - 1);
   }
   
   BigInt comb(int n, int k) {
       if (combt[n][k].num != "0") return combt[n][k];
       BigInt res;
       if (k == 0 || k == n) res = 1;
       else res = comb(n - 1, k) + comb(n - 1, k - 1);
       combt[n][k] = res;
       return res;
   }
private:
    vector<BigInt> pow2;
    vector<vector<BigInt>> combt;
};

int main() {
    // your code goes here
    Solution s;
    s.numConnected(50);
    return 0;
}
