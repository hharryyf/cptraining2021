#include <bits/stdc++.h>
#define MAX_SIZE 1011
using namespace std;

char a[MAX_SIZE], b[MAX_SIZE];
vector<pair<char, int>> c1, c2;

int main() {
    int l1, l2, i;
    fgets(a, MAX_SIZE, stdin);
    fgets(b, MAX_SIZE, stdin);
    l1 = strlen(a);
    l2 = strlen(b);
    a[--l1] = '\0';
    b[--l2] = '\0';
    
    //printf("%s\n", a);
    //printf("%s\n", b);
    int cnt = 0;
    for (i = 0; i < l1; ++i) {
        if (i == 0) {
            cnt++;
        } else {
            if (a[i] != a[i-1]) {
                c1.emplace_back(a[i-1], cnt);
                cnt = 1;
            } else {
                cnt++;
            }
        }
    }

    if (cnt > 0) {
        c1.emplace_back(a[l1-1], cnt);
    }

    cnt = 0;
    for (i = 0; i < l2; ++i) {
        if (i == 0) {
            cnt++;
        } else {
            if (b[i] != b[i-1]) {
                c2.emplace_back(b[i-1], cnt);
                cnt = 1;
            } else {
                cnt++;
            }
        }
    }

    if (cnt > 0) {
        c2.emplace_back(b[l2-1], cnt);
    }

    set<char> ret;
    for (i = 0 ; i < (int) c1.size(); ++i) {
        if (c1[i].second != c2[i].second) {
            ret.insert(c1[i].first);
        }
    }
    for (auto v : ret) {
        printf("%c", v);
    }
    printf("\n");
    return 0;
}