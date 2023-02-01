inline int range( unsigned short int min,  unsigned short int max,  unsigned int random_number){
    return (int)(random_number % (max + 1 - min) + min);
}

inline unsigned int next_uint(unsigned int seed, unsigned int extra)
{
    seed ^= seed << 11;
    seed ^= seed >> 8;
    extra ^= extra >> 19;
    return seed ^ extra;
}

//1790253981 * seed + 1900727103

__kernel void add(__global unsigned int* output)
{
//unsigned short int starter_to_newsave_index[9] = {5, 31, 0, 22, 7, 44, 25, 6, 50};
unsigned int seed = get_global_id(0);
short int newsave_weight[59] = {
        9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9, 9, 9, 9, 9, 3,
        9,
        3,
        9, 3, 9, 9, 9, 3, 9, 9, 1, 3, 5, 5, 3, 3, 9, 9, 9, 9, 9, 9, 9, 3
    };
    unsigned int newsave_weightz = 449;

 {
        const unsigned short int range_s = range(1, 73, next_uint(seed + 1, 1790253981 * (seed + 1) + 1900727103)) - 72;
        const unsigned short int i = range_s > 0 ? 8 : 7 + (unsigned short int)(range_s / 9);
        
output[seed] = i;

      //  const unsigned short int starter_to_uint8 = starter_to_newsave_index[i];
      //  newsave_weightz -= newsave_weight[starter_to_uint8];
       // newsave_weight[starter_to_uint8] = 0;
    }
//output[seed] = seed;


}