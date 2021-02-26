#include <bits/stdc++.h>

#define MAX_SIZE 11111
typedef long long ll;
#define INF 100000000000
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
int bad[MAX_SIZE];

int encode(int x, int y, int z) {
    return x * 100 + y * 10 + z;
}


int main() {
    int T, i, j, k;
    scanf("%d", &T);
    while (T-- > 0) {
        mf.init();
        memset(bad, 0, sizeof(bad));
        int F, Q;
        scanf("%d", &F);
        Q = F;
        mf.s = MAX_SIZE - 2, mf.t = MAX_SIZE - 1;
        while (Q-- > 0) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            bad[encode(x, y, z)] = 1;
        } 

        for (i = 0; i < 1000; ++i) {
            if (!bad[i]) {
                mf.addedge(i, mf.t, 6);
            }
        }

        int edg = 0;
        for (i = 0 ; i < 10; ++i) {
            for (j = 0 ; j < 10; ++j) {
                for (k = 0 ; k < 10; ++k) {
                    if (i < 9) {
                        mf.addedge(encode(i, j, k) + 1000, encode(i, j, k), INF);
                        mf.addedge(encode(i, j, k) + 1000, encode(i+1, j, k), INF);
                        mf.addedge(mf.s, encode(i, j, k) + 1000, 2);
                        edg += 2;
                    }

                    if (j < 9) {
                        mf.addedge(encode(i, j, k) + 2000, encode(i, j, k), INF);
                        mf.addedge(encode(i, j, k) + 2000, encode(i, j+1, k), INF);
                        mf.addedge(mf.s, encode(i, j, k) + 2000, 2);
                        edg += 2;
                    }

                    if (k < 9) {
                        mf.addedge(encode(i, j, k) + 3000, encode(i, j, k), INF);
                        mf.addedge(encode(i, j, k) + 3000, encode(i, j, k+1), INF);
                        mf.addedge(mf.s, encode(i, j, k) + 3000, 2);
                        edg += 2;
                    }
                }
            }
        }

        auto ret = mf.Dinic();
        printf("%I64d\n", 1ll * 6 * F - (edg - ret));
    }
    return 0;
}