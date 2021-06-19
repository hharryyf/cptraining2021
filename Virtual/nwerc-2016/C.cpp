/*
    Not my code, Dallas coded it in contest
*/
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double

const ll MAXN = 101;

ll x,y;
ll n;

struct shield {
    ll l;
    ll u;
    ld f;
    shield() {
        l = u = 0;
        f = 0;
    }
};

shield shields[MAXN];

int main() {
    scanf("%lld %lld",&x,&y);
    scanf("%lld",&n);
    for (ll i=0;i<n;i++) {
        scanf("%lld %lld %Lf",&shields[i].l, &shields[i].u, &shields[i].f);
    }
    ld out = y;
    for (ll i=0;i<n;i++) {
        out -= shields[i].u-shields[i].l;
    }
    for (ll i=0;i<n;i++) {
        out += (shields[i].u-shields[i].l)*shields[i].f;
    }
    out = (ld)x/out;
    printf("%Lf\n",out);
}
