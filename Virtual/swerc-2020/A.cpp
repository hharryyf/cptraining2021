#include <bits/stdc++.h>
#define MAX_SIZE 55
using namespace std;

map<string, pair<int, int>> mp;
int N, K;
char s[MAX_SIZE];

int main() {
    int i;
    scanf("%d%d\n", &N, &K);
    for (i = 0 ; i < 3 * N; ++i) {
        fgets(s, MAX_SIZE, stdin);
        int len = strlen(s);
        s[--len] = '\0';
        string curr(s);
        if (mp.find(curr) == mp.end()) {
            mp[curr] = make_pair(1, i); 
        } else {
            auto p = mp[curr];
            p.first++;
            p.second = i;
            mp[curr] = p;
        }
    }

    vector<pair<pair<int, int>, string>> ret;
    for (auto p : mp) {
        ret.push_back(make_pair(p.second, p.first));
    }

    sort(ret.begin(), ret.end());

    for (i = (int) ret.size() - 1; i >= (int) ret.size() - K && i >= 0; --i) {
        printf("%s\n", ret[i].second.c_str());
    }
    return 0;
}