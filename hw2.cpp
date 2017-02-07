//
//	Bryant Clouse
//	Multi-armed bandit
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <random>
#include <iomanip>
#include <cmath>
#include "Classes.h"

//#define PI_ (double) 3.14159265358979323846
//#define ZERO_TO_ONE (double)rand()/RAND_MAX

using namespace std;


//===============================================
//	Main Function
//===============================================

int main(int argc, char * argv[]) {
	FILE *data_log, *pull_log;
	MAB dummy (false);
	vector<MAB> MAB_list;
	vector<double> mean_list;
	int answer;
	int input;
	int n = 20;

	srand(time(NULL));
	data_log = fopen("MAB_Data_Log.txt", "w+");
	pull_log = fopen("Learner_Pull_Log.txt", "w+");
	
	for (int i = 0; i < n; i++) {
		dummy.set_values(true);
		MAB_list.push_back(dummy);
		mean_list.push_back(dummy.get_mean());
	}
	answer = maximum(mean_list)+1;

	Learner Bob (n,0.1,0.1,n*10);
	Bob.search_values(MAB_list,data_log,pull_log);
	fprintf(data_log, "   Actual answer: %d", answer);
	cout << "The acutal answer is: " << answer;
	fprintf(data_log, "\n\n===== MAB DATA ====\n");
	for (int i = 0; i < MAB_list.size(); i++) {
		fprintf(data_log, "%2d) ", i+1);
		MAB_list.at(i).M_display(data_log);		
	}
	Bob.L_display(data_log);
	for (int i = 0; i < n; i++) {
		MAB_list.at(i).TestA();
	}
	cout << endl;
	fclose(data_log);

	return 0;
}