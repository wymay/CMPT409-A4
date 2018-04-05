# CMPT 409 A4

## Q1098 Robits on Ice
### Data Structure
* A map storing <state, possible route>.
### Algorithm
* Bidirectional BFS
  * The state is determined by a bitmap to store all visited positions and the current position.
  * The starting and ending states are known, BFS from these two states until the robot reaches the middle point. 
  * The result is the sum of multiplied state with the same bitmap.
### Prune to Reduce Time
* if the robot reach keypoints in wrong time
* the manhattan distance from current position to the next keypoint is more than the time left
* if the position about to visit cuts the surrounding into half

## Q10032 Tug of war
### Data Structure
* A 3D matrix DP[i][j][k], which means with the first i people, whether it is possible to form a team weights j with k people.
### Algorithm
* Dynamic Programming:
  * The initial state: DP[0][0][0]=True.
  * The DP recursion equation in 3D is DP[i][j][k] = DP[i-1][j][k] || DP[i-1][j-weight[i]][k-1].
* Compress the k dimension into a 64 bit integer and use bitwise operation to speed up.
  * The initial state: DP[0][0]=1, which means it is possible to get a team with weight 0 and 0 people.
  * The DP recursion equation in 2D is DP[i][j] = DP[i-1][j] | DP[i-1][j-weight[i]] << 1
* The DP need to run from large j to small j to reuse i dimension of the array. 

## Q2608 Constrained Circular Permutations:
### Data Structure:
* A vector storing the integer from 2 to N for further Permutations.
* An int count to count the valid permutations.
### Algorithm:
* Fix the first number as integer to reduce rotation-equivalence.
* Use recursion to compute permutations. 
  * Each time swap 2 values in the vector. 
  * Meanwhile, if the triplet sum is greater than the given number, stop and continue to next permutation.
* If the swap goes to the end of the vector, count++
* After checking all permutations, return count/2 as the result.
* In order to reduce time, check triplet sum while computing permutation to prune invalid ones.

## Q10006 Carmichael Number:
### Data Structure:
* An array primer[65001] storing whether it is a prime number or not.
### Algorithm:
* Update the primer[65001] using brute force, by looping prime from 2 to sqrt(65001) and their multiples.
* If the number is prime then it is normal, it is not, then using function testFermatFullEquation to get test all the Fermat tests.
### Several Points to Reduce Time:
* Function testFermatOneEquation using equation a^n mod n == (a^(n/2) mod n) * (a^(n/2) mod n) to reduce time and space of multiplication.
* After updating the table, time complexity of the function isPrime(n) is O(1). Do prime test before fermat tests to reduce the size numbers that is prime.
