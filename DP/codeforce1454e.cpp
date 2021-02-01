#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

int N;

int cmpid[MAX_SIZE];
vector<int> g[MAX_SIZE];
int low[MAX_SIZE];
int visited[MAX_SIZE];
int instack[MAX_SIZE];
int sz[MAX_SIZE];
stack<int> s;
int k = 1;

void tarjan(int v, int pre) {
	 visited[v] = k++;
	 low[v] = visited[v];
	 s.push(v);
	 instack[v] = 1;
	 for (auto nv : g[v]) {
	 	 if (nv != pre) {
		 	if (!visited[nv]) {
			    tarjan(nv, v);
			    low[v] = min(low[v], low[nv]);
	        } else if (instack[nv]) {
			    low[v] = min(low[v], visited[nv]);
			} 
         }
	 }
	 
	 if (low[v] == visited[v]) {
	 	while (s.top() != v) {
	        cmpid[s.top()] = v;
			sz[v]++;
            instack[s.top()] = 0;
			s.pop(); 
	    }
        sz[v]++;
	    cmpid[s.top()] = v;
		instack[s.top()] = 0;
		s.pop();
	 }
}

void init() {
    k = 1;
    for (int i = 1; i <= N; ++i) {
        visited[i] = low[i] = cmpid[i] = sz[i] = 0;
        g[i].clear();
    }
    while (!s.empty()) s.pop();
}

int cnt = 0;

void dfs(int v, int pre) {
    cnt++;
    for (auto nv : g[v]) {
        if (sz[cmpid[nv]] == 1 && nv != pre) {
            dfs(nv, v);
        }
    }
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        init();
        for (i = 0 ; i < N; ++i) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }

        tarjan(1, 0);
        long long ans = 1ll * N * (N - 1);
        for (i = 1; i <= N; ++i) {
            if (sz[cmpid[i]] > 1) {
                cnt = 0;
                dfs(i, 0);
                ans = ans - 1ll * (cnt - 1) * cnt / 2;
            }
        }

        printf("%I64d\n", ans);
    }
    return 0;
}