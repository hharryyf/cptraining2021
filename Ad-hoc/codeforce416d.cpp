#include <bits/stdc++.h>
#define MAX_SIZE 200011
typedef long long ll;
using namespace std;

int N;
ll a[MAX_SIZE];

int main() {
    int i, j, ans = 0;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) scanf("%I64d", &a[i]);
    i = 1;
    while (i <= N) {
        ans++;
        vector<int> pos;
        j = i;
        while (j <= N) {
            if (a[j] != -1) {
                if ((int) pos.size() > 1) {
                    ll d = (a[pos.back()] - a[pos.front()]) / (pos.back() - pos.front());
                    if ((a[j] - a[pos.back()]) % (j - pos.back()) != 0) break;
                    if ((a[j] - a[pos.back()]) / (j - pos.back()) != d) break;
                } else if ((int) pos.size() == 1) {
                    if ((a[j] - a[pos.back()]) % (j - pos.back()) != 0) break;
                    ll d = (a[j] - a[pos.back()]) / (j - pos.back());
                    if (d > 0) {
                        if (a[pos.front()] <= d * (pos.front() - i)) break;                        
                    }
                }

                pos.push_back(j);
            } else {
                if ((int) pos.size() > 1) {
                    ll d = (a[pos.back()] - a[pos.front()]) / (pos.back() - pos.front());
                    if (d * (j - pos.back()) + a[pos.back()] <= 0) {
                        break;
                    }
                }
            }
            ++j;
        }

        i = j;
    }

    printf("%d\n", ans);
    return 0;
}