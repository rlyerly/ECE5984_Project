#include <stdio.h>
#include <string.h>
#include "post_processing.h"

#define ERR( message ) fprintf(stderr, "Error: message!\n")

int post_process(pp_data* data)
{
	//Preliminary checks, make sure the user didn't do anything stupid...
	if(data->input_size > 128)
	{
		ERR("Input size too large");
		return FAILURE;
	}

	if(!data->input_data.sample)
	{
		ERR("No input data");
		return FAILURE;
	}

	if(!data->output_data)
	{
		ERR("No output data buffer");
		return FAILURE;
	}

	//Perform the requested type of post-processing
	switch(data->type)
	{
	case NONE:
		//Copy input data to output data, set output size
		memcpy(data->output_data, data->input_data.sample,
				data->input_size);
		data->output_size = data->input_size;
		break;
	case VON_NEUMANN:
		break;
	case SHA3:
		break;
	case MULTI_SAMPLE:
		break;
	case TOEPLITZ:
		break;
	default:
		ERR("Requested unknown type of post-processing");
		return FAILURE;
	}

	return SUCCESS;
}
