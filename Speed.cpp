#include<iostream>
#include<cstdio>
#include <cstdlib>
#include <vector> 
#include <chrono>
#include <cmath>
#include <omp.h>
#include <stdio.h>
#define N 1000

using namespace std;
using namespace std::chrono;

vector<vector<float>> createRandomMatrix(int& n) {
	vector< vector<float> > a(n, vector<float>(n,0));
	int i = 0, j = 0;
	for(size_t i = 0;i < n; ++i){
        for(size_t j = 0;j < n; ++j){
            a[i][j]=rand();
        }
    }
return  a;
}

vector< vector<float> > ILU1(vector< vector<float> > &matrix) {
	auto myArray= matrix;
	int n=myArray.size();
	int i = 0, j = 0, k = 0;
	
	for (i = 1; i < n; ++i) { 
		for(k= 0; k <= (i-1); ++k){
			myArray[i][k]=myArray[i][k]/myArray[k][k]; 
			for(j= k+1; j < n; ++j){
				myArray[i][j]=myArray[i][j]-myArray[i][k]*myArray[k][j];
			}
		}	
	}
	return myArray;		
}

vector< vector<float> > ILU2(vector< vector<float> > matrix) {
	auto myArray= matrix;
	int n=myArray.size();
	int i = 0, j = 0, k = 0;
	
	for (i = 1; i < n; ++i) { 
		for(k= 0; k <= (i-1); ++k){
			myArray[i][k]=myArray[i][k]/myArray[k][k]; 
			for(j= k+1; j < n; ++j){
				myArray[i][j]=myArray[i][j]-myArray[i][k]*myArray[k][j];
			}
		}
	}	
	return myArray;	
	
}


double add1(double &a, int &n){
	double b;
	for (int i=1;i<n;++i){
		b=i+1;
	}
	return b;
}

double add2(double a, int n){
	double b;
	for (int i=1;i<n;++i){
		b=i+1;
	}
	return b;
}

int main(int argc, char **argv){
	/*
	//______Checking speed between & and without & on a function part 1_____
	int n= 1000000;
	double a= 25;
	double *a_p=&a;
	
	system_clock::time_point start = system_clock::now();
	
	auto answer_s=add1(a,n);		
	
	system_clock::time_point stop = system_clock::now();
	nanoseconds duration = stop - start;
	
	cout << "Time &: "<< (duration).count() << " nanoseconds"<<endl;
	cout << "Result : "<< answer_s <<endl;
	
	//________________________________________________

	system_clock::time_point start_p = system_clock::now();
		
	auto answer_2=add2(a,n);				
	
	system_clock::time_point stop_p = system_clock::now();
	nanoseconds duration_p = stop_p - start_p;
	cout << "Time without &: "<< (duration_p).count() << " nanoseconds"<<endl;
	cout << "Result : "<< answer_2 <<endl;
	
	//______________________________________________________
	*/
	
	//______Checking speed between & and without & on a function part 2___
		
		
	int n= 1000;
	createRandomMatrix(n);
	auto x_series= createRandomMatrix(n);
	
	system_clock::time_point start = system_clock::now();
	
	auto answer_s=ILU1(x_series);		
	
	system_clock::time_point stop = system_clock::now();
	nanoseconds duration = stop - start;
	
	cout << "Time &: "<< duration_cast<microseconds>(duration).count() << " microseconds ("<<duration_cast<milliseconds>(duration).count()
	<<" milliseconds) for matrix size " << x_series.size()<<endl;
	
	//____________________________________________________
	
	
	system_clock::time_point start_p = system_clock::now();
		
	auto answer_p=ILU1(x_series);		
	
	system_clock::time_point stop_p = system_clock::now();
	nanoseconds duration_p = stop_p - start_p;
	cout << "Time without &: "<< duration_cast<microseconds>(duration_p).count() << " microseconds ("<<duration_cast<milliseconds>(duration_p).count()
	<<" milliseconds) for matrix size " << x_series.size()<<endl;;
	
	
    }
