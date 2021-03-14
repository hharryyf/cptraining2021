#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 2e5+10 , mod = 1e9+7;

void solve(){
   string s;
   cin >> s;
   int n = s.length();
   ll dp[n + 1][10] , dp2[n + 1][10];
   for(int i = 0 ; i < 10 ; i++){
      dp[1][i] = 0;
      dp2[1][i] = 1;
   }
   for(int i = 2 ; i <= n ; i++){
      for(int j = 0 ; j <= 9 ; j++){
         dp[i][j] = dp2[i][j] = 0;
         for(int k = 0 ; k <= 9 ; k++){
            if(j >= k){
               dp2[i][j] += dp2[i - 1][k];
            }
            if(j <= k){
               dp[i][j] += dp[i - 1][k];
               if(k > j){
                  dp[i][j] += dp2[i - 1][k];
               }
            }
         }
      }
   }
   ll ans = 0;
   bool done = false;
   for(int i = 0 ; i < n ; i++){
      for(int j = 0 ; j < s[i] - '0' ; j++){
         if(!done){
            if(i == 0 || j >= (s[i - 1] - '0')){
               ans += dp[n - i][j] + dp2[n - i][j];
            }
            else{
               ans += dp2[n - i][j];
            }
         }
         else{
            ans += dp2[n - i][j];
         }
      }
      if(i == 0){
         continue;
      }
      if(s[i] > s[i - 1] && done){
         cout << "-1\n";
         return;
      }
      if(s[i] < s[i - 1]){
         done = true;
      }
   }
   cout << ans << "\n";
}

int32_t main(){
   ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   int t = 1;
   cin >> t;
   while(t--){
      solve();
   }
   return 0;
}
