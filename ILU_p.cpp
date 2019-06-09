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

void printMatrix(auto &myArray, int rows, int column) {
	for(size_t x = 0;x < rows; ++x){
        for(size_t y = 0;y < column;++y){
            printf("%f", myArray[x][y]);
			printf("  ");
        }
        cout << endl;
    }		
}

pair<float**, float**> LUD_pair(float** &a, size_t n) {
// get upper decomposition
	float **U;
	U = new float*[n];
	for (int i = 0; i < n; ++i) {
		U[i] = new float[n];
	}
	if (U==NULL) {
		cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	// initialization
	for(size_t i = 0;i < n; ++i){
		for(size_t j=0; j<n; ++j){
			U[i][j]=a[i][j];
		}
	}
	
	for(size_t i = 1;i < n; ++i){
		for(size_t j=0; j<=(i-1); ++j){
			U[i][j]=0;
		}
	}
// get lower decomposition
	float **L;
	L = new float*[n];
	for (int i = 0; i < n; ++i) {
		L[i] = new float[n];
	}
	if (L==NULL) {
		cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	// initialization
	for(size_t i = 0;i < n; ++i){
		for(size_t j=0; j<n; ++j){
			L[i][j]=a[i][j];
		}
	}

	for(size_t i = 0;i < n; ++i){
		for(size_t j = i;j <n; ++j){
			L[i][j]=0;
		}
		L[i][i]=1;	
	}
	return make_pair(U, L);	
}

int countError(float** &A,float** &B, int N) {
	int count=0;
	for(size_t i = 0;i < N; ++i){
        for(size_t j = 0;j < N; ++j){
            if(abs(A[i][j]-B[i][j])>1e-2){
				count+=1;
			}
        }
    }	
	return count;
}

float** transpose(float** &A, int rows, int column) {
		float **result;
		result = new float*[rows];

		for (int i = 0; i < rows; ++i) {
			result[i] = new float[column];
		}
		if (result==NULL) {
			cout << "Allocation of memory failed\n"<<endl;
			exit(0);
		}
		
		for (int i = 0; i < column; ++i) {
			for (int j = 0; j < rows; ++j){
				result[i][j]=A[j][i];
			}
		}
		return result;
	}

float** multiply(float** &A, float**B, size_t A_rows, size_t A_col, size_t B_col) {
		float **result;
		result = new float*[A_rows];

		for (int i = 0; i < A_rows; ++i) {
			result[i] = new float[B_col];
		}
		if (result==NULL) {
			cout << "Allocation of memory failed\n"<<endl;
			exit(0);
		}
		for (int i = 0; i < A_rows; ++i) {
			for (int j = 0; j < B_col; ++j){
				float s = 0;
				for (int k = 0; k <A_col; k++) {
					s += A[i][ k] * B[k][j];
				}
				result[i][j]=s;
			}
		}
		return result;
	}
	

	
float** createRandomMatrix(int& n) {
	system_clock::time_point start = system_clock::now();
	float **a;
	a = new float*[n];
	for (int i = 0; i < n; ++i) {
		a[i] = new float[n];
	}
	
	for(size_t i = 0;i < n; ++i){
        for(size_t j = 0;j < n; ++j){
			system_clock::time_point stop = system_clock::now();
			nanoseconds duration = stop - start;
			int time_count=duration.count();
			//srand(i+j+time_count);
            a[i][j]=((float) rand()/(RAND_MAX));
        }
    }
return  a;
}

//_____Incomplete LU Factorization (Algorithm 1)___________________________________
//Store result in one matrix

float** ILU (float** &a, int n) {
	float **matrix;
	matrix = new float*[n];
	for (int i = 0; i < n; ++i) {
		matrix[i] = new float[n];
	}
	if (matrix==NULL) {
        cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	// initialization
	for(size_t i = 0;i < n; ++i){
		for(size_t j=0; j<n; ++j){
			matrix[i][j]=a[i][j];
		}
	}
	
	for (size_t i = 1; i < n; ++i) { 
		for(size_t k= 0; k <=(i-1); ++k){
			matrix[i][k]=matrix[i][k]/matrix[k][k]; 
			for(size_t j= k+1; j < n; ++j){
				matrix[i][j]=matrix[i][j]-matrix[i][k]*matrix[k][j];
			}
		}
	}	
	return matrix;
}


//_____LU Factorization___________________________________
 pair<float**, float**> LUF_pair(float** &myArray,int n) {
	float **U;
	U = new float*[n];
	for (int i = 0; i < n; ++i) {
		U[i] = new float[n];
	}
	if (U==NULL) {
        cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	// initialization
	for(size_t i = 0;i < n; ++i){
		for(size_t j=0; j<n; ++j){
			U[i][j]=myArray[i][j];
		}
	}
	//___________________________________
	float **L;
	L = new float*[n];
	for (int i = 0; i < n; ++i) {
		L[i] = new float[n];
	}
	if (L==NULL) {
        cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	// initialization
	for (size_t i = 0; i < n; ++i) {     //L = I
		for(size_t j= 0; j < n; ++j){
			if (i==j){
				L[i][j]=1;
			}
		}
	}
	//____Algorithm________________________________________
	
	for (size_t k = 0; k < (n-1); ++k) { 
		for(size_t j= k+1; j < n; ++j){
			L[j][k]=U[j][k]/U[k][k]; 
			for(size_t x= k; x < n;++x){
				U[j][x]=U[j][x]-L[j][k]*U[k][x];		
			}			
		}
	}	
	return make_pair(U, L);	
}



// ___________Algorithm 2_____________
pair<float**, float**> fine_grained_ILU(float** &matrix, size_t n) {
	auto matrix_temp=LUD_pair(matrix,n);
	float** U=matrix_temp.first;
	float** L=matrix_temp.second;
	float sum1,sum2;
	size_t i, j, k, sweep;
	
	for (sweep=1; sweep<5; ++sweep){
		for (i = 0; i < n; ++i) { 
			for(j= 0; j < n; ++j){
				sum1=0;			//re-initialization
				for(k= 0; k < j; ++k){
					sum1+=L[i][k]*U[k][j];
				}
				sum2=0;			//re-initialization
				for(k= 0; k < i; ++k){
					sum2+=L[i][k]*U[k][j];
				}
				
				if(i>j){
					L[i][j]=(matrix[i][j]-sum1)/U[j][j]; 
				}
				else{
					U[i][j]=matrix[i][j]-sum2;
				}	
			}
		}	
	}
	return make_pair(U, L);	
}

// ___________Algorithm 3_____________
float** symmetric_fine_grained_ILU(float** &matrix, size_t n) {
	auto matrix_temp=LUD_pair(matrix, n);
	float** U=matrix_temp.first;
	float sum,s;
	int i, j, k, sweep;
	
	for (sweep=1; sweep<5; ++sweep){
		for (i = 0; i < n; ++i) { 
			for(j= 0; j < n; ++j){
				for(k= 0; k <= (i-1); ++k){
					sum+=U[k][i]*U[k][j];
				}
				s=matrix[i][j]-sum;
				if(i!=j){
					U[i][j]=s/U[i][i]; 
				}
				else{
					U[i][i]=pow(s,0.5);
				}
				sum=0; // reinitialization
			}
		}	
	}
	for(int i = 0; i < n; ++i){
		delete[] matrix_temp.second[i]; //deletes an inner array of L
	}
	delete[] matrix_temp.second;
	
	return U;	
}

 

int main(int argc, char **argv){
	//#############################################################
	/*
	int N=190;
	float **matrix;
	matrix = createRandomMatrix(N);
	
	float **matrix_positive_definite;
	matrix_positive_definite = new float*[N];

	for (int i = 0; i < N; ++i) {
		matrix_positive_definite[i] = new float[N];
	}
	if (matrix_positive_definite==NULL) {
        cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	#pragma omp parallel num_threads(6)
	{
	#pragma omp for
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			float s = 0;
				for (int k = 0; k <N; k++) {
					s += matrix[k][i] *matrix[k][j];
				}
			matrix_positive_definite[i][j] = s;
		}
	}
	}//end of pragma
	
	auto answer=symmetric_fine_grained_ILU(matrix_positive_definite,N);
	printf("U [2][5] = %f \n", (float) answer[2][5]);
	
	printf("Matrix positive definite= \n");
	printMatrix(matrix_positive_definite,N,N);
	printf("U = \n");
	printMatrix(answer,N,N);
	
	
	
	//Deletion___________________________
	for(int i = 0; i < N; ++i){
		delete[] matrix[i]; //deletes an inner array 
		delete[] matrix_positive_definite[i];
		delete[] answer[i];
		
	}

	delete[] matrix;
	delete[] matrix_positive_definite;
	delete[] answer;
	*/
//###############################################################
	
/*
	int matrix_size,no_of_data;
	cout << "Please enter matrix size: ";
	cout<<endl;
	cin >> matrix_size; //max 400
    cout << "Please enter number of data: ";
	cout<<endl;
	cin >> no_of_data;
	cout << "All measurement units are in microseconds"<<endl;
	cout<<endl;
	cout << "Algorithm II = Fine-Grained Parallel Incomplete Factorization." <<endl;
	cout << "TIME_SERIES TIME_PARALLEL  ERROR_SUM  ERROR_COUNT "<<endl;
	cout << "=================================================="<<endl;
	vector<float> duration_s_array;
	vector<float> duration_p_array;
	
	int i, j, k, sweep;
	float sum1, sum2;
	
	float** matrix=createRandomMatrix(matrix_size);
	auto matrix_t=transpose(matrix,matrix_size,matrix_size);
	auto matrix_positive_definite=multiply(matrix_t,matrix,matrix_size,matrix_size,matrix_size); // create positive definite matrix
	auto matrix_decompose=LUD_pair(matrix_positive_definite,matrix_size); // decomposition	
		
	float ** U_series;
	U_series = new float*[matrix_size];

	for (int i = 0; i < matrix_size; ++i) {
		U_series[i] = new float[matrix_size];
	}
	if (U_series==NULL) {
		cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	
	float ** U_parallel;
	U_parallel = new float*[matrix_size];

	for (int i = 0; i < matrix_size; ++i) {
		U_parallel[i] = new float[matrix_size];
	}
	if (U_parallel==NULL) {
		cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	float ** L_series;
	L_series = new float*[matrix_size];

	for (int i = 0; i < matrix_size; ++i) {
		L_series[i] = new float[matrix_size];
	}
	if (L_series==NULL) {
		cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	
	float ** L_parallel;
	L_parallel = new float*[matrix_size];

	for (int i = 0; i < matrix_size; ++i) {
			L_parallel[i] = new float[matrix_size];
	}
	if (L_parallel==NULL) {
			cout << "Allocation of memory failed\n"<<endl;
			exit(0);
	}
	
	for(int sample=0;sample<no_of_data ;++sample){	
		
	
		for (int i = 0; i < matrix_size; ++i) {
			for (int j = 0; j < matrix_size; ++j) {
				U_series[i][j] = matrix_decompose.first[i][j];
			}
		}
		//___________________________________
		
	
		for (int i = 0; i < matrix_size; ++i) {
			for (int j = 0; j < matrix_size; ++j) {
				U_parallel[i][j] = matrix_decompose.first[i][j];
			}
		}
		//___________________________________
		
	
		for (int i = 0; i < matrix_size; ++i) {
			for (int j = 0; j < matrix_size; ++j) {
				L_series[i][j] = matrix_decompose.second[i][j];
			}
		}
		//____________________________________
		
	
		for (int i = 0; i < matrix_size; ++i) {
			for (int j = 0; j < matrix_size; ++j) {
				L_parallel[i][j] = matrix_decompose.second[i][j];
			}
		}
	//___________________________________
		
		
		system_clock::time_point start = system_clock::now();
		
		for (sweep=1; sweep<5; ++sweep){
			for (i = 0; i < matrix_size; ++i) { 
				for(j= 0; j < matrix_size; ++j){
					sum1=0;			//re-initialization
					for(k= 0; k <j; ++k){
						sum1+=L_series[i][k]*U_series[k][j];
					}
					sum2=0;			//re-initialization
					for(k= 0; k <i; ++k){
						sum2+=L_series[i][k]*U_series[k][j];	
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
		
		//#pragma omp parallel for schedule(static)
		//#pragma omp parallel for schedule(static) reduction(+:sum1)
		//#pragma omp parallel for collapse(2)
		//#pragma omp parallel num_threads(2) shared(U_parallel, L_parallel)
		#pragma omp parallel num_threads(2)
		{
		for (sweep=1; sweep<5; ++sweep){
			#pragma omp for
			for (i = 0; i < matrix_size; ++i) { 
				for(j= 0; j < matrix_size; ++j){
					sum1=0;			//re-initialization
					
					for(k= 0; k <j; ++k){
						sum1+=L_parallel[i][k]*U_parallel[k][j];
					}
					
					sum2=0;			//re-initialization
					for(k= 0; k < i; ++k){
						sum2+=L_parallel[i][k]*U_parallel[k][j]; //this is the error source
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
		}//end of pragma
		
		
		system_clock::time_point stop_p = system_clock::now();
		nanoseconds duration_p = stop_p - start_p;
		duration_p_array.push_back(duration_cast<microseconds>(duration_p).count());
		
		cout  << duration_cast<microseconds>(duration_p).count()<< "            ";
		
		//Calculating accuracy
		float error_sum= 0;
		float error=0;
		for (i = 0; i < matrix_size; ++i) { 
			for (j = 0; j < matrix_size; ++j){
				error=abs(U_parallel[i][j]-U_series[i][j]+L_parallel[i][j]-L_series[i][j]);
				error_sum +=error;
			}
		}
		
		int count_error=0;//Re-initialization
		count_error=countError(U_series, U_parallel, matrix_size);
		cout << error_sum<<"           "<< count_error<<endl;	
		
	}
	
	cout<<endl;
	cout << "Total time series: " <<endl;
	std::copy(duration_s_array.begin(), duration_s_array.end(), std::ostream_iterator<float>(std::cout, "  "));
	cout<<endl;
	cout << "Total time parallel: " <<endl;
	std::copy(duration_p_array.begin(), duration_p_array.end(), std::ostream_iterator<float>(std::cout, "  "));
	cout<<endl;
	
	
	float average_s = accumulate( duration_s_array.begin(), duration_s_array.end(), 0.0)/ duration_s_array.size();
	float average_p = accumulate( duration_p_array.begin(), duration_p_array.end(), 0.0)/ duration_p_array.size();
	cout << "Average time series : " <<average_s<<endl;
	cout << "Average time parallel: " <<average_p<<endl;
	float performance;
	
	if(average_s>average_p){
		performance=(average_s-average_p)/average_p*100;
	}
	else{
		performance=0;
	}
	cout << "Performance improvement : " <<performance<<" %"<<endl;
	
	for(int i = 0; i < matrix_size; ++i){
		delete[] matrix[i]; //deletes an inner array 
		delete[] matrix_t[i]; 
		delete[] matrix_positive_definite[i];  //deletes an inner array 
		delete[] matrix_decompose.first[i]; 
		delete[] matrix_decompose.second[i]; 
		delete[] U_parallel[i];
		delete[] U_series[i];
		delete[] L_parallel[i];
		delete[] L_series[i];
	}
	
	delete[] matrix;
	delete[] matrix_t;
	delete[] matrix_positive_definite;
	delete[] matrix_decompose.first;
	delete[] matrix_decompose.second;
	delete[] U_parallel;
	delete[] U_series;
	delete[] L_parallel;
	delete[] L_series;	
	
	*/
	
	
	//########################################################################
	
	
	int matrix_size,no_of_data;
	cout << "Please enter matrix size: ";
	cout<<endl;
	cin >> matrix_size; 
    cout << "Please enter number of data: ";
	cout<<endl; //max 600
	cin >> no_of_data;
	cout << "All measurement units are in microseconds"<<endl;
	cout<<endl;
	cout << "Algorithm III = Symmetric Fine-Grained Parallel Incomplete Factorization." <<endl;
	cout << "TIME_SERIES TIME_PARALLEL  ERROR_SUM  ERROR_COUNT "<<endl;
	cout << "=================================================="<<endl;
	vector<float> duration_s_array;
	vector<float> duration_p_array;
	float** a= createRandomMatrix(matrix_size); 
	int i, j, k, sweep;
	float sum,residual,s;
	
	float** matrix=createRandomMatrix(matrix_size);
	float** matrix_t=transpose(matrix, matrix_size, matrix_size);
	float** matrix_positive_definite=multiply(matrix_t,matrix, matrix_size, matrix_size, matrix_size); // create positive definite matrix
	auto matrix_decompose=LUD_pair(matrix_positive_definite,matrix_size); // decomposition	
	
	float ** U_series;
	U_series = new float*[matrix_size];

	for (int i = 0; i < matrix_size; ++i) {
		U_series[i] = new float[matrix_size];
	}
	if (U_series==NULL) {
		cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	
	float ** U_parallel;
	U_parallel = new float*[matrix_size];

	for (int i = 0; i < matrix_size; ++i) {
		U_parallel[i] = new float[matrix_size];
	}
	if (U_parallel==NULL) {
		cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	
	for(int sample=0;sample<no_of_data ;++sample){
		
		for (int i = 0; i < matrix_size; ++i) {
			for (int j = 0; j < matrix_size; ++j) {
				U_series[i][j] = matrix_decompose.first[i][j];
			}
		}
		//___________________________________
		
	
		for (int i = 0; i < matrix_size; ++i) {
			for (int j = 0; j < matrix_size; ++j) {
				U_parallel[i][j] = matrix_decompose.first[i][j];
			}
		}
		//___________________________________
		
		system_clock::time_point start = system_clock::now();
		
		for (sweep=1; sweep<5; ++sweep){
			for (i = 0; i < matrix_size; ++i) { 
				for(j= 0; j < matrix_size; ++j){
					for(k= 0; k <= (i-1); ++k){
						sum+=U_series[k][i]*U_series[k][j];
					}
					s=matrix_positive_definite[i][j]-sum;
					
					if(i!=j){
						U_series[i][j]=s/U_series[i][i]; 
					}
					else{
						U_series[i][i]=pow(s,0.5);
					}
					sum=0;// reinitialization
				}
			}	
		}
			
		system_clock::time_point stop = system_clock::now();
		
		nanoseconds duration = stop - start;
		duration_s_array.push_back(duration_cast<microseconds>(duration).count());
		
		cout << duration_cast<microseconds>(duration).count() <<"         ";
		
		//________________________________________________	
		system_clock::time_point start_p = system_clock::now();
		for (sweep=1; sweep<5; ++sweep){
		#pragma omp parallel
		{
			#pragma omp for collapse(2) reduction(+:sum)
			for (i = 0; i < matrix_size; ++i) { 
				
				for(j= 0; j < matrix_size; ++j){
					for(k= 0; k <= (i-1); ++k){
						//sum+=U_parallel[k][i]*U_parallel[k][j]; //change algorithm
						float sum_temp=U_series[k][i]*U_series[k][j];
						sum+=sum_temp;
					}
					
					s=matrix_positive_definite[i][j]-sum;
					
					if(i!=j){
						U_parallel[i][j]=s/U_parallel[i][i]; 
					}
					else{
						U_parallel[i][i]=pow(s,0.5);
					}
					sum=0; // reinitialization
				}
			}
		
		} //end of parallel region
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
				error=abs(U_parallel[i][j]-U_series[i][j]);
				error_sum +=error;
			}
		}
		
		int count_error=0;//Re-initialization
		count_error=countError(U_series,U_parallel, matrix_size);
		cout << error_sum<<"           "<< count_error<<endl;
		
	}
	cout<<endl;
	cout << "Total time series: " <<endl;
	std::copy(duration_s_array.begin(), duration_s_array.end(), std::ostream_iterator<float>(std::cout, "  "));
	cout<<endl;
	cout << "Total time parallel: " <<endl;
	std::copy(duration_p_array.begin(), duration_p_array.end(), std::ostream_iterator<float>(std::cout, "  "));
	cout<<endl;
	
	
	float average_s = accumulate( duration_s_array.begin(), duration_s_array.end(), 0.0)/ duration_s_array.size();
	float average_p = accumulate( duration_p_array.begin(), duration_p_array.end(), 0.0)/ duration_p_array.size();
	cout << "Average time series : " <<average_s<<endl;
	cout << "Average time parallel: " <<average_p<<endl;
	float performance;
	if(average_s>average_p){
		performance=(average_s-average_p)/average_p*100;
	}
	else{
		performance=0;
	}
	cout << "Performance improvement : " <<performance<<" %"<<endl;
	for(int i = 0; i < matrix_size; ++i){
		delete[] matrix[i]; //deletes an inner array 
		delete[] matrix_t[i]; 
		delete[] matrix_decompose.first[i];  
		delete[] matrix_decompose.second[i]; 
		delete[] matrix_positive_definite[i];  
		delete[] U_parallel[i]; 
		delete[] U_series[i];
		
	}
	delete[] matrix;
	delete[] matrix_t;
	delete[] matrix_decompose.first;
	delete[] matrix_decompose.second; 
	delete[] matrix_positive_definite;
	delete[] U_parallel;
	delete[] U_series;
	
	
	//########################################################################
	/*
	int matrix_size,no_of_data;
	cout << "Please enter matrix size: ";
	cout<<endl;
	cin >> matrix_size;
    cout << "Please enter number of data: ";
	cout<<endl;
	cin >> no_of_data;
	cout << "All measurement units are in microseconds"<<endl;
	cout<<endl;
	cout << "Algorithm I =  ILU" <<endl;
	cout << "TIME_SERIES TIME_PARALLEL  ERROR_SUM  ERROR_COUNT "<<endl;
	cout << "=================================================="<<endl;
	vector<float> duration_s_array;
	vector<float> duration_p_array;
	float** a=createRandomMatrix(matrix_size);
	float sum2=0;
	float ** a_series;
	a_series = new float*[matrix_size];

	for (int i = 0; i < matrix_size; ++i) {
		a_series[i] = new float[matrix_size];
	}
	if (a_series==NULL) {
		cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	
	float ** a_parallel;
	a_parallel = new float*[matrix_size];

	for (int i = 0; i < matrix_size; ++i) {
		a_parallel[i] = new float[matrix_size];
	}
	if (a_parallel==NULL) {
		cout << "Allocation of memory failed\n"<<endl;
		exit(0);
	}
	
	for(int sample=0;sample<no_of_data ;++sample){	
		int i, j, k;
		
		for (int i = 0; i < matrix_size; ++i) {
			for (int j = 0; j < matrix_size; ++j) {
				a_series[i][j] = a[i][j];
			}
		}
		//___________________________________
	
		for (int i = 0; i < matrix_size; ++i) {
			for (int j = 0; j < matrix_size; ++j) {
				a_parallel[i][j] = a[i][j];
			}
		}
		//___________________________________
		
		system_clock::time_point start = system_clock::now();
		
		for (i = 1; i < matrix_size; ++i) { 
				for(k= 0; k <= (i-1); ++k){
					a_series[i][k]=a_series[i][k]/a_series[k][k]; 
					for(j= k+1; j < matrix_size; ++j){
					a_series[i][j]=a_series[i][j]-a_series[i][k]*a_series[k][j];
					}
				}
		}
		
		system_clock::time_point stop = system_clock::now();
		
		nanoseconds duration = stop - start;
		duration_s_array.push_back(duration_cast<microseconds>(duration).count());
		
		cout << duration_cast<microseconds>(duration).count() <<"         ";
		
		
		//________________________________________________	
		//int chunk = 4096 ; //change from original paper due to lower comp specs
		
		system_clock::time_point start_p = system_clock::now();
				
		//#pragma omp parallel shared (chunk) private (i,j,k) num_threads (8)
		//#pragma omp parallel private (i) num_threads (8)
		#pragma omp parallel 
		{
			
		//#pragma omp for schedule (dynamic, chunk)	//error using chunk
		//#pragma omp for schedule (dynamic)
		//#pragma omp atomic
			#pragma omp for collapse(1) reduction(+:sum2)
			for (i = 1; i < matrix_size; ++i) { 
				 //works but slower
				for(k= 0; k <= (i-1); ++k){
					
					a_parallel[i][k]=a_parallel[i][k]/a_parallel[k][k]; 
				//#pragma omp parallel for
					for(j= k+1; j < matrix_size; ++j){
						//a_parallel[i][j]=a_parallel[i][j]-a_parallel[i][k]*a_parallel[k][j];
						float sum1=0;
						sum1 =a_parallel[i][k]*a_parallel[k][j];
						float sum2=0;
						sum2=a_parallel[i][j]-sum1;
						a_parallel[i][j]=sum2;
					}
				}
		
			}		
		} // end pragma
		
		system_clock::time_point stop_p = system_clock::now();
		nanoseconds duration_p = stop_p - start_p;
		duration_p_array.push_back(duration_cast<microseconds>(duration_p).count());
		
		cout  << duration_cast<microseconds>(duration_p).count()<< "            ";
		
			
		//Calculating accuracy
		float error_sum= 0;
		float error=0;
		for (i = 0; i < matrix_size; ++i) { 
			for (j = 0; j < matrix_size; ++j){
				error=abs(a_parallel[i][j]-a_series[i][j]);
				error_sum +=error;
			}
		}
		
		int count_error=0;//Re-initialization
		count_error=countError(a_series,a_parallel, matrix_size);
		cout << error_sum<<"           "<< count_error<<endl;
			
	}
	cout<<endl;
	cout << "Total time series: " <<endl;
	std::copy(duration_s_array.begin(), duration_s_array.end(), std::ostream_iterator<float>(std::cout, "  "));
	cout<<endl;
	cout << "Total time parallel: " <<endl;
	std::copy(duration_p_array.begin(), duration_p_array.end(), std::ostream_iterator<float>(std::cout, "  "));
	cout<<endl;
	
	
	float average_s = accumulate( duration_s_array.begin(), duration_s_array.end(), 0.0)/ duration_s_array.size();
	float average_p = accumulate( duration_p_array.begin(), duration_p_array.end(), 0.0)/ duration_p_array.size();
	cout << "Average time series : " <<average_s<<endl;
	cout << "Average time parallel: " <<average_p<<endl;
	float performance;
	if(average_s>average_p){
		performance=(average_s-average_p)/average_p*100;
	}
	else{
		performance=0;
	}
	cout << "Performance improvement : " <<performance<<" %"<<endl;
	
	for(int i = 0; i < matrix_size; ++i){
		delete[] a[i]; //deletes an inner array 
		delete[] a_parallel[i]; 
		delete[] a_series[i];
		
	}
	delete[] a;
	delete[] a_parallel;
	delete[] a_series;
	
	*/
	//#######################################################################
	
	/*
	
	float z= -0.5;// -1 < z < 2 to be symmetric positive definite
	vector<vector<float> >a={{1,2,3,4},{21,22,23,24},{31,3,1,34},{1,2,43,4}};
	vector<vector<float> >b={{2,-1,z},{-1,2,-1},{z,-1,2}}; //symmetric positive definite
	vector<vector<float> >c={{4,1,-1},{1,2,1},{-1,1,2}}; //symmetric positive definite
	
	
	
	printf("____________________________________ \n");
	auto answer3=fine_grained_ILU(a);
	printf("ILU fine-grained upper matrix = \n");
	printMatrix(answer3.first);
	printf("ILU fine-grained lower matrix = \n");
	printMatrix(answer3.second);
	
	*/
	
	
    }
