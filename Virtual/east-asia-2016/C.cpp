/*
   This is not my code, Ali implemented it
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 1e3+10 , mod = 1e9+7;

void solve(){
   int n;
   cin >> n;
   int a[n];
   vector <int> v;
   for(int i = 0 ; i < n ; i++){
      cin >> a[i];
      v.push_back(a[i]);
   }
   sort(v.begin() , v.end());
   v.resize(unique(v.begin() , v.end()) - v.begin());
   for(int i = 0 ; i < n ; i++){
      a[i] = lower_bound(v.begin() , v.end() , a[i]) - v.begin();
   }
   int first[n] , lst[n];
   vector <int> ins[n];
   for(int i = 0 ; i < n ; i++){
      lst[i] = n;
      ins[i].push_back(i);
   }
   int cur = n;
   for(int i = n - 1 ; i >= 0 ; i--){
      cur = min(cur , lst[a[i]]);
      first[i] = cur;
      lst[a[i]] = i;
   }
   int ans = 0;
   bool mark[n] , mark2[n];
   memset(mark2 , 0 , sizeof(mark2));
   for(int i = 0 ; i < n ; i++){
      if(n - i <= ans){
         break;
      }
      memset(mark , 0 , sizeof(mark));
      //set <int> s;
      for(int j = i ; j < n ; j++){
         if(mark[a[j]]){
            break;
         }
         ans = max(ans , j - i + 1);
         mark[a[j]] = true;
         /*for(int v : ins[a[j]]){
            s.insert(v);
         }*/

         int l = j + 1 , r = j;
         while(l < n){
            while(r < l - 1){
               r++;
            }
            while(r < n - 1 && !mark[a[r + 1]] && !mark2[a[r + 1]]){
               r++;
               mark2[a[r]] = true;
            }
            if(r >= l){
               ans = max(ans , r - l + 1 + j - i + 1);
               mark2[a[l]] = false;
            }
            l++;
         }
      }
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
