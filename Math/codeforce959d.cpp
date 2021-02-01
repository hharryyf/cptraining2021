#include <bits/stdc++.h>
#define MAX_SIZE 1500013
using namespace std;

const int maxn = 1500011;
int a[MAX_SIZE], N, visited[MAX_SIZE];
int ans[MAX_SIZE];
vector<int> fac[MAX_SIZE];
vector<int> prime;
set<int> candidate;

void del(int v) {
    for (int i = 1; i * v <= maxn; ++i) candidate.erase(v * i);
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) scanf("%d", &a[i]);
    for (i = 2; i <=  maxn; ++i) {
        if (!visited[i]) {
            prime.push_back(i);
            for (int j = 1; j * i <= maxn; ++j) {
                visited[i * j] = 1;
            }
        }
    }

    for (i = 0 ; i < (int) prime.size(); ++i) {
        for (int j = 1; j * prime[i] <= maxn; ++j) {
            fac[prime[i] * j].push_back(prime[i]);
        }
    }
    for (i = 2; i <= maxn; ++i) candidate.insert(i);

    int ok = 0;
    for (i = 1; i <= N; ++i) {
        if (ok == 0) {
            for (auto p : fac[a[i]]) {
                if (candidate.find(p) == candidate.end()) {
                    ok = 1;
                    break;
                }
            }

            if (!ok) {
                ans[i] = a[i];
                for (auto p : fac[a[i]]) del(p);
            } else {
                ans[i] = *candidate.lower_bound(a[i]);
                for (auto p : fac[ans[i]]) {
                    del(p);
                }
            }
        } else {
            ans[i] = *candidate.begin();
            for (auto p : fac[ans[i]]) {
                del(p);
            }
        }
    }   

    for (i = 1; i <= N; ++i) {
        printf("%d ", ans[i]);
    }
    return 0;
}