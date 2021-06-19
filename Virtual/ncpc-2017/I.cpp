#include <bits/stdc++.h>
#define MAX_SIZE 511
using namespace std;
const int inf = 1e7;
int pre[MAX_SIZE][MAX_SIZE];
int dist[MAX_SIZE][MAX_SIZE];
char files[MAX_SIZE][11], root[11];
char ipt[MAX_SIZE * MAX_SIZE];
map<string, int> mp;
int N;

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

int main() {
    int i, j, k;
    for (i = 0; i < MAX_SIZE; ++i) {
        for (j = 0 ; j < MAX_SIZE; ++j) {
            dist[i][j] = inf;
        }
    }
    scanf("%d", &N);
    for (i = 1; i <= N; ++i) {
        scanf("%s", files[i]);
        mp[string(files[i])] = i;
    }

    for (i = 1; i <= N; ++i) {
        scanf("%s%d", root, &k);
        int v = mp[string(root)];
        getchar();
        while (k-- > 0) {
            fgets(ipt, MAX_SIZE * MAX_SIZE, stdin);
            vector<string> imp;
            split(string(ipt), imp, ", \n");
            for (j = 1; j < (int) imp.size(); ++j) {
                int nxt = mp[imp[j]];
                dist[v][nxt] = 1;
            }
        }
    }

    for (i = 1; i <= N; ++i) {
        for (j = 1; j <= N; ++j) {
            if (dist[i][j] != inf) {
                pre[i][j] = i;
            }
        }
    }

    for (k = 1; k <= N; ++k) {
        for (i = 1; i <= N; ++i) {
            for (j = 1; j <= N; ++j) {
                if (dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    pre[i][j] = pre[k][j];
                }
            }
        }
    }

    int idx = -1;
    for (i = 1; i <= N; ++i) {
        if (dist[i][i] != inf) {
            if (idx == -1 || dist[idx][idx] > dist[i][i]) idx = i;
        }
    }

    if (idx == -1) {
        printf("SHIP IT\n");
        return 0;
    }

    vector<int> ret;
    int x = idx, y = idx;
    ret.push_back(y);
    y = pre[x][y];
    while (y != x) {
        ret.push_back(y);
        y = pre[x][y];
    }
    
    reverse(ret.begin(), ret.end());
    for (auto v : ret) {
        printf("%s ", files[v]);
    }
    printf("\n");
    return 0;
}