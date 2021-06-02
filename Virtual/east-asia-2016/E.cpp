/*
    implemented by Dallas in contest, not my code
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101;
long double ab[MAXN][2];
long double X[MAXN];

int main() {
    int T;
    scanf("%d",&T);
    for (int casen=1;casen<=T;casen++) {
        printf("Case #%d: ",casen);
        int N;
        scanf("%d",&N);
        for (int i=0;i<N;i++) {
            scanf("%Lf:%Lf",&ab[i][0],&ab[i][1]);
            X[i] = 1/(1+ab[i][1]/ab[i][0]);
        }
        sort(X,X+N);
        int out = 0;
        long double cur = 0;
        for (int i=0;i<N;i++) {
            cur += X[i];
            if (cur >= 1) {
                break;
            }
            out = max(out,i+1);
        }
        printf("%d\n",out);
    }
}
