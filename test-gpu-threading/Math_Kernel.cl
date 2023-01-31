__kernel void add(__global unsigned int* seed, __global unsigned int* out)
{
unsigned int num = get_global_id(0);
        //	out[num] = in[num] * 10;
	
	unsigned int zeed = seed[num];
        unsigned int extra = 1790253981 * zeed + 1900727103;
        extra ^= extra >> 19;
	    zeed ^= zeed << 11;
        zeed ^= zeed >> 8;
        out[num] = zeed ^ extra;
}