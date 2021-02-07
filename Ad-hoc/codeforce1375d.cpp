#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

int N;
int a[MAX_SIZE], vis[MAX_SIZE];

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d", &N);
        for (i = 0 ; i < N; ++i) {
            scanf("%d", &a[i]);
        }
        vector<int> ret;
        int ok = 1;
        while (ok) {
            ok = 0;
            
            for (i = 0; i < N; ++i) {
                if (a[i] != i) {
                    ok = 1;
                    break;
                }
            }
            
            if (ok == 0) break;
            
            for (i = 0 ; i <= N + 1; ++i) {
                vis[i] = 0;
            }
            
            for (i = 0 ; i < N; ++i) {
                vis[a[i]] = 1;
            }
            
            int mex = 0;
            for (i = 0 ; i <= N + 1; ++i) {
                if (!vis[i]) {
                    mex = i;
                    break;
                }
            }
            
            if (mex == N) {
                for (i = 0 ; i < N; ++i) {
                    if (a[i] != i) {
                        a[i] = mex;
                        ret.push_back(i + 1);
                        break;
                    }
                }
            } else {
                a[mex] = mex;
                ret.push_back(mex + 1);
            }
        }
        
        printf("%d\n", (int) ret.size());
        for (auto v : ret) {
            printf("%d ", v);
        }
        printf("\n");
    }
    return 0;
}