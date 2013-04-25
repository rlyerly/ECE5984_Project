#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

/*
 * Correlate hex chars to bit representations.
 */
enum HexChar {
	ZERO = 0, ONE, TWO, THREE,
	FOUR, FIVE, SIX, SEVEN,
	EIGHT, NINE, A, B,
	C, D, E, F
};

/*
 * Convert a string of hex vals (max 8 chars) into an unsigned int.
 */
uint32_t string2int(const char* string)
{
	int i = 0, numChars = strlen(string);
	uint32_t intVal = 0, bits = 0;

	for(i = 0; i < numChars; i++)
	{
		switch(string[i])
		{
		case '0':
			bits = ZERO;
			break;
		case '1':
			bits = ONE;
			break;
		case '2':
			bits = TWO;
			break;
		case '3':
			bits = THREE;
			break;
		case '4':
			bits = FOUR;
			break;
		case '5':
			bits = FIVE;
			break;
		case '6':
			bits = SIX;
			break;
		case '7':
			bits = SEVEN;
			break;
		case '8':
			bits = EIGHT;
			break;
		case '9':
			bits = NINE;
			break;
		case 'A':
		case 'a':
			bits = A;
			break;
		case 'B':
		case 'b':
			bits = B;
			break;
		case 'C':
		case 'c':
			bits = C;
			break;
		case 'D':
		case 'd':
			bits = D;
			break;
		case 'E':
		case 'e':
			bits = E;
			break;
		case 'F':
		case 'f':
			bits = F;
			break;
		default:
			printf("Unknown hex character \'%c\'\n", string[i]);
			exit(1);
		}

		intVal |= bits << (numChars - i - 1) * 4;
	}

	return intVal;
}

/*
 * Convert strings to binary data & write to file.
 */
void write2file(char* first, char* second, char* third, FILE* outfile)
{
	uint32_t binary[3] = {0, 0, 0};

	binary[0] = string2int(first);
	binary[1] = string2int(second);
	binary[2] = string2int(third);

	fwrite((void*)binary, sizeof(uint32_t), 3, outfile);
}

int main(int argc, char** argv)
{
	const char* infileName = "infile.dat";
	const char* outfileName = "outfile.dat";
	char arg = 0;
	opterr = 0;

	//Select input/output file
	while((arg = getopt(argc, argv, "hi:o:")) != -1)
	{
		switch(arg)
		{
		case 'h':
			printf("Usage: hex2bin -i <infile> -o <outfile>\n");
			return 1;
		case 'i':
			infileName = optarg;
			break;
		case 'o':
			outfileName = optarg;
			break;
		default:
			printf("Unknown argument: %c\n", arg);
			return 1;
		}
	}

	//Sanity check
	int numLines = 0;

	char first[9];
	char second[9];
	char third[9];

	FILE* infile = fopen(infileName, "r");
	if(!infile)
	{
		printf("Could not open %s for reading\n", infileName);
		return 1;
	}

	FILE* outfile = fopen(outfileName, "wb");
	if(!outfile)
	{
		printf("Could not open %s for writing\n", outfileName);
		fclose(infile);
		return 1;
	}

	//Get first line
	if(fscanf(infile, "%s %s %s\n", first, second, third) == 3)
	{
		write2file(first, second, third, outfile);
		numLines++;
	}

	//Get rest of lines
	while(!feof(infile))
	{
		write2file(first, second, third, outfile);
		numLines++;

		if(fscanf(infile, "%s %s %s\n", first, second, third) < 3)
			break;
	}

	//Save last line
	write2file(first, second, third, outfile);
	numLines++;
	
	fclose(infile);
	fclose(outfile);

	printf("Read %d lines\n", numLines);

	return 0;
}
