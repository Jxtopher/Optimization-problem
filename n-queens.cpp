//
// @Author: Jxtopher
// @License: *
// @Date: 2018
// @Version: 1
// @Purpose: solve the n-queeen problem with the depth-first search
//
// @Compilation:
// g++ n-queens.cpp -std=c++0x -Wall -O -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused
//
/* @Example class call Nqueen to solve the problem n-queen:
using namespace jxtopher;

int main() {
    unsigned int N = 5;
    Nqueen solver;
    solver.nqueen(N);
    return EXIT_SUCCESS;
}
*/

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <cmath>
#include <list>

using namespace std;

namespace jxtopher {

class Solution {
public:
	Solution(unsigned int _n) : n(_n) {
		s = new int[_n];
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
	void solver_nqueen(Solution &current_sol, list<Solution> & final_solution) {
		solver_nqueen(current_sol, 0, final_solution);
	}

	void nqueen(unsigned int n) {
		Solution solution(n);
		list <Solution> final_solution;
		solver_nqueen(solution, final_solution);

		cout<<"[+] Possible solutions :"<<endl;
		for (std::list<jxtopher::Solution>::iterator it=final_solution.begin(); it!=final_solution.end(); ++it)
			(*it).print();
		cout<<"[+] *** END ***"<<endl;
	}


protected:
	void solver_nqueen(Solution &current_sol, unsigned int currentCell, list<Solution> & final_solution) {
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
				bool constraint_line = check_line(current_sol, currentCell + 1);
				bool constraint_diagonal = check_diagonal(current_sol, currentCell + 1);

				if (constraint_line && constraint_diagonal) {
					// Descendre dans l'arbre (parcourt en profondeur)
					solver_nqueen(current_sol, currentCell + 1, final_solution);
				}
				i++;
			}
		}
	}

	bool check_diagonal(Solution &solution, unsigned int n) {
		for (unsigned int i = 0 ; i < n ; i++) {
			for (unsigned int j = i + 1 ; j < n ; j++) {
					if (abs(solution[i] - solution[j]) == abs(static_cast<int>(i) - static_cast<int>(j))) {
						return false;
					}
			}
		}
		return true;
	}

	bool check_line(Solution &solution, unsigned int n) {
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
