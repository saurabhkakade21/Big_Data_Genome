//Name: Saurabh Jawahar Kakade sk2354@nau.edu

// !!! Use the head command to make a smaller version of the dataset file to transfer to your laptop... for example
// head -2000 /common/contrib/classroom/inf503/hw_dataset.fa > /scratch/vyf2/sample_hw_dataset.fa
//... this will take 2000 lines from the time of file (1000 reads)

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include "homework.h"
using namespace std;

void func(string file)
{
	FASTAreadset_LL fasta(file);
	// FASTAreadset_LL fasta1 = fasta;
	FASTAreadset_LL fasta1(fasta);
}
	
int main(int argc, char ** argv){ 

////////////////////////////////////////////////////////////////////////////////////	
//Lets do sanity checks to make sure the proper number of parameters were passed in
////////////////////////////////////////////////////////////////////////////////////

	if (argc != 4){  // unexpected program call
		cout << endl << endl << "=========================="<< endl;
		cout << "Error: 2 input parameters expected" <<endl;
		cout << "Proper usage is:" <<endl;
		cout << "./homework <problem-flag> <filepath>" << endl;
		cout << "Example:" << endl;
		cout << "./homework A /scratch/vyf2/HW1/sample_hw_dataset.fa 1000"  << endl;
		cout << "=========================="<< endl << endl;
		cout << "exiting..." << endl;
		exit(-1);
	}else{

		cout << "\n\nThe number of arguments passed: " << argc << endl;
		cout << "The first argument is: " << argv[0] << endl;
		cout << "The second argument is: " << argv[1] << endl; 
		cout << "The third argument is: " << argv[2] << endl;
		cout << "The fourth argument is: " << argv[3] << endl;
	}

	int user_input_for_no_of_reads = atoi(argv[3]);
	char* second_argument = argv[1];

	FASTAreadset_LL fasta(argv[2]);
	// FASTAreadset_LL fasta1 = fasta;
	// FASTAreadset_LL fasta1(fasta);

	switch(*second_argument)
	{
		case 'A': 
			cout << "\n Using the first 36 million reads to initialize (fill up) the array data-structure with the entire 36 million reads" << endl;
			fasta.read_reads(user_input_for_no_of_reads);
			// fasta.display_reads();
			
			break;

		case 'B': 
			cout << "\nImplementing a destructor for class to delete / deallocate your array data structure" << endl;
			fasta.delete_data_structure();
			fasta.display_reads();
			break;

		case 'C': 
			cout << "\nImplementation of Copy Constructor: " << endl;
			fasta.read_reads(user_input_for_no_of_reads);
			func(argv[2]);
			break;

		case 'D':
			cout << "\nImplementing Search function: " << endl;
			fasta.read_reads(user_input_for_no_of_reads);
			fasta.search_function(user_input_for_no_of_reads);
			break;

		case 'E':
			cout << "\nPart 02 function: \n" << endl;
			fasta.read_genomic_data(user_input_for_no_of_reads);
			fasta.search_genomic_data(user_input_for_no_of_reads);
			fasta.print_genomic_data();
			break;

		default:
			cout << "Enter second argument from A to E !!!" << endl;
			break;
	}
	
	return (0);
}
