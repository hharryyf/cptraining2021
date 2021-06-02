/*
   Coded by Ali, not my code
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 2e3+10 , mod = 1e9+7;

int pw(int x , int y){
   int ret = 1;
   for( ; y ; y /= 2){
      if(y & 1){
         ret = 1ll * ret * x % mod;
      }
      x = 1ll * x * x % mod;
   }
   return ret;
}

void solve(){
   int n , m , k;
   cin >> n >> m >> k;
   int val = 0;
   for(int i = 2 ; i <= k ; i++){
      val += pw(i - 1 , n + m - 2);
      if(val >= mod){
         val -= mod;
      }
      //cout << val << endl;
   }
   val = 1ll * val * pw(k , n * m - (n + m - 1)) % mod;
   int ans = 1ll * val * n * m % mod;
   //cout << ans << endl;
   ans += pw(k , n * m);
   //cout << ans << endl;
   if(ans >= mod){
      ans -= mod;
   }
   cout << ans << "\n";
}

int32_t main(){
   ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   int t = 1;
   int cur = 1;
   cin >> t;
   while(t--){
      cout << "Case #" << cur++ << ": ";
      solve();
   }
   return 0;
}
