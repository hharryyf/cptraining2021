#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 10000000000;
const int maxn = 2011;

struct Edge {
    int from, to;
	ll cap, flow, cost;
    Edge(int u, int v, ll c, ll f, ll w):from(u),to(v),cap(c),flow(f),cost(w)
    {}
};

struct MCMF {
    int n, m;
    int src, target;
    vector<Edge> edges; 
    vector<int> G[maxn]; 
    int inq[maxn]; 
    ll d[maxn]; 
    int p[maxn]; 
    ll a[maxn]; 

    MCMF() {}

    void init(int n=maxn) {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }

    void addedge(int from, int to, ll cap, ll cost) {
        edges.push_back(Edge(from, to, cap, 0, cost)); 
        edges.push_back(Edge(to, from, 0, 0, -cost)); 
        m = edges.size();
        G[from].push_back(m-2); 
        G[to].push_back(m-1);
    }

    bool SPFA(int s, int t, ll &flow, ll &cost) {
        for(int i = 0; i < n; i++) d[i] = INF;
        memset(inq, 0, sizeof(inq));
        d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

        queue<int> Q;
        Q.push(s);
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            inq[u] = 0;
            for(int i = 0; i < (int) G[u].size(); i++) {
                Edge& e = edges[G[u][i]];
                if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u], e.cap - e.flow);
                    if(!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
                }
            }
        }
        if(d[t] == INF) return false; 
        flow += a[t]; 
        cost += d[t] * a[t]; 
        for(int u = t; u != s; u = edges[p[u]].from) {
        		edges[p[u]].flow += a[t]; 
        		edges[p[u]^1].flow -= a[t];
		}
        return true;
    }

    ll mincostMaxflow(ll &cost) {
        ll flow = 0; 
		cost = 0;
        while(SPFA(src, target, flow, cost));
        return flow;
    }
};

MCMF mf;
int N, M;
int hor[32][32], ver[32][32], ok[32][32];

int in(int x, int y) {
    return (x * M + y) * 2;
}

int out(int x, int y) {
    return (x * M + y) * 2 + 1;
}

void solve() {
    int i, j;
    mf.init();
    mf.src = 0, mf.target = maxn - 1;
    memset(ok, 0, sizeof(ok));
    scanf("%d%d", &N, &M);
    for (i = 1; i <= N; ++i) {
        for (j = 1; j < M; ++j) {
            scanf("%d", &hor[i][j]);
            if ((i + j) & 1) {
                mf.addedge(in(i, j + 1), out(i, j), 1, -hor[i][j]);
            } else {
                mf.addedge(in(i, j), out(i, j + 1), 1, -hor[i][j]);
            }
        }
    }

    for (i = 1; i < N; ++i) {
        for (j = 1; j <= M; ++j) {
            scanf("%d", &ver[i][j]);
            if ((i + j) & 1) {
                mf.addedge(in(i, j), out(i + 1, j), 1, -ver[i][j]);
            } else {
                mf.addedge(in(i + 1, j), out(i, j), 1, -ver[i][j]);
            }
        }
    }
    int K;
    scanf("%d", &K);    
    while (K-- > 0) {
        int x, y;
        scanf("%d%d", &x, &y);
        ok[x][y] = 1;
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= M; ++j) {
            mf.addedge(mf.src, in(i, j), 1, 0);
            if (!ok[i][j]) {
                mf.addedge(in(i, j), out(i, j), 1, 0);
            }
            mf.addedge(out(i, j), mf.target, 1, 0);
        }
    }

    ll cost = 0;
    if (mf.mincostMaxflow(cost) != N * M) {
        printf("Impossible\n");
    } else {
        printf("%lld\n", -cost);
    }
}

int main() {
    int T, t;
    scanf("%d", &T);
    for (t = 1; t <= T; ++t) {
        printf("Case #%d: ", t);
        solve();
    }
    return 0;
}