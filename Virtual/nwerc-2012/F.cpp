#include <bits/stdc++.h>
#define MAX_SIZE 1031
using namespace std;

char st[MAX_SIZE][MAX_SIZE];
int N;

int main() {
    int i, j;
    while (scanf("%d", &N) != EOF) {
        unordered_set<int> live;
        for (i = 1; i <= N; ++i) {
            scanf("%s", st[i] + 1);
            live.insert(i);
        }
        
        for (i = 1; i < N; i = i * 2) {
            unordered_set<int> pending, strong;
            for (j = 2; j <= N; ++j) {
                if (live.find(j) != live.end()) {
                    pending.insert(j);
                    if (st[1][j] == '0') {
                        strong.insert(j);
                    }
                }
            }

            for (auto v : strong) {
                if (live.find(v) == live.end() || pending.find(v) == pending.end()) continue;
                for (j = 1; j <= N; ++j) {
                    if (pending.find(j) != pending.end() && st[j][v] == '1' && strong.find(j) == strong.end()) {
                        pending.erase(j);
                        pending.erase(v);
                        live.erase(v);
                        printf("%d %d\n", j, v);
                        break;
                    }
                }
            }   

            /*
            printf("pending: ");
            for (auto v : pending) {
                printf("%d ", v);
            }

            printf("\n");
            */
            bool findok = false;
            for (auto v : pending) {
                if (st[1][v] == '1') {
                    live.erase(v);
                    pending.erase(v);
                    printf("%d %d\n", 1, v);
                    findok = true;
                    break;
                }
            }
            
            if (!findok) {
                printf("wrong answer!\n");
                exit(0);
            }

            for (auto v : strong) {
                if (live.find(v) == live.end() || pending.find(v) == pending.end()) continue;
                for (j = 1; j <= N; ++j) {
                    if (pending.find(j) != pending.end() && st[j][v] == '1') {
                        pending.erase(j);
                        pending.erase(v);
                        live.erase(v);
                        printf("%d %d\n", j, v);
                        break;
                    }
                }
            } 

            int pre = -1, j = 0;
            for (auto v : pending) {
                if (j % 2 == 1) {
                    printf("%d %d\n", v, pre);
                    if (st[v][pre] == '1') {
                        live.erase(pre);
                    } else {
                        live.erase(v);
                    }
                }
                pre = v;
                j = j + 1;
            }
        }
        // printf("\n\n");
    }
    return 0;
}