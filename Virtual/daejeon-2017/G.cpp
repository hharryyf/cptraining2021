#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct event {
    int x, y, tp;
    bool operator <(event other) const {
        if (x != other.x) return x < other.x;
        return tp < other.tp;
    }
};

int N, M;
vector<int> tmp;
vector<int> disc;
vector<event> evt;

int main() {
    int i, j, L = -1, U = -1, cnt = 0, flag = 0, flag2 = 0;
    ll ans = 0, ans2 = 0;
    scanf("%d%d", &N, &M);
    scanf("%d", &L);
    for (i = 1; i <= N; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        tmp.push_back(x);
        evt.push_back(event{x, y, 0});
    }

    scanf("%d", &U);
    for (i = 1; i <= M; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        tmp.push_back(x);
        evt.push_back(event{x, y, 1});
    }

    sort(tmp.begin(), tmp.end());
    sort(evt.begin(), evt.end());
    for (i = 0 ; i < (int) tmp.size(); ++i) {
        if (i == 0 || tmp[i] != tmp[i-1]) {
            disc.push_back(tmp[i]);
        }
    }
    
    for (i = 0, j = 0; i < (int) disc.size(); ++i) {
        if (L < U) {
            flag = 0;
            ans2 += 1ll * (U - L) * (i > 0 ? (disc[i] - disc[i-1]) : 0);
           
        } else {
            flag = 1;
        }

        while (j < (int) evt.size() && evt[j].x == disc[i]) {
            if (evt[j].tp == 0) {
                L = evt[j].y;
            } else {
                U = evt[j].y;
            }
            ++j;
        }

        if (flag && L < U) {
            flag2 = 1;
        }

        if (!flag && L >= U) {
            if (flag2) {
                ans = ans + ans2;
                cnt++;
            }
            ans2 = 0;
            flag2 = 1;
        }

    }
    printf("%d %lld\n", cnt, ans);
    return 0;
}