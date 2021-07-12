/*
    Not my code, Ali coded it in contest
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 5e2+10 , mod = 1e9+7;

int d[N][N] , dis[N][N];

void solve(){
   int m , n;
   cin >> m >> n;
   for(int i = 0 ; i < n ; i++){
      vector <pii> v;
      for(int j = 0 ; j < m ; j++){
         int x;
         cin >> x;
         if(x == 0){
            x = mod;
         }
         v.push_back({x , j});
      }
      sort(v.begin() , v.end());
      for(int j = 0 ; j < m ; j++){
         int k = j;
         while(k < m && v[j].first == v[k].first){
            k++;
         }
         for(int p = j ; p < k ; p++){
            for(int q = k ; q < m ; q++){
               d[v[p].second][v[q].second]++;
            }
         }
         j = k - 1;
      }
   }
   for(int i = 0 ; i < m ; i++){
      for(int j = 0 ; j < m ; j++){
         if(i == j){
            continue;
         }
         // cout << i << " " << j << " " << d[i][j] << endl;
         if(d[i][j] > d[j][i]){
            dis[i][j] = d[i][j];
         }
      }
   }
   for(int i = 0 ; i < m ; i++){
      for(int j = 0 ; j < m ; j++){
         for(int k = 0 ; k < m ; k++){
            dis[j][k] = max(dis[j][k] , min(dis[j][i] , dis[i][k]));
         }
      }
   }
   for(int i = 0 ; i < m ; i++){
      int num = 0;
      for(int j = 0 ; j < m ; j++){
         if(i == j){
            continue;
         }
         if(dis[i][j] >= dis[j][i]){
            num++;
         }
         // cout << i << " " << j << " " << dis[i][j] << " " << dis[j][i] << endl;
      }
      if(num == m - 1){
         cout << i + 1 << " ";
      }
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
