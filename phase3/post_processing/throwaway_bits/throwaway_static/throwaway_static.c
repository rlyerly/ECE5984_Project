#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

/*
 * Convenience macro to convert number of bits to a mask.
 */
#define MASK( numBits ) masks[numBits - 1]

/*
 * Jump table to convert number of bits to extract into an appropriate mask.
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

const char* help = "throwaway_bits_static - saves only the specified LSBs of 32-bit numbers in the specified input file and packs them in the specified output file for use in NIST & DIEHARD tests\n\nUsage: throwaway_bits <options>\n\t-h              : display this help\n\t-i <input file> : input file\n\t-o <output file>: output file\n\t-n <num bits>   : number of bits to save\n";

int main(int argc, char** argv)
{
	const char* infileName = "infile.dat";
	const char* outfileName = "outfile.dat";
	int arg = 0;
	unsigned int num2extract = 32;

	while((arg = getopt(argc, argv, "hi:o:n:")) != -1)
	{
		switch(arg)
		{
		case 'h':
			printf("%s\n", help);
			return 1;
		case 'i':
			infileName = optarg;
			break;
		case 'o':
			outfileName = optarg;
			break;
		case 'n':
			num2extract = atoi(optarg);
			break;
		default:
			printf("Unknown option %c\n", arg);
			printf("\n%s\n", help);
			return 1;
		}
	}

	//Correct input errors
	if(num2extract > 32 || num2extract == 0)
		num2extract = 32;
	printf("Extracting %d bits from each number\n", num2extract);

	//Open files
	FILE* infile = fopen(infileName, "rb");
	if(!infile)
	{
		printf("Could not open file %s for reading\n", infileName);
		return 1;
	}

	FILE* outfile = fopen(outfileName, "wb");
	if(!outfile)
	{
		fclose(infile);
		printf("Could not open file %s for writing\n", outfileName);
		return 1;
	}

	int numRead;
	if(32 % num2extract == 0)
		numRead = 32 / num2extract;
	else
		numRead = 32 / num2extract + 1;
	int num2read = numRead;
	int numLeftover = 0;
	int i = 0;
	uint32_t* numbers = (uint32_t*)malloc(sizeof(uint32_t) * num2read);
	uint32_t packedNum = 0;
	uint32_t leftoverBits = 0;
	uint32_t mask = MASK(num2extract);

	//Read & pack numbers
	size_t numFromFile = fread((void*)numbers, sizeof(uint32_t),
		num2read, infile);
	while(numFromFile == num2read)
	{
		//Utilize leftover bits
		packedNum = leftoverBits;

		//Extract bits & save
		for(i = 0; i < num2read; i++)
			packedNum |= (numbers[i] & mask)
				<< (i * num2extract + numLeftover);
		fwrite((void*)&packedNum, sizeof(uint32_t), 1, outfile);

		//Store leftover bits
		numLeftover = (i * num2extract + numLeftover) - 32;
		leftoverBits = (numbers[i - 1] >> (num2extract - numLeftover))
			& MASK(numLeftover - 1);

		//Determine number to read
		if((numLeftover + (num2read - 1) * num2extract) >= 32)
			num2read = numRead - 1;
		else
			num2read = numRead;

		//Read more data
		numFromFile = fread((void*)numbers, sizeof(uint32_t),
			num2read, infile);
	}

	//Grab bits from last numbers in file
	packedNum = leftoverBits;
	for(i = 0; i < numFromFile; i++)
		packedNum |= (numbers[i] & mask)
			<< (i * num2extract + numLeftover);
	fwrite((void*)&packedNum, sizeof(uint32_t), 1, outfile);

	fclose(infile);
	fclose(outfile);

	free(numbers);

	return 0;
}
