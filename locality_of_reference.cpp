/*
Checking for locality of reference.
Changing the order of index looping is much faster due to cache penalty.
With -O3 flags is around 5X faster for n = 1500

*/
#include <cmath>	//for calculating power & NaN
#include<iostream>
#include<cstdio>
#include <vector>
#include <cstdlib>
#include <fstream> // for writing to file
#include <math.h>       //exp, pi
#include <fstream>
#include <ctime>
#include <chrono>	//for time measurement


using namespace std;
using namespace std::chrono;

int main(int argc, char **argv){
	cout<<"Start of the program"<<endl;
	
	int n=1000;
	cout<<"Number of elements = "<<n<<endl;
	vector< vector<float> > A_01(n, vector<float>(n,0.0));
	vector< vector<float> > B_01(n, vector<float>(n,0.0));
	vector< vector<float> > C_01(n, vector<float>(n,0.0));
	vector< vector<float> > C_02(n, vector<float>(n,0.0));
	vector< vector<float> > C_03(n, vector<float>(n,0.0));
	
	//Fill up matrix
	for(int i = 0;i < n; ++i){
        for(int j = 0;j < n; ++j){
            A_01[i][j]=((float) rand()/(RAND_MAX));
			B_01[i][j]=((float) rand()/(RAND_MAX));
			
        }
    }
	
	system_clock::time_point start_01 = system_clock::now();
	for(int i = 0;i < n; ++i){
        for(int j = 0;j < n; ++j){
			for(int k = 0;k < n; ++k){
				C_01[i][j] = C_01[i][j] + A_01[i][k] * B_01[k][j];
			}
		}
    }	
	system_clock::time_point stop_01 = system_clock::now();
	
	std::chrono::duration<float, std::milli> duration_01 = stop_01 - start_01;
	cout << "Execution time (normal algo) = "<<duration_01.count()<<" millisecond"<<endl;
	
	//--------------------------------------------------------
	system_clock::time_point start_02 = system_clock::now();
	for(int i = 0;i < n; ++i){
        for(int k = 0;k < n; ++k){
			for(int j = 0; j < n; ++j){
				C_02[i][j] = C_02[i][j] + A_01[i][k] * B_01[k][j];
			}
		}
    }	
	system_clock::time_point stop_02 = system_clock::now();
	
	std::chrono::duration<float, std::milli> duration_02 = stop_02 - start_02;
	cout << "Execution time (with locality) = "<<duration_02.count()<<" millisecond"<<endl;
	//--------------------------------------------------------
	int BLOCK_SIZE= 50; //Best result so far
	cout<<"BLOCK_SIZE= "<<BLOCK_SIZE<<endl;
	
	system_clock::time_point start_03 = system_clock::now();
	for (int ii = 0; ii < n; ii += BLOCK_SIZE){
		for (int kk = 0; kk < n; kk += BLOCK_SIZE){
			for (int jj = 0; jj < n; jj += BLOCK_SIZE){
				float maxi = min(ii + BLOCK_SIZE, n);
				for (int i = ii; i < maxi; i++){
					float  maxk = min(kk + BLOCK_SIZE, n);
					for (int k = kk; k < maxk; k++){
						float  maxj = min(jj + BLOCK_SIZE, n);
						for (int j = jj; j < maxj; j++){
							C_03[i][j] = C_03[i][j] + A_01[i][k] * B_01[k][j];
						}
					}
				}
			}
		}
	}
	
	system_clock::time_point stop_03 = system_clock::now();
	
	std::chrono::duration<float, std::milli> duration_03 = stop_03 - start_03;
	cout << "Execution time (with locality & blocking) = "<<duration_03.count()<<" millisecond"<<endl;

//--------------------------------------------------------
	//Checking
	for(int i = 0;i < 3; ++i){
        for(int j = 0; j < 2; ++j){
            cout <<"\t" << C_01[i][j]<< " - "<<C_02[i][j]<< " - " <<C_03[i][j]<< endl;			
        }
    }
	
	float C_gap=0.0;
	
	for(int i = 0;i < n; ++i){
        for(int j = 0;j < n; ++j){
            C_gap += abs(C_01[i][j]-C_02[i][j]) + abs(C_01[i][j]-C_03[i][j]);			
        }
    }
	cout <<"C_gap = "<<C_gap << endl;
	
}