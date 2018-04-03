Q1098 Robots on Ice:
Basic idea is bidirectional BFS. The state is determined by: a bitmap to store all visited positions and the current position. Use a map to store  <state, possible route>. The starting and ending states are known, BFS from these two state until the robot reach the middle point. Result is the sum of multiplied state with the same bitmap.
Prune to reduce time:
1. if the robot reach keypoints in wrong time
2. the manhattan distance from current position to next keypoint is more than the time left
3. if the position about to visit cut the surrounding into half

Q10032 Tug of war:
Use DP to find the max weight of the team with less people. DP[i][j][k] means with the first i people, it's possible to form a team weights j with k people. DP[i][j][k] = DP[i-1][j][k] || DP[i-1][j-weight[i]][k-1]. DP[0][0][0]=True. We can compress the k dimension into a 64 bit integer because maximum number of people in a team is 50, and use bitwise operation to speed up. Then the DP becomes: DP[i][j] = DP[i-1][j] | DP[i-1][j-weight[i]] << 1. DP[0][0] is 1, which means it's possible to get a team with weight 0 and 0 people. We can reuse i dimension of the array, then the DP need to run from large j to small j. 

Q2608 Constrained Circular Permutations:
- Data Structure:
Using vector to store the integer from 2 to N for further Permutations.
Using int count to count the valid permutations.
- Algorithm:
1. Fix the first number as integer to reduce rotation-equivalence.
2. Use recursion to compute permutations. Each time swap 2 values in the vector. Meanwhile, if the triplet sum is greater than the given number, stop and continue to next permutation.
3. If the swap goes to the end of the vector, count++
4. After checking all permutations, return count/2 as a result (reduce the mirror-equivalence).
[In order to reduce time, checking triplet sum while computing permutation to prune invalid ones]

Q10006 Carmichael Number:
- Data Structure:
Using array primer[65001] to store if it is a prime number or not.
- Algorithm:
1. First, update the primer[65001] for later convenience to know if it is prime.
	To update the array, using brute force loop  prime from 2 to sqrt(65001) and their multiples to get composite number.
2. Second, if the number is prime then it is normal, it is not, then using function testFermatFullEquation to get test all the Fermat tests.
	function testFermatOneEquation using equation a^n mod n == (a^(n/2) mod n) * (a^(n/2) mod n) to reduce multiple time and reduce size of multiple number.

Several Points to reduce time:
1. improving Fermat test like we mentioned above in point 2 to reduce reduce multiple time and reduce size of multiple number.
2. After update table. function isPrime(n) time complexity is O(1).
	Do prime test first then do fermat tests to reduce number for those which is prime.
