/*
Test max arg size (256 Byte) for Cuda kernel.
Passing struct to kernel arguments to overcome limitation of number of args in kernel
But regular kernel turns out working properly with 70 args

https://devtalk.nvidia.com/default/topic/458705/is-there-any-limit-on-of-arguments-in-cuda-kernel-/

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


struct struct_ab {
	double* array_01;	double* array_02;	double* array_03;	
	double* array_04;	double* array_05;	double* array_06;
	double* array_07;	double* array_08;	double* array_09;		
	double* array_10;	double* array_11;	double* array_12;
	double* array_13;	double* array_14;	double* array_15;
	double* array_16;	double* array_17;	double* array_18;
	double* array_19;	double* array_20;	double* array_21;
	double* array_22;	double* array_23;	double* array_24;
	double* array_25;	double* array_26;	double* array_27;
	double* array_28;	double* array_29;	double* array_30;
	double* array_31;	double* array_32;	double* array_33;
	double* array_34;	double* array_35;	double* array_36;
	double* array_37;	double* array_38;	double* array_39;
	double* array_40;	double* array_41;	double* array_42;
	double* array_43;	double* array_44;	double* array_45;
	double* array_46;	double* array_47;	double* array_48;
	double* array_49;	double* array_50;	
	double* array_51;	double* array_52;	double* array_53;	
	double* array_54;	double* array_55;	double* array_56;
	double* array_57;	double* array_58;	double* array_59;		
	double* array_60;
	double* array_61;	double* array_62;	double* array_63;	
	double* array_64;	double* array_65;	double* array_66;
	double* array_67;	double* array_68;	double* array_69;		
	double* array_70;	
	};


__global__ void vector_add_struct(struct_ab mystruct_ab, double* c){

	size_t i= threadIdx.x+ blockDim.x*threadIdx.y+blockDim.x*blockDim.y*blockIdx.x;
	c[i]=mystruct_ab.array_01[i]+mystruct_ab.array_02[i]\
		+ mystruct_ab.array_03[i]+mystruct_ab.array_04[i]\
		+ mystruct_ab.array_05[i]+mystruct_ab.array_06[i]\
		+ mystruct_ab.array_07[i]+mystruct_ab.array_08[i]\
		+ mystruct_ab.array_09[i]+mystruct_ab.array_10[i]\
		+ mystruct_ab.array_11[i]+mystruct_ab.array_12[i]\
		+ mystruct_ab.array_13[i]+mystruct_ab.array_14[i]\
		+ mystruct_ab.array_15[i]+mystruct_ab.array_16[i]\
		+ mystruct_ab.array_17[i]+mystruct_ab.array_18[i]\
		+ mystruct_ab.array_19[i]+mystruct_ab.array_20[i]\
		+ mystruct_ab.array_21[i]+mystruct_ab.array_22[i]\
		+ mystruct_ab.array_23[i]+mystruct_ab.array_24[i]\
		+ mystruct_ab.array_25[i]+mystruct_ab.array_26[i]\
		+ mystruct_ab.array_27[i]+mystruct_ab.array_28[i]\
		+ mystruct_ab.array_29[i]+mystruct_ab.array_30[i]\
		+ mystruct_ab.array_31[i]+mystruct_ab.array_32[i]\
		+ mystruct_ab.array_33[i]+mystruct_ab.array_34[i]\
		+ mystruct_ab.array_35[i]+mystruct_ab.array_36[i]\
		+ mystruct_ab.array_37[i]+mystruct_ab.array_38[i]\
		+ mystruct_ab.array_39[i]+mystruct_ab.array_40[i]\
		+ mystruct_ab.array_41[i]+mystruct_ab.array_42[i]\
		+ mystruct_ab.array_43[i]+mystruct_ab.array_44[i]\
		+ mystruct_ab.array_45[i]+mystruct_ab.array_46[i]\
		+ mystruct_ab.array_47[i]+mystruct_ab.array_48[i]\
		+ mystruct_ab.array_49[i]+mystruct_ab.array_50[i]\
		+ mystruct_ab.array_51[i]+mystruct_ab.array_52[i]\
		+ mystruct_ab.array_53[i]+mystruct_ab.array_54[i]\
		+ mystruct_ab.array_55[i]+mystruct_ab.array_56[i]\
		+ mystruct_ab.array_57[i]+mystruct_ab.array_58[i]\
		+ mystruct_ab.array_59[i]+mystruct_ab.array_60[i]\
		+ mystruct_ab.array_61[i]+mystruct_ab.array_62[i]\
		+ mystruct_ab.array_63[i]+mystruct_ab.array_64[i]\
		+ mystruct_ab.array_65[i]+mystruct_ab.array_66[i]\
		+ mystruct_ab.array_67[i]+mystruct_ab.array_68[i]\
		+ mystruct_ab.array_69[i]+mystruct_ab.array_70[i]
	;
}

//max = 43 args 
__global__ void vector_add70(double* array_01, double* array_02, double* array_03, 
		double* array_04, double* array_05, double* array_06, 
		double* array_07, double* array_08, double* array_09,
		double* array_10,
		double* array_11, double* array_12, double* array_13, 
		double* array_14, double* array_15, double* array_16, 
		double* array_17, double* array_18, double* array_19,
		double* array_20,
		double* array_21, double* array_22, double* array_23, 
		double* array_24, double* array_25, double* array_26, 
		double* array_27, double* array_28, double* array_29,
		double* array_30,
		double* array_31, double* array_32, double* array_33, 
		double* array_34, double* array_35, double* array_36,	
		double* array_37, double* array_38, double* array_39,
		double* array_40,
		double* array_41, double* array_42, double* array_43, 
		double* array_44, double* array_45, double* array_46, 
		double* array_47, double* array_48, double* array_49,
		double* array_50,
		double* array_51, double* array_52, double* array_53, 
		double* array_54, double* array_55, double* array_56, 
		double* array_57, double* array_58, double* array_59,
		double* array_60,
		double* array_61, double* array_62, double* array_63, 
		double* array_64, double* array_65, double* array_66, 
		double* array_67, double* array_68, double* array_69,
		double* array_70,
		
		double* c){

	size_t i= threadIdx.x+ blockDim.x*threadIdx.y+blockDim.x*blockDim.y*blockIdx.x;
	c[i]=c[i]=array_01[i]+array_02[i] + array_03[i]+array_04[i] 
		+ array_05[i]+array_06[i] + array_07[i]+array_08[i]\
		+ array_09[i]+array_10[i]\
		+ array_11[i]+array_12[i] + array_13[i]+array_14[i]\
		+ array_15[i]+array_16[i] + array_17[i]+array_18[i]\
		+ array_19[i]+array_20[i]\
		+ array_21[i]+array_22[i] + array_23[i]+array_24[i]\
		+ array_25[i]+array_26[i] + array_27[i]+array_28[i]\
		+ array_29[i]+array_30[i]\
		+ array_31[i]+array_32[i] + array_33[i]+array_34[i]\
		+ array_35[i]+array_36[i] + array_37[i]+array_38[i]\
		+ array_39[i]+array_40[i]\
		+ array_41[i]+array_42[i] + array_43[i]+array_44[i]\
		+ array_45[i]+array_46[i] + array_47[i]+array_48[i]\
		+ array_49[i]+array_50[i]
		+ array_51[i]+array_52[i] + array_53[i]+array_54[i] 
		+ array_55[i]+array_56[i] + array_57[i]+array_58[i]\
		+ array_59[i]+array_60[i]\
		+ array_61[i]+array_62[i] + array_63[i]+array_64[i] 
		+ array_65[i]+array_66[i] + array_67[i]+array_68[i]\
		+ array_69[i]+array_70[i]\
		
	;
}

int main(int argc, char **argv){
	cout<<"Start of program"<<endl;
	const size_t node = 100;
		
	double *array_01_serial = new double[node]; double *array_02_serial = new double[node];
	double *array_03_serial = new double[node]; double *array_04_serial = new double[node];
	double *array_05_serial = new double[node]; double *array_06_serial = new double[node];
	double *array_07_serial = new double[node]; double *array_08_serial = new double[node];
	double *array_09_serial = new double[node]; double *array_10_serial = new double[node];
	double *array_11_serial = new double[node]; double *array_12_serial = new double[node];
	double *array_13_serial = new double[node]; double *array_14_serial = new double[node];
	double *array_15_serial = new double[node]; double *array_16_serial = new double[node];
	double *array_17_serial = new double[node]; double *array_18_serial = new double[node];
	double *array_19_serial = new double[node]; double *array_20_serial = new double[node];
	double *array_21_serial = new double[node]; double *array_22_serial = new double[node];
	double *array_23_serial = new double[node]; double *array_24_serial = new double[node];
	double *array_25_serial = new double[node]; double *array_26_serial = new double[node];
	double *array_27_serial = new double[node]; double *array_28_serial = new double[node];
	double *array_29_serial = new double[node]; double *array_30_serial = new double[node];
	double *array_31_serial = new double[node]; double *array_32_serial = new double[node];
	double *array_33_serial = new double[node]; double *array_34_serial = new double[node];
	double *array_35_serial = new double[node]; double *array_36_serial = new double[node];
	double *array_37_serial = new double[node]; double *array_38_serial = new double[node];
	double *array_39_serial = new double[node]; double *array_40_serial = new double[node];
	double *array_41_serial = new double[node]; double *array_42_serial = new double[node];
	double *array_43_serial = new double[node]; double *array_44_serial = new double[node];
	double *array_45_serial = new double[node]; double *array_46_serial = new double[node];
	double *array_47_serial = new double[node]; double *array_48_serial = new double[node];
	double *array_49_serial = new double[node]; double *array_50_serial = new double[node];
	double *array_51_serial = new double[node]; double *array_52_serial = new double[node];
	double *array_53_serial = new double[node]; double *array_54_serial = new double[node];
	double *array_55_serial = new double[node]; double *array_56_serial = new double[node];
	double *array_57_serial = new double[node]; double *array_58_serial = new double[node];
	double *array_59_serial = new double[node]; double *array_60_serial = new double[node];
	double *array_61_serial = new double[node]; double *array_62_serial = new double[node];
	double *array_63_serial = new double[node]; double *array_64_serial = new double[node];
	double *array_65_serial = new double[node]; double *array_66_serial = new double[node];
	double *array_67_serial = new double[node]; double *array_68_serial = new double[node];
	double *array_69_serial = new double[node]; double *array_70_serial = new double[node];
	
	
	double *c_serial = new double[node];
	
	double *array_01 = new double[node];	double *array_02 = new double[node];
	double *array_03 = new double[node]; 	double *array_04 = new double[node];
	double *array_05 = new double[node];	double *array_06 = new double[node];
	double *array_07 = new double[node];	double *array_08 = new double[node];	
	double *array_09 = new double[node];	double *array_10 = new double[node];	
	double *array_11 = new double[node];	double *array_12 = new double[node];	
	double *array_13 = new double[node];	double *array_14 = new double[node];	
	double *array_15 = new double[node];	double *array_16 = new double[node];	
	double *array_17 = new double[node];	double *array_18 = new double[node];	
	double *array_19 = new double[node];	double *array_20 = new double[node];
	double *array_21 = new double[node];	double *array_22 = new double[node];
	double *array_23 = new double[node];	double *array_24 = new double[node];
	double *array_25 = new double[node];	double *array_26 = new double[node];
	double *array_27 = new double[node];	double *array_28 = new double[node];
	double *array_29 = new double[node];	double *array_30 = new double[node];
	double *array_31 = new double[node];	double *array_32 = new double[node];
	double *array_33 = new double[node];	double *array_34 = new double[node];
	double *array_35 = new double[node];	double *array_36 = new double[node];
	double *array_37 = new double[node];	double *array_38 = new double[node];	
	double *array_39 = new double[node];	double *array_40 = new double[node];	
	double *array_41 = new double[node];	double *array_42 = new double[node];
	double *array_43 = new double[node]; 	double *array_44 = new double[node];
	double *array_45 = new double[node];	double *array_46 = new double[node];
	double *array_47 = new double[node];	double *array_48 = new double[node];	
	double *array_49 = new double[node];	double *array_50 = new double[node];	
	double *array_51 = new double[node];	double *array_52 = new double[node];
	double *array_53 = new double[node]; 	double *array_54 = new double[node];
	double *array_55 = new double[node];	double *array_56 = new double[node];
	double *array_57 = new double[node];	double *array_58 = new double[node];	
	double *array_59 = new double[node];	double *array_60 = new double[node];	
	double *array_61 = new double[node];	double *array_62 = new double[node];
	double *array_63 = new double[node]; 	double *array_64 = new double[node];
	double *array_65 = new double[node];	double *array_66 = new double[node];
	double *array_67 = new double[node];	double *array_68 = new double[node];	
	double *array_69 = new double[node];	double *array_70 = new double[node];	
	
	
	
	double *c = new double[node];
	
	cout<<"No of nodes = "<<node<<endl;
	
	//Initialization
	for (size_t i = 0; i < node; ++i) {
			std::srand(std::time(nullptr)); // use current time as seed for random generator
			array_01[i]=((double) rand()/(RAND_MAX))*i;	array_02[i]=((double) rand()/(RAND_MAX))*i;
			array_03[i]=((double) rand()/(RAND_MAX))*i;	array_04[i]=((double) rand()/(RAND_MAX))*i;
			array_05[i]=((double) rand()/(RAND_MAX))*i;	array_06[i]=((double) rand()/(RAND_MAX))*i;
			array_07[i]=((double) rand()/(RAND_MAX))*i;	array_08[i]=((double) rand()/(RAND_MAX))*i;
			array_09[i]=((double) rand()/(RAND_MAX))*i;	array_10[i]=((double) rand()/(RAND_MAX))*i;
			
			array_11[i]=((double) rand()/(RAND_MAX))*i;	array_12[i]=((double) rand()/(RAND_MAX))*i;
			array_13[i]=((double) rand()/(RAND_MAX))*i;	array_14[i]=((double) rand()/(RAND_MAX))*i;
			array_15[i]=((double) rand()/(RAND_MAX))*i;	array_16[i]=((double) rand()/(RAND_MAX))*i;
			array_17[i]=((double) rand()/(RAND_MAX))*i;	array_18[i]=((double) rand()/(RAND_MAX))*i;
			array_19[i]=((double) rand()/(RAND_MAX))*i;	array_20[i]=((double) rand()/(RAND_MAX))*i;
			
			array_21[i]=((double) rand()/(RAND_MAX))*i;	array_22[i]=((double) rand()/(RAND_MAX))*i;
			array_23[i]=((double) rand()/(RAND_MAX))*i;	array_24[i]=((double) rand()/(RAND_MAX))*i;
			array_25[i]=((double) rand()/(RAND_MAX))*i;	array_26[i]=((double) rand()/(RAND_MAX))*i;
			array_27[i]=((double) rand()/(RAND_MAX))*i;	array_28[i]=((double) rand()/(RAND_MAX))*i;
			array_29[i]=((double) rand()/(RAND_MAX))*i;	array_30[i]=((double) rand()/(RAND_MAX))*i;
		
			array_31[i]=((double) rand()/(RAND_MAX))*i;	array_32[i]=((double) rand()/(RAND_MAX))*i;
			array_33[i]=((double) rand()/(RAND_MAX))*i;	array_34[i]=((double) rand()/(RAND_MAX))*i;
			array_35[i]=((double) rand()/(RAND_MAX))*i;	array_36[i]=((double) rand()/(RAND_MAX))*i;
			array_37[i]=((double) rand()/(RAND_MAX))*i;	array_38[i]=((double) rand()/(RAND_MAX))*i;
			array_39[i]=((double) rand()/(RAND_MAX))*i;	array_40[i]=((double) rand()/(RAND_MAX))*i;
			
			array_41[i]=((double) rand()/(RAND_MAX))*i;	array_42[i]=((double) rand()/(RAND_MAX))*i;
			array_43[i]=((double) rand()/(RAND_MAX))*i;	array_44[i]=((double) rand()/(RAND_MAX))*i;
			array_45[i]=((double) rand()/(RAND_MAX))*i;	array_46[i]=((double) rand()/(RAND_MAX))*i;
			array_47[i]=((double) rand()/(RAND_MAX))*i;	array_48[i]=((double) rand()/(RAND_MAX))*i;
			array_49[i]=((double) rand()/(RAND_MAX))*i;	array_50[i]=((double) rand()/(RAND_MAX))*i;
			array_51[i]=((double) rand()/(RAND_MAX))*i;	array_52[i]=((double) rand()/(RAND_MAX))*i;
			array_53[i]=((double) rand()/(RAND_MAX))*i;	array_54[i]=((double) rand()/(RAND_MAX))*i;
			array_55[i]=((double) rand()/(RAND_MAX))*i;	array_56[i]=((double) rand()/(RAND_MAX))*i;
			array_57[i]=((double) rand()/(RAND_MAX))*i;	array_58[i]=((double) rand()/(RAND_MAX))*i;
			array_59[i]=((double) rand()/(RAND_MAX))*i;	array_60[i]=((double) rand()/(RAND_MAX))*i;
			array_61[i]=((double) rand()/(RAND_MAX))*i;	array_62[i]=((double) rand()/(RAND_MAX))*i;
			array_63[i]=((double) rand()/(RAND_MAX))*i;	array_64[i]=((double) rand()/(RAND_MAX))*i;
			array_65[i]=((double) rand()/(RAND_MAX))*i;	array_66[i]=((double) rand()/(RAND_MAX))*i;
			array_67[i]=((double) rand()/(RAND_MAX))*i;	array_68[i]=((double) rand()/(RAND_MAX))*i;
			array_69[i]=((double) rand()/(RAND_MAX))*i;	array_70[i]=((double) rand()/(RAND_MAX))*i;
			
		
			//-------------------------------------------
			array_01_serial[i]= array_01[i];	array_02_serial[i]= array_02[i];			
			array_03_serial[i]= array_03[i];	array_04_serial[i]= array_04[i];
			array_05_serial[i]= array_05[i];	array_06_serial[i]= array_06[i];
			array_07_serial[i]= array_07[i];	array_08_serial[i]= array_08[i];
			array_09_serial[i]= array_09[i];	array_10_serial[i]= array_10[i];
			array_11_serial[i]= array_11[i];	array_12_serial[i]= array_12[i];
			array_13_serial[i]= array_13[i];	array_14_serial[i]= array_14[i];
			array_15_serial[i]= array_15[i];	array_16_serial[i]= array_16[i];
			array_17_serial[i]= array_17[i];	array_18_serial[i]= array_18[i];
			array_19_serial[i]= array_19[i];	array_20_serial[i]= array_20[i];
			array_21_serial[i]= array_21[i];	array_22_serial[i]= array_22[i];
			array_23_serial[i]= array_23[i];	array_24_serial[i]= array_24[i];
			array_25_serial[i]= array_25[i];	array_26_serial[i]= array_26[i];
			array_27_serial[i]= array_27[i];	array_28_serial[i]= array_28[i];
			array_29_serial[i]= array_29[i];	array_30_serial[i]= array_30[i];
			array_31_serial[i]= array_31[i];	array_32_serial[i]= array_32[i];
			array_33_serial[i]= array_33[i];	array_34_serial[i]= array_34[i];
			array_35_serial[i]= array_35[i];	array_36_serial[i]= array_36[i];			
			array_37_serial[i]= array_37[i];	array_38_serial[i]= array_38[i];
			array_39_serial[i]= array_39[i];	array_40_serial[i]= array_40[i];
			
			array_41_serial[i]= array_41[i];	array_42_serial[i]= array_42[i];			
			array_43_serial[i]= array_43[i];	array_44_serial[i]= array_44[i];
			array_45_serial[i]= array_45[i];	array_46_serial[i]= array_46[i];
			array_47_serial[i]= array_47[i];	array_48_serial[i]= array_48[i];
			array_49_serial[i]= array_49[i];	array_50_serial[i]= array_50[i];
			array_51_serial[i]= array_51[i];	array_52_serial[i]= array_52[i];			
			array_53_serial[i]= array_53[i];	array_54_serial[i]= array_54[i];
			array_55_serial[i]= array_55[i];	array_56_serial[i]= array_56[i];
			array_57_serial[i]= array_57[i];	array_58_serial[i]= array_58[i];
			array_59_serial[i]= array_59[i];	array_60_serial[i]= array_60[i];
			array_61_serial[i]= array_61[i];	array_62_serial[i]= array_62[i];			
			array_63_serial[i]= array_63[i];	array_64_serial[i]= array_64[i];
			array_65_serial[i]= array_65[i];	array_66_serial[i]= array_66[i];
			array_67_serial[i]= array_67[i];	array_68_serial[i]= array_68[i];
			array_69_serial[i]= array_69[i];	array_70_serial[i]= array_70[i];
			
		}

//	#########################################################
//Serial version
	for (size_t i = 0; i < node; ++i) {
		c_serial[i]=array_01_serial[i]+array_02_serial[i] + array_03_serial[i]+array_04_serial[i]\
			+ array_05_serial[i]+array_06_serial[i]	+ array_07_serial[i]+array_08_serial[i]\
			+ array_09_serial[i]+array_10_serial[i]\
			+ array_11_serial[i]+array_12_serial[i] + array_13_serial[i]+array_14_serial[i]\
			+ array_15_serial[i]+array_16_serial[i]	+ array_17_serial[i]+array_18_serial[i]\
			+ array_19_serial[i]+array_20_serial[i]\
			+ array_21_serial[i]+array_22_serial[i]	+ array_23_serial[i]+array_24_serial[i]\
			+ array_25_serial[i]+array_26_serial[i]	+ array_27_serial[i]+array_28_serial[i]\
			+ array_29_serial[i]+array_30_serial[i]\
			+ array_31_serial[i]+array_32_serial[i]	+ array_33_serial[i]+array_34_serial[i]\
			+ array_35_serial[i]+array_36_serial[i]	+ array_37_serial[i]+array_38_serial[i]\
			+ array_39_serial[i]+array_40_serial[i]\
			+ array_41_serial[i]+array_42_serial[i]	+ array_43_serial[i]+array_44_serial[i]\
			+ array_45_serial[i]+array_46_serial[i]	+ array_47_serial[i]+array_48_serial[i]\
			+ array_49_serial[i]+array_50_serial[i]\
			+ array_51_serial[i]+array_52_serial[i] + array_53_serial[i]+array_54_serial[i]\
			+ array_55_serial[i]+array_56_serial[i]	+ array_57_serial[i]+array_58_serial[i]\
			+ array_59_serial[i]+array_60_serial[i]\
			+ array_61_serial[i]+array_62_serial[i] + array_63_serial[i]+array_64_serial[i]\
			+ array_65_serial[i]+array_66_serial[i]	+ array_67_serial[i]+array_68_serial[i]\
			+ array_69_serial[i]+array_70_serial[i]\
			
		;
	}
	
	//###########################################################################
	//PARALLEL VERSION
	cout<<"Start parallel version"<<endl;
	
	// Create memory buffers on the device for each vector 
	double* buffer_array_01, *buffer_array_02, *buffer_array_03;
	double* buffer_array_04, *buffer_array_05, *buffer_array_06; 
	double* buffer_array_07, *buffer_array_08, *buffer_array_09;
	double* buffer_array_10;
	double* buffer_array_11, *buffer_array_12, *buffer_array_13;
	double* buffer_array_14, *buffer_array_15, *buffer_array_16; 
	double* buffer_array_17, *buffer_array_18, *buffer_array_19;
	double* buffer_array_20;
	double* buffer_array_21, *buffer_array_22, *buffer_array_23;
	double* buffer_array_24, *buffer_array_25, *buffer_array_26; 
	double* buffer_array_27, *buffer_array_28, *buffer_array_29;
	double* buffer_array_30;
	double* buffer_array_31, *buffer_array_32, *buffer_array_33;
	double* buffer_array_34, *buffer_array_35, *buffer_array_36; 
	double* buffer_array_37, *buffer_array_38, *buffer_array_39;
	double* buffer_array_40;
	double* buffer_array_41, *buffer_array_42, *buffer_array_43;
	double* buffer_array_44, *buffer_array_45, *buffer_array_46; 
	double* buffer_array_47, *buffer_array_48, *buffer_array_49;
	double* buffer_array_50;
	double* buffer_array_51, *buffer_array_52, *buffer_array_53;
	double* buffer_array_54, *buffer_array_55, *buffer_array_56; 
	double* buffer_array_57, *buffer_array_58, *buffer_array_59;
	double* buffer_array_60;
	double* buffer_array_61, *buffer_array_62, *buffer_array_63;
	double* buffer_array_64, *buffer_array_65, *buffer_array_66; 
	double* buffer_array_67, *buffer_array_68, *buffer_array_69;
	double* buffer_array_70;
	
	double *buffer_c;
	
	struct_ab mystruct_ab_d; //struct in device
	
	cudaMalloc(&buffer_array_01, node*sizeof(double));
	cudaMalloc(&buffer_array_02, node*sizeof(double));
	cudaMalloc(&buffer_array_03, node*sizeof(double));
	cudaMalloc(&buffer_array_04, node*sizeof(double));
	cudaMalloc(&buffer_array_05, node*sizeof(double));
	cudaMalloc(&buffer_array_06, node*sizeof(double));
	cudaMalloc(&buffer_array_07, node*sizeof(double));	
	cudaMalloc(&buffer_array_08, node*sizeof(double));
	cudaMalloc(&buffer_array_09, node*sizeof(double));
	cudaMalloc(&buffer_array_10, node*sizeof(double));
	cudaMalloc(&buffer_array_11, node*sizeof(double));
	cudaMalloc(&buffer_array_12, node*sizeof(double));
	cudaMalloc(&buffer_array_13, node*sizeof(double));
	cudaMalloc(&buffer_array_14, node*sizeof(double));
	cudaMalloc(&buffer_array_15, node*sizeof(double));
	cudaMalloc(&buffer_array_16, node*sizeof(double));
	cudaMalloc(&buffer_array_17, node*sizeof(double));	
	cudaMalloc(&buffer_array_18, node*sizeof(double));
	cudaMalloc(&buffer_array_19, node*sizeof(double));
	cudaMalloc(&buffer_array_20, node*sizeof(double));
	cudaMalloc(&buffer_array_21, node*sizeof(double));
	cudaMalloc(&buffer_array_22, node*sizeof(double));
	cudaMalloc(&buffer_array_23, node*sizeof(double));
	cudaMalloc(&buffer_array_24, node*sizeof(double));
	cudaMalloc(&buffer_array_25, node*sizeof(double));
	cudaMalloc(&buffer_array_26, node*sizeof(double));
	cudaMalloc(&buffer_array_27, node*sizeof(double));	
	cudaMalloc(&buffer_array_28, node*sizeof(double));
	cudaMalloc(&buffer_array_29, node*sizeof(double));
	cudaMalloc(&buffer_array_30, node*sizeof(double));
	cudaMalloc(&buffer_array_31, node*sizeof(double));
	cudaMalloc(&buffer_array_32, node*sizeof(double));
	cudaMalloc(&buffer_array_33, node*sizeof(double));
	cudaMalloc(&buffer_array_34, node*sizeof(double));
	cudaMalloc(&buffer_array_35, node*sizeof(double));
	cudaMalloc(&buffer_array_36, node*sizeof(double));
	cudaMalloc(&buffer_array_37, node*sizeof(double));	
	cudaMalloc(&buffer_array_38, node*sizeof(double));
	cudaMalloc(&buffer_array_39, node*sizeof(double));
	cudaMalloc(&buffer_array_40, node*sizeof(double));
	cudaMalloc(&buffer_array_41, node*sizeof(double));
	cudaMalloc(&buffer_array_42, node*sizeof(double));
	cudaMalloc(&buffer_array_43, node*sizeof(double));
	cudaMalloc(&buffer_array_44, node*sizeof(double));
	cudaMalloc(&buffer_array_45, node*sizeof(double));
	cudaMalloc(&buffer_array_46, node*sizeof(double));
	cudaMalloc(&buffer_array_47, node*sizeof(double));	
	cudaMalloc(&buffer_array_48, node*sizeof(double));
	cudaMalloc(&buffer_array_49, node*sizeof(double));
	cudaMalloc(&buffer_array_50, node*sizeof(double));
	cudaMalloc(&buffer_array_51, node*sizeof(double));
	cudaMalloc(&buffer_array_52, node*sizeof(double));
	cudaMalloc(&buffer_array_53, node*sizeof(double));
	cudaMalloc(&buffer_array_54, node*sizeof(double));
	cudaMalloc(&buffer_array_55, node*sizeof(double));
	cudaMalloc(&buffer_array_56, node*sizeof(double));
	cudaMalloc(&buffer_array_57, node*sizeof(double));	
	cudaMalloc(&buffer_array_58, node*sizeof(double));
	cudaMalloc(&buffer_array_59, node*sizeof(double));
	cudaMalloc(&buffer_array_60, node*sizeof(double));
	cudaMalloc(&buffer_array_61, node*sizeof(double));
	cudaMalloc(&buffer_array_62, node*sizeof(double));
	cudaMalloc(&buffer_array_63, node*sizeof(double));
	cudaMalloc(&buffer_array_64, node*sizeof(double));
	cudaMalloc(&buffer_array_65, node*sizeof(double));
	cudaMalloc(&buffer_array_66, node*sizeof(double));
	cudaMalloc(&buffer_array_67, node*sizeof(double));	
	cudaMalloc(&buffer_array_68, node*sizeof(double));
	cudaMalloc(&buffer_array_69, node*sizeof(double));
	cudaMalloc(&buffer_array_70, node*sizeof(double));
	
	
	cudaMalloc(&buffer_c, node*sizeof(double));		
	
	cudaMemcpy(buffer_array_01, array_01, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_02, array_02, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_03, array_03, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_04, array_04, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_05, array_05, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_06, array_06, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_07, array_07, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_08, array_08, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_09, array_09, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_10, array_10, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_11, array_11, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_12, array_12, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_13, array_13, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_14, array_14, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_15, array_15, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_16, array_16, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_17, array_17, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_18, array_18, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_19, array_19, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_20, array_20, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_21, array_21, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_22, array_22, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_23, array_23, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_24, array_24, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_25, array_25, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_26, array_26, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_27, array_27, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_28, array_28, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_29, array_29, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_30, array_30, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_31, array_31, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_32, array_32, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_33, array_33, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_34, array_34, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_35, array_35, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_36, array_36, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_37, array_37, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_38, array_38, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_39, array_39, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_40, array_40, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_41, array_41, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_42, array_42, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_43, array_43, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_44, array_44, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_45, array_45, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_46, array_46, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_47, array_47, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_48, array_48, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_49, array_49, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_50, array_50, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_51, array_51, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_52, array_52, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_53, array_53, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_54, array_54, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_55, array_55, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_56, array_56, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_57, array_57, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_58, array_58, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_59, array_59, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_60, array_60, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_61, array_61, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_62, array_62, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_63, array_63, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_64, array_64, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_65, array_65, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_66, array_66, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_67, array_67, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_68, array_68, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_69, array_69, node*sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(buffer_array_70, array_70, node*sizeof(double), cudaMemcpyHostToDevice);
	

	mystruct_ab_d.array_01 = buffer_array_01; mystruct_ab_d.array_02 = buffer_array_02; 
	mystruct_ab_d.array_03 = buffer_array_03; mystruct_ab_d.array_04 = buffer_array_04; 
	mystruct_ab_d.array_05 = buffer_array_05; mystruct_ab_d.array_06 = buffer_array_06; 
	mystruct_ab_d.array_07 = buffer_array_07; mystruct_ab_d.array_08 = buffer_array_08; 
	mystruct_ab_d.array_09 = buffer_array_09; mystruct_ab_d.array_10 = buffer_array_10; 
	mystruct_ab_d.array_11 = buffer_array_11; mystruct_ab_d.array_12 = buffer_array_12; 
	mystruct_ab_d.array_13 = buffer_array_13; mystruct_ab_d.array_14 = buffer_array_14; 
	mystruct_ab_d.array_15 = buffer_array_15; mystruct_ab_d.array_16 = buffer_array_16; 
	mystruct_ab_d.array_17 = buffer_array_17; mystruct_ab_d.array_18 = buffer_array_18; 
	mystruct_ab_d.array_19 = buffer_array_19; mystruct_ab_d.array_20 = buffer_array_20; 
	mystruct_ab_d.array_21 = buffer_array_21; mystruct_ab_d.array_22 = buffer_array_22; 
	mystruct_ab_d.array_23 = buffer_array_23; mystruct_ab_d.array_24 = buffer_array_24; 
	mystruct_ab_d.array_25 = buffer_array_25; mystruct_ab_d.array_26 = buffer_array_26; 
	mystruct_ab_d.array_27 = buffer_array_27; mystruct_ab_d.array_28 = buffer_array_28; 
	mystruct_ab_d.array_29 = buffer_array_29; mystruct_ab_d.array_30 = buffer_array_30; 
	mystruct_ab_d.array_31 = buffer_array_31; mystruct_ab_d.array_32 = buffer_array_32; 
	mystruct_ab_d.array_33 = buffer_array_33; mystruct_ab_d.array_34 = buffer_array_34; 
	mystruct_ab_d.array_35 = buffer_array_35; mystruct_ab_d.array_36 = buffer_array_36; 
	mystruct_ab_d.array_37 = buffer_array_37; mystruct_ab_d.array_38 = buffer_array_38; 
	mystruct_ab_d.array_39 = buffer_array_39; mystruct_ab_d.array_40 = buffer_array_40; 
	mystruct_ab_d.array_41 = buffer_array_41; mystruct_ab_d.array_42 = buffer_array_42; 
	mystruct_ab_d.array_43 = buffer_array_43; mystruct_ab_d.array_44 = buffer_array_44; 
	mystruct_ab_d.array_45 = buffer_array_45; mystruct_ab_d.array_46 = buffer_array_46; 
	mystruct_ab_d.array_47 = buffer_array_47; mystruct_ab_d.array_48 = buffer_array_48; 
	mystruct_ab_d.array_49 = buffer_array_49; mystruct_ab_d.array_50 = buffer_array_50; 
	mystruct_ab_d.array_51 = buffer_array_51; mystruct_ab_d.array_52 = buffer_array_52; 
	mystruct_ab_d.array_53 = buffer_array_53; mystruct_ab_d.array_54 = buffer_array_54; 
	mystruct_ab_d.array_55 = buffer_array_55; mystruct_ab_d.array_56 = buffer_array_56; 
	mystruct_ab_d.array_57 = buffer_array_57; mystruct_ab_d.array_58 = buffer_array_58; 
	mystruct_ab_d.array_59 = buffer_array_59; mystruct_ab_d.array_60 = buffer_array_60; 
	mystruct_ab_d.array_61 = buffer_array_61; mystruct_ab_d.array_62 = buffer_array_62; 
	mystruct_ab_d.array_63 = buffer_array_63; mystruct_ab_d.array_64 = buffer_array_64; 
	mystruct_ab_d.array_65 = buffer_array_65; mystruct_ab_d.array_66 = buffer_array_66; 
	mystruct_ab_d.array_67 = buffer_array_67; mystruct_ab_d.array_68 = buffer_array_68; 
	mystruct_ab_d.array_69 = buffer_array_69; mystruct_ab_d.array_70 = buffer_array_70; 
	
	
	
	
	//Use manual block size
	dim3 gridDim(node,1,1);         // 512 x 512 x 64
	dim3 blockDim(1, 1, 1); // 1024 x 1024 x 64, max threads/block=128-512 (multiple of 32)
	
	
	cout<<"Not using struct"<<endl;		
	vector_add70<<<gridDim,blockDim>>>(buffer_array_01, buffer_array_02, buffer_array_03, 
		buffer_array_04, buffer_array_05, buffer_array_06, 
		buffer_array_07, buffer_array_08, buffer_array_09, 
		buffer_array_10, 
		buffer_array_11, buffer_array_12, buffer_array_13, 
		buffer_array_14, buffer_array_15, buffer_array_16, 
		buffer_array_17, buffer_array_18, buffer_array_19, 
		buffer_array_20, 
		buffer_array_21, buffer_array_22, buffer_array_23, 
		buffer_array_24, buffer_array_25, buffer_array_26, 
		buffer_array_27, buffer_array_28, buffer_array_29, 
		buffer_array_30, 
		buffer_array_31, buffer_array_32, buffer_array_33, 
		buffer_array_34, buffer_array_35, buffer_array_36, 		
		buffer_array_37, buffer_array_38, buffer_array_39, 
		buffer_array_40, 
		buffer_array_41, buffer_array_42, buffer_array_43, 
		buffer_array_44, buffer_array_45, buffer_array_46, 
		buffer_array_47, buffer_array_48, buffer_array_49, 
		buffer_array_50,	
		buffer_array_51, buffer_array_52, buffer_array_53, 
		buffer_array_54, buffer_array_55, buffer_array_56, 
		buffer_array_57, buffer_array_58, buffer_array_59, 
		buffer_array_60, 
		buffer_array_61, buffer_array_62, buffer_array_63, 
		buffer_array_64, buffer_array_65, buffer_array_66, 
		buffer_array_67, buffer_array_68, buffer_array_69, 
		buffer_array_70, 		
		
		buffer_c); 
	
	/*
	cout<<"Using struct"<<endl;
	vector_add_struct<<<gridDim,blockDim>>>(mystruct_ab_d, buffer_c); 
	*/
	
	cudaDeviceSynchronize();
	cudaMemcpy(c, buffer_c, node *sizeof(double), cudaMemcpyDeviceToHost);
	
   //##########################################################
	
	//Checking
	double sum_c_serial=0.0;
	double sum_c=0.0;
	
	for (size_t i = 0; i < 6; ++i) {
		cout<< "\t"<< c[i] <<" - "<< c_serial[i] << endl;
	}
	
	for (size_t i = 0; i < node; ++i) {
		sum_c += c[i];
		sum_c_serial += c_serial[i];
	}
	cout<<"Gap= "<<sum_c - sum_c_serial <<endl;
	
	cudaFree(buffer_array_01);	cudaFree(buffer_array_02);
	cudaFree(buffer_array_03);	cudaFree(buffer_array_04);
	cudaFree(buffer_array_05);	cudaFree(buffer_array_06);
	cudaFree(buffer_array_07);	cudaFree(buffer_array_08);
	cudaFree(buffer_array_09);	cudaFree(buffer_array_10);
	cudaFree(buffer_array_11);	cudaFree(buffer_array_12);
	cudaFree(buffer_array_13);	cudaFree(buffer_array_14);
	cudaFree(buffer_array_15);	cudaFree(buffer_array_16);
	cudaFree(buffer_array_17);	cudaFree(buffer_array_18);
	cudaFree(buffer_array_19);	cudaFree(buffer_array_20);
	cudaFree(buffer_array_21);	cudaFree(buffer_array_22);
	cudaFree(buffer_array_23);	cudaFree(buffer_array_24);
	cudaFree(buffer_array_25);	cudaFree(buffer_array_26);
	cudaFree(buffer_array_27);	cudaFree(buffer_array_28);
	cudaFree(buffer_array_29);	cudaFree(buffer_array_30);
	cudaFree(buffer_array_31);	cudaFree(buffer_array_32);
	cudaFree(buffer_array_33);	cudaFree(buffer_array_34);
	cudaFree(buffer_array_35);	cudaFree(buffer_array_36);
	cudaFree(buffer_array_37);	cudaFree(buffer_array_38);
	cudaFree(buffer_array_39);	cudaFree(buffer_array_40);
	cudaFree(buffer_array_41);	cudaFree(buffer_array_42);
	cudaFree(buffer_array_43);	cudaFree(buffer_array_44);
	cudaFree(buffer_array_45);	cudaFree(buffer_array_46);
	cudaFree(buffer_array_47);	cudaFree(buffer_array_48);
	cudaFree(buffer_array_49);	cudaFree(buffer_array_50);
	cudaFree(buffer_array_51);	cudaFree(buffer_array_52);
	cudaFree(buffer_array_53);	cudaFree(buffer_array_54);
	cudaFree(buffer_array_55);	cudaFree(buffer_array_56);
	cudaFree(buffer_array_57);	cudaFree(buffer_array_58);
	cudaFree(buffer_array_59);	cudaFree(buffer_array_60);
	cudaFree(buffer_array_61);	cudaFree(buffer_array_62);
	cudaFree(buffer_array_63);	cudaFree(buffer_array_64);
	cudaFree(buffer_array_65);	cudaFree(buffer_array_66);
	cudaFree(buffer_array_67);	cudaFree(buffer_array_68);
	cudaFree(buffer_array_69);	cudaFree(buffer_array_70);
	
	cudaFree(buffer_c);	
	
	delete [] array_01;	delete [] array_02;	delete [] array_03;	delete [] array_04;	
	delete [] array_05;	delete [] array_06;	delete [] array_07;	delete [] array_08;	
	delete [] array_09;	delete [] array_10;	
	delete [] array_11;	delete [] array_12;	delete [] array_13;	delete [] array_14;	
	delete [] array_15;	delete [] array_16;	delete [] array_17;	delete [] array_18;	
	delete [] array_19;	delete [] array_20;	
	delete [] array_21;	delete [] array_22;	delete [] array_23;	delete [] array_24;	
	delete [] array_25;	delete [] array_26;	delete [] array_27;	delete [] array_28;	
	delete [] array_29;	delete [] array_30;	
	delete [] array_31;	delete [] array_32;	delete [] array_33;	delete [] array_34;	
	delete [] array_35;	delete [] array_36;	delete [] array_37;	delete [] array_38;	
	delete [] array_39;	delete [] array_40;
	delete [] array_41;	delete [] array_42;	delete [] array_43;	delete [] array_44;	
	delete [] array_45;	delete [] array_46;	delete [] array_47;	delete [] array_48;	
	delete [] array_49;	delete [] array_50;	
	delete [] array_51;	delete [] array_52;	delete [] array_53;	delete [] array_54;	
	delete [] array_55;	delete [] array_56;	delete [] array_57;	delete [] array_58;	
	delete [] array_59;	delete [] array_60;
	delete [] array_61;	delete [] array_62;	delete [] array_63;	delete [] array_64;	
	delete [] array_65;	delete [] array_66;	delete [] array_67;	delete [] array_68;	
	delete [] array_69;	delete [] array_70;
	
	delete [] c;
	
	delete [] array_01_serial;	delete [] array_02_serial;	delete [] array_03_serial;	
	delete [] array_04_serial; 	delete [] array_05_serial;	delete [] array_06_serial;
	delete [] array_07_serial;	delete [] array_08_serial; delete [] array_09_serial;
	delete [] array_10_serial;
	delete [] array_11_serial;	delete [] array_12_serial;	delete [] array_13_serial;	
	delete [] array_14_serial; 	delete [] array_15_serial;	delete [] array_16_serial;
	delete [] array_17_serial;	delete [] array_18_serial; delete [] array_19_serial;
	delete [] array_20_serial;
	delete [] array_21_serial;	delete [] array_22_serial;	delete [] array_23_serial;	
	delete [] array_24_serial; 	delete [] array_25_serial;	delete [] array_26_serial;
	delete [] array_27_serial;	delete [] array_28_serial; delete [] array_29_serial;
	delete [] array_30_serial;
	delete [] array_31_serial;	delete [] array_32_serial;	delete [] array_33_serial;	
	delete [] array_34_serial; 	delete [] array_35_serial;	delete [] array_36_serial;	
	delete [] array_37_serial;	delete [] array_38_serial; delete [] array_39_serial;
	delete [] array_40_serial;
	delete [] array_41_serial;	delete [] array_42_serial;	delete [] array_43_serial;	
	delete [] array_44_serial; 	delete [] array_45_serial;	delete [] array_46_serial;
	delete [] array_47_serial;	delete [] array_48_serial; delete [] array_49_serial;
	delete [] array_50_serial;
	delete [] array_51_serial;	delete [] array_52_serial;	delete [] array_53_serial;	
	delete [] array_54_serial; 	delete [] array_55_serial;	delete [] array_56_serial;
	delete [] array_57_serial;	delete [] array_58_serial; delete [] array_59_serial;
	delete [] array_60_serial;
	delete [] array_61_serial;	delete [] array_62_serial;	delete [] array_63_serial;	
	delete [] array_64_serial; 	delete [] array_65_serial;	delete [] array_66_serial;
	delete [] array_67_serial;	delete [] array_68_serial; delete [] array_69_serial;
	delete [] array_70_serial;
	
	delete [] c_serial;
	
	printf("End of program!\n");
	
	
}