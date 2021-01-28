# cptraining2021
Practice for 2021 SPPC, the aim for this training is to revenge for the unfortunate defeat to TLE 2020 in SPPC 2020

* Phase 1: FFT, Combinatorics and Geometry 
1. Thief in a Shop (diff=2400, FFT, exponential by squaring)
This is the standard application of FFT, generating all possible sum of a[i] + b[j].
https://codeforces.com/problemset/problem/632/E


2. Sum of Paths (diff=2200, dp, combinatorics)
This is a very technical problem. Define dp[i][j] as the number of paths that ends/starts at i after j steps.
Then, we claim the contribution of element i is cnt[i] = sum(dp[i][j] * dp[i][K-j], j = 0..K). The second formula
is quite hard to understand. The main reason for it to work is instead of counting cnt[i] directly we can think
cnt[i] as the total contribution of a[i] appears at the jth position. This is again the common combinatorics trick: "calculate twice".
https://codeforces.com/contest/1467/problem/D


3. K and Medians (diff=2200, constructive algorithm, ad-hoc)
The problem is quite simple. Note that the answer is yes 
iff there are even number of chunks of size (k-1) / 2 and there is at least 1 remaining elements between the 
last element of the first chunk and the first element of the last chunk. https://codeforces.com/problemset/problem/1468/H


4. LaIS (diff=2200, range tree, dp)
The observation is if we define dp[i] = maximum LAIS that ends at i, there are two types of transition. Type 1 is the
standard LIS transition, type 2 is the transition from dp[j] + 2 which a[j] <= a[i] and there exists some k such that
k is between j and i and a[k] >= a[j]. Type 2 transition can be done with sweeping.
https://codeforces.com/contest/1468/problem/A


5. Lucky Tickets (diff=2400, NTT)
The observation is there are only 9e5 many possible sums for the first half. If we can calculate how many ways to construct
easy of these sum, the answer is trivial. How to compute this? It is exactly the same as CF632E but since mod is required we
use NTT instead of FFT. https://codeforces.com/problemset/problem/1096/G


6. Lightsabers (hard) (diff=2600, FFT, greedy)
It is not hard to see the answer is the coefficient of the degree K term of the polynomial which p[i] = 1 + x + ... + x^cnt which
cnt is the occurence of i in the array. But how can we multiply things together? Remember the standard greedy problem, stone merging?
We can maintain the size of the polynomials and always multiply the two shortest polynomials together.
https://codeforces.com/contest/958/problem/F3

7. Strange Housing (diff=2200, constructive algorithm, ad-hoc)
The problem is not hard. It can be seen easily the only break condition is the graph is not connected. Then, we get an uncolored vertex
and color it 1 and then set all of its neighbour to be 0, then pick a vertex that is connected to a "0" vertex and repeat the above 
procedure until no vertex can be colored. https://codeforces.com/contest/1471/problem/F

8. Cleaning (diff=2200, ad-hoc, line sweep)
The problem is quite stright forward. If we look at the piles from left to right we can easily write out an alternative sign equation.
https://codeforces.com/problemset/problem/1474/D


9. Barrels and boxes (diff=2300, combinatorics, stars and bars)
Quite standard starts and bars combinatorics https://codeforces.com/problemset/problem/768/F


