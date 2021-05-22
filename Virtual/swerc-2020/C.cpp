#include <bits/stdc++.h>
typedef double ld;
using namespace std;

const ld eps = 1e-9;
int sgn(ld x) {
    if (fabs(x) <= eps) return 0;
    if (x > 0) return 1;
    return -1;
}

struct point {
    ld x, y;
    point(ld x=0, ld y=0) : x(x), y(y) {}
    point operator -(point other) {
        return point(x - other.x, y - other.y);
    }
    
    point operator +(point other) {
        return point(x + other.x, y + other.y);
    }
    
    bool operator < (point other) {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    
    point operator *(ld p) {
        return point(x*p, y*p);
    }
};

typedef point Vector;

ld Dot(Vector A, Vector B){
    return A.x*B.x + A.y*B.y;
}

#define MAX_SIZE 1011
point c[MAX_SIZE];
ld X, Y;
int N, f[MAX_SIZE];
ld L[MAX_SIZE], R[MAX_SIZE], U[MAX_SIZE], D[MAX_SIZE];

int find(int x) {
    if (x != f[x]) return f[x] = find(f[x]);
    return x;
}

void unionset(int x, int y) {
    int a = find(x), b = find(y);
    f[a] = b;
    L[b] = min(L[b], L[a]);
    R[b] = max(R[b], R[a]);
    U[b] = max(U[b], U[a]);
    D[b] = min(D[b], D[a]);
}

bool check(ld d) {
    int i, j;
    for (i = 1; i <= N; ++i) {
        f[i] = i;
        L[i] = c[i].x - d, R[i] = c[i].x + d, U[i] = c[i].y + d, D[i] = c[i].y - d;
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j < N; ++j) {
            if (sgn(Dot(c[i] - c[j], c[i] - c[j]) - d * d * 4) <= 0) {
                unionset(i, j);
            }
        }
    }

    for (i = 1; i <= N; ++i) {
        int x = find(i);
        if (U[x] >= Y && D[x] <= 0) return false;
        if (L[x] <= 0 && R[x] >= X) return false;
        if (L[x] <= 0 && D[x] <= 0) return false;
        if (R[x] >= X && U[x] >= Y) return false; 
    }

    return true;
}

int main() {
    int i;
    ld low = 0, high = 4e6, ans = 0;
    scanf("%lf%lf%d", &X, &Y, &N);
    for (i = 1; i <= N; ++i) {
        scanf("%lf%lf", &c[i].x, &c[i].y);
    }

    for (i = 0; i < 80; ++i) {
        ld mid = 0.5 * (low + high);
        if (check(mid)) {
            ans = mid;
            low = mid;
        } else {
            high = mid;
        }
    }

    printf("%.9lf\n", ans);
    return 0;
}