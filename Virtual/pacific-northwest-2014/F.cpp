#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 257 , mod = 1e9+9;

bool good2(int m){
   vector <pii> bad;
   bad.push_back({0 , 5});
   bad.push_back({2 , 7});
   bad.push_back({4 , 1});
   bad.push_back({6 , 3});
   for(pii x : bad){
      int i = x.first , j = x.second;
      if(((1 << i) & m) && ((1 << j) & m)){
         return false;
      }
   }
   return true;
}

bool good(int m1 , int m2){
   vector <pii> bad;
   bad.push_back({0 , 2});
   bad.push_back({1 , 4});
   bad.push_back({1 , 3});
   bad.push_back({2 , 0});
   bad.push_back({2 , 4});
   bad.push_back({3 , 1});
   bad.push_back({3 , 5});
   bad.push_back({3 , 6});
   bad.push_back({4 , 2});
   bad.push_back({4 , 6});
   bad.push_back({5 , 3});
   bad.push_back({5 , 7});
   bad.push_back({5 , 0});
   bad.push_back({6 , 4});
   bad.push_back({7 , 2});
   bad.push_back({7 , 5});
   for(pii x : bad){
      int i = x.first , j = x.second;
      if(((1 << i) & m1) && ((1 << j) & m2)){
         return false;
      }
   }
   return true;
}

typedef int Mat[N][N];

int MyN = 0;
Mat a[30] , c , ret;

void mul(Mat a , Mat b , Mat c){
   for(int i = 0 ; i < MyN ; i++){
      for(int j = 0 ; j < MyN ; j++){
         c[i][j] = 0;
      }
   }
   for(int i = 0 ; i < MyN ; i++){
      for(int j = 0 ; j < MyN ; j++){
         for(int k = 0 ; k < MyN ; k++){
            c[i][j] += 1ll * a[i][k] * b[k][j] % mod;
            c[i][j] %= mod;
         }
      }
   }
}

void solve(){
   int m , n;
   cin >> m >> n;
   if(n == 1){
      cout << (1 << m) << "\n";
      return;
   }
   int mskn = 2 * m;
   MyN = (1 << mskn);
   for(int i = 0 ; i < (1 << mskn) ; i++){
      for(int j = 0 ; j < (1 << mskn) ; j++){
         ret[i][j] = 0;
      }
   }
   for(int i = 0 ; i < (1 << mskn) ; i++){
      ret[i][i] = 1;
   }
   if((2 & n)){
      mul(ret , a[1] , c);
      swap(ret , c);
   }
   for(int i = 2 ; i < 30 ; i++){
      mul(a[i - 1] , a[i - 1] , c);
      swap(a[i] , c);
      if((1 << i) & n){
         mul(ret , a[i] , c);
         swap(ret , c);
      }
   }
   int ans[1 << mskn][1 << mskn];
   memset(ans , 0 , sizeof(ans));
   if(n & 1){
      for(int i = 0 ; i < (1 << mskn) ; i++){
         for(int j = 0 ; j < (1 << mskn) ; j++){
            bool bad = false;
            for(int k = 1 ; k < 8 ; k += 2){
               if((1 << k) & j){
                  bad = true;
               }
            }
            if(bad){
               continue;
            }
            if(good(i , j)){
               for(int k = 0 ; k < (1 << mskn) ; k++){
                  int val = 0;
                  if((1 << 1) & i){
                     val += (1 << 0);
                  }
                  if((1 << 3) & i){
                     val += (1 << 2);
                  }
                  if((1 << 5) & i){
                     val += (1 << 4);
                  }
                  if((1 << 7) & i){
                     val += (1 << 6);
                  }

                  if((1 << 0) & j){
                     val += (1 << 1);
                  }
                  if((1 << 2) & j){
                     val += (1 << 3);
                  }
                  if((1 << 4) & j){
                     val += (1 << 5);
                  }
                  if((1 << 6) & j){
                     val += (1 << 7);
                  }

                  (ans[k][val] += ret[k][i]) %= mod;
               }
            }
         }
      }
   }
   else{
      for(int i = 0 ; i < (1 << mskn) ; i++){
         for(int j = 0 ; j < (1 << mskn) ; j++){
            ans[i][j] = ret[i][j];
         }
      }
   }
   int tot = 0;
   for(int i = 0 ; i < (1 << mskn) ; i++){
      tot += ans[0][i];
      tot %= mod;
      //cout << i << " " << ans[0][i] << endl;
   }
   cout << tot << "\n";
}

int32_t main(){
   ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   for(int i = 0 ; i < (1 << 8) ; i++){
      for(int j = 0 ; j < (1 << 8) ; j++){
         if(good(i , j) && good2(j) && good2(i)){
            a[1][i][j] = 1;
         }
      }
   }
   int t = 1;
   cin >> t;
   while(t--){
      solve();
   }
   return 0;
}
