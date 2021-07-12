/*
    Not my code, Dallas coded it in contest
*/

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2001;
const int MAXM = 2001;

int m,n,w,h;
int wi[MAXM];
int di[MAXN];

queue<int> q;
priority_queue<pair<int, int>> pq;
queue<pair<int, pair<int, int>>> lastWork;

bool bad;
vector<int> out[MAXM];

int main() {
    scanf("%d %d %d %d",&m,&n,&w,&h);
    for (int i=0;i<m;i++) {
        scanf("%d",&wi[i]);
    }
    for (int i=0;i<n;i++) {
        scanf("%d",&di[i]);
    }
    for (int i=0;i<m;i++) {
        pq.push(make_pair(wi[i],i));
    }
    for (int i=0;i<n;i++) {
        while (q.size() > 0) {
            int ite = q.front();
            if (ite > i-w) {break;}
            q.pop();
        }
        while (lastWork.size() > 0) {
            if (lastWork.front().first > i-(h+w)) {
                break;
            }
            pq.push(lastWork.front().second);
            lastWork.pop();
        }
        int num = di[i] - q.size();
        if (num < 0) {
            bad = true;
            break;
        }
        while (pq.size() > 0 && num > 0) {
            pair<int, int> ite = pq.top();
            pq.pop();
            // cout << ite.first << endl;
            if (ite.first > w) {
                lastWork.push(make_pair(i, make_pair(ite.first-w, ite.second)));
            }
            q.push(i);
            out[ite.second].push_back(i+1);
            num--;
        }
        if (num != 0) {
            bad = true;
            break;
        }
    }
    if (!(pq.empty() && lastWork.size() == 0)) {
        bad = true;
    }
    if (bad) {
        printf("-1\n");
    } else {
        printf("1\n");
        for (int i=0;i<m;i++) {
            for (int x : out[i]) {
                printf("%d ",x);
            }
            printf("\n");
        }
    }
    return 0;
}