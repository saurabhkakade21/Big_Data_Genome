The program consist of 4 files (Copy in one dir on monsoon):
	homework.cpp
	homework.h
	homework_cpp.h
	Makefile

Following commands are neede to execute the program:

Step 01:

	Monsoon: cp /common/contrib/classroom/inf503/hw_dataset.fa .
	Monsoon: cp /common/contrib/classroom/inf503/test_genome.fasta .
	

Step 02: Monsoon: make

Step 03: To execute part A of program:
 
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework A /hw3_dataset.fa ./test_genome.fasta
	
Step 04: To check the job status for CPU time and RAM:

	Monsoon: jobstats -j <job_id>
 
Step 05: To execute part B of program:
 
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework B /hw3_dataset.fa ./test_genome.fasta
	
Step 06: To execute part C of program: //part 02
 
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework C /hw3_dataset.fa ./test_genome.fasta

Step 07: To execute part D of program:
 
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework D /hw3_dataset.fa ./test_genome.fasta

