#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char** argv) {
	int fd = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR);
	if (fd < 0) {
		perror(argv[1]);
		return -1;
	}

	struct stat info;
	if (fstat(fd, &info) < 0) {
		perror("Error stating input file");
		return -1;
	}

	char* add = mmap(0, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (add == MAP_FAILED) {
		perror("Error mapping input file");
		return -1;
	}

	clock_t begin = clock();
	for (int i = 0; i < info.st_size; i++) {
		char c = add[i];
		if (add[i] == 'X') {
			printf("success\n");
			close(fd);
			clock_t end = clock();
			double elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;
			printf("Time taken: %fs\n", elapsed_time);
			return 0;
		}
	}
	printf("failure\n");
	close(fd);
	clock_t end = clock();
	double elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time taken: %fs\n", elapsed_time);
	return 0;
}