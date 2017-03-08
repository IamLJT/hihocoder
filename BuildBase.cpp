#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
int N, int M, int K, int T;
vector<ll> a, vector<ll> b;

ll min(ll x, ll y) { if (x < y)return x; else return y; };

ll mincost(int c)
{
	vector<ll> f(K, INT_MAX);
	vector<ll> B_(M, 0);
	f[0] = 0;
	for (int i = 0; i < M; i++){
		B_[i] = b[i] / (pow(T, c - 1));
		for (int j = 0; j < K; j++) {
			int x = j + B_[i];
			f[min(x, K)] = min(f[min(K, x)], f[j] + a[i]);
		}
	}
	return f[K];
}