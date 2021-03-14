#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 1e7+10 , mod = 1e9+7;
const ld eps = 1e-18;

ld dp[N];
int e , es , ef;

bool check(ld m){
   int cur = e;
   ld len = 225;
   while(cur > 0){
      int turn = (cur + es - 1) / es;
      if(m >= (ld)(len - 25) / (turn)){
         return true;
      }
      if(len - 25 <= m){
         return true;
      }
      len -= m / dp[max(0 , cur - es)];
      cur = max(0 , cur - ef);
   }
   return len <= m;
}

void solve(){
   cin >> e >> es >> ef;
   dp[0] = 1;
   for(int i = 1 ; i <= e ; i++){
      int n1 = max(i - es , 0);
      int n2 = max(i - ef , 0);
      ld div = (ld)dp[n1] / ld(dp[n1] + dp[n2]);
      dp[i] = max(div * dp[n2] , eps);
   }
   ld l = 0 , r = 112.5;
   for(int i = 0 ; i < 30 ; i++){
      ld mid = (l + r) / 2;
      if(check(mid)){
         r = mid;
      }
      else{
         l = mid;
      }
   }
   cout << fixed << setprecision(6) << l;
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
