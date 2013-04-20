/*
 * Common includes & definitions necessary for the implementation of the
 * secure TRNG in changing environments implementation.
 *
 * Author: Rob Lyerly <rlyerly@vt.edu>
 */

/*The public parameter chosen in the "pre-processing stage" */
#define PI 0x1234

/* Definitions of parameters in the paper */
/* Min-entropy (k) of the accelerometer/gyroscope */
#define MIN_ENTROPY 256 //TODO get real min-entropy


