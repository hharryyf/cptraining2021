#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 2e5+10 , mod = 1e9+7;

void solve(){
   int a[3] , b[3];
   for(int i = 0 ; i <3 ; i++){
      cin >> a[i];
   }
   for(int i = 0 ; i < 3 ; i++){
      cin >> b[i];
   }
   sort(a , a + 3);
   sort(b , b + 3);
   for(int i = 0 ; i < 3 ; i++){
      if(a[i] != b[i]){
         cout << "NO";
         return;
      }
   }
   if(a[0] * a[0] + a[1] * a[1] != a[2] * a[2]){
      cout << "NO";
   }
   else{
      cout << "YES";
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
