#include <stdio.h>
#include <sys/time.h>

#define BYTES_SAMPLED 	10000 //10MB
#define US_PER_S 	1000000 

int main(int argc, char * argv[]) {
	
    FILE *out_file;
    FILE *rand_file;
    char rand_bytes[BYTES_SAMPLED];
    int i = 0;
    char * out_name;
    char * out_str;
    struct timeval tv1;
    struct timeval tv2;

    if (argc != 2) {
	printf("usage: ./randomdevs <u or r>\n");
    }
    else if (!strcmp(argv[1],"u")) {
	rand_file = fopen("/dev/urandom", "r");
	out_name = "/data/dev_urandom_10mb";
	out_str = "urandom";
    }
    else if (!strcmp(argv[1],"r")) {
	rand_file = fopen("/dev/random", "r");
	out_name = "/data/dev_random_10mb";
	out_str = "random";
    }
    else {
	printf("usage: ./randomdevs <u or r>\n");
    }

    out_file = fopen(out_name, "w");

    gettimeofday(&tv1,NULL);

    printf("Starting to read from /dev/%s at: %lds or %ldus\n",out_str,tv1.tv_sec, tv1.tv_usec);
    fread(&rand_bytes, 1, BYTES_SAMPLED,rand_file);
    
    gettimeofday(&tv2,NULL);
    printf("Writing to file at: %lds or %ldus\n",tv2.tv_sec,tv2.tv_usec);
    
    for (i=0;i<BYTES_SAMPLED;i++) {
	//printf(".");
        fprintf(out_file,"%c",rand_bytes[i]);
    }
    
    //printf("FINISHED! with a rate of %lldbits/sec\n",(long long)((BYTES_SAMPLED*8)/((tv2.tv_usec-tv1.tv_usec)/US_PER_S)));
    
    fclose(rand_file);
    fclose(out_file);

    return 0;
}

