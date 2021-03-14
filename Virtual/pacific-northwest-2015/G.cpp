#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 2e5+10 , mod = 1e9+7;
const ll M = 1e12;

map <ll , int> fen;

void add(ll x , int val){
   for( ; x < M ; x += x & -x){
      fen[x] = max(fen[x] , val);
   }
}

int get(ll x){
   int ret = 0;
   for( ; x ; x -= x & -x){
      ret = max(ret , fen[x]);
   }
   return ret;
}

void solve(){
   int n , r , w , h;
   cin >> n >> r >> w >> h;
   vector < pair <ll , ll> > v;
   for(int i = 0 ; i < n ; i++){
      ll x , y;
      cin >> x >> y;
      x *= r;
      v.push_back({x - y , -(x + y)});
   }
   sort(v.begin() , v.end());
   ll ret = 0;
   for(auto x : v){
      ll l = x.first;
      ll r = -x.second;
      ll ans = get(M - r);
      add(M - r , ans + 1);
      ret = max(ret , ans + 1);
   }
   cout << ret;
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
