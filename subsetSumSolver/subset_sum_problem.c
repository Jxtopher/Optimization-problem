#include "subset_sum_problem.h"

// On suppose a<b
int rand_a_b(int a, int b) {
    return rand() % (b - a) + a;
}

struct SSP *build_rand_SSP(unsigned int size, int nb_min, int nb_max) {
	unsigned int i, j;
	int distance_zero = 0;
	struct SSP *data = malloc(sizeof(struct SSP));
	data->set = malloc(size * sizeof(int));
	data->subset = malloc(size * sizeof(bool));
	data->subset_solution = malloc(size * sizeof(bool));
	data->size = size;

	for (i = 0 ; i < size ; i++) {
		data->set[i] = rand_a_b(nb_min, nb_max);
		data->subset[i] = 0;
		if (rand_a_b(0, 1000) < 500) {
			distance_zero += data->set[i];
			data->subset_solution[i] = 1;
		} else
			data->subset_solution[i] = 0;
	}
	
	for (i = 0, j = 0 ; i < abs(distance_zero) ;) {
		if (data->subset_solution[j] == 1) {
			if (distance_zero < 0) {
					data->set[j]++;
					i++;
			} else if (distance_zero > 0) {
					data->set[j]--;
					i++;
			}
		}
		
		if (j++ >= size) j = 0;
	}
	
	return data;
}

// Copie un tableau boolean de b dans a ( a <- b )
void copy_solution(bool *a, bool *b, unsigned int size) {
	unsigned int i;
	
	for (i = 0 ; i < size ; i++)
		a[i] = b[i];
}

// Evaluation du sous-ensemble chercher
int evaluation_SSP(struct SSP *data) {
	unsigned int i;
	int total = 0;
	bool NA = true;
	
	for (i = 0 ; i < data->size ; i++)
		if (data->subset[i] == 1) {
			total += data->set[i];
			NA = false;
		}
		
	if (NA) 
		for (i = 0 ; i < data->size ; i++)
			total += data->set[i];
	return total;
}

void mutation(struct SSP *data) {
	int random = rand_a_b(0, data->size - 1);
	data->subset[random] = ! data->subset[random];
}

void print_SSP(struct SSP *data) {
	unsigned int i;
	
	for (i = 0 ; i < data->size ; i++) {
		printf("%d\t", data->set[i]);
	}
	printf("\n");
	for (i = 0 ; i < data->size ; i++) {
		printf("%d\t", data->subset[i]);
	}
	printf("\n");
	for (i = 0 ; i < data->size ; i++) {
		printf("%d\t", data->subset_solution[i]);
	}
	printf("\n");
}