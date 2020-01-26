/* Performance testing for assignment operator '+='
Comparison between '+=' and '='
Two kernels should be executed separately or else the kernels will influence each other
Kernel that executed later was faster regardless of operator
Result :	 assignment operator '=' is faster than '+='
			100 ms vs 94 ms for 256*100000  nodes
This result will be beneficial to optimize Peridynamics kernel

*/
#include <cmath>	//for calculating power & NaN
#include<iostream>
#include<cstdio>
#include <vector>
#include <cstdlib>
#include <fstream> // for writing to file
#include <math.h>       //exp, pi
#include <chrono>	//for time measurement
#include <fstream>
#include <ctime>

using namespace std;
using namespace std::chrono;

//Use assignment operator '+='
__global__ void add_01 (float *array_a,
	 float *array_b,
	 float *array_c ){
	
	size_t i= threadIdx.x+ blockDim.x*threadIdx.y+blockDim.x*blockDim.y*blockIdx.x;
	
	array_c[i] += (array_a[i]+array_b[i])*sqrt(array_a[i])*sqrt(array_b[i]);
}

//Use assignment operator '='
__global__ void add_02 (float *array_a,
	 float *array_b,
	 float *array_c ){
	
	size_t i= threadIdx.x+ blockDim.x*threadIdx.y+blockDim.x*blockDim.y*blockIdx.x;
	
	array_c[i] = (array_a[i]+array_b[i])*sqrt(array_a[i])*sqrt(array_b[i]);
	
}


int main(int argc, char **argv){
	cout<<"Start of program assignment operator test"<<endl;
	const size_t node = 256*100000;
	
	//Differentiate a,b to 01 & 02 to avoid kernel reusing the value
	float *array_a_01= (float*) calloc (node, sizeof(float));
	float *array_b_01= (float*) calloc (node, sizeof(float));
	float *array_a_02= (float*) calloc (node, sizeof(float));
	float *array_b_02= (float*) calloc (node, sizeof(float));
	float *array_c_01= (float*) calloc (node, sizeof(float));
	float *array_c_02= (float*) calloc (node, sizeof(float));

	cout<<"No of nodes = "<<node<<endl;
	
	//Initialization
	for (size_t i = 0; i < node; ++i) {
			array_a_01[i]= 2.30*i; // dummy value
			array_b_01[i]= 1.45*i; // dummy value
			
			array_a_02 [i] = array_a_01 [i];
			array_b_02 [i] = array_b_01 [i];
	}
	
	//###########################################################################
	/*
	int blockSize;      // The launch configurator returned block size 
    int minGridSize;    // The minimum grid size needed to achieve the maximum occupancy for a full device launch 
    int gridSize;       // The actual grid size needed, based on input size 
	
	cudaOccupancyMaxPotentialBlockSize(&minGridSize, &blockSize, cal_dilatation, 0, node); 
	gridSize = (node + blockSize - 1) / blockSize; 
	
	printf("\t Blocksize= %i\n", blockSize);
	printf("\t minGridSize= %i \n",minGridSize);
	printf("\t gridSize= %i \n",gridSize);*/
	
	
	// Create memory buffers on the device for each vector 
	
	float* buffer_array_a_01, * buffer_array_b_01;
	float* buffer_array_a_02, * buffer_array_b_02;
	float * buffer_array_c_01, * buffer_array_c_02;
	
	cudaMalloc(&buffer_array_a_01, node*sizeof(float));
	cudaMalloc(&buffer_array_a_02, node*sizeof(float));
	cudaMalloc(&buffer_array_b_01, node*sizeof(float));
	cudaMalloc(&buffer_array_b_02, node*sizeof(float));
	cudaMalloc(&buffer_array_c_01, node*sizeof(float));
	cudaMalloc(&buffer_array_c_02, node*sizeof(float));
	
	cudaMemcpy(buffer_array_a_01, array_a_01, node*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_a_02, array_a_02, node*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_b_01, array_b_01, node*sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_b_02, array_b_02, node*sizeof(float), cudaMemcpyHostToDevice);
	
	dim3 gridDim(node/256,1,1);         // 512 x 1 x 1
	dim3 blockDim(256, 1, 1); // 1024 x 1024 x 1
	
	
	printf("Using manual gridDim %i, ", gridDim.x);
	printf("blockDim %i, ", blockDim.x);
	printf("= %i;", (gridDim.x*blockDim.x));
	printf("\t Gap = %zi \n", (gridDim.x*blockDim.x)-node);
	
	
	/*printf("Using optimized blockSize %i, ", blockSize);
	printf("gridSize %i, ", gridSize);
	printf("= %i;", (gridSize*blockSize));
	printf("\t Gap = %zi \n", (gridSize*blockSize)-node);*/
	
	//Comment out one of the 2 kernels below---------------------------	
	
/*
	system_clock::time_point start_01 = system_clock::now();
	add_01<<< gridDim , blockDim>>>(buffer_array_a_01, buffer_array_b_01, buffer_array_c_01);
	cudaMemcpy(array_c_01, buffer_array_c_01, node *sizeof(float), cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();
	system_clock::time_point stop_01 = system_clock::now();
	
	std::chrono::duration<float, std::milli> duration_01 = stop_01 - start_01;
	cout << "Assignment operator '+=' time  = "<<duration_01.count()<<" millisecond"<<endl;
	*/
	//------------------------------------------------------------
	

	system_clock::time_point start_02 = system_clock::now();
	add_02<<< gridDim , blockDim>>>(buffer_array_a_02, buffer_array_b_02, buffer_array_c_02);
	cudaMemcpy(array_c_02, buffer_array_c_02, node *sizeof(float), cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();
	system_clock::time_point stop_02 = system_clock::now();
	
	std::chrono::duration<float, std::milli> duration_02 = stop_02 - start_02;
	cout << "Assignment operator '=' time  = "<<duration_02.count()<<" millisecond"<<endl;
	
	
	
   //##########################################################
	
	//Checking
	
	
	printf("\t array_c_01 - array_c_02 : \n");
	for (size_t i = 0; i < 5; ++i) {
		printf("\t\t %f", array_c_01[i]);	
		printf(" - %f \n",  array_c_02[i]);	
	}
	
	
	cudaFree(buffer_array_a_01); cudaFree(buffer_array_a_02);
	cudaFree(buffer_array_b_01); cudaFree(buffer_array_b_02); 
	cudaFree(buffer_array_c_01); 
	cudaFree(buffer_array_c_02); 
	
	free(array_a_01);	free(array_a_02);
	free (array_b_01);	free(array_b_02);	
	free (array_c_01);  free (array_c_02);
	
	printf("End of program!\n\n");
	
	
}