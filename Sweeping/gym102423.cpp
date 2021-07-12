#include <bits/stdc++.h>
typedef long double ld;
using namespace std;
const ld pi = acos(-1.0);
const ld eps = 1e-11;
struct line {
    ld intime, b, k;
    bool operator <(line other) {
        return intime < other.intime;
    }
};

int sgn(ld x) {
    if (fabs(x) < eps) return 0;
    if (x > 0) return 1;
    return -1;
}

vector<ld> alltime;
vector<ld> disc;
vector<line> add;
vector<line> del;
ld curr = 0, ans = -1e17, K = 0;
int N;

ld y1(ld x, ld t, ld s, ld a) {
    return -s * x + t + s * (a - 2 * pi);
}

ld y2(ld x, ld t, ld s, ld a) {
    return s * x + t - s * a;
}

ld y3(ld x, ld t, ld s, ld a) {
    return -s * x + t + s * a;
}

ld y4(ld x, ld t, ld s, ld a) {
    return s * x + t - s * (a + 2 * pi);
}

void update(ld t, ld s, ld a) {
    // simple case
    if (s == 0) {
        curr += t;
        return;
    }
    ld L, R;
    if (sgn(a - pi) > 0) {
        L = 0.0;
        R = min((t + s * (a - 2 * pi)) / s, a - pi);
        if (sgn(L - R) <= 0) {
            add.push_back(line{L, y1(0, t, s, a), -s});
            del.push_back(line{R, y1(R, t, s, a), -s});
            alltime.push_back(L);
            alltime.push_back(R);
        }
    }

    L = max(max(0.0L, a - t / s), a - pi);
    R = a;
    add.push_back(line{L, y2(L, t, s, a), s});
    del.push_back(line{R, y2(R, t, s, a), s});
    alltime.push_back(L);
    alltime.push_back(R);
    
    L = a;
    R = min(min(pi * 2, a + t / s), a + pi);
    add.push_back(line{L, y3(L, t, s, a), -s});
    del.push_back(line{R, y3(R, t, s, a), -s});
    alltime.push_back(L);
    alltime.push_back(R);
    if (sgn(a - pi) < 0) {
        // TODO
        L = max(a + pi, (s * (a + 2 * pi) - t) / s);
        R = 2 * pi;
        if (sgn(L - R) <= 0) {
            add.push_back(line{L, y4(L, t, s, a), s});
            del.push_back(line{R, y4(R, t, s, a), s});
            alltime.push_back(L);
            alltime.push_back(R);
        }
    }
}

int main() {
    int i, j, k;
    scanf("%d", &N);
    for (i = 0 ; i < N; ++i) {
        ld t, s, a;
        scanf("%Lf%Lf%Lf", &t, &s, &a);
        update(t, s, a);
    }

    sort(alltime.begin(), alltime.end());   
    sort(add.begin(), add.end());
    sort(del.begin(), del.end());
    for (i = 0 ; i < (int) alltime.size(); ++i) {
        if (i == 0 || alltime[i] != alltime[i-1]) {
            disc.push_back(alltime[i]);
        }
    }

    if (disc.empty() || sgn(disc[0]) > 0) ans = curr;
    // cout << ans << endl;
    for (i = 0, j = 0, k = 0 ; i < (int) disc.size(); ++i) {
        while (j < (int) add.size() && sgn(disc[i] - add[j].intime) >= 0) {
            K += add[j].k;
            //cout << "add line at " << add[j].intime << " " << add[j].k << " " << add[j].b << endl;
            curr += add[j].b;
            ++j;
        }
        
        //cout << curr << " " << ans << endl;
        //ans = max(ans, curr);

        while (k < (int) del.size() && sgn(disc[i] - del[k].intime) >= 0) {
            //cout << "delete line at " << del[k].intime << " " << del[k].k << " " << del[k].b << endl;
            K -= del[k].k;
            curr -= del[k].b;
            ++k;
        }

        //cout << curr << " " << ans << endl;
        ans = max(ans, curr);
        
        if (i != (int) disc.size() - 1) {
            curr += K * (disc[i+1] - disc[i]);
        }
        //cout << curr << " "<< ans << endl;
        ans = max(ans, curr);
    }

    printf("%.10Lf\n", ans);
    return 0;
}