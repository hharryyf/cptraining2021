#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int wt[20];

ll calc(string s, int len) {
    int i, j, mx = (len + 1) / 2;
    ll ret = 0;
    vector<int> vc;
    for (auto ch : s) {
        vc.push_back(ch - '0');
    }
    reverse(vc.begin(), vc.end());
    vc.push_back(0);
    for (i = 0 ; i < (1 << mx); ++i) {
        vector<int> tmp(vc.size());
        vector<int> res(vc.size());
        ll curr = 1;
        for (j = 0 ; j < mx; ++j) {
            if ((1 << j) & i) {
                tmp[j+1] += 1;
            }
        }

        for (j = 0 ; j < mx; ++j) {
            int cbit = tmp[j+1] * 10 + vc[j] - tmp[j];
            if (cbit < 0 || cbit > 18) {
                curr = 0;
                break;
            } else {
                res[j] = res[len - j - 1] = cbit;
                if (j == mx - 1 && len % 2 == 1) {
                    curr = curr * (cbit % 2 == 0 ? 1 : 0);
                } else {
                    curr = curr * ((j == 0 && cbit < 10) ? wt[cbit] - 1 : wt[cbit]);
                    //curr = curr * wt[cbit];
                }
            }
        }


        for (j = 0 ; j < (int) res.size(); ++j) {
            if (j != (int) res.size()) {
                res[j + 1] += res[j] / 10;
            }

            res[j] %= 10;
        }

        int valid = 1;
        for (j = 0 ; j < len + 1; ++j) {
            if (vc[j] != res[j]) {
                valid = 0;
                break;
            }
        }

        if (valid && curr != 0) {
           /* for (auto v : res) {
                cout << v << " ";
            }
            cout << endl;*/
            ret = ret + curr;
        }
    }
    // cout << "calc " << s << " " << len << " = " << ret << endl;
    return ret;
}

void init() {
    int i, j;
    for (i = 0 ; i <= 9; ++i) {
        for (j = 0 ; j <= 9; ++j) {
            wt[i+j]++;
        }
    }

    // printf("%d\n", wt[10]);
}

void solve() {
    ll N;
    scanf("%I64d", &N);
    string s = to_string(N);
    if ((int) s.length() < 2) {
        if (N % 2 == 0) {
            printf("1\n");
        } else {
            printf("0\n");
        }
        return;
    }

    ll ans = calc(s, (int) s.length() - 1) + calc(s, (int) s.length());
    printf("%I64d\n", ans);
}

int main() {
    int T;
    init();
    scanf("%d", &T);
    while (T-- > 0) {
        solve();
    }
    return 0;
}