
Setup:

	You will do this on the linux server

	Once you are logged into a crunchy machine, type: module avail
	
	Check the latest gcc version. 
	
	Type: module load gcc-9.2 (or whatever latest version of gcc you find as long as it is 6 or higher).
	
	Must do that each time you loggin and compile

Dependencies:

	openmp, linux server

Compile:

	gcc -Wall -std=c99 -o automata -fopenmp automata.c

Run:

	./automata [X] [Y] [Z] [filename] 

Explanation:

	X stands for number of iterations/generations for the cellular automata
	Y stands for the size of the board
	Z stands for the number of threads 
	filename means the the name of the input file

	In the end, the program will automatically output filename.out that contains the final result


For example:

	gcc -Wall -std=c99 -o automata -fopenmp automata.c
	./genmap 1000 f
	./automata 1000 1000 1 f
	./automata 1000 1000 2 f
	./automata 1000 1000 5 f
	./automata 1000 1000 10 f
	./automata 1000 1000 20 f

Results:

	[admin@linux-server ~]$ gcc -Wall -std=c99 -o automata -fopenmp automata.c
	[admin@linux-server ~]$ ./genmap 1000 f
	[admin@linux-server ~]$ ./automata 1000 1000 1 f
	Time: 29.789973 seconds
	[admin@linux-server ~]$ ./automata 1000 1000 2 f
	Time: 14.937482 seconds
	[admin@linux-server ~]$ ./automata 1000 1000 5 f
	Time: 6.081438 seconds
	[admin@linux-server ~]$ ./automata 1000 1000 10 f
	Time: 3.143275 seconds
	[admin@linux-server ~]$ ./automata 1000 1000 20 f
	Time: 1.644452 seconds
	[admin@linux-server ~]$ 