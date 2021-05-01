The program consist of 4 files (Copy in one dir on monsoon):
	homework.cpp
	homework.h
	Makefile
	test_genome.fasta (genome)
	

Following commands are neede to execute the program:

Step 01: No extra files needed to copy from monsoon

Step 02: Monsoon: make

Step 03: To execute part01 A of program:
 
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework A ./test_genome.fasta 5000 0
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework A ./test_genome.fasta 50000 0
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework A ./test_genome.fasta 100000 0
	
Step 04: To check the job status for CPU time and RAM:

	Monsoon: jobstats -j <job_id>
 
Step 05: To execute part01 B of program: 
 
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework A ./test_genome.fasta 1000 5
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework A ./test_genome.fasta 50000 5
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework A ./test_genome.fasta 100000 5