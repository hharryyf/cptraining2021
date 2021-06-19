/*
    Not my code, Ali coded it in contest
    This approach is different do the one I can think of binary search on final answer
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 2e5+10 , mod = 1e9+7;

void solve(){
   int n;
   cin >> n;
   int ans = 0;
   set <int> s;
   for(int i = 0 ; i < n ; i++){
      int x;
      cin >> x;
      if(s.find(x) != s.end()){
         s.erase(x);
      }
      else{
         if(!s.empty()){
            ans = max(ans , min(x , *s.rbegin()));
         }
         s.insert(x);
      }
   }
   if(!s.empty()){
      ans = max(ans , *s.rbegin());
   }
   s.clear();
   for(int i = 0 ; i < n ; i++){
      int x;
      cin >> x;
      if(s.find(x) != s.end()){
         s.erase(x);
      }
      else{
         if(!s.empty()){
            ans = max(ans , min(x , *s.rbegin()));
         }
         s.insert(x);
      }
   }
   cout << ans;
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
