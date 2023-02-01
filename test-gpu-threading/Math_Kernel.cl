inline int range(const unsigned short int min, const unsigned short int max,
                 const unsigned int random_number) {
  return (int)(random_number % (max + 1 - min) + min);
}

inline unsigned int next_uint(unsigned int seed, unsigned int extra) {
  seed ^= seed << 11;
  seed ^= seed >> 8;
  extra ^= extra >> 19;
  return seed ^ extra;
}

// 1790253981 * seed + 1900727103
__constant unsigned short int floors[19] = {
    2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 16, 17, 18, 19, 21, 22, 23, 24};
__constant unsigned short int starter_to_newsave_index[9] = {5,  31, 0, 22, 7,
                                                             44, 25, 6, 50};

__kernel void add(__global unsigned int *output) {
  unsigned int seed = get_global_id(0);
  short int newsave_weight[59] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 9, 9, 9,
                                  9, 9, 9, 9, 9, 9, 9, 9, 9, 3, 3, 9, 9, 9, 9,
                                  9, 9, 9, 9, 3, 9, 3, 9, 3, 9, 9, 9, 3, 9, 9,
                                  1, 3, 5, 5, 3, 3, 9, 9, 9, 9, 9, 9, 9, 3};
  unsigned int newsave_weightz = 449;

  // Prefix sum for the newsave_weight array.
  short int prefix_sum[59];
  prefix_sum[0] = 0;
  for (int i = 0; i < 58; i++) {
    prefix_sum[i + 1] = prefix_sum[i] + newsave_weight[i];
  }

  {
    const int range_s =
        range(1, 73,
              next_uint(seed + 1, 1790253981 * (seed + 1) + 1900727103)) -
        72;
    const unsigned short int i = range_s > 0 ? 8 : 7 + (short int)(range_s / 9);

    output[seed] = i;

    const unsigned short int starter_to_uint8 = starter_to_newsave_index[i];
    newsave_weightz -= newsave_weight[starter_to_uint8];
    newsave_weight[starter_to_uint8] = 0;
  }
  for (int i = 0; i < 19; ++i) {
    const unsigned short int floor_index = floors[i];
    const unsigned int random_number = next_uint(
        seed + floor_index, 1790253981 * (seed + floor_index) + 1900727103);
    const bool shoguul_is_open =
        (unsigned short int)(range(0, 100, random_number) / 5) == 0;

    const unsigned int shoguul_rn =
        next_uint((seed + floor_index) * 1812433253 + 1, random_number);

    const unsigned short int range_1 = range(1, 19, random_number) - 1;
    unsigned short int range_2 = range(1, 18, shoguul_rn) - 1;

    if (range_1 <= range_2)
      range_2++;

    // Find the index of the weight to be selected.
    unsigned short int index = 0;
    short int range_n = range(1, newsave_weightz, random_number);
    while (prefix_sum[index + 1] < range_n) {
      index++;
    }

    newsave_weightz -= newsave_weight[index];
    newsave_weight[index] = 0;
  }
}