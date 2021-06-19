#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

pair<int, int> a[33];


int main() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i) {
        cin >> a[i].first; 
        a[i].second = i;
    }

    sort(a + 1, a + 1 + N);

    int sm = 0;
    for (int i = 1; i < N; ++i) {
        sm += a[i].first;
    }

    if (sm < a[N].first) {
        printf("impossible\n");
        return 0;
    }

    for (int i = N; i >= 1; --i) {
        cout << a[i].second << " ";
    }
    cout << endl;
    return 0;
}