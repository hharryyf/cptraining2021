# cptraining2021
Practice for 2021 SPPC, the aim for this training is to revenge for the unfortunate defeat to TLE 2020 in SPPC 2020

* Phase 1: FFT, Combinatorics and ad-hoc 
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


10. Similar Sets (diff=2300, ad-hoc, sqrt decomposition)
This is a very technical problem. First step, divide the sets into small and large the boundary is sqrt(M), here M is the sum of ki.
Then, for larger sets we just see directly if it is similar to another set. For small sets, we can put all the combination of numbers
into array of vectors and use the same trick as the larger set part to solve it. https://codeforces.com/problemset/problem/1468/M


11. The Great Mixing (diff=2300, ad-hoc, BFS) 
This is a very techinical problem. Note that solving equation (n-a[1]) + (n-a[2]) + ... + (n-a[p]) = 0 can be done
with BFS cycle detection!! After that, we must realize that the order a[1]..a[p] is not matter, which means only concentration -1000 to 1000 is necessary. https://codeforces.com/problemset/problem/788/C


12. Nezzar and Board (diff=1800, ad-hoc, constructive algorithm)
The problem is quite easy but interesting. Consider given 2 numbers x and y then the resulting sequence formed by all numbers that
has difference k times (y - x) with x. Then, if we generalize this to N numbers if would be a sequence has difference of gcd(a[i] - a[i-1]) from a[0]. https://codeforces.com/problemset/problem/1477/A


13. Nezzar and Binary String (diff=1900, ad-hoc, range tree)
This problem is simple, just reverse the order of the queries and we are done. https://codeforces.com/problemset/problem/1477/B


14. Nezzar and Nice Beatmap (diff=2200, geometry, constructive algorithm)
Trick: always walk to the furthest point. https://codeforces.com/problemset/problem/1477/C


15. Unusual Matrix (diff=1900, Ad-hoc, 2-cnf)
Think the problem as a 2CNF and we are done. https://codeforces.com/contest/1475/problem/F

16. Mahmoud and Ehab and another array construction task (diff=1900, math)
The idea is we are actually interested in the MEX. 
https://codeforces.com/problemset/problem/959/D


17. Number of Simple Paths (diff=2000, tree dp, observation)
Just observe that if we extract the cycle first, only pair of points that are in different "rooted cycle tree" would contribute
to the answer twice. https://codeforces.com/problemset/problem/1454/E

18. Memory and Scores (diff=2200, knapsack dp)
Key observation: take the difference between dp[t-1][diff] and dp[t-1][diff-1] and you'll see something.
https://codeforces.com/problemset/problem/712/D


19. Hobbits (diff=2500, geometry, cross product)
This problem is quite simple, only requires some high school geometry stuff. The only place to be careful is precision control,
https://codeforces.com/contest/1468/problem/G


20. Pashmak and Buses (diff=1900, constructive algorithm, math)
Just use k-based representation of 1 to n, d^k is less than n then no solution. https://codeforces.com/problemset/problem/459/C


21. Divide and Sum (diff=1900, math, combinatorics, proof by contradiction)
It can be proved by constradiction that all partitions have the same cost. 
https://codeforces.com/problemset/problem/1444/B


22. AB-string (diff=1900, combinatorics)
Just remember the string only contains 2 types of characters, if you try to solve a general problem 'A' - 'Z' then you are dead.
https://codeforces.com/contest/1238/problem/D


23. SPPC 2020 problem B (dp, line sweep, range tree)
This problem is exactly the same as NWERC 2019 problem H, just write out the equation of dp and use the same trick to maintain it.
I'm completely confused on why we haven't solve that in contest. 


24. Classy Numbers (diff=1900, generating combinations, binary search)
If can be observed that the total valid number less than 1e18 + 1 is only around 6e5, we can generate all of them and use
binary search for each query. https://codeforces.com/problemset/problem/1036/C


25. Print a 1337-string... (diff=1900, Ad-hoc, constructive algorithm)
The idea is quite easy, just always find the larget T such that C(T, 2) <= N. https://codeforces.com/contest/1202/problem/D


26. 505 (diff=2000, Ad-hoc, dp on broken profile)
It can be observed easily that when min(N, M) > 3 there's no solution and for other cases we can use dp on broken profile.
https://codeforces.com/problemset/problem/1391/D


27. Pathwalks (diff=2100, dp, dynamic range tree)
Quite simple, just LIS on graph. https://codeforces.com/problemset/problem/960/F


28. Make Them Equal (diff=2000, ad-hoc, constructive algorithm)
Think what initially positive element means. https://codeforces.com/contest/1416/problem/B


29. Maximum Value (diff=2100, partial sum, sparse table)
The idea is we can make good use of the partial sum n / 1 + n / 2 + ... + n / n = O(nlogn).
https://codeforces.com/problemset/problem/484/B


30. Guess the Root (diff=2200, gaussian elimination)
It is a good problem to test the gaussian elimination template. 
https://codeforces.com/contest/1155/problem/E


31. Grime Zoo (diff=2100, ad-hoc)
I guessed the ? are replaced with 111...000 or 000...111 and magically it is correct. Actually, using proof
by contradiction can proof this easiliy. And the rest is a standard sweeping and data structure problem.
https://codeforces.com/contest/1411/problem/D


32. Longest Subsequence (diff=2100, math)
Exactly the same trick as CF1154g. https://codeforces.com/contest/632/problem/D


33. Vasya and Beautiful Arrays (diff=2100, math, sparse table)
Exactly the same trick as CF484B. https://codeforces.com/problemset/problem/354/C


34. Replace by MEX (diff=1900, constructive algorithm, ad-hoc)
Make the final array to [0,1,2...n-1]. https://codeforces.com/contest/1375/problem/D


35. Maximum Subsequence Value (diff=1900, constructive algorithm, ad-hoc)
The idea is think what k - 2 means, how many element should the final array consists. 
https://codeforces.com/problemset/problem/1365/E


36. Population Size (diff=2400, greedy, ad-hoc)
It can be proved easily that always go for the rightmost valid position is optimal. The rest would be case work.
https://codeforces.com/contest/416/problem/D


37. Chris and Road (diff=2100, geometry)
Need to be aware of precision. https://codeforces.com/contest/703/problem/C


38. Kuroni and the Celebration (diff=1900, Ad-hoc)
Always get 2 degree 1 node and query. Eliminate all nodes on the path except the LCA.
https://codeforces.com/problemset/problem/1305/D


39. Painting the Array I (diff=1900)
This is an insane problem, guess the result. https://codeforces.com/contest/1479/problem/B1


40. Shovels Shop (diff=2100, dp, greedy)
It can be seen quite easily that only the first K items are useful and we can do a O(K^2) dp with this observation.
https://codeforces.com/problemset/problem/1154/F


41. Super M (diff=2200, tree diameter)
This problem uses the property of euler traversal of a tree. https://codeforces.com/contest/592/problem/D


42. Two strings (diff=2100, greedy, binary search)
Quite standard trick, I've seen this trick more than 5 times. https://codeforces.com/contest/762/problem/C


43. Multiples and Power Differences (diff=2200, Ad-hoc)
The key of solving this problem is to realize two facts, the grid is bipartite and LCM(1, 2, 3...16) + 16^4 <= 1e6.
https://codeforces.com/problemset/problem/1485/D


44.  Ivan and Burgers (diff=2500, range tree, z2_basis)
The only fuck about this problem is the time limit is so tight. https://codeforces.com/contest/1100/problem/F

45 - 54. SPPC 2016 except H
https://codeforces.com/gym/101177/attachments


55. Containment (min-cut, enclosure graph model)
https://codeforces.com/gym/100827

56. Function (implementation)
https://codeforces.com/gym/100827

57. Pushups (simple dp)
https://codeforces.com/gym/100827

58. Salary Inequity (range tree)
https://codeforces.com/gym/100827

59 - 66 pacific-north-west-div1-2015 (ACDEGHJK)
https://codeforces.com/gym/100820/attachments

67 - 76 pacific-north-west-div1-2014 (ACDEFGHIKL)
https://codeforces.com/gym/100827/problem/G


77 - 88 pacific-north-west-div1-2013 (ABCDEFGHIKLM)
https://codeforces.com/gym/101655/attachments/download/6474/20132014-acmicpc-pacific-northwest-regional-contest-en.pdf


89 - 94 asia-seoul-2020 (BEFHIL)
This contest is extremely technical, F is dominate tree, I is divc optimization.
https://codeforces.com/gym/102920

95. Travelling Salesman Problem (diff=2200, ad-hoc, greedy)
The simple observation is the cost is at least the sum of c[i]. Then, we should realize the cost from the smallest
a[i] to largest a[i] is something we must consider because the rest would be free. 
https://codeforces.com/contest/1503/problem/C

96 - 104 nwerc-2014 (C-K)
https://codeforces.com/gym/101482

105 -112 nwerc-2012 (ABDEFIJK)
https://codeforces.com/gym/101398

113 - 122 nwerc-2020 (ACDEFGHIJK)
https://codeforces.com/gym/103049

123 - 134 Asia-Daejeon-2017
https://codeforces.com/gym/101667

135 - 144 SWERC-2020 (Without B, J, M)
https://codeforces.com/gym/103081/problem/F

145 - 154 CHINA-FINAL/EAST-ASIA-2016 (without I, K)
https://codeforces.com/gym/101194/attachments

155 - 164 NWERC-2016 (Without D)
https://codeforces.com/gym/101170

165 - 172 CERC-2012 (ACDEGHIJ)
https://codeforces.com/gym/100624/attachments

173 - 183 SPPC-2017 (ACDEFGHIJKL)
The problem link is at prog4fun.

184. Interstellar Travel (line sweep)
The idea of this problem is very simple, but the implementation is annoying. For each star, the contribution is like a line wave.
We can use line sweep to sum of the contribution, and query at the turning points. https://codeforces.com/gym/102423/

185 - 194 Asia-Seoul-2018 (no H and I)
https://codeforces.com/gym/101987/
