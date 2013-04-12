#include <stdlib.h>
#include <string.h>
#include <alloca.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/random.h>
#include <err.h>

static void
add_entropy(const char *buf, int len)
{
	/* Hold an always open descriptor to the random device */
	static int rnd = -1;

	/* Open random on the first run. */
	if (rnd < 0) {
		rnd = open("/dev/random", O_RDWR);
		if (rnd < 0)
			err(EXIT_FAILURE, "Failed to open /dev/random");
	}

	/* Determine how much entropy this actually represents */
	int e_cnt = len << 3; /*?*/
	
    /* Build the request */
    struct rand_pool_info *rpi = alloca((2 * sizeof(int)) + len);
	rpi->entropy_count = e_cnt;
	rpi->buf_size = len;
	memcpy(rpi->buf, buf, len);
	
	/* Add the entropy to the pool */
	int ret = ioctl(rnd, RNDADDENTROPY, rpi);
	if (ret == -1) 
		err(EXIT_FAILURE, "Failed to add entropy to pool");
}

int
main(int argc, char **argv)
{
	while (1) {
		add_entropy("test", 4);
		break;
	}
}
