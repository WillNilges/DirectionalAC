#include <CL/opencl.h>
#include <iostream>
#include <cstdlib>

int main(){
cl_platform_id platform;
std::cout << clGetPlatformIDs(1, &platform, NULL) << std::endl;
std::cout << "Platform: " << platform << std::endl;
cl_device_id device;
clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

std::cout << "Device: " << device << std::endl;
return 0;
}
