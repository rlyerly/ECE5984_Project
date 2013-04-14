#include "post_processing.h"

#define SIZE 16

int main(int argc, char** argv)
{
	uint8_t inbuf[SIZE];
	uint8_t outbuf[SIZE];

	// Test SHA-3
	pp_data data;
	data.type = SHA3;
	data.input_data.sample = inbuf;
	data.output_data = outbuf;
	post_process(&data);

	return 0;
}
