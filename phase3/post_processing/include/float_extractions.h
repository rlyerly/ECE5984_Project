/*
 * Defines some common functions for extracting the different parts of IEEE
 * 32-bit floating point numbers.
 *
 * Author: Rob Lyerly <rlyerly@vt.edu>
 */

/*
 * Union used for conversions
 */
union f2i {
	float f;
	unsigned int i;
};

/*
 * Function to convert a float to an unsigned int
 */
inline unsigned int float2int(float f)
{
	union f2i convert;
	convert.f = f;
	return convert.i;
}

/* Extract the sign from an int */
#define SIGN( num ) ((num >> 31) & 0x1)

/* Extract the exponent from an int */
#define EXPONENT( num ) ((num >> 23) & 0xff)

/* Extract the mantissa from an int */
#define MANTISSA( num ) (num & 0x7fffff)

/* Function to convert a float to an unsigned int and extract the sign */
inline unsigned int sign(float f)
{
	return SIGN(float2int(f));
}

/* Function to convert a float to an unsigned int and extract the exponent */
inline unsigned int exponent(float f)
{

	return EXPONENT(float2int(f));
}

/* Function to convert a float to an unsigned int and extract the mantissa */
inline unsigned int mantissa(float f)
{
	return MANTISSA(float2int(f));
}
