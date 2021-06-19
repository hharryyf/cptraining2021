#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll inf = 1e15;
struct dynamictree {
    struct node {
        int val;
        ll l, r;
        struct node *left, *right;
    
        node(ll l, ll r, int val) {
            this->left = this->right = NULL;
            this->l = l, this->r = r, this->val = val;
        }
    };
    
    node *tree;
    
    dynamictree() {
        tree = new node(0, inf, 0);
	}

    node *inc(node *rt, ll pos, ll l, ll r, int val) {
        if (l > r || pos < l || pos > r) return rt;
        if (rt == NULL) {
            rt = new node(l, r, 0);
        }
        
        if (l == r && pos == r) {
            rt->val += val;
            return rt;
        }
        
        ll mid = l + (r - l) / 2;
        if (pos <= mid) {
            rt->left = inc(rt->left, pos, l, mid, val);
        } else {
            rt->right = inc(rt->right, pos, mid + 1, r, val);
        }
        int v1 = rt->left == NULL ? 0 : rt->left->val;
        int v2 = rt->right == NULL ? 0 : rt->right->val;
        rt->val = v1 + v2;
        return rt;
    }
    
    int getans(node *rt, ll l, ll r) {
        if (rt == NULL) return 0;
        if (l <= rt->l && rt->r <= r) return rt->val;
        ll mid = rt->l + (rt->r - rt->l) / 2;
        if (r <= mid) {
            return getans(rt->left, l, r);
        } else if (l >= mid + 1) {
            return getans(rt->right, l, r);
        } else {
            return getans(rt->left, l, r) + getans(rt->right, l, r);
        }
    }
    
    // increment pos by val in tree[version]
    void update(ll pos, int val) {
        tree = inc(tree, pos, 0, inf, val);
    }
    
    int query(ll l, ll r) {
        if (l > r) return 0;
        return getans(tree, l, r);
    }
};

dynamictree tree = dynamictree();
#define MAX_SIZE 100011
pair<ll, ll> team[MAX_SIZE];
int N, M;
ll calc(ll sc, ll p) {
    return sc * 1e9 + (5e8 - p);
}

int main() {
    scanf("%d%d", &N, &M);
    tree.update(calc(0, 0), N);
    while (M-- > 0) {
        int tid, p;
        scanf("%d%d", &tid, &p);
        tree.update(calc(team[tid].first, team[tid].second), -1);
        team[tid].first++;
        team[tid].second += p;
        tree.update(calc(team[tid].first, team[tid].second), 1);
        printf("%d\n", tree.query(calc(team[1].first, team[1].second) + 1, inf) + 1);
    }
    return 0;
}