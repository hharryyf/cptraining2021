#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 2e5+10 , mod = 1e9+7;

int n , m , k , dis[N][3];
vector <int> g[N][3];

void bfs(queue <int> q , int id){
   while(q.size()){
      int v = q.front();
      q.pop();
      for(int u : g[v][id]){
         if(dis[u][id] > dis[v][id] + 1){
            dis[u][id] = dis[v][id] + 1;
            q.push(u);
         }
      }
   }
}

void solve(){
   memset(dis , 63 , sizeof(dis));
   cin >> n >> m >> k;
   queue <int> q1 , q2;
   for(int i = 0 ; i < m ; i++){
      int x;
      cin >> x;
      x--;
      q1.push(x);
      dis[x][0] = 0;
   }
   for(int i = 0 ; i < k ; i++){
      int x;
      cin >> x;
      x--;
      q2.push(x);
      dis[x][1] = 0;
   }
   for(int i = 0 ; i < n ; i++){
      int t;
      cin >> t;
      while(t--){
         int v;
         cin >> v;
         v--;
         g[i][2].push_back(v);
         g[v][0].push_back(i);
         g[v][1].push_back(i);
      }
   }
   bfs(q1 , 0);
   bfs(q2 , 1);
   queue <int> q3;
   dis[0][2] = 0;
   q3.push(0);
   bfs(q3 , 2);
   int ans = mod;
   for(int i = 0 ; i < n ; i++){
      // cout << i << " " << dis[i][0] << " " << dis[i][1] << " " << dis[i][2] << endl;
      ans = min(1ll * ans , 1ll * dis[i][0] + dis[i][1] + dis[i][2]);
   }
   if(ans >= mod){
      cout << "impossible";
   }
   else{
      cout << ans;
   }
}

int32_t main(){
   ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   int t = 1;
   //cin >> t;
   int cur = 1;
   while(t--){
      //cout << "Case #" << cur++ << ": ";
      solve();
   }
   return 0;
}
