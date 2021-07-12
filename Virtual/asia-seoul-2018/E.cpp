#include <bits/stdc++.h>
#define MAX_SIZE 300011
typedef long long ll;
typedef long double ld;
using namespace std;

pair<ld, ld> points[MAX_SIZE];
ld minR[MAX_SIZE], maxR[MAX_SIZE];
int N;

bool check(ld H) {
    int i, v1 = N + 1;
    if (points[1].second > H && points[1].first == 0) return false;
    for (i = 1; i <= N; ++i) {
        if (points[i].second > H) {
            v1 = i;
            break;
        }
    }

    if (v1 == N + 1) return true;
    ld mn = points[v1].second, mx = points[v1].second;
    for (i = v1; i <= N; ++i) {
        ld mnr , mxr;
        mn = min(mn, points[i].second);
        mx = max(mx, points[i].second);
        if (i == N) {
            if (mx - mn <= 2 * H && mx >= H) return true;
        } else {
            mnr = minR[i+1], mxr = maxR[i+1];
            if (mx - mn <= 2 * H && mx >= H) {
                if (max(mxr, mx) - 2 * H <= mnr) return true;
            }
        }
    }
    return false;
}

int main() {
    int i;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%Lf%Lf", &points[i].first, &points[i].second);
    }
    sort(points + 1, points + 1 + N);
    minR[N] = maxR[N] = points[N].second;
    for (i = N - 1; i >= 1; --i) {
        minR[i] = min(minR[i+1], points[i].second);
        maxR[i] = max(maxR[i+1], points[i].second);
    }
    ld low = 0, high = 1e9, ans = 1e9;
    for (i = 0 ; i < 150; ++i) {
        ld mid = (low + high) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid;
        } else {
            low = mid;
        }
    }
    
    check(1.0);
    printf("%.1Lf\n", ans);
    return 0;
}
