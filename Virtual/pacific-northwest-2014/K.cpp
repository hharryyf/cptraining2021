#include <bits/stdc++.h>
using namespace std;
int vals[5][5];
int usedR[5][5];
int usedC[5][5];
int colRest1[5];
int colRest2[5];
int rowRest1[5];
int rowRest2[5];
int N;

int checkCond() {
    int largest;
    int num;
    for (int row=0;row<N;row++) {
        largest = 0;
        num = 0;
        for (int col=0;col<N;col++) {
            if (vals[row][col] >= largest) {
                num += 1;
                largest = vals[row][col];
            }
        }
        if (rowRest1[row] && (rowRest1[row] != num)) {
            return 0;
        }
        largest = 0;
        num = 0;
        for (int col=N-1;col>-1;col--) {
            if (vals[row][col] >= largest) {
                num += 1;
                largest = vals[row][col];
            }
        }
        if (rowRest2[row] && (rowRest2[row] != num)) {
            return 0;
        }
    }
    for (int col=0;col<N;col++) {
        largest = 0;
        num = 0;
        for (int row=0;row<N;row++) {
            if (vals[row][col] >= largest) {
                num += 1;
                largest = vals[row][col];
            }
        }
        if (colRest1[col] && (colRest1[col] != num)) {
            return 0;
        }
        largest = 0;
        num = 0;
        for (int row=N-1;row>-1;row--) {
            if (vals[row][col] >= largest) {
                num += 1;
                largest = vals[row][col];
            }
        }
        if (colRest2[col] && (colRest2[col] != num)) {
            return 0;
        }
    }
    return 1;
}

int solve(int row, int col) {
    if (col == N) {
        row += 1;
        col = 0;
    }
    if (row == N) {
        // printf("REACHED");
        if (checkCond()) {
            return 1;
        }
        return 0;
    }
    // if (!checkCond()) {
    //     return 0;
    // }
    if (vals[row][col]) {
        return solve(row,col+1);
    }
    for (int i=0;i<N;i++) {
        if (usedR[row][i] || usedC[col][i]) {
            continue;
        }
        usedR[row][i] = 1;
        usedC[col][i] = 1;
        vals[row][col] = i+1;
        if (solve(row,col+1)) {
            return 1;
        }
        usedR[row][i] = 0;
        usedC[col][i] = 0;
        vals[row][col] = 0;
    }
    return 0;
}

int main() {
    int T;
    char row[8];
    scanf("%d",&T);
    for (int caseN = 0; caseN < T; caseN++) {
        int bad = 0;
        for (int i=0;i<5;i++) {
            for (int j=0;j<5;j++) {
                vals[i][j] = 0;
                usedR[i][j] = 0;
                usedC[i][j] = 0;
                colRest1[i] = 0;
                colRest2[i] = 0;
                rowRest1[i] = 0;
                rowRest2[i] = 0;
            }
        }
        scanf("%d",&N);
        for (int i=0;i<N+2;i++) {
            scanf("%s",row);
            if (i==0) {
                for (int j=0;j<N+2;j++) {
                    char c = row[j];
                    if (c != '-') {
                        colRest1[j-1] = c-'0';
                    }
                }
            } else if (i==N+1) {
                for (int j=0;j<N+2;j++) {
                    char c = row[j];
                    if (c != '-') {
                        colRest2[j-1] = c-'0';
                    }
                }
            } else {
                if (row[0] != '-') {
                    rowRest1[i-1] = row[0]-'0';
                }
                if (row[N+1] != '-') {
                    rowRest2[i-1] = row[N+1]-'0';
                }
                for (int j=1;j<N+1;j++) {
                    if (row[j] != '-') {
                        vals[i-1][j-1] = row[j]-'0';
                        if (usedR[i-1][row[j]-'0'-1] || usedC[j-1][row[j]-'0'-1]) {
                            bad = 1;
                        }
                        usedR[i-1][row[j]-'0'-1] = 1;
                        usedC[j-1][row[j]-'0'-1] = 1;
                    }
                }
            }
        }
        // for (int i=0;i<N;i++) {
        //         for (int j=0;j<N;j++) {
        //             printf("%d",vals[i][j]);
        //         }
        //         printf("\n");
        //     }
        //     printf("\n");
        if (bad || !solve(0,0)) {
            printf("no\n\n");
        } else {
            for (int i=0;i<N;i++) {
                for (int j=0;j<N;j++) {
                    printf("%d",vals[i][j]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}