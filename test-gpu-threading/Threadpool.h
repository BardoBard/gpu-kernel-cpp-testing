#pragma once
#include <iostream>
#include <vector>
#include <CL/cl.h>

class Threadpool
{
private:
    bool is_gpu_available;
    cl_device_id* devices;
    cl_command_queue command_queue = nullptr;
    cl_platform_id platform = nullptr;
    cl_context context;

public:
    Threadpool() : is_gpu_available(false)
    {
        cl_uint num_platforms; //the number of platforms
        cl_int status = clGetPlatformIDs(0, NULL, &num_platforms);
        //get platform, platform can be AMD APP, NVIDIA or Intel
        if (status != CL_SUCCESS || num_platforms < 1)
        {
            std::cout << "Error: Drivers or GPU might not be supported" << std::endl;
            return;
        }
        cl_platform_id* platforms = static_cast<cl_platform_id*>(malloc(num_platforms * sizeof(cl_platform_id)));
        status = clGetPlatformIDs(num_platforms, platforms, NULL);
        platform = platforms[0];
        free(platforms);

        cl_uint num_devices = 0;
        status = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);
        if (status != CL_SUCCESS) //no GPU available.
        {
            std::cout << "No GPU device available." << std::endl;
            return;
        }

        //allocate memory for amount of GPUs
        devices = static_cast<cl_device_id*>(malloc(num_devices * sizeof(cl_device_id)));
        clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, num_devices, devices, NULL);


        //create context
        context = clCreateContext(NULL, 1, devices,NULL,NULL,NULL);

        command_queue = clCreateCommandQueueWithProperties(context, devices[0], 0, NULL);
    }

    ~Threadpool()
    {
        clReleaseCommandQueue(command_queue); //Release  Command queue.
        clReleaseContext(context); //Release context.
        free(devices);
    }

    void execute_kernel(const std::string& filename, const std::string& function_name, std::vector<unsigned>& int1);
};
