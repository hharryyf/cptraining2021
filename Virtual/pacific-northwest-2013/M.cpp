#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 10000000000;
const int maxn = 71;

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

int a[maxn], b[maxn];

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        int N, M, A, B, i, j;
        mf.init();
        mf.src = 0, mf.target = maxn - 1;
        scanf("%d%d%d%d", &M, &N, &A, &B);
        for (i = 1; i <= N; ++i) {
            scanf("%d", &a[i]);
            mf.addedge(mf.src, i, a[i], 0);
        }

        /*
           s  [1-N]   [1-M]   [1-N]   t
        */

        for (i = 1; i <= N; ++i) {
            scanf("%d", &b[i]);
            mf.addedge(i + M + N, mf.target, b[i], 0);
        }

        for (i = 1; i <= M; ++i) {
            for (j = 1; j <= N; ++j) {
                int v;
                scanf("%d", &v);
                mf.addedge(j, i + N, INF, A * v);
                mf.addedge(i + N, j + N + M, INF, B * v);
            }
        }
        ll cost = 0;
        mf.mincostMaxflow(cost);
        cout << cost << endl;
    }
    return 0;
}