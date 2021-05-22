#include <bits/stdc++.h>
#define MAX_SIZE 1000011
using namespace std;
typedef long long ll;
int parent[MAX_SIZE][20];
ll psum[MAX_SIZE][20];
vector<int> d;
int sz[MAX_SIZE];
bool visited[MAX_SIZE], instack[MAX_SIZE];
int N, K;
void init() {
    int i, j;
    d = vector<int>(MAX_SIZE, 0);
    for (i = 1; i < MAX_SIZE; ++i) {
        for (j = i; j < MAX_SIZE; j += i) {
            d[j]++;
        }
    }
}

ll query(int v) {
    ll ret = 0;
    // printf("%d %d\n", v, sz[v]);
    if (sz[v] < K) return -1; 
    int i, k = K;
    for (i = 19; i >= 0; --i) {
        if ((1 << i) <= k) {
            ret = ret + psum[v][i];
            v = parent[v][i];
            k = k - (1 << i);
        }
    }

    return ret;
}

void dfs(int v) {
    int i, j;
    visited[v] = 1;
    instack[v] = 1;
    d.push_back(v);
    int nv = parent[v][0];
    if (!visited[nv]) {
        dfs(nv);
    } else {
        if (instack[nv]) {
            for (i = 0; i < (int) d.size(); ++i) {
                if (d[i] == nv) {
                    for (j = 0 ; j < i; ++j) {
                        instack[d[j]] = false;
                        sz[d[j]] = (int) d.size() - j;
                    }
                    
                    for (j = i; j < (int) d.size(); ++j) {
                        sz[d[j]] = (int) d.size() - i;
                        instack[d[j]] = false;
                    }

                    d.clear();
                    break;
                }
            }
        } else {
            for (i = 0 ; i < (int) d.size(); ++i) {
                instack[d[i]] = false;
                sz[d[i]] = sz[nv] + (int) d.size() - i;
            }
            
            d.clear();
        }
    }
}

int main() {
    int i, j;
    scanf("%d%d", &N, &K);
    if (K == 1) {
        printf("0\n");
        return 0;
    }
    init();
    for (i = 1; i < N; ++i) {
        psum[i][0] = i;
        parent[i][0] = (i + d[i]) % N;
    }

    for (i = 1; i < 20; ++i) {
        for (j = 0; j < N; ++j) {
            parent[j][i] = parent[parent[j][i-1]][i-1];
            psum[j][i] = psum[j][i-1] + psum[parent[j][i-1]][i-1];
        }
    }
    
    for (i = 1; i < N; ++i) {
        if (!visited[i]) {
            d.clear();
            dfs(i);
        }
    }
    
    ll ans = -1;
    int st = -1;
    for (i = 1; i < N; ++i) {
        ll tmp = query(i);
        if (tmp != -1) {
            if (ans == -1) {
                ans = tmp;
                st = i;
            } else if (ans > tmp) {
                ans = tmp;
                st = i;
            }
        }
    }

    if (ans == -1) {
        printf("-1\n");
        return 0;
    }

    for (i = 0 ; i < K; ++i) {
        printf("%d ", st);
        st = parent[st][0];
    }
    printf("\n");
    return 0;
}