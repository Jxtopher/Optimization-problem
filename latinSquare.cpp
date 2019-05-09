//
// @Author: Jxtopher
// @Date: 27 Jan 2019
// @Version: 1 beta
// @Purpose: latin square
// @Compilation: g++ main.cpp -lgecodeint -lgecodesearch -lgecodekernel -lgecodesupport -lgecodedriver -lgecodeminimodel -lgecodegist
//

//
#include <iostream>
#include <unistd.h>

// gecode
#include <gecode/minimodel.hh>
#include <gecode/int.hh>
#include <gecode/driver.hh>

using namespace Gecode;
using namespace std;

class LatinSquare : public Script {
  public:
    LatinSquare(const SizeOptions &opt) : Script(opt),
                                            n(opt.size()),
                                            latinSquare(*this, n * n, 0, n - 1) {

        Matrix<IntVarArray> matrix(latinSquare, n, n);

        for (unsigned int i = 0 ; i < n ; i++) {
            distinct(*this, matrix.col(i));
            distinct(*this, matrix.row(i));
        }
        
        branch(*this, latinSquare, INT_VAR_SIZE_MIN(), INT_VAL_SPLIT_MIN());
    }

    LatinSquare(bool share, LatinSquare &s) : Script(share, s), n(s.n) {
        latinSquare.update(*this, share, s.latinSquare);
    }

    virtual Space *copy(bool share) {
        return new LatinSquare(share, *this);
    }

    virtual void print(std::ostream &os) const {
        Matrix<IntVarArray> matrix(latinSquare, n, n);
        for (int i = 0 ; i < n ; i++) {
            os << "\t";
            for (int j = 0 ; j < n ; j++) {
                os.width(2);
                os << matrix(i,j) << "  ";
            }
            os << std::endl;
        }
    }

  private:
    const int n;
    IntVarArray latinSquare;
};

int main() {
    SizeOptions opt("Latin square");
    opt.size(3);

    Script::run<LatinSquare, DFS, SizeOptions>(opt);
    return EXIT_SUCCESS;
}
