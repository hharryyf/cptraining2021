#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;

struct Player {
    double fi, ot;
    char name[24];
    bool operator < (Player other) const {
        return ot < other.ot;
    }
};

Player p[MAX_SIZE];
int N;

double calc(int idx) {
    if (idx == 1) return p[1].fi + p[2].ot + p[3].ot + p[4].ot;
    if (idx == 2) return p[1].ot + p[2].fi + p[3].ot + p[4].ot;
    if (idx == 3) return p[1].ot + p[2].ot + p[3].fi + p[4].ot;
    return p[idx].fi + p[1].ot + p[2].ot + p[3].ot;
}

void print(double ans, int idx) {
    printf("%lf\n", ans);
    vector<int> candidate;
    if (idx == 1) {
        candidate.push_back(1);
        candidate.push_back(2);
        candidate.push_back(3);
        candidate.push_back(4);
    } else if (idx == 2) {
        candidate.push_back(2);
        candidate.push_back(1);
        candidate.push_back(3);
        candidate.push_back(4);
    } else if (idx == 3) {
        candidate.push_back(3);
        candidate.push_back(1);
        candidate.push_back(2);
        candidate.push_back(4);
    } else {
        candidate.push_back(idx);
        candidate.push_back(1);
        candidate.push_back(2);
        candidate.push_back(3);
    }

    for (auto id : candidate) {
        printf("%s\n", p[id].name);
    }
}

int main() {
    int i;
    int idx = -1;
    double ans = 100;
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%s%lf%lf", p[i].name, &p[i].fi, &p[i].ot);
    }

    sort(p + 1, p + 1 + N);
    for (i = 1; i <= N; ++i) {
        double curr = calc(i);
        if (ans > curr) {
            ans = curr;
            idx = i;
        }
    }

    print(ans, idx);
    return 0;
}