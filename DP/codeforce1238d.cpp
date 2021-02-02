#include <bits/stdc++.h>
#define MAX_SIZE 300011
using namespace std;

char s[MAX_SIZE];
int preA = 0, preB = 0;
int N;

int main() {
    int i;
    long long ans = 0;
    scanf("%d", &N);
    scanf("%s", s + 1);
    for (i = 1; i <= N; ++i) {
        if (s[i] == 'A') {
            if (preA != 0) {
                ans = ans + preA;
                if (preB > 0 && preB < preA) ans--;
            } 
            preA = i;      
        } else {
            if (preB != 0) {
                ans = ans + preB;
                if (preA > 0 && preA < preB) ans--;
            } 
            preB = i;
        }
    }

    cout << ans << endl;
    return 0;
}