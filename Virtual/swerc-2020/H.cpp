#include <bits/stdc++.h>
#define LEFT (index<<1)
#define RIGHT (index<<1|1)
#define MID ((l+r)>>1)
#define MAX_SIZE 262192
using namespace std;

struct segt {
    int left, right, value;
};

int cnt = 0;
int root[MAX_SIZE], version[MAX_SIZE];
segt tree[MAX_SIZE * 30];
int N;

int build(int l, int r) {
    if (l > r) return 0;
    int curr = ++cnt;
    if (l == r) return curr;
    tree[curr].left = build(l, MID);
    tree[curr].right = build(MID + 1, r);
    return curr;
}

int update(int rt, int pos, int l, int r, int val) {
    if (pos < l || pos > r || l > r || rt == 0) return rt;
    int curr = ++cnt;
    tree[curr] = tree[rt];
    if (pos == l && l == r) {
        tree[curr].value += val;
        return curr;
    }

    if (pos <= MID) {
        tree[curr].left = update(tree[rt].left, pos, l, MID, val);
    } else {
        tree[curr].right = update(tree[rt].right, pos, MID + 1, r, val);
    }
    tree[curr].value = tree[tree[curr].left].value + tree[tree[curr].right].value;
    return curr;
}

int query(int rt, int start, int end, int l, int r) {
    if (rt == 0 || start > end || l > r || start > r || l > end) return 0;
    if (start <= l && r <= end) return tree[rt].value;
    if (end <= MID) {
        return query(tree[rt].left, start, end, l, MID);
    } else if (start >= MID + 1) {
        return query(tree[rt].right, start, end, MID + 1, r);
    }

    return query(tree[rt].left, start, end, l, MID) + query(tree[rt].right, start, end, MID + 1, r);
}

#define MAX_LEN 2000111
char s[MAX_LEN];

void SplitString(const string& s, vector<string>& v, const string& c) {
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2-pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }

    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

int main() {
    int i, ct = 0;
    scanf("%d\n", &N);
    root[0] = build(0, N - 1);
    version[0] = 0;
    for (i = 1; i <= N; ++i) {
        if (fgets(s, MAX_LEN, stdin) == NULL) {
            version[i] = ct; 
            continue;
        }

        vector<string> ret;
        SplitString(string(s), ret, " ");
        for (auto s1 : ret) {
            if (s1[0] == '-') {
                root[ct + 1] = update(root[ct], atoi(s1.c_str() + 1), 0, N - 1, -1);
                ++ct;
            } else if (s1[0] == '+') {
                root[ct + 1] = update(root[ct], atoi(s1.c_str() + 1), 0, N - 1, 1);
                ++ct;
            }
            // printf("%d\n", atoi(s1.c_str()+1));
        }
        version[i] = ct; 
    }
    int x = 0;
    for (i = 1; i <= N; ++i) {
        int curr;
        scanf("%d", &curr);
        x = (x + query(root[version[curr]], x, N - 1, 0, N - 1)) % N;
    }
    printf("%d\n", x);
    return 0;
}