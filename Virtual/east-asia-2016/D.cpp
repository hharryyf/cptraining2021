/*
    implemented by Ali in contest, not my code
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 3e5+10 , mod = 1e9+7;

int n , k;
ll a[N];

bool check(int m){
   vector <ll> v[m];
   for(int i = 0 ; i < m ; i++){
      v[i].push_back(a[i]);
   }
   int cur = 0 , num = 1 , pos = m;
   while(pos < n && num < k){
      if(a[pos] / 2 >= v[cur].back()){
         v[cur].push_back(a[pos]);
         cur++;
         if(cur == m){
            num++;
            cur = 0;
         }
      }
      pos++;
   }
   return num >= k;
}

void solve(){
   cin >> n >> k;
   for(int i = 0 ; i < n ; i++){
      cin >> a[i];
   }
   sort(a , a + n);
   int l = 0 , r = n / k + 1;
   while(r - l > 1){
      int m = (l + r) / 2;
      if(check(m)){
         l = m;
      }
      else{
         r = m;
      }
   }
   cout << l << "\n";
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
