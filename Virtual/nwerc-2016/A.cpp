/*
    This is not my code, Ali implemented it.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 41 , M = 401 , mod = 1e9+7;

int n , m , dp[N][N][M][10] , tp[N][N][M][10] , ps[N][N][M][10];
string s[N];

int go(int l , int r , int dig , int mn){
   if(dig == m){
      return 0;
   }
   if(dp[l][r][dig][mn] != -1){
      return dp[l][r][dig][mn];
   }
   int val1 = mod;
   if(mn != 9){
      val1 = go(l , r , dig , mn + 1);
   }
   int val2 = mod;
   int add = 0;
   int pos = -1;
   for(int i = l ; i <= r ; i++){
      if(s[i][dig] - '0' != mn){
         add++;
      }
      int cur = add + go(l , i , dig + 1 , 0);
      if(i == r || mn < 9){
         if(i < r){
            cur += go(i + 1 , r , dig , mn + 1);
         }
         if(cur < val2){
            pos = i;
         }
         val2 = min(val2 , cur);
      }
   }
   if(val1 < val2){
      tp[l][r][dig][mn] = 0;
   }
   else{
      tp[l][r][dig][mn] = 1;
      ps[l][r][dig][mn] = pos;
   }
   dp[l][r][dig][mn] = min(val1 , val2);
   return dp[l][r][dig][mn];
}

void gen(int l , int r , int dig , int mn){
   if(dig == m){
      return;
   }
   if(tp[l][r][dig][mn] == 0){
      gen(l , r , dig , mn + 1);
   }
   else{
      for(int i = l ; i <= ps[l][r][dig][mn] ; i++){
         s[i][dig] = char('0' + mn);
      }
      if(ps[l][r][dig][mn] < r){
         gen(ps[l][r][dig][mn] + 1 , r , dig , mn + 1);
      }
      gen(l , ps[l][r][dig][mn] , dig + 1 , 0);
   }
}

void solve(){
   memset(dp , -1 , sizeof(dp));
   cin >> n >> m;
   for(int i = 0 ; i < n ; i++){
      cin >> s[i];
   }
   go(0 , n - 1 , 0 , 0);
   gen(0 , n - 1 , 0 , 0);
   for(int i = 0 ; i < n ; i++){
      cout << s[i] << "\n";
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
