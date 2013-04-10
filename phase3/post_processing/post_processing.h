/*
 * Post-processing Library
 *
 * Defines the interface to apply different post-processing techniques to data
 * obtained from random-number sources to eliminate bias and ensure uniformity.
 *
 * Author: Rob Lyerly <rlyerly@vt.edu>
 */
#define SUCCESS 0
#define FAILURE 1

/*
 * Enumerates the possible types of post-processing available to the user.
 *
 * NONE:	Apply no post-processing.  You probably don't need to use this
 *		library if you're not dispersing the data.  In this case,
 *		input data is copied directly into the output buffer and the
 *		input size is returned.
 *
 * VON_NEUMANN:	Apply von-Neumann whitening.  This is a stream-processing
 *		approach where two consecutive bits are analyzed.  If they are
 *		the same, they are thrown out.  If the first bit is 0 and the
 *		second bit is 1, then a 1 is output.  If the first bit is 1
 *		and the second bit is 0, then a 0 is output.  In this way, you
 *		can get up to 4 bits of randomness per byte.
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
	VON_NEUMANN,
	SHA3,
	MULTI_SAMPLE,
	TOEPLITZ
};

/*
 * 
 */
typedef struct _pp_data {
	//Type of post-processing
	enum pp_type type;

	//Input size + data
	unsigned int input_size; //TODO do we need to set this to a fixed size?
	union idata {
		char* sample;
		char* samples[3];
	} input_data;

	//Output size + data
	unsigned int output_size;
	char* output_data;
} pp_data;

/*
 * Apply post-processing to the supplied data.  The calling function must set
 * the type of post-processing and the input data on which to apply it.  On
 * return, the output data will be filled with dispersed data.
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
