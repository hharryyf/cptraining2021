#include <bits/stdc++.h>

using namespace std;

int n, m, a, b, c, d, r;
map<int, pair<double, double>> ss;
int critical;
double res;
// c1 + c2 * x = 

int f(int x) {
    if (x <= 0) {
        return -m - 2 * x; 
    }

    return m - 2 * x;
}

double solve(double c1, double c2, int x) {
    // cout << c1 << " " << c2 << " " << x << endl;
    if (ss.find(x) != ss.end()) {
        auto p = ss[x];
        res = (c1 - p.first) / (p.second - c2);
        return res;
    }
    
    ss[x] = make_pair(c1, c2);
    double t = 1.0 * x / m;
    if (x <= 0) {
        return solve(c1 + c2 * a / r, c2 * (b + r * t * t) / r, f(x));
    } else {

        return solve(c1 + c2 * c / r, c2 * (d + r * t * t) / r, f(x));
    }
}

double solve2(int x) {
    double t = 1.0 * x / m;
    if (x == critical) return res;
    if (x <= 0) {
        return 1.0 * a / r + (1.0 * b + r * t * t) / r * solve2(f(x));
    }

    return 1.0 * c / r + (1.0 * d + r * t * t) / r * solve2(f(x));
}

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%d%d%d%d%d%d%d", &n, &m, &a, &b, &c, &d, &r);
        set<int> vs;
        ss.clear();
        critical = n;
        while (true) {
            if (vs.find(critical) != vs.end()) break;
            vs.insert(critical);
            critical = f(critical);
        }

        // printf("%d\n", critical);
        solve(0, 1, critical);
        // printf("%d\n", 4);
        printf("%.9lf\n", solve2(n));
    }
    return 0;
}