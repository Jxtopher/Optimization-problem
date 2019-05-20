#ifndef HEADER_SUBSET_SUM_PROBLEM
#define HEADER_SUBSET_SUM_PROBLEM

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct SSP {
    int *set;				// L'ensemble des nombres
	bool *subset;			// Sous-ensemble chercher
	bool *subset_solution; 	// Sous-ensemble solution
	unsigned int size;				// Taille de l'ensemble
};

struct SSP *build_rand_SSP(unsigned int size, int nb_min, int nb_max);
void print_SSP(struct SSP *data);
void copy_solution(bool *a, bool *b, unsigned int size);
int evaluation_SSP(struct SSP *data);
void mutation(struct SSP *data);
int rand_a_b(int a, int b);

#endif