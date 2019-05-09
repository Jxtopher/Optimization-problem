//
// @Author: Jxtopher
// @Date: 27 Jan 2019
// @Version: 1 beta
// @Purpose: http://www.csplib.org/Problems/prob019/
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

class MagicSequence : public Script {
  public:
	MagicSequence(const SizeOptions &opt) :
		Script(opt),
		n(opt.size()),
		sequence(*this, n, 0, n - 1) {

		IntRelType s(IRT_EQ);

		for (unsigned int i = 0; i < n; i++) {
			count(*this, sequence, i, s, sequence[i]);
		}

		rel(*this, sum(sequence) == n);

		branch(*this, sequence, INT_VAR_SIZE_MIN(), INT_VAL_SPLIT_MIN());
	}

	MagicSequence(bool share, MagicSequence &s) : Script(share, s), n(s.n) {
		sequence.update(*this, share, s.sequence);
	}

	virtual Space *copy(bool share) {
		return new MagicSequence(share, *this);
	}

	virtual void print(std::ostream &os) const {
		for (unsigned int i = 0; i < n; i++) {
			os << sequence[i];
			os.width(2);
		}
	}

  private:
	const int n;
	IntVarArray sequence;
};

int main() {
	SizeOptions opt("Magic Sequence");
	opt.size(10);

	Script::run<MagicSequence, DFS, SizeOptions>(opt);
	return EXIT_SUCCESS;
}
