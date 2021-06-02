/*
    code after contest
*/
#include <bits/stdc++.h>
#define MAX_SIZE 524292
// #define DEBUG
typedef int ll;
using namespace std;


struct edge {
	int from, to;
	ll w;
	bool operator < (edge other) const {
		return w < other.w;
	}
};

vector<int> t[MAX_SIZE];
int n, m, q;
int f[MAX_SIZE], c[MAX_SIZE], s[MAX_SIZE];
int parent[MAX_SIZE][19], sol[MAX_SIZE];
ll val[MAX_SIZE];
int visited[MAX_SIZE];
edge edg[MAX_SIZE];

struct freqTable {
    map<int, set<int>> freTonum;
    map<int, int> numTofreq;
    int sz;
    void update(int v) {
        //printf("update %d\n", v);
        if (numTofreq.empty()) {
            numTofreq[v] = 1;
            freTonum[1].insert(v);
        } else {
            int fq = numTofreq[v];
            freTonum[fq].erase(v);
            if (freTonum[fq].empty()) freTonum.erase(fq);
            fq++;
            freTonum[fq].insert(v);
            numTofreq[v] = fq;
        }
        sz++;
        //cout << "finish update" << endl;
    }

    void clear() {
        freTonum.clear();
        numTofreq.clear();
        this->sz = 0;
    }

    int getans() {
        //cout << "get ans" << endl;
        auto &it = freTonum.rbegin()->second;
        int ret = *it.begin();
        //cout << "the answer is " << ret << endl;
        return ret;
    }
};

freqTable mp[MAX_SIZE];

int find(int x) {
	if (x == f[x]) return x;
	return f[x] = find(f[x]);
}

int find2(int x) {
    if (x == s[x]) return x;
	return s[x] = find2(s[x]);
}

void merge(int u, int v) {
    int a = find2(u), b = find2(v);
    if (a == b) return;
    if (mp[a].sz > mp[b].sz) {
        swap(a, b);
    }

    for (auto &iter : mp[a].freTonum) {
        for (auto nv : iter.second) {
            for (int pp = 0; pp < iter.first; ++pp) {
                mp[b].update(nv);
            }
        }
    }

    mp[a].clear();
    s[a] = b;
    // cout << "exit merge" << endl;
}

void dfs(int v) {
	int i;
    visited[v] = 1;
    for (i = 1; i <= 18; ++i) {
		parent[v][i] = parent[parent[v][i-1]][i-1];
    }
	
	for (auto nv : t[v]) {
		dfs(nv);
    }

    if (v <= n) {
        mp[v].update(c[v]);
        //cout << "set " << v << " insert " << c[v] << endl;
    } else {
        for (auto nv : t[v]) {
            merge(nv, v);
        }
    }

    //cout << "get answer for set " << find2(v) << endl;
    sol[v] = mp[find2(v)].getans();
    //printf("solution to %d = %d\n", v, sol[v]);
}

void kruskal_modification() {
	int i;
	int idx = n + 1;
    memset(visited, 0, sizeof(visited));
	sort(edg + 1, edg + m +	1);
	for (i = 1; i <= m; ++i) {
		int x = find(edg[i].from), y = find(edg[i].to);
		if (x == y) continue;
		f[x] = idx, f[y] = idx;
		parent[x][0] = idx, parent[y][0] = idx;
		t[idx].push_back(x);
		t[idx].push_back(y);
        //printf("ae %d %d\n", idx, x);
        //printf("ae %d %d\n", idx, y);
        val[idx] = edg[i].w;
		idx++;
	}
	for (i = idx - 1; i >= 1; --i) {
	    if (!visited[i]) {
            dfs(i);
        }
    }
}

int query(int v, int w) {
    //printf("query %d %d\n", v, w);
    for (int i = 18; i >= 0; --i) {
        if (parent[v][i] != 0) {
            if (val[parent[v][i]] <= w) {
                v = parent[v][i];
            }        
        }
    }
    //printf("weight = w get %d\n", v);
    //printf("final vertex= %d\n", v);
    return v;
}

void solve() {
    int i, ans = 0;
    for (i = 0 ; i < MAX_SIZE; ++i) {
        c[i] = val[i] = 0;
        f[i] = i;
        s[i] = i;
        t[i].clear();
        mp[i].clear();
    }

    memset(parent, 0, sizeof(parent));
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) scanf("%d", &c[i]);
    for (i = 1; i <= m; ++i) {
		scanf("%d%d%d", &edg[i].from, &edg[i].to, &edg[i].w);
	}
	
	
	kruskal_modification();
    //cout << "to query" << endl;
    scanf("%d", &q);
    while (q-- > 0) {
        int x, w;
        scanf("%d%d", &x, &w);
        #ifndef DEBUG
        x ^= ans, w ^= ans;
        #endif
        int idx = query(x, w);
        ans = sol[idx];
        printf("%d\n", ans);
    }
}

int main() {
	int i;
	int T;
    scanf("%d", &T);
    for (i = 1; i <= T; ++i) {
        printf("Case #%d:\n", i);
        solve();
    }
	return 0;
}
