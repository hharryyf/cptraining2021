#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;

struct BIT {
    int tree[MAX_SIZE];
    int N;
    void init() {
        memset(tree, 0, sizeof(tree));
        N = 0;
    }

    int shift(int x) {
        return x & (-x);
    }

    void update(int index, int val) {
        if (index <= 0) return;
        while (index <= N) {
            tree[index] += val;
            index += shift(index);
        }  
    }

    int getsum(int index) {
        int ret = 0;
        while (index > 0) {
            ret = ret + tree[index];
            index -= shift(index);
        }
        return ret;
    }

    int query(int l, int r) {
        if (l > r) return 0;
        return getsum(r) - getsum(l-1);
    }
};


struct Ball {
    int x, y, c;
    bool operator < (Ball other) const {
        return y < other.y;
    }
};

BIT t;
set<int> occ[MAX_SIZE];
set<int> yset[MAX_SIZE];
set<int> color;
int ycnt[MAX_SIZE];
vector<int> dx, dy;
int tmp[MAX_SIZE];
Ball ball[MAX_SIZE];

void init() {
    t.init();
    for (int i = 0 ; i < MAX_SIZE; ++i) {
        occ[i].clear();
        yset[i].clear();   
        ycnt[i] = 0;
    }
    color.clear();
    dx.clear();
    dy.clear();
}

int main() {
    int T, N, K, i;
    scanf("%d", &T);
    while (T-- > 0) {
        init();
        int ans = 0;
        scanf("%d%d", &N, &K);
        for (i = 1; i <= N; ++i) {
            scanf("%d%d%d", &ball[i].x, &ball[i].y, &ball[i].c);
            tmp[i] = ball[i].x;
        }

        sort(ball + 1, ball + 1 + N);
        sort(tmp + 1, tmp + N + 1);
        for (i = 1; i <= N; ++i) {
            if (i == 1 || ball[i].y != ball[i-1].y) dy.push_back(ball[i].y);
            if (i == 1 || tmp[i] != tmp[i-1]) dx.push_back(tmp[i]);
        }

        for (i = 1; i <= N; ++i) {
            ball[i].x = lower_bound(dx.begin(), dx.end(), ball[i].x) - dx.begin() + 1;    
            t.N = max(ball[i].x, t.N);
        }

        for (i = 1; i <= K; ++i) {
            occ[i].insert(0);
            occ[i].insert(t.N + 1);
        }        
        i = 1;
        for (auto y : dy) {
            int l = i, r = i-1;
            while (i <= N && ball[i].y == y) {
                int pre = 1, nxt = t.N;
                pre = *prev(occ[ball[i].c].lower_bound(ball[i].x)) + 1;
                nxt = *occ[ball[i].c].upper_bound(ball[i].x) - 1;
                ans = max(ans, t.query(pre, ball[i].x - 1));
                ans = max(ans, t.query(ball[i].x + 1, nxt));
                if (occ[ball[i].c].find(ball[i].x) == occ[ball[i].c].end()) ans = max(ans, t.query(pre, nxt));
                r = i;
                ++i;
            }

            int j = l;
            while (j <= r) {
                yset[ball[j].x].insert(ball[j].c);
                color.insert(ball[j].c);
                ycnt[ball[j].x]++;
                if ((int) yset[ball[j].x].size() != K) {
                    ans = max(ans, ycnt[ball[j].x]);
                }
                t.update(ball[j].x, 1);
                occ[ball[j].c].insert(ball[j].x);
                ++j;
            }

            if ((int) color.size() != K) {
                ans = max(ans, t.query(1, t.N));
            }
            while (l <= r) {
                int pre = 1, nxt = t.N;
                pre = *prev(occ[ball[l].c].lower_bound(ball[l].x)) + 1;
                nxt = *occ[ball[l].c].upper_bound(ball[l].x) - 1;
                ans = max(ans, t.query(pre, ball[l].x - 1));
                ans = max(ans, t.query(ball[l].x + 1, nxt));
                l++;    
            }
        }
        
        for (i = 1; i <= K; ++i) {
            vector<int> vc;
            for (auto v : occ[i]) {
                vc.push_back(v);
            }

            ans = max(ans, t.query(1, vc.front() - 1));
            ans = max(ans, t.query(vc.back() + 1, t.N));
            for (int j = 0; j < (int) vc.size() - 1; ++j) {
                ans = max(ans, t.query(vc[j] + 1, vc[j+1] - 1));
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}