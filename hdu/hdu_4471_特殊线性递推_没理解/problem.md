Problem Description
GS is suffering from tons of boring math assignment. He find it make him tired and impatient so he asks you to finish his assignment in hope that he could hang out in many places of interest and enjoy his life.
In this assignment, you’re asked to solve the following problem:
Given a recurrent function

$$ f[n] = \sum_{i=1}^t c[i] \, f[n-i] $$

and boundary values

$$ f[i], 1 \leq i \leq m $$

You should solve for f[n].
What a easy problems! Wait for a moment, you see a few lines in the last paragraph. It reads as follows: To make the problem a little hard, you are now informed that, at some special values of n (there are q such values, namely n1, n2, . . . , nq), the recurrent formula changes into something else, which means for the kth such value nk, the recurrent formula changes into

$$ f[n_k] = \sum_{i=1}^{t_k} c_k[i] \, f[n_k-i] $$

Still an easy problem, isn’t it?
Since f[n] may be quite large, you just need to output f[n] module 109 + 7.
 

Input
There are several test cases.
For each test case, the first line contains three integers n (m < n ≤ 109), m (1 ≤ m ≤ 100), q (0 ≤ q ≤ 100). The second line contains m integers, namely f[1], f[2], . . . , f[m].
The following line contains several integers, first comes t (t ≤ 100), then t integers namely c[1], c[2], . . . , c[t].
The following q lines describe q special cases of the recurrent formula, each containing several integers, namely nk, tk (tk ≤ 100, tk < nk), ck[1], ck[2], . . . , ck[tk], as mentioned earlier. It is satisfied that ni != nj if i != j.
All integers are non-negative. Unless specified, all integers are not greater than 109.
Input is terminated by EOF.
You might assume that all given data is correct.
 

Output
For each test case, output one line “Case X: Y” where X is the test case number (starting from 1) and Y is the desired answer.
 

Sample Input
7 5 0
1 1 2 3 5
2 1 1
10 5 1
1 1 2 3 5
2 1 1
10 2 1 2
 

Sample Output
Case 1: 13
Case 2: 76
 

Hint

In the first sample, you are to solve for f[7] where f[n] = f[n&#8722;1]+f[n&#8722;2] and f[1] = 1,
f[2] = 1, f[3] = 2, f[4] = 3, f[5] = 5.
In the second example, you are to solve for f[10] where f[n] = f[n &#8722; 1] + f[n &#8722; 2] and
f[1] = 1, f[2] = 1, f[3] = 2, f[4] = 3, f[5] = 5, as well as specially f[10] = f[9] + 2*f[8].