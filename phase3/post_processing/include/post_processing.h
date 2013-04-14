/*
 * Post-processing Library
 *
 * Defines the interface to apply different post-processing techniques to data
 * obtained from random-number sources to eliminate bias and ensure uniformity.
 *
 * Author: Rob Lyerly <rlyerly@vt.edu>
 */
#include <stdint.h>
#include <math.h>

#define BITS2BYTES( bits ) (int)ceil(((double)bits)/8.0)

/*
 * Enumerates the possible types of post-processing available to the user.
 *
 * NONE:	Apply no post-processing.  You probably don't need to use this
 *		library if you're not dispersing the data.  In this case,
 *		input data is copied directly into the output buffer and the
 *		input size is returned.
 *
 * SHA3:	Apply the SHA-3 algorithm.  This is a well known standard and
 *		has good statistical random number properties.  The number of
 *		post-processed bytes returned is equal to the input size.
 *
 * MULTI_SAMPLE:Apply the technique proposed in "Extracting Randomness Using
 *		Few Independent Sources" by Barak et. al. The algorithm takes
 *		three samples s1, s2 and s3.  Samples s1 and s2 are multiplied
 *		together (using modular multiplication) and the result is added
 *		to s3.
 *
 * TOEPLITZ:	Apply the technique proposed in "True Random Number Generators
 *		Secure in a Changing Environment" by Barak et. al.  Perform a
 *		matrix multiplication of the Toeplitz matrix (i.e. diagonal
 *		matrix) and the input data (in column form).
 */
enum pp_type {
	NONE,
	SHA3,
	MULTI_SAMPLE,
	TOEPLITZ
};

/*
 * Struct encapsulating all necessary information for performing
 * post-processing.  Users of the library must initialize this struct with the
 * specified type of post-processing and input data.  Once the "post_process"
 * function has been applied to this struct, it will contain the output data.
 */
typedef struct _pp_data {
	//Type of post-processing
	enum pp_type type;

	//Input size (# of bits) + data
	unsigned long input_size; //TODO do we need to set this to a fixed size?
	union idata {
		uint8_t* sample;
		uint8_t* samples[3];
	} input_data;

	//Output size (# of bits) + data
	unsigned int output_size;
	uint8_t* output_data;
} pp_data;

/*
 * Apply post-processing to the supplied data.  The calling function must set
 * the type of post-processing and the input data on which to apply it.  On
 * return, the struct will contain a pointer to the processed data.
 *
 * Arguments:
 *	data:	Data struct (defined above) which specifies the type of
 *		post-processing to apply and the data to apply it to.	
 *
 * Returns:
 *	Success (0) if the data was successfully post-processed, or failure (1)
 *	otherwise.
 */
int post_process(pp_data* data);
