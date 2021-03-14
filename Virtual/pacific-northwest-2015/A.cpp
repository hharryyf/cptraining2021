#include <bits/stdc++.h>
using namespace std;
const int V = 2005;
const int E = (V+5)*(V+5);
const int N = V;
const int INF = INT_MAX/2;
int dist[N][N];
int p[N];
int directDist[N][N];
int flights[N][3];
int numIn[N];
int numOut[N];

// the index of the first outgoing edge for each vertex, initialised to -1
int start[V];
// fill(start, start + V, -1);
// if e is an outgoing edge from u, succ[e] is another one, or -1
// cap[e] is the capacity/weight of the e
// to[e] is the destination vertex of e
int succ[E], cap[E], to[E];

int edge_counter = 0;
void add_edge(int u, int v, int c) {
  // set the properties of the new edge
  cap[edge_counter] = c, to[edge_counter] = v;
  // insert this edge at the start of u's linked list of edges
  succ[edge_counter] = start[u];
  start[u] = edge_counter;
  ++edge_counter;

  cap[edge_counter] = 0, to[edge_counter] = u;
  // insert this edge at the start of u's linked list of edges
  succ[edge_counter] = start[v];
  start[v] = edge_counter;
  ++edge_counter;
}
// for (/* edge u -> v with capacity c in the original graph */) {
//   add_edge(u, v, c); // original
//   add_edge(v, u, 0); // residual edge
// }
// edges are in pairs so we can easily go between residuals & originals
int inv(int e) { return e ^ 1; }
// easily iterate through all of u's outgoing edges (~(-1) == 0)
// for (int e = start[u]; ~e; e = succ[e]) /* do something */;

// assumes the residual graph is constructed as in the previous section
// n = #nodes, s = source, t = sink
int n, s, t;
// stores dist from s.
int lvl[N];
// stores first non-useless child.
int nextchld[N];

// constructs the BFS tree.
// Returns if the sink is still reachable.
bool bfs() {
  for (int i = 0; i < n; i++) lvl[i] = -1;
  queue<int> q;
  q.push(s); lvl[s] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    nextchld[u] = start[u]; // reset nextchld
    for (int e = start[u]; ~e; e = succ[e]) {
      if (cap[e] > 0) {
        int nxt = to[e];
        if (lvl[nxt] != -1) continue; // already seen
        lvl[nxt] = lvl[u] + 1;
        q.push(nxt);
      }
    }
  }
  return lvl[t] != -1;
}

// Finds an augmenting path with up to cflow flow.
int aug(int u, int cflow) {
  if (u == t) return cflow; // base case.
  // Note the reference here! We will keep decreasing nextchld[u]
  // Till we find a child that we can flow through.
  for (int &i = nextchld[u]; i >= 0; i = succ[i]) {
    if (cap[i] > 0) {
      int nxt = to[i];
      // Ignore edges not in the BFS tree.
      if (lvl[nxt] != lvl[u] + 1) continue;
      int rf = aug(nxt, min(cflow, cap[i]));
      // Found a child we can flow through!
      if (rf > 0) {
        cap[i] -= rf;
        cap[i^1] += rf;
        return rf;
      }
    }
  }
  lvl[u]=-1;
  return 0;
}

int mf() {
  int tot = 0;
  while (bfs())
    for (int x = aug(s,INF); x; x = aug(s,INF)) tot+=x;
  return tot;
}

int main() {
    int n1,m;
    scanf("%d %d",&n1,&m);
    for (int i=0;i<n1;i++) {
        scanf("%d",&p[i]);
    }
    for (int i=0;i<n1;i++) {
        for (int j=0;j<n1;j++) {
            scanf("%d",&dist[i][j]);
            directDist[i][j] = dist[i][j]+p[j];
            dist[i][j] = directDist[i][j];
            if (i==j) {
                dist[i][j] = 0;
                directDist[i][j] = 0;
            }
        }
    }
    for (int i=0;i<n1;i++) {
        for (int u=0;u<n1;u++) {
            for (int v=0;v<n1;v++) {
                dist[u][v] = min(dist[u][v], dist[u][i]+dist[i][v]);
            }
        }
    }
    for (int i=0;i<m;i++) {
        scanf("%d %d %d",&flights[i][0],&flights[i][1],&flights[i][2]);
        flights[i][0]--;
        flights[i][1]--;
    }
    fill(start, start + V, -1);
    for (int i=0;i<m;i++) {
        add_edge(i,i+m,INT_MAX/2);
        numIn[i+m]++;
        numOut[i]++;
    }
    for (int i=0;i<m;i++) {
        for (int j=0;j<m;j++) {
            if (i==j) {continue;}
            if (flights[i][2]+directDist[flights[i][0]][flights[i][1]]+dist[flights[i][1]][flights[j][0]] <= flights[j][2]) {
                add_edge(i+m,j,INT_MAX/2);
                // numIn[j]++;
                // numOut[i+m]++;
            }
        }
    }
    s = 2*m;
    t = s+1;
    for (int i=0;i<m;i++) {
        add_edge(s,i,INT_MAX/2);
        add_edge(i+m,t,INT_MAX/2);
    }
    s = t+1;
    add_edge(t,s,INT_MAX/2);
    s += 1;
    t = s+1;
    for (int i=0;i<2*m;i++) {
        add_edge(s,i,numIn[i]);
        add_edge(i,t,numOut[i]);
    }
    add_edge(s-1,s-3,0);
    int lo = 0;
    int hi = 1000;
    int bestSoFar = -1;
    n = t+1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        cap[edge_counter-2] = mid;
        if (mf() == m) {
            bestSoFar = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
        for (int i=0;i<edge_counter;i+=2) {
            cap[i] += cap[i+1];
            cap[i+1] = 0;
        }
        // fill(start, start + V, -1);
    }
    printf("%d\n",bestSoFar);
    return 0;
}