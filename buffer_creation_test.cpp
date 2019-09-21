/* 
Using CL_MEM_COPY_HOST_PTR when creating buffer will result in slower execution
However this is only applied to kernel method with large arguments (>4)

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

#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 110
 
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl2.hpp>
#endif


using namespace std;
using namespace std::chrono;

int main(int argc, char **argv){
	cout<<"Start of program"<<endl;
	
	size_t node=100000;
	
	vector<float> a(node,0.0);
	vector<float> b(node,0.0);
	vector<float> d(node,0.0);
	vector<float> e(node,0.0);
	vector<float> f(node,0.0);
	vector<float> c_serial(node,0.0);
	vector<float> c_01(node,0.0); //parallel with normal buffer
	vector<float> c_02(node,0.0); // parallel with CL_MEM_COPY_HOST_PTR buffer
	
	for (size_t i = 0; i < node; ++i) {
			std::srand(std::time(nullptr)); // use current time as seed for random generator
			a[i]=((float) rand()/(RAND_MAX))*i;
			b[i]=((float) rand()/(RAND_MAX))*i;
			d[i]=((float) rand()/(RAND_MAX))*i;
			e[i]=((float) rand()/(RAND_MAX))*i;
			f[i]=((float) rand()/(RAND_MAX))*i;
		
	}
	for (size_t i = 0; i < node; ++i) {
			c_serial[i]=a[i]+b[i]+d[i]+e[i]+f[i];
	}
	
	//###########################################################################
	//PARALLEL VERSION
	cout<<"Start parallel version with no of nodes "<<node<<endl;
	//Check device
	{
	//get platforms
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	if (platforms.empty())
	{
		std::cout << "*********** No platforms found! Aborting...!" << std::endl;
		return 1;
	}

	std::cout << "*********** Listing available platforms:" << std::endl;
	for (size_t i = 0; i < platforms.size(); ++i)
		std::cout << "platform[" << i << "]: " << platforms[i].getInfo<CL_PLATFORM_NAME>() << std::endl;

	cl::Platform selectedPlatform = platforms[1]; // choose Intel or NVidia
	std::cout << "*********** Using the following platform: " << selectedPlatform.getInfo<CL_PLATFORM_NAME>() << std::endl;

	//get devices
	std::vector<cl::Device> devices;
	selectedPlatform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
	if (devices.empty())	{
		std::cout << "*********** No devices found on platform " << selectedPlatform.getInfo<CL_PLATFORM_NAME>()
			<<"! Aborting...!" << std::endl;
		return 1;
	}

	std::cout << "*********** Listing available devices:" << std::endl;
	for (size_t i = 0; i < devices.size(); ++i)
		std::cout << "device[" << i << "]: " << devices[i].getInfo<CL_DEVICE_NAME>() << std::endl;

	cl::Device selectedDevice = devices[0]; // choose Intel or NVidia
	std::cout << "*********** Using the following device: " << selectedDevice.getInfo<CL_DEVICE_NAME>() << std::endl;
	}
	
	//########################################################################################
	
	cl_int error_ret;
	std::ifstream inStream("buffer_creation_test.cl");
	
    if (inStream.fail()) {
        std::cout << "Failed to load kernel. Aborting..." << std::endl;
        return 1;
    }
	
    std::string kernelStr;

    inStream.seekg(0, std::ios::end);
    kernelStr.reserve(inStream.tellg());
    inStream.seekg(0, std::ios::beg);
    //C++11
    kernelStr.assign(std::istreambuf_iterator<char>(inStream), {});
    inStream.close();

    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    if (platforms.empty())    {
        std::cout << "*********** No platforms found! Aborting...!" << std::endl;
        return 1;
    }

    cl::Platform selectedPlatform = platforms[1]; //choose Intel or NVidia
    std::cout << "*********** Using the following platform: " << selectedPlatform.getInfo<CL_PLATFORM_NAME>() << std::endl;

    //get devices
    std::vector<cl::Device> devices;
    selectedPlatform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
    if (devices.empty())    {
        std::cout << "*********** No devices found on platform " << selectedPlatform.getInfo<CL_PLATFORM_NAME>()
            << "! Aborting...!" << std::endl;
        return 1;
    }

    cl::Device selectedDevice = devices[0];
    std::cout << "*********** Using the following device: " << selectedDevice.getInfo<CL_DEVICE_NAME>() << std::endl;

    cl::Context context({selectedDevice});

    cl::Program::Sources sources;
    sources.push_back({kernelStr.c_str(), kernelStr.length()});

    cl::Program clProgram(context, sources);
    if (clProgram.build({selectedDevice}) != CL_SUCCESS) {
        std::cout<<"Building error: " << clProgram.getBuildInfo<CL_PROGRAM_BUILD_LOG>(selectedDevice) << std::endl;
        return 1;
    }	
	
	cl::CommandQueue queue(context, selectedDevice);

	cl::NDRange global(node, 1); //(nPoints, nGrids)
	cl::NDRange local(1, 1);
   
   //########################################################################################	
	system_clock::time_point start_parallel = system_clock::now();
		 // Create memory buffers on the device for each vector 
		cl::Buffer buffer_a(context, CL_MEM_READ_ONLY, sizeof(float)*node);
		cl::Buffer buffer_b(context, CL_MEM_READ_ONLY, sizeof(float)*node);
		cl::Buffer buffer_d(context, CL_MEM_READ_ONLY, sizeof(float)*node);
		cl::Buffer buffer_e(context, CL_MEM_READ_ONLY, sizeof(float)*node);
		cl::Buffer buffer_f(context, CL_MEM_READ_ONLY, sizeof(float)*node);
		cl::Buffer buffer_c_01(context, CL_MEM_READ_WRITE, sizeof(float)*node);
		
		queue.enqueueWriteBuffer(buffer_a, CL_TRUE, 0, sizeof(float) * node, &a[0]);
		queue.enqueueWriteBuffer(buffer_b, CL_TRUE, 0, sizeof(float) * node, &b[0]);
		queue.enqueueWriteBuffer(buffer_d, CL_TRUE, 0, sizeof(float) * node, &d[0]);
		queue.enqueueWriteBuffer(buffer_e, CL_TRUE, 0, sizeof(float) * node, &e[0]);
		queue.enqueueWriteBuffer(buffer_f, CL_TRUE, 0, sizeof(float) * node, &f[0]);
		
		cl::Kernel cl_kernel_vector_addition_01(clProgram, "vector_addition");
		
		cl_kernel_vector_addition_01.setArg(0, buffer_a);
		cl_kernel_vector_addition_01.setArg(1, buffer_b);
		cl_kernel_vector_addition_01.setArg(2, buffer_d);
		cl_kernel_vector_addition_01.setArg(3, buffer_e);
		cl_kernel_vector_addition_01.setArg(4, buffer_f);
		cl_kernel_vector_addition_01.setArg(5, buffer_c_01);
		
		queue.enqueueNDRangeKernel(cl_kernel_vector_addition_01, cl::NullRange, global, local, NULL);
	
		queue.enqueueReadBuffer(buffer_c_01, CL_TRUE, 0, sizeof(float) * node, &c_01[0]);
		
		queue.finish();
		
		system_clock::time_point stop_parallel = system_clock::now();
		std::chrono::duration<float, std::milli> duration_parallel = stop_parallel - start_parallel;
		cout << "Parallel buffer_creation_test = "<<duration_parallel.count()<<" millisecond"<<endl;
	
   //########################################################################################	
	system_clock::time_point start_parallel_02 = system_clock::now();
		 // Create memory buffers on the device for each vector 
		
		cl::Buffer buffer_a_02(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, node* sizeof(float), &a[0]);
		cl::Buffer buffer_b_02(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, node* sizeof(float), &b[0]);
		cl::Buffer buffer_d_02(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, node* sizeof(float), &d[0]);
		cl::Buffer buffer_e_02(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, node* sizeof(float), &e[0]);
		cl::Buffer buffer_f_02(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, node* sizeof(float), &f[0]);
		cl::Buffer buffer_c_02(context, CL_MEM_READ_WRITE, sizeof(float)*node);
	
		cl::Kernel cl_kernel_vector_addition_02(clProgram, "vector_addition");
		
		cl_kernel_vector_addition_02.setArg(0, buffer_a_02);
		cl_kernel_vector_addition_02.setArg(1, buffer_b_02);
		cl_kernel_vector_addition_02.setArg(2, buffer_d_02);
		cl_kernel_vector_addition_02.setArg(3, buffer_e_02);
		cl_kernel_vector_addition_02.setArg(4, buffer_f_02);
		cl_kernel_vector_addition_02.setArg(5, buffer_c_02);
		
		queue.enqueueNDRangeKernel(cl_kernel_vector_addition_02, cl::NullRange, global, local, NULL);
	
		queue.enqueueReadBuffer(buffer_c_02, CL_TRUE, 0, sizeof(float) * node, &c_02[0]);
		
		queue.finish();
		
		system_clock::time_point stop_parallel_02 = system_clock::now();
		std::chrono::duration<float, std::milli> duration_parallel_02 = stop_parallel_02 - start_parallel_02;
		cout << "Parallel buffer_creation_test with CL_MEM_COPY_HOST_PTR= "<<duration_parallel_02.count()<<" millisecond"<<endl;
	
	  //########################################################################################	
	  //Checking
	
	float c_gap=0.0;
	
	for (size_t i = 0; i < node; ++i) {
		c_gap += abs(c_serial[i]-c_01[i])+abs(c_serial[i]-c_02[i]);
		//c_gap += abs(c_serial[i]-c_01[i]);
		//c_gap += abs(c_serial[i]-c_02[i]);
		
	}
	cout<<"c_gap= "<<c_gap<<endl;
	
	printf("End of program!");
	
	
}