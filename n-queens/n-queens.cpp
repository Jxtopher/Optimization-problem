///
/// @file n-queens-ppc.cpp
/// @author Jxtopher
/// @version 1
/// @date 2018
/// @brief solve the n-queeen problem with the depth-first search
///
/// @compilation: g++ n-queens.cpp -std=c++0x -Wall -O -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
///

/* @Example class call Nqueen to solve the problem n-queen:
using namespace jxtopher;

int main() {
    unsigned int N = 5;
    Nqueen solver;
    solver.nqueen_recursive(N);
	solver.nqueen_iterative(N);
    return EXIT_SUCCESS;
}
*/

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <list>
#include <vector>

using namespace std;

namespace jxtopher {

class Solution {
public:
	Solution(unsigned int _n) : n(_n) {
		s = new int[_n];
	}

	Solution(const vector<int> & solution) {
		n = solution.size();
		s = new int[solution.size()];
		
		for (unsigned int i = 0 ; i < solution.size() ; i++) {
			s[i] = solution[i];
		}
	}

	Solution(const Solution & solution) {
		s = new int[solution.n];
		for (unsigned int i = 0 ; i < solution.n ; i++) {
			s[i] = solution.s[i];
		}
		n = solution.n;
	}

	Solution & operator=(const Solution &solution) {
		if (solution.n == n) {
			for (unsigned int i = 0 ; i < solution.n ; i++) {
				s[i] = solution.s[i];
			}
			n = solution.n;
		} else {
			delete s;
			s = new int[solution.n];
			for (unsigned int i = 0 ; i < solution.n ; i++) {
				s[i] = solution.s[i];
			}
			n = solution.n;
		}
		return *this;
	}

	virtual ~Solution() {
		delete s;
	}

	void print() {
		for (unsigned int i = 0 ; i < n ; i++) {
			cout<<s[i]<<" ";
		}
		cout<<endl;
	}

	void init_solution() {
		for (unsigned int i = 0 ; i < n ; i++)
			s[i] = -1;
	}

	int operator[](unsigned int index) const {
		return s[index];
	}

	int & operator[](unsigned int index) {
		return s[index];
	}

	unsigned int size() const {
		return n;
	}

private:
	int *s;
	unsigned int n;
};

class Nqueen {
public:
	void backtracking_recursive(Solution &current_sol, list<Solution> & final_solution) {
		backtracking_recursive(current_sol, 0, final_solution);
	}

	void nqueen_recursive(unsigned int n) {
		Solution solution(n);
		list <Solution> final_solution;
		backtracking_recursive(solution, final_solution);

		cout<<"[+] Possible solutions :"<<endl;
		unsigned int i = 1;
		for (std::list<jxtopher::Solution>::iterator it=final_solution.begin(); it!=final_solution.end(); ++it) {
			cout<<i++<<" : ";
			(*it).print();
		}
		cout<<"[+] *** END ***"<<endl;
	}

	void nqueen_iterative(unsigned int n) {
		Solution solution(n);
		list <vector<int>> final_solution;
		backtracking_iterative(static_cast<int>(n), n, final_solution);

		cout<<"[+] Possible solutions :"<<endl;
		unsigned int i = 1;
		for (std::list<vector<int>>::iterator it=final_solution.begin(); it!=final_solution.end(); ++it) {
			cout<<i++<<" : ";
			for (unsigned int j = 0 ; j < (*it).size() ; j++) {
				cout<<(*it)[j]<<" ";
			}
			cout<<endl;
		}
		cout<<"[+] *** END ***"<<endl;
	}

protected:
	// --------------------------------------------------------------------------
	// Backtracking recursive
	// --------------------------------------------------------------------------
	void backtracking_recursive(Solution &current_sol, unsigned int currentCell, list<Solution> & final_solution) {
		//current_sol.print();
		if (current_sol.size() == currentCell) {
			final_solution.push_front(Solution(current_sol));
			//cout<<"Wine : ";
			//current_sol.print();
		} else {
			unsigned int i = 0;
			while(i < current_sol.size()) {
				current_sol[currentCell] = static_cast<int>(i);

				//Verification des contraites
				if (filtering(current_sol, currentCell + 1)) {
					// Descendre dans l'arbre (parcourt en profondeur)
					backtracking_recursive(current_sol, currentCell + 1, final_solution);
				}
				i++;
			}
		}
	}

	// Vérification des contraites
	bool filtering(const Solution &solution, const unsigned int n) {
			bool constraint_line = check_line(solution, n);
			bool constraint_diagonal = check_diagonal(solution, n);
			return constraint_line && constraint_diagonal;
	}

	bool check_diagonal(const Solution &solution, const unsigned int n) {
		for (unsigned int i = 0 ; i < n ; i++) {
			for (unsigned int j = i + 1 ; j < n ; j++) {
					if (abs(solution[i] - solution[j]) == abs(static_cast<int>(i) - static_cast<int>(j))) {
						return false;
					}
			}
		}
		return true;
	}

	bool check_line(const Solution &solution, const unsigned int n) {
		for (unsigned int i = 0 ; i < n ; i++) {
			for (unsigned int j = i + 1 ; j < n; j++) {
				if (solution[i] == solution[j])
					return false;
			}
		}
		return true;
	}

	// --------------------------------------------------------------------------
	// Backtracking iterative
	// --------------------------------------------------------------------------
	void backtracking_iterative(const int nbDigit, const unsigned int len_string, list<vector<int>> & final_solution) {
		vector<int> string;
		unsigned int index = 0;
		
		while(true) {
			if (string.size() < len_string) {
				string.push_back(0);
				index++;
			} else if(string[string.size() - 1] != nbDigit - 1) {
					string[string.size() - 1] = (string[string.size() - 1] + 1) % nbDigit;
			} else {
				do {
					string.pop_back();
					if (string.size() == 0) {
						return ;
					}
				} while (string[string.size() - 1] == nbDigit - 1);
				string[string.size() - 1] = (string[string.size() - 1] + 1) % nbDigit;
			}

			// Filtrage
			while (!filtering(string, string.size())) {
				if(string[string.size() - 1] != nbDigit - 1) {
					string[string.size() - 1] = (string[string.size() - 1] + 1) % nbDigit;
				} else {
					do {
						string.pop_back();
						if (string.size() == 0) {
							return ;
						}
					} while (string[string.size() - 1] == nbDigit - 1);
					string[string.size() - 1] = (string[string.size() - 1] + 1) % nbDigit;
				}
			}

			// Memorisation des solutions valide
			if (string.size() == len_string) {
				final_solution.push_front(string);
				/*for (unsigned int k = 0 ; k < string.size() ; k++)
					cout<<string[k]<<" ";
				cout<<endl;*/
			}
		}
	}


	// Vérification des contraites
	bool filtering(const vector<int> &solution, const unsigned int n) {
			bool constraint_line = check_line(solution, n);
			bool constraint_diagonal = check_diagonal(solution, n);
			return constraint_line && constraint_diagonal;
	}

	bool check_diagonal(const vector<int> &solution, const unsigned int n) {
		for (unsigned int i = 0 ; i < n ; i++) {
			for (unsigned int j = i + 1 ; j < n ; j++) {
					if (abs(solution[i] - solution[j]) == abs(static_cast<int>(i) - static_cast<int>(j))) {
						return false;
					}
			}
		}
		return true;
	}

	bool check_line(const vector<int> &solution, const unsigned int n) {
		for (unsigned int i = 0 ; i < n ; i++) {
			for (unsigned int j = i + 1 ; j < n; j++) {
				if (solution[i] == solution[j])
					return false;
			}
		}
		return true;
	}
};

}


