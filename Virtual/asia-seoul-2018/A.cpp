/*
    Not my code, Ali coded it in contest
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 2e5+10 , mod = 1e9+7;

int st[N] , seg[4 * N] , flag[4 * N];
vector <int> en[N];

void relax(int ind){
   int x = flag[ind];
   flag[ind] = 0;
   seg[2 * ind] += x;
   flag[2 * ind] += x;
   seg[2 * ind + 1] += x;
   flag[2 * ind + 1] += x;
}

void add(int s , int e , int ind , int l , int r , int val){
   if(s >= r || e <= l){
      return;
   }
   if(s >= l && e <= r){
      seg[ind] += val;
      flag[ind] += val;
      return;
   }
   relax(ind);
   int mid = (s + e) / 2;
   add(s , mid , 2 * ind , l , r , val);
   add(mid , e , 2 * ind + 1 , l , r , val);
   seg[ind] = max(seg[2 * ind] , seg[2 * ind + 1]);
}

int get(int s , int e , int ind , int l , int r){
   if(s >= r || e <= l){
      return 0;
   }
   if(s >= l && e <= r){
      return seg[ind];
   }
   relax(ind);
   int mid = (s + e) / 2;
   return max(get(s , mid , 2 * ind , l , r) , get(mid , e , 2 * ind + 1 , l , r));
}

void solve(){
   int n;
   cin >> n;
   int x[n] , y[n];
   vector <int> v;
   for(int i = 0 ; i < n ; i++){
      int xx , yy;
      cin >> xx >> y[i] >> yy >> x[i];
      v.push_back(x[i]);
      v.push_back(y[i]);
   }
   sort(v.begin() , v.end());
   v.resize(unique(v.begin() , v.end()) - v.begin());
   for(int i = 0 ; i < n ; i++){
      x[i] = lower_bound(v.begin() , v.end() , x[i]) - v.begin();
      y[i] = lower_bound(v.begin() , v.end() , y[i]) - v.begin();
      st[x[i]]++;
      en[y[i]].push_back(x[i]);
   }
   int m = v.size();
   int op = 0;
   int ans = 0;
   for(int i = 0 ; i < m ; i++){
      op += st[i];
      ans = max(ans , op + get(0 , m , 1 , 0 , i));
      //cout << i << " " << op << " " << get(0 , m , 1 , 0 , i) << endl;
      op -= en[i].size();
      for(int pos : en[i]){
         add(0 , m , 1 , pos , i + 1 , 1);
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
