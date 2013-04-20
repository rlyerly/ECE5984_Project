/*
 * Defines some common functions for extracting the different parts of IEEE
 * 32-bit floating point numbers.
 *
 * Author: Rob Lyerly <rlyerly@vt.edu>
 */

/* Extract the sign from a number */
#define SIGN( num ) ((num >> 31) & 0x1)

/* Extract the exponent from a number */
#define EXPONENT( num ) ((num >> 23) & 0xff)

/* Extract the mantissa from a number */
#define MANTISSA( num ) (num & 0x7fffff)
