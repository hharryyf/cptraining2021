#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ll T;
    scanf("%lld",&T);
    for (ll caseN=1;caseN<=T;caseN++) {
        ll p;
        scanf("%lld",&p);
        // printf("%lld\n",p);
        double dist[60][60];
        ll coords[60][3];
        map<string,ll> hm;
        char planet[51];
        for (ll i=0;i<p;i++) {
            scanf("%s %lld %lld %lld",planet,&coords[i][0],&coords[i][1], &coords[i][2]);
            string tem = planet;
            hm[tem] = i;
        }
        for (ll i=0;i<p;i++) {
            for (ll j=0;j<p;j++) {
                dist[i][j] = sqrt((coords[i][0]-coords[j][0])*(coords[i][0]-coords[j][0])+(coords[i][1]-coords[j][1])*(coords[i][1]-coords[j][1])+(coords[i][2]-coords[j][2])*(coords[i][2]-coords[j][2]));
            }
        }
        ll w;
        scanf("%lld",&w);
        char planet2[51];
        // printf("%lld\n",w);
        for (ll i=0;i<w;i++) {
            scanf("%s %s",planet,planet2);
            string tem = planet;
            string tem2 = planet2;
            dist[hm[tem]][hm[tem2]] = 0;
        }
        for (ll i=0;i<p;i++) {
            for (ll u=0; u<p;u++) {
                for (ll v=0;v<p;v++) {
                    dist[u][v] = min(dist[u][v],dist[u][i]+dist[i][v]);
                }
            }
        }
        ll q;
        scanf("%lld",&q);
        printf("Case %lld:\n",caseN);
        // printf("%lld\n",q);
        for (ll i=0;i<q;i++) {
            scanf("%s %s",planet,planet2);
            string tem = planet;
            string tem2 = planet2;
            printf("The distance from %s to %s is %lld parsecs.\n",planet,planet2,(long long)round(dist[hm[tem]][hm[tem2]]));
        }
    }
}