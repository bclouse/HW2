//
//	Bryant Clouse
//	Multi-armed bandit
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <random>
#include <iomanip>
#include <cmath>

#define PI_ (double) 3.14159265358979323846
#define ZERO_TO_ONE (double)rand()/RAND_MAX

using namespace std;

//===============================================
//	Class definitions
//===============================================

class MAB {
	double mean;
	double std;
	public:
		MAB(bool);
		double pull();
		void set_values(bool);
		void display();
};

void MAB::set_values(bool randomize) {
	if (randomize) {
		mean = (ZERO_TO_ONE-0.5)*50;
		std = ZERO_TO_ONE*25;
	} else {
		mean = 0;
		std = 1;
	}
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

void MAB::display() {
	cout.fill(' '); cout.width(12);
	cout << "mean = " << mean << '\t';
	cout << "std  = " << std << "\n\n";
}

//===============================================
//	Main Function
//===============================================

int main(int argc, char * argv[]) {
	MAB dummy (false);
	vector<MAB> MAB_list;
	int input;

	srand(time(NULL));
	for (int i = 0; i < 3; i++) {
		dummy.set_values(true);
		MAB_list.push_back(dummy);
	}

	while (1) {
		cout << ">> ";
		cin >> input;
		if (!(input >= 1 && input <= MAB_list.size())) {
			cout << "NOT IN RANGE!\nENDING PROGRAM!\n\n";
			break;
		}
		cout << "You get: " << MAB_list.at(input-1).pull() << endl;
	}
	cout << "Here are the results:\n";
	for (int i = 0; i < 3; i++) {
		MAB_list.at(i).display();
	}

	return 0;
}