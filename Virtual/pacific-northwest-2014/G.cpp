#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 2e5+10 , mod = 1e9+7;

void solve(){
   int n;
   cin >> n;
   int pos = -1;
   int a[n];
   for(int i = 0 ; i < n ; i++){
      cin >> a[i];
      if(a[i] == 1){
         pos = i;
      }
   }
   bool dp[n][n][2];
   memset(dp , 0 , sizeof(dp));
   dp[pos][pos][0] = dp[pos][pos][1] = 1;
   for(int l = 2 ; l <= n ; l++){
      for(int i = 0 ; i < n ; i++){
         if(i + l > n || i > pos || i + l <= pos){
            continue;
         }
         int j = i + l - 1;
         for(int k = i ; k <= j ; k++){
            if(k > i && a[k] < a[k - 1]){
               continue;
            }
            if(k < j && a[k] < a[k + 1]){
               continue;
            }
            int rem = -1;
            bool win = false;
            if(pos > k){
               rem = k - i;
               win = dp[k + 1][j][rem % 2];
            }
            else{
               rem = j - k;
               win = dp[i][k - 1][rem % 2];
            }
            win = 1 - win;
            dp[i][j][0] |= win;
         }
         if(dp[i][j][0] == 0){
            dp[i][j][1] = 1;
         }
         for(int k = i ; k <= j ; k++){
            if(k > i && a[k] < a[k - 1]){
               continue;
            }
            if(k < j && a[k] < a[k + 1]){
               continue;
            }
            int rem = -1;
            bool win = false;
            if(pos > k){
               rem = k - i + 1;
               win = dp[k + 1][j][rem % 2];
            }
            else{
               rem = j - k + 1;
               win = dp[i][k - 1][rem % 2];
            }
            win = 1 - win;
            dp[i][j][1] |= win;
         }
      }
   }
   if(dp[0][n - 1][0] == 0){
      cout << "Bob\n";
   }
   else{
      cout << "Alice\n";
   }
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
