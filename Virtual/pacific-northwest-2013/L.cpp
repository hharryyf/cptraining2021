#include <bits/stdc++.h>
#define MAX_SIZE 1029
char s[MAX_SIZE];
using namespace std;

map<string, int> mp;
map<int, string> lead;
void SplitString(string s, vector<string>& v, const string& c) {
  for (auto &ch : s) {
      if (ch == '?' || ch == '!' || ch == ';' || ch == '\n' || ch == '.' || ch == '(' || ch == ')' || ch == '[' || ch == ']' 
      || ch == '{' || ch == '}' || ch == ',') ch = ' ';
  }
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(std::string::npos != pos2) {
    	v.push_back(s.substr(pos1, pos2-pos1));
        if (v.back().length() == 0 || v.back() == " ") v.pop_back();
    	pos1 = pos2 + c.size();
    	pos2 = s.find(c, pos1);
  }
 
  if(pos1 != s.length()) {
    	v.push_back(s.substr(pos1)); 
        if (v.back().length() == 0 || v.back() == " ") v.pop_back();
  }
}

int N;

int main() {
    scanf("%d\n", &N);
    int i, j;
    for (i = 1; i <= N; ++i) {
        fgets(s, MAX_SIZE, stdin);
        vector<string> vc;
        SplitString(string(s), vc, " ");
        lead[i] = vc.front();
        for (j = 1; j < (int) vc.size(); ++j) {
            for (auto &ch : vc[j]) {
                ch = tolower(ch);
            }
            mp[vc[j]] = i;
        }
    }

    while (fgets(s, MAX_SIZE, stdin) != NULL) {
        // printf("# %s\n", s);
        vector<string> vc;
        SplitString(string(s), vc, " ");
        for (auto v : vc) {
            for (auto &ch : v) {
                ch = tolower(ch);
            }
            // printf("%s\n", v.c_str());
            if (mp.find(v) != mp.end()) {
                printf("%s\n", lead[mp[v]].c_str());
                break; 
            }
        }
    }
    return 0;
}