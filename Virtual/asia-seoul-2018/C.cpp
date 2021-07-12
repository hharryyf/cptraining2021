/*
    Not my code, Ali coded it in contest
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 1e3+10 , mod = 1e9+7;

ld get(ld r1 , ld r2){
   return sqrt((r1 + r2) * (r1 + r2) - (r2 - r1) * (r2 - r1));
}

void solve(){
   int n;
   cin >> n;
   vector <int> v;
   for(int i = 0 ; i < n ; i++){
      int r;
      cin >> r;
      v.push_back(r);
   }
   sort(v.begin() , v.end());
   ld ans = v.back() * 2;
   v.pop_back();
   int tpl = 1 , tpr = 1 , idl = n - 1 , idr = n - 1 , reml = 0 , remr = n - 2;
   for(int i = 0 ; i < n - 1 ; i++){
      ld addl = 0;
      if(tpl == 1){
         addl = get(v[reml] , v[idl]) - v[idl] + v[reml];
      }
      else{
         addl = get(v[remr] , v[idl]) - v[idl] + v[remr];
      }
      ld addr = 0;
      if(tpr == 1){
         addr = get(v[reml] , v[idr]) - v[idr] + v[reml];
      }
      else{
         addr = get(v[remr] , v[idr]) - v[idr] + v[remr];
      }
      if(addl <= addr){
         ans += addl;
         if(tpl == 0){
            tpl = 1;
            idl = remr;
            remr--;
         }
         else{
            tpl = 0;
            idl = reml;
            reml++;
         }
      }
      else{
         ans += addr;
         if(tpr == 0){
            tpr = 1;
            idr = remr;
            remr--;
         }
         else{
            tpr = 0;
            idr = reml;
            reml++;
         }
      }
   }
   cout << fixed << setprecision(5) << ans;
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
