/*
    code in contest
*/
#include <bits/stdc++.h>
#define MAX_SIZE 262192
#define MAXLOG 19
typedef long long ll;
using namespace std;

struct rolling_hash {
    ll val[MAX_SIZE];
    ll ep[MAX_SIZE];
    ll mod = 1e9 + 7;
    int base = 41;
    int N;
    void init(int base=41, ll mod=1e9+7) {
        int i;
        this->base = base, this->mod = mod;
        ep[0] = 1;
        for (i = 1; i < MAX_SIZE; ++i) {
            ep[i] = ep[i-1] * base;
            ep[i] %= mod; 
        }
    }

    void calc(string &st, int N) {
        this->N = N;
        for (int i = 1 ; i <= N; ++i) {
            val[i] = val[i-1] * base + (st[i] - 'a' + 1);
            val[i] %= mod;
        }
    }

    ll decode(int l, int r) {
        ll valL = val[l-1] * ep[r - l + 1];
        ll valR = val[r];
        return ((valR - valL) % mod + mod) % mod;
    }

    bool equal(int l1, int r1, int l2, int r2) {
        if (r1 - l1 != r2 - l2) return false;
        return decode(l1, r1) == decode(l2, r2);
    }
};

struct SA {
    int p[MAX_SIZE];
    int cnt[MAX_SIZE];
    int c[MAXLOG][MAX_SIZE];
    int logs[MAX_SIZE];
    int rank[MAX_SIZE];
    const int alphabet = (MAX_SIZE >> 1);
    int n;
    
    void init() {
        memset(p, 0, sizeof(p));
        memset(cnt, 0, sizeof(cnt));
        memset(c, 0, sizeof(c));
        memset(rank, 0, sizeof(rank));
    }
 
    void sort_cyclic_shifts(string &s) {
        int h, i;
        n = (int) s.size();    
        for (i = 2; i < MAX_SIZE; ++i) logs[i] = logs[i/2]+1;
        for (i = 0; i < n; i++)
            cnt[(int) s[i]]++;
        for (i = 1; i < alphabet; i++)
            cnt[i] += cnt[i-1];
        for (i = 0; i < n; i++)
            p[--cnt[(int) s[i]]] = i;
        c[0][p[0]] = 0;
        int classes = 1;
        for (i = 1; i < n; i++) {
            if (s[p[i]] != s[p[i-1]])
                classes++;
            c[0][p[i]] = classes - 1;
        }
 
        vector<int> pn(n), cn(n);
        for (h = 0; (1 << h) < n; ++h) {
            for (i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt, cnt + classes, 0);
            for (i = 0; i < n; i++)
                cnt[c[h][pn[i]]]++;
            for (i = 1; i < classes; i++)
                cnt[i] += cnt[i-1];
            for (i = n-1; i >= 0; i--)
                p[--cnt[c[h][pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (i = 1; i < n; i++) {
                pair<int, int> cur = {c[h][p[i]], c[h][(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[h][p[i-1]], c[h][(p[i-1] + (1 << h)) % n]};
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            
            for (i = 0 ; i < n; ++i) {
                c[h+1][i] = cn[i];
            }
        }
 
        for (i = 0 ; i < n; ++i) rank[p[i]] = i;
    }
 
    int lcp(int i, int j) {
        int ans = 0, k;
        for (k = logs[n]; k >= 0; k--) {
            if (c[k][i] == c[k][j]) {
                ans += 1 << k;
                i += 1 << k;
                j += 1 << k;
            }
        }
        return ans;
    }
};

SA sa;

rolling_hash h1, h2;
int N;
char st[MAX_SIZE];
int len[MAX_SIZE], pos[MAX_SIZE];
bool valid[MAX_SIZE];

string curr;

bool check(int mid) {
    int i;
    unordered_set<int> ok;
    unordered_map<int, vector<int>> mp;
    memset(valid, 0, sizeof(valid));
    for (i = 1; i <= len[1] - mid + 1; ++i) {
        int l = i, r = i + mid - 1;
        int p = h1.decode(l, r);
        mp[p].push_back(i);
        ok.insert(p);
    }

    for (i = 2; i <= N; ++i) {
        for (int j = pos[i]; j <= pos[i] + len[i] - mid; ++j) {
            int l = j, r = j + mid - 1;
            int p = h1.decode(l, r);
            if (ok.find(p) != ok.end()) {
                mp.erase(p);
            }
        }
    }

    if (mp.empty()) return false;
    for (auto &iter : mp) {
        for (auto v : iter.second) {
            valid[v] = 1;
        }
    }
    return true;
}

int main() {
    int T, i, k;
    scanf("%d", &T);
    h1.init(43, 19260817);
    h2.init(41, 19260421);
    for (k = 1; k <= T; ++k) {
        int ans = 0;
        string ss = "";
        scanf("%d", &N);
        curr.clear();
        sa.init();
        curr = "";
        curr += '.';
        for (i = 1; i <= N; ++i) {
            scanf("%s", st);
            len[i] = strlen(st);
            pos[i] = (int) curr.length();
            curr.append(string(st));
            if (i == 1) {
                ss.append(string(st));
            }
        }

        ss += '$';
        sa.sort_cyclic_shifts(ss);
        h1.calc(curr, (int) curr.length() - 1);
        h2.calc(curr, (int) curr.length() - 1);
        int low = 1, high = len[1];
        while (low <= high) {
            int mid = (low + high) / 2;
            if (check(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        if (ans == 0) {
            printf("Case #%d: Impossible\n", k);
        } else {
            check(ans);
            printf("Case #%d: ", k);
            for (i = 0; i < sa.n; ++i) {
                if (valid[sa.p[i] + 1]) {
                    for (int j = sa.p[i] + 1; j <= ans + sa.p[i]; ++j) {
                        printf("%c", curr[j]);
                    }
                    break;
                }
            }
            printf("\n");
        }
    }
    return 0;
}