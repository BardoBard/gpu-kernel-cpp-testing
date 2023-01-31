#include "Threadpool.h"

int main(int argc, char* argv[])
{
    Threadpool pool = Threadpool();


    std::vector<unsigned int> x;
    x.reserve(100000000);
    for (unsigned int i = 0; i < static_cast<unsigned int>(100000000); ++i)
    {
        x.push_back(i);
    }

    pool.execute_kernel("Math_Kernel.cl", "add", x);
    return 0;
}
