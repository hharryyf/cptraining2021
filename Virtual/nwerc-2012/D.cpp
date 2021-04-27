#include <bits/stdc++.h>

using namespace std;

char digits[10][8] = {"1111110", "0110000", "1101101", "1111001", "0110011", "1011011", "1011111", "1110000", "1111111", "1111011"};
vector<pair<int, int>> interval;
int N;

pair<int, int> secondTotime(int secd) {
    return make_pair(secd / 60, secd % 60);
}

vector<int> getdigit(int secd) {
    vector<int> ret(4);
    auto p = secondTotime(secd);
    ret[0] = p.first / 10, ret[1] = p.first % 10;
    ret[2] = p.second / 10;
    ret[3] = p.second % 10;
    return ret;
}

bool check(int st) {
    // bad = 0 means it is good
    // bad = 1 means it is bad
    // bad = -1 means either is fine
    vector<vector<int>> bad = vector<vector<int>>(4, vector<int>(7, -1));
    int i, j, k;
    for (i = 0 ; i < N; ++i) {
        int curr = (st + i) % 1440;
        vector<int> realT = getdigit(curr);
        vector<int> showT = {interval[i].first / 10, interval[i].first % 10, interval[i].second / 10, interval[i].second % 10};
        for (j = 0 ; j < 4; ++j) {
            int relT = realT[j], dispT = showT[j];
            for (k = 0 ; k < 7; ++k) {
                int eT = digits[relT][k] - '0', oT = digits[dispT][k] - '0';
                if (oT == 1 && bad[j][k] == 1) {
                    return false;
                }

                if (oT == eT) {
                    if (eT == 1) {
                        bad[j][k] = 0;
                    }
                } else {
                    if (oT == 1 && eT == 0) return false;
                    if (oT == 0 && eT == 1) {
                        if (bad[j][k] == 0) {
                            return false;
                        }
                        bad[j][k] = 1;
                    }
                }
            }
        }
    }

    return true;
}

int main() {  
    while (scanf("%d", &N) != EOF) {
        int i;
        interval.clear();
        for (i = 0 ; i < N; ++i) {
            int hour, minute;
            scanf("%d:%d", &hour, &minute);
            interval.emplace_back(hour, minute);
        }
        
        int cnt = 0;
        for (i = 0 ; i < 1440; ++i) {
            if (check(i)) {
                auto ret = getdigit(i);
                printf("%d%d:%d%d ", ret[0], ret[1], ret[2], ret[3]);
                cnt++;
            }
        }

        if (cnt == 0) {
            printf("none\n");
        } else {
            printf("\n");
        }
    }
    return 0;
}