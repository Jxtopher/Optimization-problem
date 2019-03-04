//
// @Author: Jxtopher
// @Date: 2019
// @Version: 1
// @Purpose: Generator CNF File for n-queens problem
// @compilation: g++ -Os n-queens-cnf-file.cpp -o n-queens-cnf-file
// @Execution: ./n-queen-cnf-file 4 | picosat --all
//

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void createClauses(vector<unsigned int> &v, stringstream &results, unsigned int &clauses) {
    for (unsigned int l = 0 ; l < v.size() ; l++) {
        results<<"-"<<v[l]<<" ";
    }
    clauses++;
    results<<"0"<<endl;

    if (2 < v.size()) {
        for (unsigned int l = 0 ; l < v.size() ; l++) {
            for(unsigned int m = l + 1 ; m < v.size() ; m++) {
                clauses++;
                results<<"-"<<v[l]<<" -"<<v[m]<<" 0"<<endl;
            }
        }
    }
    results<<endl;
    v.clear();
    
}

int main(int argc, char **argv) {


    stringstream results;
    unsigned int n = 4;
    if (argc == 2) 
        n = atoi(argv[1]);
    unsigned int clauses = 0;
    unsigned int matrix[n][n];

    for(unsigned int i = 0, count = 1 ; i < n ; i++) {
        for(unsigned int j = 0 ; j < n ; j++) {
            matrix[i][j] = count++;
        }
    }
       

    // Lignes
    for(unsigned int i = 0 ; i < n ; i++) {
        for(unsigned int j = 0 ; j < n ; j++) {
           results<<matrix[i][j]<<" ";
        }
        clauses++;
        results<<"0"<<endl;

        for(unsigned int j = 0 ; j < n ; j++) {
            for(unsigned int k = j + 1 ; k < n ; k++) {
                clauses++;
                results<<"-"<<matrix[i][j]<<" -"<<matrix[i][k]<<" 0"<<endl;
            }
        }

        results<<endl;
    }


    // Colonnes
    results<<"c colonnes"<<endl;
    for(unsigned int i = 0 ; i < n ; i++) {
        for(unsigned int j = 0 ; j < n ; j++) {
           results<<matrix[j][i]<<" ";
        }
        clauses++;
        results<<"0"<<endl;

        for(unsigned int j = 0 ; j < n ; j++) {
            for(unsigned int k = j + 1 ; k < n ; k++) {
                clauses++;
                results<<"-"<<matrix[j][i]<<" -"<<matrix[k][i]<<" 0"<<endl;
            }
        }

        results<<endl;
    }

    // diagos
    results<<"c diagos"<<endl;
    vector<unsigned int> v;
    for (unsigned int k = 0 ; k < n ; k++) {
            v.push_back(matrix[k][k]);
    }
    createClauses(v, results, clauses);

    

    for (unsigned int k = 1 ; k < n - 1 ; k++) { 
        for(unsigned int i = 0,  j = k ; j < n ; i++, j++) {
                v.push_back(matrix[i][j]);
        }
        createClauses(v, results, clauses);

        for(unsigned int i = k,  j = 0 ; i < n ; i++, j++) {
                v.push_back(matrix[i][j]);
        }
        createClauses(v, results, clauses);
    }
    
    

    // anti-diagos
    results<<"c anti-diagos"<<endl;
    for (unsigned int k = 0 ; k < n ; k++) { 
            v.push_back(matrix[k][n-k-1]);
    }

    createClauses(v, results, clauses);

    for (unsigned int k = 1 ; k < n - 1 ; k++) { 
        for(unsigned int i = 0,  j = k ; j < n ; i++, j++) {
                v.push_back(matrix[i][n-1-j]);
        }
        createClauses(v, results, clauses);

        for(unsigned int i = k,  j = 0 ; i < n ; i++, j++) {
                v.push_back(matrix[i][n-1-j]);
        }
        createClauses(v, results, clauses);
    }

    //
    cout<<"c  "<<n<<"-queens-CNF-File.cnf"<<endl;
    cout<<"c"<<endl;
    cout<<"p cnf "<<n*n<<" "<<clauses<<endl;

    cout<<results.str();

    return 0;
}
