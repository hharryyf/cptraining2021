#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
using namespace __gnu_pbds;
/*
    Not my code, implemented by Dallas
*/

using namespace std;
typedef tree<ll, null_type, less<ll>, rb_tree_tag, 
            tree_order_statistics_node_update> ordered_set;
const ll MAXN = 1e5+5;
ll n;
struct collision {
    ll a;
    ll b;
    long double time;
    collision() {
        a = b = 0;
        time = 0;
    }
};
struct compare {
    bool operator()(const collision& a, const collision& b) {
        return a.time < b.time;
    }
};
priority_queue<collision, vector<collision>, compare> pq;
ordered_set cur_drones;
bool seen[MAXN];
ll all_drones[MAXN][2];
int main() {
    scanf("%lld",&n);
    for (ll i=0;i<n;i++) {
        scanf("%lld %lld",&all_drones[i][0],&all_drones[i][1]);
        cur_drones.insert(i);
    }
    collision temp;
    for (ll i=1;i<n;i++) {
        if (all_drones[i][1] < all_drones[i-1][1]) {
            temp.a = i-1;
            temp.b = i;
            temp.time = ((long double)all_drones[i][0]-(long double)all_drones[i-1][0])/((long double)all_drones[i][1]-(long double)all_drones[i-1][1]);
            pq.push(temp);
        }
    }
    collision temp2;
    while (!pq.empty()) {
        temp = pq.top();
        pq.pop();
        if (seen[temp.a] || seen[temp.b]) {continue;}
        seen[temp.a] = true;
        seen[temp.b] = true;
        ll posa = (cur_drones.order_of_key(temp.a));
        ll posb = (cur_drones.order_of_key(temp.b));
        if (posa > 0 && posb < cur_drones.size()-1) {
            posa = *(cur_drones.find_by_order(posa-1));
            posb = *(cur_drones.find_by_order(posb+1));
            if (all_drones[posb][1] < all_drones[posa][1]) {
                temp2.a = posa;
                temp2.b = posb;
                temp2.time = ((long double)all_drones[posb][0]-(long double)all_drones[posa][0])/((long double)all_drones[posb][1]-(long double)all_drones[posa][1]);
                pq.push(temp2);
            }
        }
        cur_drones.erase(temp.a);
        cur_drones.erase(temp.b);
    }
    printf("%lld\n",(ll)cur_drones.size());
    for (auto x : cur_drones) {
        printf("%lld ",x+1);
    }
    printf("\n");
}