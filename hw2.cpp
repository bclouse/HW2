//
//	Bryant Clouse
//	Multi-armed bandit

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <random>
#include <iomanip>

#define ZERO_TO_ONE (float)rand()/RAND_MAX

using namespace std;

//===============================================
//	Class definitions
//===============================================

class MAB {
	vector<float> mean;
	vector<float> std;
	public:
		MAB();
		MAB(int);
		float pull(int);
};

MAB::MAB() {
	mean = 1;
	std = 0.5;
}

MAB::MAB() {

}

float MAB::pull(int index) {

}

//===============================================
//	Main Function
//===============================================

int main(int argc, char * argv[]) {
	srand(time(NULL));

	return 0;
}