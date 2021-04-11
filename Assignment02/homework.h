//Name: Saurabh Jawahar Kakade sk2354@nau.edu

#ifndef FASTA_H
#define FASTA_H

// header files
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;
     

//structure node function for linked list
struct Node 
{
    char dataStructure_LL[50];	//to store data
    char headercounter_LL[50];	//to store read head
	struct Node *next;
};


//main class 
class FASTAreadset_LL
{
    private:
		char ** data_array; //an aray used for temp purpose
		char ** header_array; //an aray used for temp purpose

		int num_of_reads; //to read the number of reads from user
        string file_path; // to store file name
        ifstream input; //used for file operations
		Node* head; // to create new node head
		Node* data_head; // to create new node for temporary purpose

    public:
        
        FASTAreadset_LL() //constructor
        {
            cout << "Constructor Function executed !!!" << endl;
			head = NULL;
			data_head = NULL;
        }    
        
        FASTAreadset_LL(string filepath)  //default constructor
        {
            file_path = filepath;

            if(input.is_open()) //check whether file is open already
			{
				input.close(); // closing file
			}

			input.open(file_path.c_str()); 
			head = NULL;
			data_head = NULL;

        }

		FASTAreadset_LL(const FASTAreadset_LL &a) // copy constructor with object name a
		{
			cout << "Copy Constructor Called !!! " << endl;
   			
			head = NULL;	//initialize linked pointers to null
   			data_head = NULL;
   			
   			Node* current_node;
   			int count = 0;
   			Node* temp = a.head;
			   
   			while(temp != NULL)
			{
   				
				Node* new_node = new Node;

				strcpy(new_node -> dataStructure_LL, temp -> dataStructure_LL);

				for(int i = 0; i < 50; i++)
				{
	    			(new_node -> dataStructure_LL)[i] = (temp -> dataStructure_LL)[i];
				}
	    		
				(new_node -> dataStructure_LL)[50] = '\0';
				
				new_node -> next = NULL;
				 
				if(count == 0)
				{
				 	head = new_node;
				}
				else
				{
				 	current_node -> next = new_node;
				}
				count++;
				current_node = new_node;
				temp = temp -> next;   	
				
			}
			
			temp = a.data_head;

			count = 0;

			while(temp != NULL)
			{
   				 
				Node* new_node = new Node;

				for(int i = 0; i < 50; i++)
				{
	    		 	(new_node -> dataStructure_LL)[i] = (temp -> dataStructure_LL)[i];
				}
	    		
				(new_node -> dataStructure_LL)[50] = '\0';
				new_node -> next = NULL;
				new_node -> next = NULL;
				 
				if(count == 0)
				{
				 	data_head = new_node;
				}
				else
				{
				 	current_node -> next = new_node;
				}
				
				count++;
				current_node = new_node;
				temp = temp -> next;   	

			}
		}
				
        void read_reads(int no_of_read_lines) // function to read number of reads from file
        {
            
			num_of_reads = no_of_read_lines;

			data_array = new char*[num_of_reads];
			
			for (int i = 0; i < num_of_reads; i++)
			{
				data_array[i] = new char[50];
			}
			
			Node * current_ll = new Node;	//temporary node

			for (int i = 0; i < num_of_reads; i++)
			{
				Node * new_node = new Node;

				input >> new_node->headercounter_LL;		//read read sequence		
				input >> new_node->dataStructure_LL;		//read data sequence

				data_array[i] = new_node->dataStructure_LL;

				new_node->next = NULL;

				if(current_ll != NULL)
				{
					current_ll->next = new_node;
				}

				current_ll = new_node;

				if(i == 0)
				{
					head = new_node;
				}

			}

			input.close(); //closing the file

        }

		void display_reads() // display function to print linked list
		{
			Node* temp; //pointer to traverse the linked list
			temp = head;
			
			while(temp != NULL)
			{
				cout << temp -> dataStructure_LL << "\n";
				temp = temp -> next;
			}
		}

		int search_in_ll(int no_of_read_lines, char sequence_to_compare[]) // function to search sequence in linked list 
		{	
			int counter_ll = 0;

			Node* temp = head; 
			
			for (int i = 0; i < no_of_read_lines; i++)
			{
				
				if(strcmp(sequence_to_compare, temp -> dataStructure_LL) == 0)
				{
					cout<<endl;

					cout << sequence_to_compare << " found at index " << i << endl;

					counter_ll++;
				}
				temp = temp -> next;
			}

			cout << endl;
			return counter_ll;
		}
        
		void search_function(int no_of_read_lines) 	//search function which would take a sequence fragment and search for this fragment within the FASTAreadset_LL object.
		{
			int return_value;
			
			char sequence_to_compare_01[] = "CTAGGTACATCCACACACAGCAGCGCATTATGTATTTATTGGATTTATTT";
			char sequence_to_compare_02[] = "GCGCGATCAGCTTCGCGCGCACCGCGAGCGCCGATTGCACGAAATGGCGC";
			char sequence_to_compare_03[] = "CGATGATCAGGGGCGTTGCGTAATAGAAACTGCGAAGCCGCTCTATCGCC";
			char sequence_to_compare_04[] = "CGTTGGGAGTGCTTGGTTTAGCGCAAATGAGTTTTCGAGGCTATCAAAAA";
			char sequence_to_compare_05[] = "ACTGTAGAAGAAAAAAGTGAGGCTGCTCTTTTACAAGAAAAAGTNNNNNN";


			cout << "Search function for sequence 01" << sequence_to_compare_01 << "\n";
			return_value = search_in_ll(no_of_read_lines, sequence_to_compare_01);
			if(return_value ==0) { cout << "Not found" << "\n\n"; }


			cout << "Search function for sequence 02 " << sequence_to_compare_02 <<  "\n";
			return_value = search_in_ll(no_of_read_lines, sequence_to_compare_02);
			if(return_value != -1) { cout << "Not found" << "\n\n"; }


			cout << "Search function for sequence 03 " << sequence_to_compare_03 <<  "\n";
			return_value = search_in_ll(no_of_read_lines, sequence_to_compare_03);
			if(return_value != -1) { cout << "Not found" << "\n\n"; }


			cout << "Search function for sequence 04 " << sequence_to_compare_04 << "\n";
			return_value = search_in_ll(no_of_read_lines, sequence_to_compare_04);
			if(return_value != -1) { cout << "Not found" << "\n\n"; }

	
			cout << "Search function for sequence 05 " << sequence_to_compare_05 <<  "\n";
			return_value = search_in_ll(no_of_read_lines, sequence_to_compare_05);
			if(return_value != -1) { cout << "Not found" << "\n\n"; }

		}
       
	   	void read_genomic_data(int no_of_read_lines)	//Read in the Bacillus anthracis genome
		{

            if(input.is_open()) //check whether file is open already
			{
				input.close(); // closing file
			}

			input.open(file_path.c_str()); // initialize th file

			char temp[50]; // to store 50 characters in a temp forlder

			char genome_character = '\0';

			int count = 0;
			int num_of_records = 0;

			Node* current;
			
			while(genome_character != '\n')
			{
				input.get(genome_character);	//avoid first line from file
			}

			while (input.get(genome_character))
			{
  				if(genome_character == 'A' || genome_character == 'C' || genome_character == 'G' || genome_character == 'T' || genome_character == 'N')
				{
  					
					temp[count] = genome_character;
  					count++;
				
  					if(count == 50)
					{
						count--;	//as we are counting from 0 to last will be 49

  						num_of_records++;
  						
  						Node* new_node = new Node;

  						for(int k = 0; k < 50; k++)
						{
			    			(new_node -> dataStructure_LL)[k] = temp[k];
						}

			    		(new_node -> dataStructure_LL)[50] = '\0';

			    		new_node -> next = NULL;

						count = 0;
			    		
			    		if(num_of_records == 1)
						{
			    			data_head = new_node;
						}
						else
						{
							current -> next = new_node;
						}

						current = new_node;
						
					}

					if(data_head != NULL)
					{
						for(int i = 1; i < 50; i++)
						{
							temp[i - 1] = temp[i];
						}
					}
				}  
				// count =0;
			}         
			

			cout << "Total 50-character fragments: " << num_of_records << endl;
			input.close();
		}

		int search_genomic_data(int no_of_read_lines)	//Iterate through all 50-mers found in the genome
		{
			
			Node* compare_node = data_head;
			
			int return_value = 0;
			int total_search_found = 0;
			
			while(compare_node != NULL)
			{

				return_value = search_in_ll(no_of_read_lines, compare_node -> dataStructure_LL);

				compare_node = compare_node -> next;

				if(return_value > 0) { total_search_found++; }

			}

			cout << "Total 50-character fragments in read set: " << total_search_found << endl;

			return total_search_found;
		}

		void print_genomic_data() //print the genome data linked list
		{

			Node* current = data_head;

			while(current != NULL)
			{
				cout << current -> dataStructure_LL << "\n";
				current = current -> next;
			}
		}
		
        void delete_data_structure() // function to print deconstructor inilialisation 
        {
            cout << "\nDeconstructor Function executed !!!\n" << endl;
        }

		void deleteList(Node** head_ref) // function to delete entire linked list
        {
 
            Node* current = *head_ref;
            Node* next = NULL;
 
            while (current != NULL) 
            {
                next = current->next;
                free(current);
                current = next;
            }
 
            *head_ref = NULL;

        }
   
        ~FASTAreadset_LL()
            {
                deleteList(&head);
				deleteList(&data_head);
            }
        
};

#endif