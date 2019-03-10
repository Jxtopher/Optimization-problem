///
/// \file n-queens-cnf-file.cpp
/// \author Jxtopher
/// \version 1
/// \date 2019
/// \brief Generator CNF File for n-queens problem
///
/// @compilation: g++ -Os n-queens-cnf-file.cpp -o n-queens-cnf-file
/// @execution: ./n-queens-cnf-file 4 | picosat --all
///

#include <cstdlib>  // EXIT_SUCCESS
#include <iostream> // count, endl
#include <vector>   // vector
#include <sstream>  // stringstream

using namespace std;

void createnumClauses(vector<unsigned int> &v, stringstream &clauses, unsigned int &numClauses) {
    for (unsigned int i = 0 ; i < v.size() ; i++) {
        clauses<<"-"<<v[i]<<" ";
    }

    numClauses++;
    clauses<<"0"<<endl;

    if (2 < v.size()) {
        for (unsigned int i = 0 ; i < v.size() ; i++) {
            for(unsigned int j = i + 1 ; j < v.size() ; j++) {
                numClauses++;
                clauses<<"-"<<v[i]<<" -"<<v[j]<<" 0"<<endl;
            }
        }
    }

    clauses<<endl;
    v.clear();   
}

int main(int argc, char **argv) {
    stringstream clauses;
    unsigned int n = 4;
    if (argc == 2) 
        n = atoi(argv[1]);
    unsigned int numClauses = 0;
    unsigned int matrix[n][n];

    for(unsigned int i = 0, count = 1 ; i < n ; i++) {
        for(unsigned int j = 0 ; j < n ; j++) {
            matrix[i][j] = count++;
        }
    }


    // Lines
    clauses<<"c lines"<<endl;
    for(unsigned int i = 0 ; i < n ; i++) {
        for(unsigned int j = 0 ; j < n ; j++) {
           clauses<<matrix[i][j]<<" ";
        }
        numClauses++;
        clauses<<"0"<<endl;

        for(unsigned int j = 0 ; j < n ; j++) {
            for(unsigned int k = j + 1 ; k < n ; k++) {
                numClauses++;
                clauses<<"-"<<matrix[i][j]<<" -"<<matrix[i][k]<<" 0"<<endl;
            }
        }

        clauses<<endl;
    }


    // Columns
    clauses<<"c columns"<<endl;
    for(unsigned int i = 0 ; i < n ; i++) {
        for(unsigned int j = 0 ; j < n ; j++) {
           clauses<<matrix[j][i]<<" ";
        }
        numClauses++;
        clauses<<"0"<<endl;

        for(unsigned int j = 0 ; j < n ; j++) {
            for(unsigned int k = j + 1 ; k < n ; k++) {
                numClauses++;
                clauses<<"-"<<matrix[j][i]<<" -"<<matrix[k][i]<<" 0"<<endl;
            }
        }

        clauses<<endl;
    }

    // diagonales
    clauses<<"c diagonales"<<endl;
    vector<unsigned int> v;
    for (unsigned int i = 0 ; i < n ; i++) {
            v.push_back(matrix[i][i]);
    }
    createnumClauses(v, clauses, numClauses);

    for (unsigned int i = 1 ; i < n - 1 ; i++) { 
        for(unsigned int j = 0,  k = i ; k < n ; j++, k++) {
                v.push_back(matrix[j][k]);
        }
        createnumClauses(v, clauses, numClauses);

        for(unsigned int j = i,  k = 0 ; j < n ; j++, k++) {
                v.push_back(matrix[j][k]);
        }
        createnumClauses(v, clauses, numClauses);
    }
    
    // anti-diagonals
    clauses<<"c anti-diagonals"<<endl;
    for (unsigned int i = 0 ; i < n ; i++) { 
            v.push_back(matrix[i][n-i-1]);
    }
    createnumClauses(v, clauses, numClauses);

    for (unsigned int i = 1 ; i < n - 1 ; i++) { 
        for(unsigned int j = 0,  k = i ; k < n ; j++, k++) {
                v.push_back(matrix[j][n-1-k]);
        }
        createnumClauses(v, clauses, numClauses);

        for(unsigned int j = i,  k = 0 ; j < n ; j++, k++) {
                v.push_back(matrix[j][n-1-k]);
        }
        createnumClauses(v, clauses, numClauses);
    }

    //
    cout<<"c  "<<n<<"-queens-CNF-File.cnf"<<endl;
    cout<<"c"<<endl;
    cout<<"p cnf "<<n*n<<" "<<numClauses<<endl;

    cout<<clauses.str();

    return EXIT_SUCCESS;
}
