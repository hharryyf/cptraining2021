#include <bits/stdc++.h>
#define MAX_SIZE 211
typedef long long ll;
using namespace std;

pair<int, int> ord[MAX_SIZE * MAX_SIZE];
int a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE][MAX_SIZE];
pair<int, int> h[MAX_SIZE * MAX_SIZE], t[MAX_SIZE * MAX_SIZE];
int n, c, d;

int main() {
    int i, j, k = 0;
    scanf("%d%d%d", &n, &c, &d);    
    for (i = 0; i < n; ++i) {
        for (j = 0 ; j < n; ++j) {
            if (j == 0) {
                ord[k] = {i, 0};
            } else if (j == 1) {
                ord[k] = {(i + 1) % n, n - 1};
            } else {
                ord[k] = {(i + j) % n, n - j};
            }
            k++;
        }
    }
/*
    for (i = 0 ; i < n * n; ++i) {
        printf("%d %d\n", ord[i].first, ord[i].second);
    }
*/ 
    for (i = 0; i < c; ++i) {
        scanf("%d", &h[i].first);
        h[i].second = i;
    }
    for (i = 0; i < d; ++i) {
        scanf("%d", &t[i].first);
        t[i].second = i;
    }
    
    sort(t, t + d);
    sort(h, h + c);
    j = 0;
    for (i = c - 1; i >= 0; --i) {
        while (h[i].first-- > 0) {
            a[ord[j].first][ord[j].second] = h[i].second + 1;
            ++j;
        }
    }

    j = 0;
    for (i = d - 1; i >= 0; --i) {
        while (t[i].first-- > 0) {
            b[ord[j].first][ord[j].second] = t[i].second + 1;
            ++j;
        }
    }
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            printf("%dv%d", a[i][j], b[i][j]);
            if (j != n) {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}