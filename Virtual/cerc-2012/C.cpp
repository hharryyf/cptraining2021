#include <bits/stdc++.h>

using namespace std;

vector<string> st = {"H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne",
"Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar",
"K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr",
"Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe",
"Cs", "Ba",  "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn",
"Fr", "Ra",  "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Fl", "Lv",
"La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu",
"Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk",  "Cf",  "Es",  "Fm",  "Md",  "No",  "Lr"};
unordered_set<string> table;

#define MAX_SIZE 50011
int dp[MAX_SIZE];
char a[MAX_SIZE];

void change(string &ss) {
    for (auto &ch : ss) {
        if (ch >= 'A' && ch <= 'Z') ch += 'a' - 'A';
    }
}

int main() {
    int T;
    for (auto v : st) {
        change(v);
        table.insert(v);
    }
    scanf("%d", &T);
    while (T-- > 0) {
        scanf("%s", a + 1);
        int i, N = strlen(a + 1);
        dp[0] = 1;
        for (i = 1; i <= N; ++i) dp[i] = 0;
        string curr = "";
        curr += a[1];
        if (table.find(curr) != table.end()) dp[1] = 1;
        for (i = 2; i <= N; ++i) {
            curr = "";
            curr += a[i];
            if (table.find(curr) != table.end()) {
                dp[i] |= dp[i-1];
            }
            curr += a[i-1];
            reverse(curr.begin(), curr.end());
            if (table.find(curr) != table.end()) {
                dp[i] |= dp[i-2];
            }
        }

        printf("%s\n", dp[N] ? "YES" : "NO");
    }
    return 0;
}