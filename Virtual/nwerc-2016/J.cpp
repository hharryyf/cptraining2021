#include <bits/stdc++.h>
#define MAX_SIZE 2222
typedef long long ll;
const ll INF = 1000000000000000ll;
using namespace std;

struct Maxflow {
    struct edge {
    	int from, to;
    	ll flow, capacity;
    };
    
    // start and end point
    int s, t;
    
    // list array
    vector<edge> edg;
    
    // g reference to the ith vertex's edges
    vector<int> g[MAX_SIZE];
    
    // distance array and visited array
    int dist[MAX_SIZE], visited[MAX_SIZE];
    int cur[MAX_SIZE];
    
    void init() {
    	edg.clear();
    	int i;
    	for (i = 0 ; i < MAX_SIZE; i++) {
    		g[i].clear();
    	}
    }
    
    void addedge(int from, int to, ll capacity) {
    	edge e1 = edge{from, to, 0ll, capacity};
    	edge e2 = edge{to, from, 0ll, 0ll};
    	edg.push_back(e1), edg.push_back(e2);
    	g[from].push_back((int) edg.size() - 2);
    	g[to].push_back((int) edg.size() - 1);
    }
    
    // construct the level graph
    bool bfs() {
    	memset(visited,0,sizeof(visited));
    	memset(dist,0,sizeof(dist));
    	queue<int> q;
    	q.push(s);
    	visited[s] = 1;
    	dist[s] = 0;
    	while (!q.empty()) {
    		int v = q.front();
    		q.pop();
    		for (int i = 0 ; i < (int) g[v].size(); i++) {
    			edge &e = edg[g[v][i]];
    			int nxt = e.to;
    			if (!visited[nxt] && e.capacity > e.flow) {
    				dist[nxt] = dist[v] + 1;
    				q.push(nxt);
    				visited[nxt] = 1;
    			}  
    		}
    	}
    	
    	return visited[t];
    }
    
    ll dfs(int x, ll cp) {
    	if (x == t || cp == 0) {
    		return cp;
    	}
    	
    	ll flow = 0, newflow;
    	for (int &y = cur[x]; y < (int) g[x].size(); y++) {
    		edge &e = edg[g[x][y]];
    		if (dist[x] + 1 == dist[e.to]) {
    			ll minn = min(cp, e.capacity - e.flow);
    			newflow = dfs(e.to, minn);
    			if (newflow > 0) {
    				e.flow += newflow;
    				edg[g[x][y] ^1].flow -= newflow;
    				flow += newflow;
    				cp -= newflow;
    				
    				if (cp == 0) {
    					break;
    				}
    			}
    		}
    	}
    	
    	return flow;
    }
    
    ll Dinic(){
        ll flow=0;
        while(bfs()){
            memset(cur,0,sizeof(cur));
            flow += dfs(s,INF);
        }
        return flow;
    }
};

Maxflow mf;

int req(int did) {
    return MAX_SIZE - did - 4;
}

int dlink(int did) {
    return MAX_SIZE - did - 64;
}

int encode(int qid, int did, int iout) {
    if (iout) {
        return (did * 31 + qid) * 2;
    } 
    return (did * 31 + qid) * 2 + 1; 
}

int c[31], sense[101];
int tol[31];

int main() {
    mf.s = MAX_SIZE - 2, mf.t = MAX_SIZE - 1;
    int i, N, Q, S;
    scanf("%d%d%d", &N, &Q, &S);
    for (i = 1; i <= S; ++i) {
        scanf("%d", &sense[i]);
    }
    for (i = 1; i <= Q; ++i) {
        scanf("%d", &c[i]);
    }

    ll ans = 0;
    for (i = 1; i <= N; ++i) {
        int v;
        scanf("%d", &v);
        mf.addedge(dlink(i), mf.t, v);
        memset(tol, 0, sizeof(tol));
        ll curr = 0;
        for (int j = 1; j <= S; ++j) {
            int cc;
            scanf("%d", &cc);
            tol[sense[j]] += cc;
            ans += cc;
            curr += cc;
        }
        mf.addedge(mf.s, req(i), curr);
        for (int j = 1; j <= Q; ++j) {
            mf.addedge(req(i), encode(j, i, 0), tol[j]);
            mf.addedge(encode(j, i, 1), dlink(i), c[j]);
            mf.addedge(encode(j, i, 0), encode(j, i, 1), c[j]);
            if (i != N)
                mf.addedge(encode(j, i, 1), encode(j, i  + 1, 0), c[j]);
        }
    }

    if (mf.Dinic() == ans) {
        printf("possible\n");
    } else {
        printf("impossible\n");
    }
    return 0;
}