#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 1048577
int dist[MAX_SIZE];
int visited[MAX_SIZE];
char s[22];

int main() {
    int i, N, M;
    scanf("%d%d", &N, &M);
    for (i = 0 ; i < (1 << M); ++i) {
        dist[i] = MAX_SIZE;
    }

    queue<int> q;
    for (i = 0 ; i < N; ++i) {
        scanf("%s", s);
        int curr = 0;
        for (int j = 0 ; j < M; ++j) {
            curr = curr * 2 + (s[j] - '0');
        }
        dist[curr] = 0;
        q.push(curr);    
    }

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (visited[v]) continue;
        visited[v] = 1;
        for (i = 0 ; i < M; ++i) {
            int nv = v ^ (1 << i);
            if (!visited[nv] && dist[nv] > dist[v] + 1) {
                q.push(nv);
                dist[nv] = dist[v] + 1;
            }
        }
    }

    int idx = 0;
    for (i = 1; i < (1 << M); ++i) {
        if (dist[idx] < dist[i]) idx = i;
    }

    for (i = M - 1; i >= 0; --i) {
        printf("%d", ((idx >> i) & 1));
    }
    printf("\n");
    return 0;
}