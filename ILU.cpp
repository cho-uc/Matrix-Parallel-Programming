#include<iostream>
#include<cstdio>
#include <cstdlib>
#include <vector> 
#include <chrono>
#include <cmath>
#include <omp.h>
#include <stdio.h>

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
	for (i = 0; i < n; i++) { //L = I
		for(j= 0; j < n; j++){
			if (i==j){
				L[i][j]=1;
			}
		}
	}
	//____Algorithm________________________________________
	
	for (k = 0; k < n; k++) { 
		for(j= k+1; j < n; j++){
			L[j][k]=U[j][k]/U[k][k]; 
			for(x= k; x < n; x++){
				U[j][x]=U[j][x]-L[j][k]*U[k][x];
			}
		}
		
	}	
	
	return make_pair(U, L);	
}


pair<vector< vector<float> >, vector< vector<float> >> fine_grained_ILU(vector< vector<float> > &a) {
	int n=a.size();
	vector< vector<float> > U(n, vector<float>(n,2));
	vector< vector<float> > L(n, vector<float>(n,2));
	
	float sum=0,residual;
	int i = 0, j = 0, k = 0;
	
	
	while (residual>1e-6){
		
	for (i = 0; i < n; i++) { 
		for(j= 0; j < n; j++){
			for(k= 0; k < n; k++){
			sum+=L[i][k]*U[k][j];
			if(i>j){
				L[i][j]=(a[i][j]-sum)/U[j][j]; 
			}
			else{
				U[i][j]=a[i][j]-sum;
			}
			}
		}
		
	}	
	residual=1e-6;	//need to be updated
	}
	return make_pair(U, L);	
	
}

vector< vector<float>> symmetric_fine_grained_ILU(vector< vector<float> > &a) {
	int n=a.size();
	vector< vector<float> > U(n, vector<float>(n,2));
	
	float sum=0,residual,s;
	int i = 0, j = 0, k = 0;
	
	while (residual>1e-6){
		
	for (i = 0; i < n; i++) { 
		for(j= 0; j < n; j++){
			for(k= 0; k < n; k++){
			sum+=U[k][i]*U[k][j];
			s=a[i][j]-sum;
			if(i!=j){
				U[i][j]=s/U[i][i]; 
			}
			else{
				U[i][i]=pow(s,0.5);
			}
			}
		}
		
	}	
	residual=1e-6;	//need to be updated
	}
	return U;	
	
}

//_____Incomplete LU Factorization___________________________________
//Store result in one matrix
 vector< vector<float> > ILU(vector< vector<float> > &matrix) {
	auto myArray= matrix;
	int n=myArray.size();
	int i = 0, j = 0, k = 0;
	
	for (i = 1; i < n; i++) { 
		for(k= 0; k <= (i-1); k++){
			myArray[i][k]=myArray[i][k]/myArray[k][k]; 
			for(j= k+1; j < n; j++){
				myArray[i][j]=myArray[i][j]-myArray[i][k]*myArray[k][j];
			}
		}
		
	}	
		
	return myArray;	
	
}


int main(int argc, char **argv){
    	/*
	
	
	
	int n = 400;
	auto x_series= createRandomMatrix(n);	
	system_clock::time_point start = system_clock::now();
	
	auto answer_s=ILU(x_series);		
	
	system_clock::time_point stop = system_clock::now();
	nanoseconds duration = stop - start;
	
	cout << "Time series: "<< duration_cast<microseconds>(duration).count() << " microseconds ("<<duration_cast<milliseconds>(duration).count()
	<<" milliseconds) for matrix size " << x_series.size()<<endl;;
	
	//________________________________________________
	auto x_parallel= createRandomMatrix(n);	
	int chunk = 4096 ;
	system_clock::time_point start_p = system_clock::now();
	int i;
	# pragma omp parallel shared ( chunk ) private (i)
	{
	# pragma omp for schedule (dynamic, chunk )
	auto answer_p=ILU(x_parallel);		
	}
	
	system_clock::time_point stop_p = system_clock::now();
	nanoseconds duration_p = stop_p - start_p;
	cout << "Time parallel: "<< duration_cast<microseconds>(duration_p).count() << " microseconds ("<<duration_cast<milliseconds>(duration_p).count()
	<<" milliseconds) for matrix size " << x_parallel.size()<<endl;;
	
	
	*/
	
	int n=4;
	auto x_parallel= createRandomMatrix(n);	
	printMatrix(x_parallel);
	
	vector<vector<float> >a={{1,2,3,4},{21,22,23,24},{31,3,0,34},{1,2,43,4}};
	
	printf("Initial matrix = \n");
	printMatrix(a);
	printf("ILU = \n");
	auto answer1=ILU(a);
	printMatrix(answer1);
	
	printf("LUF upper matrix = \n");
	auto answer=LUF(a);
	printMatrix(answer.first);
	printf("LUF  lower matrix = \n");
	printMatrix(answer.second);	
	
	/*
	auto answer2=symmetric_fine_grained_ILU(a);
	printf("ILU symmetric fine-grained upper matrix = \n");
	printMatrix(answer2);
	
	
	auto answer=fine_grained_ILU(a);
	printf("ILU fine-grained upper matrix = \n");
	printMatrix(answer2.first);
	printf("ILU fine-grained lower matrix = \n");
	printMatrix(answer2.second);
	*/
    }
