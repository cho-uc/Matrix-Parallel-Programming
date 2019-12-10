/*
Comparing performance between push back vector with C-style array
for discretization of 3D block
For : 24000000 nodes
	Discretization with vector push-back= 234 ms
	Discretization with C-Style array= 179

*/

#include<iostream>
#include<cstdio>
#include <vector>
#include <cstdlib>
#include <chrono>	//for time measurement
#include <fstream>

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv){
	cout<<"Start of program"<<endl;
	
	const float length = 1.0; //X
	const float width = 1.0e-1; //Y
	const float heigth = 1.0e-1; //Z

	
	const size_t ndivx = 600;
	const size_t ndivy = 200;
	const size_t ndivz = 200;
	
	const size_t node = ndivx*ndivy*ndivz;
	const float delta_x=length/ndivx;
	const float delta_y=width/ndivy;
	const float delta_z=heigth/ndivz;
	
	float *x = new float[node];
	float *y = new float[node];
	float *z = new float[node];
	float *delta_V = new float[node];
		
	vector<float> x_vector;
	vector<float> y_vector;
	vector<float> z_vector;
	vector<float> delta_V_vector;	
	
	x_vector.reserve(node); //allocate memory
	y_vector.reserve(node);
	z_vector.reserve(node);
	delta_V_vector.reserve(node);
	
	cout<<"No of nodes = "<<ndivx<<"x"<<ndivy<<"x"<<ndivz<<" = "<<node<<endl;
	
	//Vector type array
	system_clock::time_point start_01 = system_clock::now();
	
	for (size_t i = 0; i < ndivx; ++i) { 
		for (size_t j = 0; j < ndivy; ++j) {
			for (size_t k = 0; k < ndivz; ++k) {
				x_vector.push_back(delta_x*(0.5+i));
				y_vector.push_back(delta_y*(0.5+j));
				z_vector.push_back(delta_z*(0.5+k));
				delta_V_vector.push_back(delta_x*delta_y*delta_z);
				
			}
		}		
	}
	
	system_clock::time_point stop_01 = system_clock::now();	
	
	std::chrono::duration<double, std::milli> duration_01 = stop_01 - start_01;
	cout << "Discretization with vector push-back= "<<duration_01.count()<<" milliseconds"<<endl;
	
	//###########################################################################
	
	//C-Style array
	system_clock::time_point start_02 = system_clock::now();
	
	for (size_t i = 0; i < ndivx; ++i) {
		for (size_t j = 0; j < ndivy; ++j) {
			for (size_t k = 0; k < ndivz; ++k) {
				x[k+i*ndivy*ndivz+j*ndivz]=(delta_x*(0.5+i));
				y[k+i*ndivy*ndivz+j*ndivz]=(delta_y*(0.5+j));
				z[k+i*ndivy*ndivz+j*ndivz]=(delta_z*(0.5+k));
				delta_V[k+i*ndivy*ndivz+j*ndivz]=delta_x*delta_y*delta_z;
			}
		}		
	}	
		
	system_clock::time_point stop_02 = system_clock::now();
	std::chrono::duration<double, std::milli> duration_02 = stop_02 - start_02;
	cout << "Discretization with C-Style array= "<<duration_02.count()<<" millisecond"<<endl;
	
	
   //##########################################################
	
	//Checking
	float x_gap=0.0;
	float y_gap=0.0;
	float z_gap=0.0;
	float delta_V_gap=0.0;
	
	for (size_t i = 0; i < node; ++i) {
		x_gap += abs(x_vector[i]-x[i]);
		y_gap += abs(y_vector[i]-y[i]);
		z_gap += abs(z_vector[i]-z[i]);
		delta_V_gap += abs(delta_V_vector[i]-delta_V[i]);;
	}
	cout<<"Gap X= "<<x_gap<<", gap Y= "<<y_gap<<endl;
	cout<<"Gap Z= "<<z_gap<<", gap delta_V= "<<delta_V_gap<<endl;

	for (size_t i = 0; i < 9; ++i) {
		cout<<"\t"<<x_vector[i]<<" - "<<x[i]<<endl;
	}
	
	delete [] x;	delete [] y;	delete [] z;
	delete [] delta_V; 
	
	printf("End of program!");
	
	
}