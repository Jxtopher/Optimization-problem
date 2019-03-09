///
/// \file n-queens-ppc.cpp
/// \author Jxtopher
/// \version 1
/// \date 2019
/// \brief http://www.csplib.org/Problems/prob054/
///
/// @compilation: g++ -Os n-queens-cnf-file.cpp -o n-queens-cnf-file
/// @Execution: g++ n-queens-ppc.cpp -lgecodeint -lgecodesearch -lgecodekernel -lgecodesupport -lgecodedriver -lgecodeminimodel -lgecodegist
///

//
#include <iostream>
#include <unistd.h>

// gecode
#include <gecode/minimodel.hh>
#include <gecode/int.hh>
#include <gecode/driver.hh>



using namespace Gecode;
using namespace std;

class Nqueen  : public Script {
    public:
        Nqueen(const SizeOptions& opt) : 
            Script(opt),
            n(opt.size()), 
            solution(*this, n, 0, n - 1) {

            // remove symmetry
            rel(*this, solution[0] == 1);

            // All cells must have a different value
            distinct(*this, solution);

            // diagos
            {
                for (unsigned int i = 0 ; i < n  ; i++) {
                    for(unsigned int j = i + 1 ; j < n ; j++) {
                        rel(*this, solution[i] != solution[j] - abs(j - i));
                        rel(*this, solution[i] != solution[j] + abs(j - i));
                    }
                }
            }

            branch(*this, solution, INT_VAR_SIZE_MIN(), INT_VAL_SPLIT_MIN());
        }


    Nqueen(bool share, Nqueen& s) : 
        Script(share,s), n(s.n) {
        solution.update(*this, share, s.solution);
    }

    virtual Space* copy(bool share) {
        return new Nqueen(share,*this);
    }

    virtual void print(std::ostream& os) const {
         

        for (unsigned int i = 0 ; i < n ; i++) {
            os<<solution[i];
            os.width(2);
        }
    }

    private:
        const int n;
        IntVarArray solution;  
};

int main() {
    SizeOptions opt("n-queen");
    opt.size(10);
    
    Script::run<Nqueen,DFS,SizeOptions>(opt);
    return EXIT_SUCCESS;
}
