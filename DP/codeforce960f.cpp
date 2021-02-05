#include <bits/stdc++.h>
#define MAX_SIZE 100011
using namespace std;

struct dynamictree {
    struct node {
        int val;
        int l, r;
        struct node *left, *right;
    
        node(int l, int r, int val) {
            this->left = this->right = NULL;
            this->l = l, this->r = r, this->val = val;
        }
    };
    
    node *tree[MAX_SIZE];
    
    node *update(node *rt, int pos, int l, int r, int val) {
        if (l > r || pos < l || pos > r) return rt;
        if (rt == NULL) {
            rt = new node(l, r, 0);
        }
        
        if (l == r && pos == r) {
            rt->val = max(val, rt->val);
            return rt;
        }
        
        int mid = l + (r - l) / 2;
        if (pos <= mid) {
            rt->left = update(rt->left, pos, l, mid, val);
        } else {
            rt->right = update(rt->right, pos, mid + 1, r, val);
        }
        int v1 = rt->left == NULL ? 0 : rt->left->val;
        int v2 = rt->right == NULL ? 0 : rt->right->val;
        rt->val = max(v1,  v2);
        return rt;
    }
    
    int getans(node *rt, int l, int r) {
        if (rt == NULL) return 0;
        if (l <= rt->l && rt->r <= r) return rt->val;
        int mid = rt->l + (rt->r - rt->l) / 2;
        if (r <= mid) {
            return getans(rt->left, l, r);
        } else if (l >= mid + 1) {
            return getans(rt->right, l, r);
        } else {
            return max(getans(rt->left, l, r), getans(rt->right, l, r));
        }
    }
    
    // increment pos by val in tree[version]
    void change(int pos, int val, int version) {
        tree[version] = update(tree[version], pos, 0, 100000, val);
    }
    
    int query(int l, int r, int version) {
        if (l > r) return 0;
        return getans(tree[version], l, r);
    }
};

dynamictree tree;
struct edge {
    int from, to, weight;
    bool operator < (edge other) const {
        return weight < other.weight;
    }
};

edge edg[MAX_SIZE];

int N, M;

int main() {
    int i, ans = 0;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) {
        scanf("%d%d%d", &edg[i].from, &edg[i].to, &edg[i].weight);
    }

    // sort(edg + 1, edg + 1 + M);
    for (i = 1; i <= M; ++i) {
        int curr = tree.query(0, edg[i].weight - 1, edg[i].from) + 1;
        tree.change(edg[i].weight, curr, edg[i].to);
        ans = max(ans, curr);
    }

    printf("%d\n", ans);
    return 0;
}