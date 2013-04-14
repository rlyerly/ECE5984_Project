/* Standard library includes */
#include <stdio.h>
#include <string.h>
#include <math.h>

/* Post-processing library includes */
#include "post_processing.h"
#include "KeccakNISTInterface.h"

#define ERR( message ) fprintf(stderr, "Error: message!\n")

int post_process(pp_data* data)
{

	//Preliminary checks, make sure the user didn't do anything stupid...
	if(data->input_size > 128)
	{
		ERR("Input size too large");
		return FAIL;
	}

	if(!data->input_data.sample)
	{
		ERR("No input data");
		return FAIL;
	}

	if(!data->output_data)
	{
		ERR("No output data buffer");
		return FAIL;
	}

	//Perform the requested type of post-processing
	switch(data->type)
	{
	case NONE:
		memcpy(data->output_data, data->input_data.sample,
				BITS2BYTES(data->input_size));
		data->output_size = data->input_size;
		break;
	case SHA3:
		if(!Hash(data->input_size, data->input_data.sample,
				data->input_size, data->output_data))
		{
			ERR("Incorrect input size for SHA-3.  Must have 224, 256, 384 or 512 bits of input data");
			data->output_size = 0;
			return FAIL;
		}
		data->output_size = data->input_size;
		break;
	case MULTI_SAMPLE:
		break;
	case TOEPLITZ:
		break;
	default:
		ERR("Requested unknown type of post-processing");
		return FAIL;
	}

	return SUCCESS;
}
