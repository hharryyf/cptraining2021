#include <bits/stdc++.h>
#define MAX_SIZE 200011
#define double long double
const double Pi = acos(-1.0);
using namespace std;
const double eps = 1e-10;
int sgn(double x) {
    if (fabs(x) <= eps) return 0;
    if (x > 0) return 1;
    return -1;
}

struct point {
    double x, y;
    long long wt;
    point(double x=0, double y=0, long long wt=0) : x(x), y(y), wt(wt) {}
    bool operator < (point other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

typedef point Vector;

double Dot(Vector A, Vector B){
    return A.x*B.x + A.y*B.y;
}

double Cross(Vector A, Vector B){
    return A.x*B.y-A.y*B.x;
}

double polarangle(double y, double x) {
    return atan2l(y, x);
}

vector<pair<double, point>> pts;
vector<long long> pre;
int N;

int main() {
    int i, j;
    long long tol = 0, curr = 0, ans = 0;
    scanf("%d", &N);
    pts = vector<pair<double, point>>();
    for (i = 0 ; i < N; ++i) {
        int x, y, w;
        scanf("%d%d%d", &x, &y, &w);
        pts.push_back(make_pair(polarangle(y, x), point(x, y, w)));
        tol += w;
        ans += w;
    }

    sort(pts.begin(), pts.end());
    vector<pair<double, point>> candidate;
    for (i = 0 ; i < N; ++i) {
        if (candidate.empty()) {
            candidate.push_back(pts[i]);
        } else {
            if (sgn(pts[i].first - pts[i-1].first) == 0 && sgn(Cross(pts[i].second, pts[i-1].second)) == 0) {
                candidate[(int) candidate.size() - 1].second.wt += pts[i].second.wt;
            } else {
                candidate.push_back(pts[i]);
            }
        }
    }   

    ans = llabs(ans);
    int sz = candidate.size();
    if (sz == 1) {
        cout << ans << endl;
        return 0;
    }
    
    for (i = 0 ; i < sz - 1; ++i) {
        candidate.push_back(candidate[i]);
    }

    pre = vector<long long>(2 * sz - 1, 0);
    pre[0] = candidate[0].second.wt;
    for (i = 1; i < 2 * sz - 1; ++i) {
        pre[i] = pre[i-1] + candidate[i].second.wt;
    }

    ans = 1e18;
    for (i = 0, j = 0; i < sz; ++i) {
        if (i == j) {
            j = i + 1;
        }

        while (j < 2 * sz - 1 && sgn(Cross(candidate[i].second, candidate[j].second)) > 0) {
            j = j + 1;
        }
        
        // prefix sum of [i, j - 1]
        curr = (j > 0 ? pre[j-1] : 0ll) - (i > 0 ? pre[i-1] : 0);
        // cout << i << " " << curr << endl;
        ans = min(ans, llabs(curr - (tol - curr)));
        if (j < 2 * sz - 1 && sgn(Cross(candidate[i].second, candidate[j].second)) == 0) {
            curr = pre[j] - pre[i];
            ans = min(ans, llabs(curr - (tol - curr)));
        }
    }

    cout << ans << endl;
    return 0;
}