# 1. Write an implementation of the Dining Philosophers program, demonstrating deadlock avoidance.

## Code based on https://rosettacode.org/wiki/Dining_philosophers#Python

```

import threading
import random
import time

class Philosopher(threading.Thread):
    
    running = True
    def __init__(self, name, left_fork, right_fork):
        threading.Thread.__init__(self)
        self.name = name
        self.left_fork = left_fork
        self.right_fork = right_fork

    def run(self):
        while(self.running):
            time.sleep(random.uniform(1, 10))
            print({self.name} is hungry)
            self.dine()

    def dine(self):
        fork1, fork2 = self.left_fork, self.right_fork
        while self.running:
            fork1.acquire(True)
            locked = fork2.acquire(False)
            if locked: 
                break
            fork1.release()
            print({self.name} swapped forks)
            fork1, fork2 = fork2, fork1
        else:
            return
        self.dining()
        fork1.release()
        fork2.release()

    def dining(self):			
        print(f'{self.name} started eating')
        time.sleep(random.uniform(1, 10))
        print(f'{self.name} finished eating and put down his forks')

def dining_philosophers():
    names = ['Socrates', 'Aristotle', 'Kant', 'Mills', 'Singer']
    forks = [threading.Lock() for i in range(5)] 
    philosophers = [Philosopher(names[i], forks[i], forks[(i + 1) % 5]) for i in range(5)]
    for p in philosophers: 
        p.start()

dining_philosophers()



```


# 2. Write a short paragraph explaining why your program is immune to deadlock?
<br>

In this problem, philosophers should hold forks on both sides at the same time. Then the philosopher can eat food in front of them. When each philosopher holds one fork, it happens that he or she can't hold two forks at the same time. Thus, a philosopher may not be able to eat and may eat less than other philosophers. Our program can prevent deadlock. If a philosopher hold a fork and can't hold the second fork, he or she will drop the first fork. So, another philosopher can pick up the fork and then checks to see if both adjacent forks are available to use a few seconds later. Philosophers use forks when they can use forks on both sides at the same time and it doesn't keep single forks locked infinitely.


---

# 3. Modify the file-processes.cpp program from Figure 8.2 on page 338 to simulate this shell command: <br>
tr a-z A-Z < /etc/passwd <br>
Write the code in “C”, not in C++.

``` 

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t returnedValue = fork();
    if (returnedValue < 0) {
        perror("error forking");
        return -1;
    } else if (returnedValue == 0) {
        printf("returnedValue == 0");
        if (close(STDIN_FILENO) < 0) { 
            perror("error closing standard input");
            return -1;
        }
        if (open("/etc/passwd", O_RDONLY, S_IRUSR) < 0) {
            perror("error opening my-processes");
            return -1;
        }
        execlp("tr", "tr", "a-z", "A-Z", NULL);
        perror("error executing tr");
        return -1;
    } else {
        if (waitpid(returnedValue, 0, 0) < 0) {
            perror("error waiting for child");
            return -1;
        }
        printf("\nNote the parent still has the old standard output.\n");
    }
}


```


# 4. <br>

```

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


```


# 5.
<br>

The Java class from Chapter 4 that would be appropriate to use for the holding area would be the Bounded Buffer class. The way the Bounded Buffer class works is that each time the producer stores a value into an intermediate storage area, called a buffer and the consumer retrieves the value from the buffer when it is ready. In this sense, the receive method can place the messages into a temporary holding area, while the other thread running in the TopicServer can take the meassages and send them to the appropriate subscribers.


```
