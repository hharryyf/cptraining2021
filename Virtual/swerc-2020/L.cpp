#include <bits/stdc++.h>
#define MAX_SIZE 50011
#define WRONG_ANSWER
using namespace std;

int N, M;
int cap[MAX_SIZE];
vector<int> g[MAX_SIZE];
map<int, int> preference[MAX_SIZE];
// preference, customer
priority_queue<pair<int, int>> waitlist[MAX_SIZE];
queue<int> reject, reject2;
int assign[MAX_SIZE];
// add customer cid to resturant rid
void addcustomer(int cid, int rid) {
    int p = preference[rid][cid];
    assign[cid] = rid;
    #ifndef WRONG_ANSWER
    printf("returant %d put %d with priority %d on waitlist\n", rid, cid, p);
    #endif
    waitlist[rid].push({p, cid});
    if ((int) waitlist[rid].size() > cap[rid]) {
        auto bad = waitlist[rid].top();
        waitlist[rid].pop();
        #ifndef WRONG_ANSWER
        printf("resturant %d reject %d with preference %d\n", rid, bad.second, bad.first);
        #endif
        assign[bad.second] = -1;
        reject2.push(bad.second);
    }
}

void apply(int cid) {
    if (g[cid].empty()) {
        return;
    }
    int candidate = g[cid].back();
    g[cid].pop_back();
    addcustomer(cid, candidate);
}

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

#define MAX_LEN 4000011
char in[MAX_LEN];

int main() {
    int i;
    for (i = 0 ; i < MAX_SIZE; ++i) assign[i] = -1;
    scanf("%d%d", &N, &M);
    for (i = 1; i <= M; ++i) scanf("%d", &cap[i]);
    getchar();
    for (i = 1; i <= N; ++i) {
        reject.push(i);
    }

    for (i = 1; i <= N; ++i) {
        fgets(in, MAX_LEN, stdin);
        //printf("%s\n", in);
        vector<string> ret;
        SplitString(string(in), ret, " ");
        for (auto ss : ret) {
            if ((int)ss.length() == 0 || ss[0] > '9' || ss[0] < '0') continue;
            g[i].push_back(atoi(ss.c_str()));
        }
        reverse(g[i].begin(), g[i].end());
    }

    for (i = 1; i <= M; ++i) {
        int j = 1;
        fgets(in, MAX_LEN, stdin);
        //printf("%s\n", in);
        vector<string> ret;
        SplitString(string(in), ret, " ");
        for (auto ss : ret) {
            if ((int)ss.length() == 0 || ss[0] > '9' || ss[0] < '0') continue;
            if (atoi(ss.c_str()) == 0) continue;
            preference[i][atoi(ss.c_str())] = j++;
        }
    }

    while (true) {
        if (reject.empty()) break;
        while (!reject.empty()) {
            int v = reject.front();
            reject.pop();
            apply(v);        
        }

        while (!reject2.empty()) {
            reject.push(reject2.front());
            reject2.pop();
        }
    }

    for (i = 1; i <= N; ++i) {
        if (assign[i] != -1) {
            printf("%d\n", i);
        }
    }
    return 0;
}