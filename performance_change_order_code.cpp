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

pair<vector< vector<float> >, vector< vector<float> >> LUD_pair(vector< vector<float> > &a) {
// get upper decomposition
int n= a.size(); 
vector< vector<float> > U=a;
vector< vector<float> > L=a;

for(size_t i = 1;i < a.size(); ++i){
    for(size_t j=0;j<=(i-1); ++j){
        U[i][j]=0;
    }
}
// get lower decomposition
for(size_t i = 0;i < a.size(); ++i){
    for(size_t j = i;j <n; ++j){
        L[i][j]=0;
	}
	L[i][i]=1;	
}
return make_pair(U, L);	
}

void printMatrix(vector<vector<float>> &myArray) {
	for(size_t x = 0;x < myArray.size(); ++x){
        for(size_t y = 0;y < myArray[x].size();++y){
            printf("%f", myArray[x][y]);
			printf("  ");
        }
        cout << endl;
    }
		
}
int countError(vector<vector<float>> &A,vector<vector<float>> &B) {
	int count=0;
	for(size_t i = 0;i < A.size(); ++i){
        for(size_t j = 0;j < A.size(); ++j){
            if(abs(A[i][j]-B[i][j])>1e-2){
				count+=1;
			}
        }
    }	
	return count;
}

vector<vector<float>> multiply(vector<vector<float>> &A, vector<vector<float>> &B) {
		int n= A.size();
		vector< vector<float> > result(n, vector<float>(n,0));
		int i = 0, j = 0,k;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j){
				double s = 0;
				for (int k = 0; k <n; k++) {
					s += A[i][ k] * B[k][j];
				}
				result[i][j]=s;
			}
		}
		return result;
	}
vector<vector<float>> transpose(vector<vector<float>> &A) {
		int rows = A.size();
		int column = A[0].size();
		vector< vector<float> > result(column, vector<float>(rows,0));
		int i, j;
		for (i = 0; i < column; ++i) {
			for (j = 0; j < rows; ++j){
				result[i][j]=A[j][i];
			}
		}
		return result;
	}
	
vector<vector<float>> createRandomMatrix(int& n) {
	vector< vector<float> > a(n, vector<float>(n,0));
	int i = 0, j = 0;
	for(size_t i = 0;i < n; ++i){
        for(size_t j = 0;j < n; ++j){
           a[i][j]=((float) rand()/(RAND_MAX));
        }
    }
return  a;
}


int main(int argc, char **argv){
	
	
	int matrix_size,no_of_data;
	cout << "Please enter matrix size: ";
	cout<<endl;
	cin >> matrix_size;
    cout << "Please enter number of data: ";
	cout<<endl;
	cin >> no_of_data;
	cout << "All measurement units are in microseconds"<<endl;
	cout<<endl;
	cout << "Algorithm II = Testing." <<endl;
	cout << "TIME_II-I  TIME_I-II   ERROR_SUM  ERROR_COUNT "<<endl;
	cout << "=================================================="<<endl;
	vector<float> duration_s_array;
	vector<float> duration_p_array;
	vector< vector<float> > a= createRandomMatrix(matrix_size);
	int i, j, k, sweep;
	float s;
	
	auto matrix=createRandomMatrix(matrix_size);
	auto matrix_t=transpose(matrix);
	auto matrix_positive_definite=multiply(matrix_t,matrix); // create positive definite matrix
	auto matrix_decompose=LUD_pair(matrix_positive_definite); // decomposition
	vector< vector<float> > U=matrix_decompose.first;
	vector< vector<float> > L=matrix_decompose.second;
	
	
	
	for(int sample=0;sample<no_of_data ;++sample){	
		vector< vector<float> > U_series= U;
		vector< vector<float> > L_series= L;
		vector< vector<float> > U_parallel= U;
		vector< vector<float> > L_parallel= L;
		
		system_clock::time_point start = system_clock::now();
		
		for (sweep=1; sweep<3; ++sweep){
			for (i = 0; i < matrix_size; ++i) { 
				
				for(j= 0; j < matrix_size; ++j){
					float sum2=0;			//re-initialization
					for(k= 0; k <= (i-1); ++k){
						//sum2+=L_series[i][k]*U_series[k][j];
						float sum2_temp=L_series[i][k]*U_series[k][j];
						sum2+=sum2_temp;
						
						
					}
					float sum1=0;			//re-initialization
					
					for(k= 0; k <= (j-1); ++k){
						//sum1+=L_series[i][k]*U_series[k][j];
						float sum1_temp=L_series[i][k]*U_series[k][j];
						sum1+=sum1_temp;
					}
					
					
					if(i>j){
						L_series[i][j]=(matrix_positive_definite[i][j]-sum1)/U_series[j][j]; 
					}
					else{
						U_series[i][j]=matrix_positive_definite[i][j]-sum2;
					}	
				}
			}	
		}
			
		system_clock::time_point stop = system_clock::now();
		
		nanoseconds duration = stop - start;
		duration_s_array.push_back(duration_cast<microseconds>(duration).count());
		
		cout << duration_cast<microseconds>(duration).count() <<"         ";
		
		//________________________________________________	
		system_clock::time_point start_p = system_clock::now();
		for (sweep=1; sweep<3; ++sweep){
		{
			for (i = 0; i < matrix_size; ++i) { 
				for(j= 0; j < matrix_size; ++j){			
					float sum1=0;			//re-initialization
					
					for(k= 0; k <= (j-1); ++k){
						
						float sum1_temp=L_parallel[i][k]*U_parallel[k][j];
						sum1+=sum1_temp;
						
					}
					float sum2=0;			//re-initialization
					
					for(k= 0; k <= (i-1); ++k){	
					
						float sum2_temp=L_parallel[i][k]*U_parallel[k][j];
						
						sum2+=sum2_temp;
						
					}
					
					if(i>j){
						L_parallel[i][j]=(matrix_positive_definite[i][j]-sum1)/U_parallel[j][j]; 
					}
					else{
						U_parallel[i][j]=matrix_positive_definite[i][j]-sum2;
					}		
				}
			}
		}
		
		}
		
		system_clock::time_point stop_p = system_clock::now();
		nanoseconds duration_p = stop_p - start_p;
		duration_p_array.push_back(duration_cast<microseconds>(duration_p).count());
		
		cout  << duration_cast<microseconds>(duration_p).count()<< "            ";
		
		//Calculating accuracy
		float error_sum= 0;
		float error=0;
		for (i = 0; i < matrix_size; ++i) { 
			for (j = 0; j < matrix_size; ++j){
				error=abs(U_parallel[i][j]-U_series[i][j])+abs(L_parallel[i][j]-L_series[i][j]);
				error_sum +=error;
			}
		}
		
		int count_error=0;//Re-initialization
		count_error=countError(U_series,U_parallel)+countError(L_series,L_parallel);
		cout << error_sum<<"           "<< count_error<<endl;
		
	}
	cout<<endl;
	cout << "Total time (part II -> part I): " <<endl;
	std::copy(duration_s_array.begin(), duration_s_array.end(), std::ostream_iterator<float>(std::cout, "  "));
	cout<<endl;
	cout << "Total time (part I -> part II): " <<endl;
	std::copy(duration_p_array.begin(), duration_p_array.end(), std::ostream_iterator<float>(std::cout, "  "));
	cout<<endl;
	
	
	float average_s = accumulate( duration_s_array.begin(), duration_s_array.end(), 0.0)/ duration_s_array.size();
	float average_p = accumulate( duration_p_array.begin(), duration_p_array.end(), 0.0)/ duration_p_array.size();
	cout << "Average time (part II->part I) : " <<average_s<<endl;
	cout << "Average time (part I->part II): " <<average_p<<endl;
	float performance;
	if(average_s>average_p){
		performance=(average_s-average_p)/average_p*100;
	}
	else{
		performance=0;
	}
	cout << "Performance improvement : " <<performance<<" %"<<endl;
	
	
	return 0;
	
    }
