#include <bits/stdc++.h>

using namespace std;

map<string, int> mp;
vector<int> g[511];
int dp[511][2011];
string idTost[2011];
vector<string> equ[511];
char ss[511], target[2011];
int N;

void init() {
    for (int i = 0 ; i < 511; ++i) {
        g[i].clear();
        equ[i].clear();
        for (int j = 0 ; j < 2011; ++j) {
            dp[i][j] = -1;
        }
    }

    mp.clear();
}

void split(string s, vector<string> &ret, string t) {
    set<char> h;
    for (auto ch : t) h.insert(ch);
    string curr = "";
    for (auto ch : s) {
        if (h.find(ch) != h.end()) {
            if ((int) curr.length() != 0) {
                ret.push_back(curr);
                curr = "";
            }
        } else {
            curr += ch;
        }
    }

    if ((int) curr.length() != 0) {
        ret.push_back(curr);
    }
}

int dfs(int v, int pos) {
    int i, len = strlen(target + 1), j;
    if (dp[v][pos] != -1) return dp[v][pos];
    if (g[v].empty()) {
        dp[v][pos] = pos;
        i = pos + 1, j = 0;
        while (i <= len && j < (int) idTost[v].length()) {
            if (idTost[v][j] == target[i]) {
                dp[v][pos] = i;
                i++;  
            } 
            j++;
        }

        // printf("%d %d = %d\n", v, pos, dp[v][pos]);
        return dp[v][pos];
    }

    if ((int) g[v].size() == 1) {
        return dp[v][pos] = dfs(g[v][0], pos);
    }

    int ret = dfs(g[v][0], pos);
    return dp[v][pos] = dfs(g[v][1], ret);
}

int main() {
    int T, i;
    scanf("%d", &T);
    while (T-- > 0) {
        init();
        scanf("%d", &N);
        getchar();
        for (i = 1; i <= N; ++i) {
            fgets(ss, 511, stdin);
            split(string(ss), equ[i], " \n+=");
            for (auto &st : equ[i]) {
                mp[st] = 0;
            }
        }

        i = 1;
        for (auto &iter : mp) {
            // printf("%s %d\n", iter.first.c_str(), i);
            idTost[i] = iter.first;
            iter.second = i++;
        }

        for (i = 1; i <= N; ++i) {
            int v = mp[equ[i][0]];
            for (int j = 1; j < (int) equ[i].size(); ++j) {
                g[v].push_back(mp[equ[i][j]]);
                //printf("addedge %d %d\n", v, mp[equ[i][j]]);
            }
        }

        scanf("%s", ss);
        scanf("%s", target + 1);
        printf("%s\n", dfs(mp[string(ss)], 0) == ((int)strlen(target + 1)) ? "YES" : "NO");
        //printf("%d\n", dfs(mp[string(ss)], 0));
    }
    return 0;
}