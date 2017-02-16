#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>
#include <random>
#include <iomanip>
#include <cmath>

#define PI_ (double) 3.14159265358979323846
#define ZERO_TO_ONE (double)rand()/RAND_MAX

using namespace std;

#ifndef CLASSES_H
#define CLASSES_H

//===============================================
//	MAB Class
//===============================================

class MAB {
	private:
		double mean;
		double std;
	public:
		MAB(bool);
		double pull();
		void set_values(bool);
		void set_values(double, double);
		void M_display(FILE*);
		double get_mean();
		void TestA(double);
};

//===============================================
//	Learner Class
//===============================================

class Learner {
	private:
		int guess;
		int arms;
		int trials;
		double alpha;
		double epsilon;
		vector<double> rewards;
		vector<int> length;
	public:
		Learner();
		Learner(int, double, double, int);
		void action(vector<MAB>, int,FILE*,int);
		void learn_log(FILE*, int);
		void L_display(FILE*);
		bool compare_answer(int);
		void TestB(int**, int, int);
};

//===============================================
//	Function definition
//===============================================

vector<int> maximum(vector<double>);
double **give_2D_array(int,int);

#endif