#include <bits/stdc++.h>
using namespace std;
/*
    Not my code, implemented by Ali
*/
typedef long long ll;
typedef pair <long long , long long> pii;
typedef long double ld;
 
const long long N = 1e5+1 , mod = 1e9+7;
 
ll dp[N];
 
void solve(){
   long long n , q;
   cin >> n >> q;
   long long a[n + 1];
   for(long long i = 0 ; i < N ; i++){
      dp[i] = 1ll * mod * mod;
   }
   dp[0] = 0;
   for(long long i = 1 ; i <= n ; i++){
      cin >> a[i];
      dp[i] = a[i];
   }
   for(long long i = n + 1 ; i < N ; i++){
      for(long long j = 1 ; j <= min(i , n) ; j++){
         dp[i] = min(dp[i] , dp[i - j] + a[j]);
      }
      //cout << i << " " << dp[i] << " " << used[i] << endl;
   }
   for(long long i = 0 ; i < q ; i++){
      long long x;
      cin >> x;
      ll ans = 1ll * mod * mod;
      for(long long j = 1 ; j <= n ; j++){
         long long need = max(0LL , (x - (N - 1)) / j);
         while(x - need * j >= N){
            need++;
         }
         ll val = 1ll * need * a[j];
         int y = x - 1LL * need * j;
         val += dp[y];
         ans = min(ans , val);
         //cout << ans << " " << x << endl;
      }
      cout << ans << "\n";
   }
}
 
int32_t main(){
   ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   long long t = 1;
   //cin >> t;
   while(t--){
      solve();
   }
   return 0;
}