#include <bits/stdc++.h>
#define MAX_SIZE 1048597
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MID ((l+r)>>1)
using namespace std;
typedef int ll;
const int N = 20;
struct z2_basis {
    int n;
    int basis[N];
 
    // TODO: make sure the default constructor is the identity segment.
    z2_basis() : n(0) {}
 
    int qmax() const {
        int answer = 0;
 
        for (int i = 0; i < n; i++)
            answer = max(answer, answer ^ basis[i]);
 
        return answer;
    }
 
    void join(const z2_basis &other) {
        if (n == N)
            return;
 
        for (int i = 0; i < other.n; i++) {
            int x = other.basis[i];
 
            for (int j = 0; j < n; j++)
                x = min(x, x ^ basis[j]);
 
            if (x != 0) {
                basis[n++] = x;
 
                // Insertion sort.
                for (int k = n - 1; k > 0 && basis[k] > basis[k - 1]; k--)
                    swap(basis[k], basis[k - 1]);
            }
        }
 
        assert(n <= N);
    }
 
    // TODO: decide whether to re-implement this for better performance. Mainly relevant when segments contain arrays.
    void join(const z2_basis &a, const z2_basis &b) {
        *this = a;
        join(b);
    }
};

z2_basis tree[MAX_SIZE];
int n, c[MAX_SIZE];

void build() {  // build the tree
    for (int i = n - 1; i > 0; --i) tree[i].join(tree[i<<1], tree[i<<1|1]);
}


int query(int l, int r) {
    z2_basis ret = z2_basis();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) ret.join(tree[l++]);
        if (r&1) ret.join(tree[--r]);
    }
    return ret.qmax();
}


int main() {
    int q, i;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &c[i]);
        tree[n + i].n = c[i] == 0 ? 0 : 1;
        tree[n + i].basis[0] = c[i];
    }
    build();
    scanf("%d", &q);
    while (q-- > 0) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%d\n", query(l-1, r));
    }
    return 0;
}