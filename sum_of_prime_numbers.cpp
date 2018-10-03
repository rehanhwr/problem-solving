// C++ program to print some configurations of
// distinct prime numbers which its sum is equal to N
#include <bits/stdc++.h> 
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

bool prime[5000+7];

// function to get all prime number below n using sieveEratothenes
void SieveOfEratosthenes(int n) {

	// Create a boolean array "prime[0..n]" and initialize 
	// all entries it as true. A value in prime[i] will 
	// finally be false if i is Not a prime, else true.
	memset(prime, true, sizeof(prime)); 

	for (int p = 2; p * p <= n; p++) {
		
		// If prime[p] is not changed, then it is a prime 
		if (prime[p] == true) {
			
			// Update or mark as false all multiples of p 
			for (int i = p * 2; i <= n; i += p) {
				prime[i] = false; 
			}
		} 
	}
}

bool used[5000+7]; // boolean to check wether prime i has been used / included in result(solution)
vvi result; // vector of vector of int to store solution


void testIsNPrime(int n) {
	// check if n is prime number
	if (prime[n] && !used[n]) {
		vi vct;
		vct.push_back(n);
		result.push_back(vct);
		used[n] = true;
	}
}

// function to handle if N is even
void evenHandler(int n) {
	// using Goldbach Conjecture which stated that 
	// every even integer greater than two is the sum of two prime numbers.
	for (int i = 2; i < n; i++) {
		if (prime[i] && !used[i]) {
			if (prime[n-i] && !used[n-i] && (i != n-i)) {

				vi vct;
				vct.push_back(i);
				vct.push_back(n-i);

				// mark i and n-i as used
				used[i] = true;
				used[n-i] = true;

				result.push_back(vct);
			}
		}
	}

	testIsNPrime(n);
}

// function to handle if N is odd
void oddHandler(int n) {
	// the idea is substract N by odd prime number and then 
	// used Goldbach Conjecture to find the rest prime numbers
	for (int candidate = 3; candidate < n; candidate++) {
		// candidate should be odd prime number and not used as solution yet
		if ((candidate & 1) && prime[candidate] && !used[candidate]) {
			
			// remainder must be even
			int remainder = n - candidate;

			// basically this for loop is similar to evenHandler function
			// but it includes candidate as nominee of solution 
			// and add it as additional constraint to conditional statement
			for (int i = candidate + 1; i < remainder && !used[candidate]; i++) {
				if (prime[i] && !used[i]) {
					if (prime[remainder-i] && !used[remainder-i] 
						&& (i != remainder-i) && (remainder-i != candidate)) {

						vi vct;
						vct.push_back(candidate);
						vct.push_back(i);
						vct.push_back(remainder-i);
						
						// mark candidate, i and remainder as used
						used[candidate] = true;
						used[i] = true;
						used[remainder-i] = true;

						result.push_back(vct);
					}
				}
			}
		}
	}

	testIsNPrime(n);
}

// function to solve problem
void solve(int n) {

	// set initial value of used to false, if i is included in solution then
	// change its value (used[i]) to true.
	memset(used, false, sizeof used);

	used[0] = true;
	used[1] = true;

	// if n is odd
	if (n & 1) {
		oddHandler(n);
	} else {
		evenHandler(n);
	}

	if (result.size() == 0) {
		cout << "[[]]" << endl;
		return;
	}

	// print solution
	cout << "[" ;
	for (int i = 0; i < result.size(); i++) {
		cout << "[";
		for (int j = 0; j < result[i].size(); j++) {
			if (j == result[i].size() - 1) {
				cout << result[i][j];
			} else {
				cout << result[i][j] << ",";
			}
		}

		if (i == result.size() - 1) {
			cout << "]";
		} else {
			cout << "],";
		}
	}
	cout << "]\n";
}

// Main program to test above functions
int main() { 
	int N; 
	cin >> N;

	SieveOfEratosthenes(N); 
	solve(N);

	return 0; 
} 
