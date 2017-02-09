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

void Learner::action(vector<MAB> list, int sr, FILE *ans, FILE *p) {
	int index;
	vector<int> dummy;
	double val;
	double alpha_ = alpha;

	for (int j = 0; j < sr; j++) {
		//fprintf(p, "====================\nIteration %d)\n====================\n\n", j);
		for (int i = 0; i < trials; i++) {
			if (ZERO_TO_ONE >= epsilon) {			//Determines if the value picked should be random or optimal
				index = rand()%arms;
				//fprintf(p, "  %2d", index+1);
			} else {
				dummy = maximum(rewards);
				index = dummy.at(rand()%dummy.size());
				//fprintf(p, "->%2d", index+1);
			}
			assert(index >= 0 && index < arms);
			val = list.at(index).pull();												//Stores the random number in "val"
			//fprintf(p, "   =   %10f\n", val);
			rewards.at(index) = val*alpha + rewards.at(index)*(1-alpha);
			length.at(index)++;
			if (i%50 == 0) {
				alpha*=0.9;
			}
		}

		dummy = maximum(rewards);									//Checks for the best arm and makes it the Learner's guess
		if (dummy.size() == 1) {
			guess = dummy.at(0)+1;
			L_display(ans);
			cout << "Learner's guess: " << guess << endl;
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
}

void Learner::L_display() {
	for (int i = 0; i < arms; i++) {
		cout << "Arm #" << i+1 << "'s total rewards are: " << rewards.at(i) << endl;
		cout << "\tAverage = " << rewards.at(i)/length.at(i) << endl;
	}
}

void Learner::L_display(FILE *fp) {
	fprintf(fp, "\n========= LEARNER DATA (%02d) =========\n", guess);
	for (int i = 0; i < arms; i++) {
		fprintf(fp, "%2d) Rewards: %10f\t\tPulls: %d\n", i+1, rewards.at(i), length.at(i));
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
/*
vector<int> max_avg(int n, vector<double> list, vector<int> num) {
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
*/