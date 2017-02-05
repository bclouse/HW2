#include "Classes.h"

//===============================================
//	MAB Class
//===============================================

void MAB::set_values(bool randomize) {
	if (randomize) {
		mean = (ZERO_TO_ONE-0.5)*50;
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

// void MAB::M_display() {
// 	cout.fill(' '); cout.width(12);
// 	cout << "mean = " << mean << '\t';
// 	cout << "std  = " << std << "\n\n";
// }

void MAB::M_display(FILE *fp) {
	fprintf(fp, "MEAN = %10f\tSTD = %8f\n", mean,std);
}

double MAB::get_mean() {
	return mean;
}

void MAB::TestA() {
	int l = 100000;
	double average;
	for (int i = 0; i < l; i++) {
		average += pull();
	}
	average /= l;
	//cout << ": " << average << endl;
	assert((average >= average - 0.1) && (average <= average+0.1));
}

void MAB::TestB() {
	//cout << "TestB" << endl;
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

void Learner::search_values(vector<MAB> list, FILE *ans, FILE *p) {
	int index;
	double val;
	fprintf(p, "====================\nIteration %d)\n====================\n\n", 1);
	for (int i = 0; i < trials; i++) {
		if (i >= trials*(1-epsilon)) {
			index = max_avg(arms,rewards,length);
			fprintf(p, "O) ");
		} else {
			index = rand()%arms;
			fprintf(p, "R) ");
		}
		assert(index >= 0 && index < arms);
		val = list.at(index).pull();
		fprintf(p, "%2d   =   %10f\n", index+1, val);
		rewards.at(index) += val;
		length.at(index)++;
	}
	guess = max_avg(arms,rewards,length) + 1;
	fprintf(ans, "Learner's answer: %d\n", guess);
	cout << "\n============================\nLearner's guess is arm #" << guess << "\n============================\n" << endl;
}

// void Learner::L_display() {
// 	for (int i = 0; i < arms; i++) {
// 		cout << "Arm #" << i+1 << "'s total rewards are: " << rewards.at(i) << endl;
// 		cout << "\tAverage = " << rewards.at(i)/length.at(i) << endl;

// 	}
// }

void Learner::L_display(FILE *fp) {
	double avg;
	fprintf(fp, "\n===== LEARNER DATA ====\n");
	for (int i = 0; i < arms; i++) {
		avg = rewards.at(i)/length.at(i);
		fprintf(fp, "%2d) Average: %10f\t\tPulls: %d\n", i+1, avg, length.at(i));
	}
}

//===============================================
//	Function Definitions
//===============================================

int maximum(vector<double> list) {
	int max = 0;

	for (int i = 1; i < list.size(); i++) {
		if (list.at(i) > list.at(max)) {
			max = i;
		}
	}
	return max;
}

int max_avg(int n, vector<double> list, vector<int> num) {
	int max = 0;
	double avg_new,avg_max = list.at(0)/num.at(0);
	//cout << "Printing Averages\n";
	//cout << avg_max << endl;

	for (int i = 1; i < list.size(); i++) {
		avg_new = list.at(i)/num.at(i);
		//cout << avg_new << endl;
		if (avg_new > avg_max) {
			max = i;
			avg_max = avg_new;
		}
	}
	//cout << "================================\n";
	return max;
}