#include <stdlib.h>
#include <stdint.h>

/*
 * Forward function declarations to add entropy.
 * TODO: Reese probably needs to create a header file with the prototypes.
 */
extern void add_entropy(const char* but, int len);

/*
 * Convenience macro to convert number of bits to a mask.
 */
#define MASK( numBits ) masks[numBits - 1]

/*
 * Jump table to convert number of bits to extract into a bitmask.
 */
int masks[] =
{
	0x1, 0x3, 0x7, 0xf,
	0x1f, 0x3f, 0x7f, 0xff,
	0x1ff, 0x3ff, 0x7ff, 0xfff,
	0x1fff, 0x3fff, 0x7fff, 0xffff,
	0x1ffff, 0x3ffff, 0x7ffff, 0xfffff,
	0x1fffff, 0x3fffff, 0x7fffff, 0xffffff,
	0x1ffffff, 0x3ffffff, 0x7ffffff, 0xfffffff,
	0x1fffffff, 0x3fffffff, 0x7fffffff, 0xffffffff
};

/*
 * Struct that encapsulates the current state of the bit extractor.
 */
typedef struct __bit_extractor {
	unsigned int num2extract;
	int samplesNeeded;
	int samples2use;
	int samplesUsed;
	int numLeftoverBits;
	uint32_t packedNum;
	uint32_t mask;
} bit_extractor;

/*
 * Initialize and return a bit extractor state variable for processing.
 */
bit_extractor* initialize_bit_extractor(unsigned int num_bits)
{
	bit_extractor* be = (bit_extractor*)malloc(sizeof(bit_extractor));

	//Sanity checking
	if(num_bits > 32)
		be->num2extract = 32;
	else
		be->num2extract = num_bits;

	//Calculate the number of samples needed to fill 32-bits
	if(32 % num_bits == 0)
		be->samplesNeeded = 32 / be->num2extract;
	else
		be->samplesNeeded = 32 / be->num2extract + 1;
	be->samples2use = be->samplesNeeded;

	be->samplesUsed = 0;
	be->numLeftoverBits = 0;
	be->packedNum = 0;
	be->mask = MASK(be->num2extract);

	return be;
}

/*
 * Pack and add bits to the entropy pool.
 */
void add_bits(bit_extractor* be, uint32_t sample)
{
	//Add bits
	be->packedNum |= (sample & be->mask)
		<< (be->samplesUsed * be->num2extract + be->numLeftoverBits);
	be->samplesUsed++;

	//See if we have a full 32-bit number
	if(be->samplesUsed >= be->samples2use)
	{
		//Add number to entropy pool
		add_entropy(be->packedNum, sizeof(be->packedNum));

		//Store leftover bits
		be->numLeftoverBits = be->samplesUsed * be->num2extract
			+ be->numLeftoverBits - 32;
		be->packedNum = (sample >> (be->num2extract - be->numLeftoverBits))
			& MASK(be->numLeftoverBits);

		//Determine required # of samples
		if((be->numLeftoverBits + (be->samplesNeeded - 1)
				* be->num2extract) >= 32)
			be->samples2use = be->samplesNeeded - 1;
		else
			be->samples2use = be->samplesNeeded;

		//Reset variables
		be->samplesUsed = 0;
	}
}

/*
 * Destroy the bit extractor struct.
 */
void destroy_bit_extractor(bit_extractor* be)
{
	free(be);
}
