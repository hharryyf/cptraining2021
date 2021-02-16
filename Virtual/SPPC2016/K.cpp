#include <bits/stdc++.h>
#define MAX_SIZE 111
using namespace std;

char s[MAX_SIZE];
int cnt[29];
map<char, int> cnt1, cnt2;
int s1, s2;

int main() {
    int i, len;
    scanf("%s", s);
    len = strlen(s);
    string st1 = "KANGAROO", st2 = "KIWIBIRD";
    for (auto ch : st1) cnt1[ch]++;
    for (auto ch : st2) cnt2[ch]++;
    for (i = 0 ; i < len; ++i) {
        if (s[i] >= 'a') s[i] = s[i] - 'a' + 'A';
        s1 += cnt1[s[i]];
        s2 += cnt2[s[i]];
    }

    if (s1 > s2) {
        printf("Kangaroos\n");
    } else if (s1 < s2) {
        printf("Kiwis\n");
    } else {
        printf("Feud continues\n");
    }
    return 0;
}