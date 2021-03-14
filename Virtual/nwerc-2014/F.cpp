  
#include <bits/stdc++.h>
#define MAX_SIZE 100011
typedef long long ll;
using namespace std;

struct point {
    ll x, y;
    point(ll x=0, ll y=0) : x(x), y(y) {}
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
    
    point operator *(double p) {
        return point(x*p, y*p);
    }

    bool operator ==(point other) {
        return (x == other.x) && (y == other.y);
    }
};

typedef point Vector;

struct segment {
    point v1, v2;
};

struct Line {
    // v is the point, p is the direction vector
    point v, p;
    Line(point v, point p):v(v), p(p) {}
};

ll Cross(Vector A, Vector B){
    return A.x*B.y-A.y*B.x;
}

point pt[MAX_SIZE];

int main() {
    int N, P, i, j;
    srand(time(NULL));
    scanf("%d%d", &N, &P);
    if (N <= 2) {
        printf("possible\n");
        return 0;
    }

    for (i = 0; i < N; ++i) {
        scanf("%I64d%I64d", &pt[i].x, &pt[i].y);
    }

    shuffle(pt, pt + N,default_random_engine(19260817));
    j = 0;
    while (j < 500) {
        int id1 = rand() % N, id2 = (1ll * rand() * rand()) % N;
        int base = rand() % N;
        id1 = id1 + base, id2 = id2 + base;
        if (id1 >= N) id1 -= N;
        if (id2 >= N) id2 -= N;
        if (id1 == id2) continue;
        ++j;
        int cnt = 2;
        for (i = 0 ; i < N; ++i) {
            if (i != id1 && i != id2) {
                Vector v1 = pt[i] - pt[id1], v2 = pt[i] - pt[id2];
                if (Cross(v1, v2) == 0) cnt++;
            }
        }

        if (cnt * 100 >= N * P) {
            printf("possible\n");
            return 0;
        }
    }

    printf("impossible\n");
    return 0;
}