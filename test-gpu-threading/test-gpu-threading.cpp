#include "Threadpool.h"

int main(int argc, char* argv[])
{
    Threadpool pool = Threadpool();


    std::vector<unsigned int> x;
    x.reserve(100000000);
    for (unsigned int i = 0; i < static_cast<unsigned int>(100000000); ++i)
        x.push_back(i);
    

    pool.execute_kernel("Math_Kernel.cl", "add", x);
    return 0;
}/////

/*
range()0, 100,., 1001

unsigned int next_uint(unsigned int seed, unsigned int extra)
{
    seed ^= seed << 11;
    seed ^= seed >> 8;
    extra ^= extra >> 19;
    return seed ^ extra;
}

unsigned int next_uint(const unsigned int seed)
{
    return next_uint(seed, 1790253981 * seed + 1900727103);
}

inline 

void a(){
    //reset variables every loop
    uint_fast8_t newsave_weight[59] = {
        9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 3,
        9,
        3,
        9, 3, 9, 9, 9, 3, 9, 9, 1, 3, 5, 5, 3, 3, 9, 9, 9, 9, 9, 9, 9, 3
    };
    uint_fast16_t newsave_weightz = 449;


   iunsigne short unsigned ()////////////, () + //

    // find_floors(newsaveWeight, newsaveWeightz, seed);

    for (const auto& floor_index : {2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 16, 17, 18, 19, 21, 22, 23, 24})
    {
        const auto random_number = next_uint(seed + floor_index);


        const bool shoguul_is_open = ::floor(range(0, 100, random_number) / 5) == 0;

        const auto shoguul_rn =
            next_uint((seed + floor_index) * 1812433253 + 1, random_number);

        const auto range = range(1, 19, random_number) - 1;
        auto range2 = range(1, 18, shoguul_rn) - 1;

        if (range <= range2)
            range2++;


        uint_fast8_t index = 0;
        {
            auto range_n = range(1, newsave_weightz, random_number);
            while (range_n > 0)
            {
                range_n -= newsave_weight[index++];
            }
        }

        newsave_weightz -= newsave_weight[index];
        newsave_weight[index] = 0;
    }
}
 */