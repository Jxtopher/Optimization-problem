#include "subset_sum_problem.h"

#include <math.h>
#include <time.h>

void firstImprovement(struct SSP *ssp_data) {
	struct SSP *ssp_tmp = malloc(sizeof(struct SSP));
	ssp_tmp->set = ssp_data->set;
	ssp_tmp->subset = malloc(ssp_data->size * sizeof(bool));
	ssp_tmp->subset_solution = ssp_data->subset_solution;
	ssp_tmp->size = ssp_data->size;
	
	int eval = evaluation_SSP(ssp_data), evalTemp;
	
	copy_solution(ssp_tmp->subset, ssp_data->subset, ssp_data->size);
	
	do {
		mutation(ssp_tmp);
		evalTemp = evaluation_SSP(ssp_tmp);
		
		//printf("%d\n", evalTemp);
		if (abs(eval) - abs(evalTemp) > 0) {
			eval = evalTemp;
			copy_solution(ssp_data->subset, ssp_tmp->subset, ssp_data->size);
			printf("%d\n", eval);
			print_SSP(ssp_data);
		} else {
			copy_solution(ssp_tmp->subset, ssp_data->subset, ssp_data->size);
		}
		
	} while(eval != 0);
}

void simulated_annealing(struct SSP *ssp_data, unsigned int T) {
	int delta;
	float u;
	struct SSP *ssp_tmp = malloc(sizeof(struct SSP));
	ssp_tmp->set = ssp_data->set;
	ssp_tmp->subset = malloc(ssp_data->size * sizeof(bool));
	ssp_tmp->subset_solution = ssp_data->subset_solution;
	ssp_tmp->size = ssp_data->size;
	
	int eval = evaluation_SSP(ssp_data), evalTemp;
	
	do  {
		mutation(ssp_tmp);
		evalTemp = evaluation_SSP(ssp_tmp);
		
		//printf("%d\n", evalTemp);
		delta = abs(eval) - abs(evalTemp);
		
		if (delta > 0) {
			eval = evalTemp;
			copy_solution(ssp_data->subset, ssp_tmp->subset, ssp_data->size);
			printf("%d\n", eval);
		} else {
			u = (float)rand_a_b(0, 100) / 100;
			//printf("%f, %f\n", u, exp2f((float)delta/T));
			if (u < exp2f((float)delta/T)) {
				eval = evalTemp;
				copy_solution(ssp_data->subset, ssp_tmp->subset, ssp_data->size);
				printf("%d\n", eval);
				//print_SSP(ssp_data);
			} else 
				copy_solution(ssp_tmp->subset, ssp_data->subset, ssp_data->size);
		}
		T--;
	} while (eval != 0 && T > 0);
}

int main() {
	srand(time(NULL));
	
	//struct SSP *data = build_rand_SSP(20, -10000, 10000);
	struct SSP *data = build_rand_SSP(15, 0, 30);
	//simulated_annealing(data, 5000);
	firstImprovement(data);
	
	return 0;
}