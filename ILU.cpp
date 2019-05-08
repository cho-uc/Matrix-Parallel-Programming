#include<iostream>
#include<cstdio>
#include <cstdlib>
#include <vector> 
#include <chrono>	//for time measurement
#include <cmath>	//for calculating power
#include <omp.h>	//for parallel
#include <stdio.h>
#include <numeric>    // for average
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator

using namespace std;
using namespace std::chrono;

void printMatrix(vector<vector<float>> &myArray) {
	for(size_t x = 0;x < myArray.size(); ++x){
        for(size_t y = 0;y < myArray[x].size();++y){
            printf("%f", myArray[x][y]);
			printf("  ");
        }
        cout << endl;
    }
		
}

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

//_____LU Factorization___________________________________
 pair<vector< vector<float> >, vector< vector<float> >> LUF(vector< vector<float> > &myArray) {
	int n=myArray.size();
	vector< vector<float> > U(n, vector<float>(n,0));
	vector< vector<float> > L(n, vector<float>(n,0));
	U=myArray; //U=A
	int i = 0, j = 0, k = 0,x=0,m=0;
	for (i = 0; i < n; ++i) { //L = I
		for(j= 0; j < n; ++j){
			if (i==j){
				L[i][j]=1;
			}
		}
	}
	//____Algorithm________________________________________
	
	for (k = 0; k < n; ++k) { 
		for(j= k+1; j < n; ++j){
			L[j][k]=U[j][k]/U[k][k]; 
			for(x= k; x < n; ++x){
				U[j][x]=U[j][x]-L[j][k]*U[k][x];
			}
		}
		
	}	
	
	return make_pair(U, L);	
}

// ___________Algorithm 2_____________
pair<vector< vector<float> >, vector< vector<float> >> fine_grained_ILU(vector< vector<float> > &a) {
	int n=a.size();
	vector< vector<float> > U=a;
	vector< vector<float> > L=a;
	
	float residual;
	int i = 0, j = 0, k = 0;
	
	
	while (residual>1e-6){
		
	for (i = 0; i < n; ++i) { 
		for(j= 0; j < n; ++j){
			float sum1=0;
			for(k= 0; k < (j-1); ++k){
				sum1+=L[i][k]*U[k][j];
			}
			float sum2=0;
			for(k= 0; k < (i-1); ++k){
				sum2+=L[i][k]*U[k][j];
			}
			
			if(i>j){
				L[i][j]=(a[i][j]-sum1)/U[j][j]; 
			}
			else{
				U[i][j]=a[i][j]-sum2;
			}
			
		}
		
	}	
	residual=1e-6;	//need to be updated
	}
	return make_pair(U, L);	
	
}

// ___________Algorithm 3_____________
vector< vector<float>> symmetric_fine_grained_ILU(vector< vector<float> > &a) {
	int n=a.size();
	vector< vector<float> > U=a;
	
	float sum=0,residual,s;
	int i = 0, j = 0, k = 0;
	
	while (residual>1e-6){
		
	for (i = 0; i < n; ++i) { 
		for(j= 0; j < n; ++j){
			for(k= 0; k < (i-1); ++k){
				sum+=U[k][i]*U[k][j];
			}
			s=a[i][j]-sum;
			if(i!=j){
				U[i][j]=s/U[i][i]; 
			}
			else{
				U[i][i]=pow(s,0.5);
			}
			
		}
		
	}	
	residual=1e-6;	//need to be updated
	}
	return U;	
	
}

//_____Incomplete LU Factorization (Algorithm1)___________________________________
//Store result in one matrix
 vector< vector<float> > ILU(vector< vector<float> > &matrix) {
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

int main(int argc, char **argv){
	/*
	int matrix_size,no_of_data;
	cout << "Please enter matrix size: ";
	cout<<endl;
	cin >> matrix_size;
    cout << "Please enter number of data: ";
	cout<<endl;
	cin >> no_of_data;
	cout << "All measurement units are in microseconds"<<endl;
	
	vector<float> duration_s_array;
	vector<float> duration_p_array;
	auto a= createRandomMatrix(matrix_size);
	auto b= createRandomMatrix(matrix_size);
	
	for(int sample=0;sample<no_of_data ;++sample){	
		
		system_clock::time_point start = system_clock::now();
		auto answer_s=ILU(b);		
		
		system_clock::time_point stop = system_clock::now();
		
		nanoseconds duration = stop - start;
		duration_s_array.push_back(duration_cast<microseconds>(duration).count());
		
		cout << "Time series ILU: "<< duration_cast<microseconds>(duration).count() <<"   ";
		
		//________________________________________________	
		//int chunk = 4096 ; 
		int chunk = 500 ; 
		system_clock::time_point start_p = system_clock::now();
		int i = 0, j = 0, k = 0;
		
		for (i = 1; i < matrix_size; ++i) { 
				for(k= 0; k <= (i-1); ++k){
					a[i][k]=a[i][k]/a[k][k]; 
				for(j= k+1; j < matrix_size; ++j){
					a[i][j]=a[i][j]-a[i][k]*a[k][j];
				}
			}
		}
		
		/*
		//# pragma omp parallel shared (chunk) private (i) num_threads (5)
		# pragma omp parallel private (i) num_threads (8)
		{
			
		# pragma omp for schedule (dynamic, chunk)
			for (i = 1; i < matrix_size; ++i) { 
				for(k= 0; k <= (i-1); ++k){
					a[i][k]=a[i][k]/a[k][k]; 
				for(j= k+1; j < matrix_size; ++j){
					a[i][j]=a[i][j]-a[i][k]*a[k][j];
				}
			}
		
		}	
			//auto answer_p=ILU(a);
		
		}
		*/
		system_clock::time_point stop_p = system_clock::now();
		nanoseconds duration_p = stop_p - start_p;
		duration_p_array.push_back(duration_cast<microseconds>(duration_p).count());
		
		cout << "Time parallel ILU: "<< duration_cast<microseconds>(duration_p).count() <<endl;
	}
	
	cout << "Total time series ILU : " <<endl;
	std::copy(duration_s_array.begin(), duration_s_array.end(), std::ostream_iterator<float>(std::cout, " "));
	cout<<endl;
	cout << "Total time parallel ILU : " <<endl;
	std::copy(duration_p_array.begin(), duration_p_array.end(), std::ostream_iterator<float>(std::cout, " "));
	cout<<endl;
	
	
	float average_s = accumulate( duration_s_array.begin(), duration_s_array.end(), 0.0)/ duration_s_array.size();
	float average_p = accumulate( duration_p_array.begin(), duration_p_array.end(), 0.0)/ duration_p_array.size();
	cout << "Average time series ILU : " <<average_s<<endl;
	cout << "Average time parallel ILU: " <<average_p<<endl;
	*/
	
	
	
	float z= -0.5;// -1 < b < 2 to be symmetric positive definite
	vector<vector<float> >a={{1,2,3,4},{21,22,23,24},{31,3,0,34},{1,2,43,4}};
	vector<vector<float> >b={{2,-1,z},{-1,2,-1},{z,-1,2}}; //symmetric positive definite
	vector<vector<float> >c={{4,1,-1},{1,2,1},{-1,1,2}}; //symmetric positive definite
	
	printf("Initial matrix = \n");
	printMatrix(a);
	printf("ILU = \n");
	auto answer1=ILU(a);	//benchmark
	printMatrix(answer1);
	
	
	
	auto answer2=symmetric_fine_grained_ILU(c);
	printf("ILU symmetric fine-grained upper matrix = \n");
	printMatrix(answer2);
	
	printf("LUF upper matrix = \n");
	auto answer=LUF(a);
	printMatrix(answer.first);
	printf("LUF lower matrix = \n");
	printMatrix(answer.second);	
	
	/*
	
	auto answer3=fine_grained_ILU(a);
	printf("ILU fine-grained upper matrix = \n");
	printMatrix(answer3.first);
	printf("ILU fine-grained lower matrix = \n");
	printMatrix(answer3.second);
	
	
	
	
	
	
	
	*/
	
	
    }
