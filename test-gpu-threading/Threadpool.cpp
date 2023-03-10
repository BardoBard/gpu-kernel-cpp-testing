#include "Threadpool.h"

#include <chrono>
#include <fstream>
#include <vector>

/* convert the kernel file into a string */
int convert_to_string(const std::string& filename, std::string& source_string)
{
    std::fstream file_stream(filename, (std::fstream::in | std::fstream::binary));

    if (file_stream.is_open())
    {
        size_t file_size;
        file_stream.seekg(0, std::fstream::end);
        const size_t size = file_size = static_cast<size_t>(file_stream.tellg());
        file_stream.seekg(0, std::fstream::beg);
        char* str = new char[size + 1];
        if (!str)
        {
            file_stream.close();
            return 0;
        }

        file_stream.read(str, file_size);
        file_stream.close();
        str[size] = '\0';
        source_string = str;
        delete[] str;
        return 0;
    }
    std::cout << "Error: failed to open file\n:" << filename << std::endl;
    return -1;
}

void Threadpool::execute_kernel(const std::string& filename, const std::string& function_name,
                                std::vector<unsigned int>& int1)
{
    /////////
    //setup//
    /////////
    std::string sourceStr;
    convert_to_string(filename, sourceStr);
    const char* source = sourceStr.c_str();
    size_t sourceSize[] = {std::strlen(source)};
    cl_program program = clCreateProgramWithSource(context, 1, &source, sourceSize, NULL);
    clBuildProgram(program, 1, devices,NULL,NULL,NULL);
    cl_kernel kernel = clCreateKernel(program, function_name.c_str(), NULL); //create kernel, NULL can be status
    size_t global_work_size[1] = {int1.size()}; //amount of threads
    //

    const auto start = std::chrono::steady_clock::now();


    cl_mem inputBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                        int1.size() * sizeof(unsigned int), (void*)int1.data(), NULL);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, int1.size() * sizeof(unsigned int), NULL, NULL);

    clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&inputBuffer); //give kernel arguments
    clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&outputBuffer); //give kernel arguments

    clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);


    unsigned int* output = static_cast<unsigned int*>(malloc(int1.size() * sizeof(unsigned int)));
    clEnqueueReadBuffer(command_queue, outputBuffer, CL_TRUE, 0, int1.size() * sizeof(unsigned int), output, 0, NULL,
                        NULL);

    const auto end = std::chrono::steady_clock::now();

    std::cout << std::endl;
    std::cout << std::chrono::duration<double, std::milli>(end - start).count() << " ms" << std::endl;
    std::cout << std::chrono::duration<double, std::nano>(end - start).count() << " ns" << std::endl;


    std::cout << "\noutput string:" << std::endl;
    // for (int i = 0; i < int1.size() * sizeof(unsigned int); ++i)
    // {
    //     std::cout << output[i] << std::endl;
    // }
    clReleaseKernel(kernel); //Release kernel.
    clReleaseProgram(program); //Release the program object.
    clReleaseMemObject(inputBuffer); //Release mem object.
    clReleaseMemObject(outputBuffer);
    if (output != NULL)
    {
        free(output);
        output = NULL;
    }
}
