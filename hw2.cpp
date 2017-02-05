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
	FILE *fp;
	MAB dummy (false);
	vector<MAB> MAB_list;
	vector<double> mean_list;
	int answer;
	int input;
	int n = 3;

	srand(time(NULL));
	fp = fopen("MAB_Data_Log.txt", "w+");
	//cout << "How many arms do you want?\n>> ";
	//cin >> n;
	//*
	for (int i = 0; i < n; i++) {
		dummy.set_values(true);
		MAB_list.push_back(dummy);
		mean_list.push_back(dummy.get_mean());
	}
	answer = maximum(mean_list)+1;
	//*/
	/*
	dummy.set_values(28.6305, 1.19668);	MAB_list.push_back(dummy);
	dummy.set_values(17.8945, 7.85031);	MAB_list.push_back(dummy);
	dummy.set_values(16.375, 5.42013);	MAB_list.push_back(dummy);
	//*/

	Learner Bob (n,1,0.1,n*10);
	Bob.search_values(MAB_list,fp);
	fprintf(fp, "   Actual answer: %d", answer);
	cout << "The acutal answer is: " << answer << endl;
	fprintf(fp, "\n\n===== MAB DATA ====\n");
	for (int i = 0; i < MAB_list.size(); i++) {
		fprintf(fp, "%2d) ", i+1);
		MAB_list.at(i).M_display(fp);		
	}
	Bob.L_display(fp);
	for (int i = 0; i < n; i++) {
		MAB_list.at(i).TestA();
	}
	cout << endl;
	fclose(fp);

	return 0;
}