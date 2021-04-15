//Name: Saurabh Jawahar Kakade sk2354@nau.edu
//Assignment 03
//Large Scale Data Structures

//header files
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include "homework.h"

using namespace std;

	
int main(int argc, char ** argv){ 

////////////////////////////////////////////////////////////////////////////////////	
//Lets do sanity checks to make sure the proper number of parameters were passed in
////////////////////////////////////////////////////////////////////////////////////

	if (argc != 4){  // unexpected program call
		cout << endl << endl << "=========================="<< endl;
		cout << "Error: Total 4 input parameters expected" <<endl;
		cout << "Proper usage is:" <<endl;
		cout << "./homework <problem-flag> <filepath01> <filepath02>" << endl;
		cout << "Example:" << endl;
		cout << "./homework A file1.fa file2.fa"  << endl;
		cout << "=========================="<< endl << endl;
		cout << "exiting..." << endl;
		exit(-1);
	}else{

		cout << "\n\nThe number of arguments passed: " << argc << endl;
		cout << "The first argument is: " << argv[0] << endl; 	//main file exe
		cout << "The second argument is: " << argv[1] << endl; 	//selection of options
		cout << "The third argument is: " << argv[2] << endl;	//file path 01
		cout << "The fourth argument is: " << argv[3] << endl;	//file path 02
	}

	char* second_argument = argv[1];	//switch case parameter

	FASTAreadset_DA fasta(argv[2]);	// calling class from homework.h to solve part 01

	int user_sizeofhashtable = 10000000;	//size of hash table 


	switch(*second_argument)
	{
		
		//Part 01
		case 'A': 
			cout << "\nRead in the read data set into your data structure: \n" << endl;
			fasta.read_reads();
			// fasta.display_reads();
			fasta.read_genomic_data(argv[3]);
			// fasta.print_genomic_data();
			fasta.SW_algorithm();
			break;

		case 'B': 
			cout << "\nSearch time in direct access arrays: \n" << endl;
			// fasta.read_reads();
			// fasta.radix_notation();
			// fasta.read_genomic_data(argv[3]);
			// fasta.search_genomic_data();
			// fasta.print_genomic_data();
			break;

		//Part 02
		case 'C': 
			cout << "\nAssessing the impact of the hash table size: \n" << endl;
			// fasta_chain.read_reads_chain();
			// fasta_chain.hash_table_creation();
			// fasta_chain.display_hash_collisions();
			// fasta_chain.display_reads_chain();
			break;

		case 'D': 
			cout << "\nSearching in the chain-linked hash table: \n" << endl;
			// fasta_chain.read_reads_chain();
			// fasta_chain.hash_table_creation();
			// fasta_chain.display_hash_collisions();
			// fasta_chain.display_reads_chain();
			// fasta_chain.read_genomic_data_chain(argv[3]);
			// fasta_chain.search_genomic_data_chain();
			break;


		default:
			cout << "Enter second argument from A to D !!!" << endl;
			break;
	}
	
	return (0);
}
