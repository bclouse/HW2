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

using namespace std;


//===============================================
//	Main Function
//===============================================

int main(int argc, char * argv[]) {
	FILE *data_log;
	MAB dummy (false);
	vector<MAB> MAB_list;
	vector<double> mean_list;
	vector<int> answer;
	int input;
	int n = 3, sr = 30, t = 1000;

	srand(time(NULL));
	data_log = fopen("MAB_Data_Log.txt", "w+");
	/*
	cout << "How many arms do you want to choose from (2-30)? ";
	cin >> n;
	cout << "How many trials do you want (1000-10000) ";
	cin >> t;
	cout << "How many Statistical Runs do you want? (1-50) ";
	cin >> sr;
	for (int i = 0; i < n; i++) {
		dummy.set_values(true);
		MAB_list.push_back(dummy);
		mean_list.push_back(dummy.get_mean());
	}
	//*/
	dummy.set_values(5,1);
	MAB_list.push_back(dummy);
	mean_list.push_back(dummy.get_mean());
	dummy.set_values(15,1);
	MAB_list.push_back(dummy);
	mean_list.push_back(dummy.get_mean());
	dummy.set_values(45,1);
	MAB_list.push_back(dummy);
	mean_list.push_back(dummy.get_mean());
	answer = maximum(mean_list);

	Learner Bob (n,0.1,0.1,t);

	cout << "The actual answer is: " << answer.at(0)+1 << endl;
	fprintf(data_log, "  Actual answer: %d\n", answer.at(0)+1);
	fprintf(data_log, "\n===== MAB DATA =====\n");
	for (int i = 0; i < MAB_list.size(); i++) {
		fprintf(data_log, "%2d) ", i+1);
		MAB_list.at(i).M_display(data_log);		
	}
	Bob.action(MAB_list,sr,data_log);
	fclose(data_log);

	return 0;
}