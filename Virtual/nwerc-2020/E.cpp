#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;
/*
   Not my code, impelmented by Ali.
*/
const int N = 2e5+10 , mod = 1e9+7;

void solve(){
   int n;
   cin >> n;
   int ax , ay;
   cin >> ax >> ay;
   int bx , by;
   cin >> bx >> by;
   int x[n] , y[n];
   for(int i = 0 ; i < n ; i++){
      cin >> x[i] >> y[i];
   }

   map <pii , bool> mp;
   for(int i = 0 ; i < n ; i++){
      int xx = bx - x[i] , yy = by - y[i];
      if(xx >= 1 && xx <= n && yy >= 1 && yy <= n){
         mp[{xx, yy}] = true;
      }
   }
   for(int i = 0 ; i < n ; i++){
      int xx = ax + x[i] , yy = ay + y[i];
      if(xx == bx && yy == by){
         cout << "Alice wins\n";
         return;
      }
      if(xx >= 1 && xx <= n && yy >= 1 && yy <= n){
         if(mp[{xx, yy}]){
            cout << "Alice wins\n";
            return;
         }
      }
   }

   if(n <= 500){
      bool mark[n + 1][n + 1];
      memset(mark , 0 , sizeof(mark));
      for(int i = 0 ; i < n ; i++){
         int xx = bx + x[i] , yy = by + y[i];
         if(xx >= 1 && xx <= n && yy >= 1 && yy <= n){
            mark[xx][yy] = true;
         }
      }
      mark[bx][by] = true;
      for(int i = 1 ; i <= n ; i++){
         for(int j = 1 ; j <= n ; j++){
            if(mark[i][j]){
               continue;
            }
            bool bad = false;
            for(int k = 0 ; k < n ; k++){
               int xx = i - x[k] , yy = j - y[k];
               if(xx >= 1 && xx <= n && yy >= 1 && yy <= n){
                  if(mark[xx][yy]){
                     bad = true;
                     break;
                  }
               }
            }
            if(!bad){
               cout << "tie " << i << " " << j << "\n";
               return;
            }
         }
      }
      cout << "Bob wins\n";
      return;
   }
   mp.clear();
   for(int i = 0 ; i < n ; i++){
      int xx = bx + x[i] , yy = by + y[i];
      if(xx >= 1 && xx <= n && yy >= 1 && yy <= n){
         mp[{xx, yy}] = true;
      }
   }
   mp[{bx, by}] = true;
   while(true){
      int i = 1ll * rand() * rand() % n + 1;
      int j = 1ll * rand() * rand() % n + 1;
      if(mp.find(make_pair(i , j)) != mp.end()){
         continue;
      }
      bool bad = false;
      for(int k = 0 ; k < n ; k++){
         int xx = i - x[k] , yy = j - y[k];
         if(xx >= 1 && xx <= n && yy >= 1 && yy <= n){
            if(mp.find(make_pair(xx , yy)) != mp.end()){
               bad = true;
               break;
            }
         }
      }
      if(!bad){
         cout << "tie " << i << " " << j << "\n";
         return;
      }
   }
}

int32_t main(){
   ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   int t = 1;
   //cin >> t;
   while(t--){
      solve();
   }
   return 0;
}
