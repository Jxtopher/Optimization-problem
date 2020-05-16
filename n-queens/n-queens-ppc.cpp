///
/// @file n-queens-ppc.cpp
/// @author Jxtopher
/// @version 1
/// @date 2019
/// @brief http://www.csplib.org/Problems/prob054/
///
/// @compilation: g++ -Os n-queens-ppc.cpp -o n-queens-ppc -lgecodeint -lgecodesearch -lgecodekernel -lgecodesupport -lgecodedriver -lgecodeminimodel -lgecodegist
/// @fixed-bug-lib : sudo strip --remove-section=.note.ABI-tag /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.11.3
/// @execution: 
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
                for (long i = 0 ; i < n  ; i++) {
                    for(long j = i + 1 ; j < n ; j++) {
                        rel(*this, solution[i] != solution[j] - abs(j - i));
                        rel(*this, solution[i] != solution[j] + abs(j - i));
                    }
                }
            }

            branch(*this, solution, INT_VAR_SIZE_MIN(), INT_VAL_SPLIT_MIN());
        }


    Nqueen(Nqueen& s) : 
        Script(s), n(s.n) {
        solution.update(*this,  s.solution);
    }

    virtual Space* copy(void) {
        return new Nqueen(*this);
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
