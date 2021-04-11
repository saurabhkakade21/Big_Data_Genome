The program consist of 3 files (Copy in one dir on monsoon):
	homework.cpp
	homework.h
	Makefile

Following commands are neede to execute the program:

Step 01: To copy  /common/contrib/classroom/inf503/hw_dataset.fa to current directory:

	Monsoon: cp  /common/contrib/classroom/inf503/hw_dataset.fa .

Step 02: Monsoon: make

Step 03: To execute part A of program:
 
	Monsoon: srun --mem=6000 -t 00:60:00 ./homework A /hw_dataset.fa 36000000
	
Step 04: To check the job status for CPU time and RAM:

	Monsoon: jobstats -j <job_id>
 
Step 05: To execute part B of program:
 
	Monsoon: srun --mem=6000 -t 00:60:00 ./homework B /hw_dataset.fa 36000000
	
Step 06: To execute part C of program:
 
	Monsoon: srun --mem=6000 -t 00:60:00 ./homework C /hw_dataset.fa 100000

Step 07: To execute part D of program:
 
	Monsoon: srun --mem=6000 -t 00:60:00 ./homework D /hw_dataset.fa 36000000

Step 08: To execute part D of program:
 
	Monsoon: srun --mem=6GB -t 00:60:00 ./homework E ./test_genome.fa 36000000
