The program consist of 6 files (Copy in one dir on monsoon):
	homework.cpp
	homework.h
	homework_BLAST.h
	Makefile
	hw3_dataset.fa (queries)
	test_genome.fasta (genome)
	

Following commands are neede to execute the program:

Step 01: No extra files needed to copy from monsoon

Step 02: Monsoon: make

Step 03: To execute part01 A of program:
 
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework A /hw3_dataset.fa ./test_genome.fasta
	
Step 04: To check the job status for CPU time and RAM:

	Monsoon: jobstats -j <job_id>
 
Step 05: To execute part01 B of program: (same for all user defined size for random sequence generation and is changed from homework.cpp file)
 
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework B /hw3_dataset.fa ./test_genome.fasta
	
Step 06: To execute part02 A of program: 
 
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework C /hw3_dataset.fa ./test_genome.fasta

Step 07: To execute part02 B of program: (same for all user defined size for random sequence generation and is changed from homework.cpp file)
 
	Monsoon: srun --mem=10GB -t 00:60:00 ./homework D /hw3_dataset.fa ./test_genome.fasta

