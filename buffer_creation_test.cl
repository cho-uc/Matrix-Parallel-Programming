__kernel void vector_addition(__global float *a,
	__global float *b,
	__global float *d,
	__global float *e,
	__global float *f,
	__global float *c){
		
	uint i= get_global_id(0);
	
	c[i]=a[i]+b[i]+d[i]+e[i]+f[i];
	
}