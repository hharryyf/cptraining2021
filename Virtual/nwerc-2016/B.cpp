/*
   Not my code, Ali coded it during the contest
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 2e5+10 , mod = 1e9+7;

vector <int> g[N] , h[N] , G[N] , vers[N] , topol;
bool mark[N];
int comp[N] , dp[N] , dp2[N] , cmp = 0 , id[N] , len[N][6][6];
map <pii , bool> mp;

void dfs_topol(int v){
   mark[v] = true;
   for(int u : g[v]){
      if(!mark[u]){
         dfs_topol(u);
      }
   }
   topol.push_back(v);
}

void dfs_cmp(int v){
   mark[v] = true;
   comp[v] = cmp;
   vers[cmp].push_back(v);
   for(int u : h[v]){
      if(!mark[u]){
         dfs_cmp(u);
      }
   }
}

void dfs(int v){
   mark[v] = true;
   for(int u : G[v]){
      if(!mark[u]){
         dfs(u);
      }
   }
   topol.push_back(v);
}

void solve(){
   int n , m;
   cin >> n >> m;
   for(int i = 0 ; i < m ; i++){
      int u , v;
      cin >> u >> v;
      u--; v--;
      g[u].push_back(v);
      h[v].push_back(u);
      mp[{u , v}] = true;
   }
   for(int i = 0 ; i < n ; i++){
      if(!mark[i]){
         dfs_topol(i);
      }
   }
   reverse(topol.begin() , topol.end());
   memset(mark , 0 , sizeof(mark));
   for(int v : topol){
      if(!mark[v]){
         dfs_cmp(v);
         cmp++;
      }
   }
   for(int i = 0 ; i < cmp ; i++){
      vector <int> v;
      int fac = 1 , cur = 1;
      for(int u : vers[i]){
         id[u] = cur - 1;
         fac *= cur;
         cur++;
         v.push_back(u);
      }
      int sz = vers[i].size();
      for(int j = 0 ; j < fac ; j++){
         int lst = 1;
         while(lst < sz && mp[{v[lst - 1] , v[lst]}]){
            lst++;
            len[i][id[v[0]]][id[v[lst - 1]]] = max(len[i][id[v[0]]][id[v[lst - 1]]] , lst - 1);
         }
         next_permutation(v.begin() , v.end());
      }
   }
   for(int i = 0 ; i < n ; i++){
      for(int v : g[i]){
         if(comp[i] != comp[v]){
            G[comp[i]].push_back(comp[v]);
         }
      }
   }
   topol.clear();
   memset(mark , 0 , sizeof(mark));
   for(int i = 0 ; i < cmp ; i++){
      if(!mark[i]){
         dfs(i);
      }
   }
   reverse(topol.begin() , topol.end());
   for(int c : topol){
      int sz = vers[c].size();
      for(int i = 0 ; i < sz ; i++){
         for(int j = 0 ; j < sz ; j++){
            dp2[vers[c][j]] = max(dp2[vers[c][j]] , dp[vers[c][i]] + len[c][i][j]);
         }
      }
      for(int v : vers[c]){
         dp[v] = max(dp[v] , dp2[v]);
         for(int u : g[v]){
            if(comp[u] != comp[v]){
               dp[u] = max(dp[u] , dp[v] + 1);
            }
         }
      }
   }
   int ans = 0;
   for(int i = 0 ; i < n ; i++){
      ans = max(ans , dp[i]);
   }
   cout << ans + 1;
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
