/// 
/// @file maximumClique.hpp
/// @author Jxtopher
/// @version 0.1
/// @date 2020-02-16
/// @brief Problème de la clique maximale
///        see : https://en.wikipedia.org/wiki/Clique_problem
///		 https://fr.wikipedia.org/wiki/Problème_de_la_clique
///              http://www.csplib.org/Problems/prob074/
///	   	 Karp's 21 NP-complete problems n°3 : http://cgi.di.uoa.gr/~sgk/teaching/grad/handouts/karp.pdf
/// compilation g++ -Os maximumClique.cpp
/// 
///

#include <cstdlib>
#include <iostream>
#include <string>
#include <istream>
#include <sstream>
#include <fstream>      // std::filebuf

#include <boost/graph/graph_utility.hpp> // print_graph
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graphviz.hpp>

using namespace std;
using namespace boost;


//-----------------------------------------------------------------------------
// Définitions des types pour le graphe
//-----------------------------------------------------------------------------

///
/// @brief Définition du type pour les noeuds graphe
///
struct VertexProperties {
    float d;
    int predecessor;
    VertexProperties() : d(std::numeric_limits<float>::infinity()), predecessor(-1) {}
    VertexProperties(float d, int predecessor) : d(d), predecessor(-1) {}
};

///
/// @brief Définition du type pour les liens graphe
///
struct EdgeProperties {
    int weight;
    EdgeProperties() : weight(0) { }
    EdgeProperties(int weight) : weight(weight) { }
};

struct EdgeInfoPropertyTag {
    typedef edge_property_tag kind;
    static std::size_t const num; // ???
};

std::size_t const EdgeInfoPropertyTag::num = (std::size_t)&EdgeInfoPropertyTag::num;
typedef property<EdgeInfoPropertyTag, EdgeProperties> edge_info_prop_type;

///
/// @brief Type de graphe
///
typedef adjacency_list<
    boost::vecS, boost::vecS, boost::undirectedS,
    VertexProperties,                               // Type vertex
    edge_info_prop_type                             // Type edge
> Graph;


//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------

/// 
/// @brief source https://stackoverflow.com/questions/30415388/how-to-read-dimacs-vertex-coloring-graphs-in-c
/// 
/// @param dimacs 
/// @param g 
/// @return true 
/// @return false 
///
bool read_dimacs(std::istream& dimacs, Graph& g) {
    size_t vertices = 0, edges = 0;

    std::string line;
    while (getline(dimacs, line))
    {
        std::istringstream iss(line);
        char ch;
        if (iss >> ch)
        {
            size_t from, to;
            std::string format;

            switch(ch) {
                case 'c': break;
                case 'p': 
                    if (vertices||edges) return false;
                    if (iss >> format >> vertices >> edges) {
                        if ("edge" != format && "col" != format ) return false;
                    }
                    break;
                case 'e': 
                    if (edges-- && (iss >> from >> to) && (add_edge(from-1, to-1, g).second))
                        break;
                default: 
                    return false;
            }
        }
    }
    return !(edges || !dimacs.eof());
}

// // Algorithme naif
// bool is_clique(const Graph& g, const unsigned int num_main_node) {
//     // Returns the number of edges leaving vertex u.
//     // unsigned int number_of_edges = boost::out_degree(num_main_node, g);

//     // Pas terrible
//     vector<unsigned int> list;
//     auto main_neighbours = boost::adjacent_vertices(num_main_node, g);
//     for (auto v : make_iterator_range(main_neighbours))
//         list.push_back(v);
//     list.push_back(num_main_node);

//     std::cout<<num_main_node<<" "<<list.size()<<std::endl;

//     //
//     for (unsigned int i = 0 ; i < list.size() ; i++) {
//         for (unsigned int j = i+1 ; j < list.size() ; j++) {
//             // check edge beteween list[i] and list[j]
//             auto neighbours = boost::adjacent_vertices(list[i], g);
//             auto x = make_iterator_range(neighbours);
//             auto p = std::find (x.begin(), x.end(), list[j]);
//             if (p == x.end()) {// Element not found
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// void find_clique(const Graph& g) {
//     unsigned int degree_vertex =  0;
//     unsigned int num_vertex = -1;
//     for (unsigned int i = 0 ; i < boost::num_vertices(g) ; i++) {
//         if (is_clique(g, i) && degree_vertex < out_degree(i, g)) {
//             degree_vertex = out_degree(i, g);
//             num_vertex = i;
//         }
//     }

//     if (degree_vertex != 0) {
//         std::cout<<"Noeud principale : "<<num_vertex<<std::endl;
//         std::cout<<"Taille de la clique : "<<degree_vertex + 1<<std::endl;
//     } else {
//         cout<<"Not found clique"<<endl;
//     }
    
// }

bool is_clique(const Graph& g, const vector<unsigned int> &list_of_nodes) {
    for (unsigned int i = 0 ; i < list_of_nodes.size() ; i++) {
        for (unsigned int j = i+1 ; j < list_of_nodes.size() ; j++) {
            // check edge beteween list[i] and list[j]
            auto neighbours = boost::adjacent_vertices(list_of_nodes[i], g);
            auto x = make_iterator_range(neighbours);
            auto p = std::find (x.begin(), x.end(), list_of_nodes[j]);
            if (p == x.end()) {// Element not found
                return false;
            }
        }
    }
    return true;
}


class CombinationGenerator {
  public:
	void operator()(const unsigned int nbDigit, unsigned int len_string, void (*f)(unsigned int, unsigned int *, unsigned int)) {
		unsigned int nbCall = 0;
		unsigned int *string = new unsigned int[len_string];

		for (unsigned int i = 0; i < len_string; i++)
			string[i] = 0;

		bool x = false;
		unsigned int i = 0;

		f(nbCall++, string, len_string);

		while (string[i] == (nbDigit - 1)) {
			i++;
			x = true;
		}

		while (i < (len_string)) {
			string[i]++;

			if (x) {
				for (unsigned int j = 0; j < i; j++)
					string[j] = 0;
				i = 0;
			}

			f(nbCall++, string, len_string);

			while (string[i] == (nbDigit - 1)) {
				i++;
				x = true;
			}
		}

		delete[] string;
	}

	static void f(unsigned int nbCall, unsigned int *string, unsigned int size) {
		std::cout << nbCall << " ";
		for (unsigned int i = 0; i < size; i++)
			std::cout << string[i] << " ";
		std::cout << std::endl;
	}
};


void find_clique(const Graph& g) {
    unsigned int degree_vertex =  0;
    unsigned int num_vertex = -1;

    vector<unsigned int> clique;
    vector<unsigned int> list_of_nodes;


    for (unsigned int i = 0 ; i < boost::num_vertices(g) ; i++) {
        clique.push_back(i);
    }
}


void sec(std::vector<unsigned int> s) {
    for (unsigned int i = 0 ; i < s.size() ; i++) {
        for (unsigned int j = i+1 ; j < s.size() ; j++) {
            
        }
    }
}

int main(int argc, char **argv) {
    string path_file = "benchmark-perso/c6.clq";
    if (argc == 2) {
        path_file = string(argv[1]);
    }
    // Crée un graphe g
    Graph g;

    // Chargement du graphe depuis un ficher
    std::cout<<"[+] Loading file : "<<path_file<<std::endl;
    std::filebuf fb;
    if (fb.open (path_file,std::ios::in)) {
        std::istream is(&fb);
        read_dimacs(is, g);
        fb.close();
    } else {
        std::cerr<<"ERROR"<<std::endl;
        return EXIT_FAILURE;
    }

    std::cout<<"[+] Nombre de noeuds : "<<boost::num_vertices(g)<<std::endl;



    // find_clique(g);
    // std::cout<<edge(0, 4, g).first<<std::endl;
    
    // cout<<boost::out_degree(0, g)<<endl;

    // auto neighbours = boost::adjacent_vertices(0, g);

    // auto p = std::find (make_iterator_range(neighbours).begin(), make_iterator_range(neighbours).end(), 3);
    // if (p != make_iterator_range(neighbours).end()) {
    //     std::cout << "Element found in myints: ";
    // } else {
    //     std::cout << "Element not found in myints\n";
    // }

    // // View
    // print_graph(g);

    /// dot -Tpdf filename.dot -o outfile.pdf
    // std::ofstream f("filename.dot");
    // boost::write_graphviz(f, g);
    // f.close();
    // boost::write_graphviz(std::cout, g);
    return EXIT_SUCCESS;
}
