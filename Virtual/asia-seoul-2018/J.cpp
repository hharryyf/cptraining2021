/*
    Not my code, Ali coded it in contest
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 1e3+10 , mod = 1e9+7;

vector <int> g[N][20];

void solve(){
   int n , m , c , h , ml;
   cin >> n >> m >> c >> h >> ml;
   int mark[n];
   memset(mark , 0 , sizeof(mark));
   for(int i = 0 ; i < h ; i++){
      int x;
      cin >> x;
      mark[x] ^= 1;
   }
   for(int i = 0 ; i < ml ; i++){
      int x;
      cin >> x;
      mark[x] ^= 2;
   }
   bool reach[n][n];
   memset(reach , 0 , sizeof(reach));
   vector <pii> q;
   for(int i = 0 ; i < n ; i++){
      for(int j = 0 ; j < n ; j++){
         if(!(mark[i] & 1) && (mark[j] & 1)){
            reach[i][j] = true;
            q.push_back({i , j});
         }
      }
   }
   for(int i = 0 ; i < m ; i++){
      int u , v , c;
      cin >> u >> c >> v;
      c--;
      g[u][c].push_back(v);
   }
   while(q.size()){
      pii x = q.back();
      q.pop_back();
      int u = x.first , v = x.second;
      // cout << u << " " << v << endl;
      if((mark[u] & 2) && (mark[v] & 2)){
         cout << "YES";
         return;
      }
      for(int i = 0 ; i < c ; i++){
         // cout << i << endl;
         for(int p : g[u][i]){
            for(int pp : g[v][i]){
               // cout << p << " " << pp << " !!!" << endl;
               if(!reach[p][pp]){
                  reach[p][pp] = true;
                  q.push_back({p , pp});
               }
            }
         }
      }
   }
   cout << "NO";
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
