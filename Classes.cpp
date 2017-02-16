#include "Classes.h"

//===============================================
//	MAB Class
//===============================================

void MAB::set_values(bool randomize) {
	if (randomize) {
		mean = (ZERO_TO_ONE)*50;
		std = ZERO_TO_ONE*5;
	} else {
		mean = 0;
		std = 1;
	}
}

void MAB::set_values(double m, double s) {
	mean = m;
	std = s;
}

MAB::MAB(bool randomize) {
	set_values(randomize);
}


double MAB::pull() {
	double output;
	double U1 = ZERO_TO_ONE, U2 = ZERO_TO_ONE;
	output = (sqrt((double)-2*log(U1))*sin(2*PI_*U2))*std+mean;
	return output;
}

void MAB::M_display(FILE *fp) {
	fprintf(fp, "MEAN = %10f\tSTD = %8f\n", mean,std);
}

double MAB::get_mean() {
	return mean;
}

void MAB::TestA(double a) {
	int l = 100000;
	double average;
	for (int i = 0; i < l; i++) {
		average = pull()*a + average*(1-a);
	}
	average /= l;
	//cout << ": " << average << endl;
	assert((average >= average - 1) && (average <= average+1));
}

//===============================================
//	Learner Class
//===============================================

Learner::Learner() {
	arms = 3;
	alpha = 0;
	epsilon = 0.1;
	trials = 5*arms;
	for (int i = 0; i < arms; i++) {
		rewards.push_back(0);
		length.push_back(0);
	}
}

Learner::Learner(int n, double a, double e, int t) {
	arms = n;
	alpha = a;
	epsilon = e;
	trials = t;
	for (int i = 0; i < arms; i++) {
		rewards.push_back(0);
		length.push_back(0);
	}
}

void Learner::action(vector<MAB> list, int sr, FILE *ans, int best_arm) {
	int index;
	vector<int> dummy;
	vector<double> l_curve;
	double val;
	double alpha_ = alpha;
	FILE *log;
	char fname[] = "Learning_Curve.txt";
	double **array = give_2D_array(trials,arms);

	for (int j = 0; j < sr; j++) {
		for (int i = 0; i < trials; i++) {
			if (ZERO_TO_ONE <= epsilon) {			//Determines if the value picked should be random or optimal
				index = rand()%arms;
			} else {
				dummy = maximum(rewards);
				index = dummy.at(rand()%dummy.size());
			}
			array[i][index]+=1;
			assert(index >= 0 && index < arms);
			val = list.at(index).pull();												//Stores the random number in "val"
			rewards.at(index) = val*alpha + rewards.at(index)*(1-alpha);
			length.at(index)++;
			if (j == 0) {
				l_curve.push_back(val);
			} else {
				l_curve[i] += val;
			}
		}

		dummy = maximum(rewards);									//Checks for the best arm and makes it the Learner's guess
		if (dummy.size() == 1) {
			guess = dummy.at(0)+1;
			L_display(ans);
			printf("SR: %2d) Learner's Guess: %d\n", j+1, guess);
		} else {
			guess = -1;
			fprintf(ans, "No guess yet\n");
			L_display(ans);
		}
		for (int i = 0; i < rewards.size(); i++) {			//Resets all of the values to 0 and resents the alpha
			rewards.at(i) = 0;
			length.at(i) = 0;
			alpha = alpha_;
		}
	}

	log = fopen(fname,"w+");
	FILE *action = fopen("Action_Curve.txt","w+");
	for (int i = 0; i < trials; i++) {
		fprintf(log, "%d\t%f\n", i, l_curve[i]/sr);
		fprintf(action,"%d",i);
		for (int j = 0; j < arms; j++) {
			fprintf(action,"\t%f",array[i][j]/sr);
		}
		fprintf(action,"\n");
	}
	fclose(log);
	fclose(action);
}

void Learner::learn_log(FILE *fp,int iter) {
	fprintf(fp,"%d", iter);
	for (int k = 0; k < arms; k++) {
		fprintf(fp,"\t%f",rewards.at(k));
	}
	fprintf(fp,"\n");
}

void Learner::L_display(FILE *fp) {
	fprintf(fp, "\n========= LEARNER DATA (%02d) =========\n", guess);
	for (int i = 0; i < arms; i++) {
		fprintf(fp, "%2d) Rewards: %10f\t\tPulls: %d\n", i+1, rewards.at(i), length.at(i));
	}
}

void Learner::TestB(int **array, int sr, int answer) {
	for (int i = 0; i < arms; i++) {
		if (i != answer) {
			assert(array[trials-1][i]/sr < array[trials-1][answer]);
		}
	}
}

//===============================================
//	Function Definitions
//===============================================

vector<int> maximum(vector<double> list) {
	vector<int> max;

	max.push_back(0);
	for (int i = 1; i < list.size(); i++) {
		if (list.at(i) > list.at(max.at(0))) {
			max.clear();
			max.push_back(i);
		} else if (list.at(i) == list.at(max.at(0))) {
			max.push_back(i);
		}
	}
	return max;
}

double **give_2D_array(int n, int m) {
	double **arr = new double* [n]();
	for (int i = 0; i < n; i++) {
		arr[i] = new double [m]();
	}
	return arr;
}