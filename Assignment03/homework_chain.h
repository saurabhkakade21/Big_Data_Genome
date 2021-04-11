//Name: Saurabh Jawahar Kakade sk2354@nau.edu
//Assignment 03
//Large Scale Data Structures


#ifndef FASTA_CHAIN_H
#define FASTA_CHAIN_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "homework.h"

using namespace std;
     

//structure node_chain function for linked list
struct Node_chain 
{
    char *hash_dataStructure_chain;		//to store data
    unsigned int header_chain;			//to store read head
	struct Node_chain *next_chain;
};

//main class 
class FASTAreadset_Chain
{
    private:
		
		char ** header_array_chain; //an aray used for temp purpose
		char ** data_array_chain; //an aray used for temp purpose

		unsigned int total_chain,value_chain,hashtablesize_chain,fragment_present,collisions_chain = 0;
		int usersizeofhashtable; //to read the number of reads from user

        string file_path_chain; // to store file name
        ifstream input_chain; //used for file operations

		Node_chain* head_chain; // to create new node head
		Node_chain* data_head_chain; // to create new node for temporary purpose
		bool bool_array_chain[4294967295];

    public:

		Node_chain **hash_table;
        
        FASTAreadset_Chain() //constructor
        {
            cout << "Constructor Function executed !!!" << endl;
			head_chain = NULL;
			data_head_chain = NULL;
        }    
        
        FASTAreadset_Chain(string filepath, int user_sizeofhashtable)  //default constructor
        {
            file_path_chain = filepath;
			usersizeofhashtable = user_sizeofhashtable;

            if(input_chain.is_open()) //check whether file is open already
			{
				input_chain.close(); // closing file
			}

			input_chain.open(file_path_chain.c_str()); 

			head_chain = NULL;
			data_head_chain = NULL;

        }
		
		int size_of_table_chain() //to count the size of the read dataset file
		{
			string input_line_chain;
			int counter1_chain = 0;
			ifstream input_chain;
			input_chain.open(file_path_chain.c_str()); 

					
			while(getline(input_chain,input_line_chain))
			{
				counter1_chain++;
			} 

			return counter1_chain;
		}

        void read_reads_chain() // function to read number of reads from read dataset
        {
            
			int counter_chain = size_of_table_chain();
			
			cout << "Number of lines in read dataset: " << counter_chain << endl;

			header_array_chain = new char*[counter_chain];
			data_array_chain = new char*[counter_chain];			
						
			for(int i=0;i<counter_chain;i++)
			{
				header_array_chain[i] = new char[16];
				data_array_chain[i] = new char[16];
			}

			Node_chain * current_chain = new Node_chain;	//temporary node

			char temp_input_chain[16];	

			for(int i=0;i<counter_chain;i++)
			{
				Node_chain * new_node = new Node_chain;

				input_chain >> header_array_chain[i];		//read read sequence		
				input_chain >> data_array_chain[i];		//read data sequence

				new_node->next_chain = NULL;

				if(current_chain != NULL)
				{
					current_chain->next_chain = new_node;
				}

				current_chain = new_node;

				if(i == 0)
				{
					head_chain = new_node;
				}

			}

			input_chain.close(); //closing the file

        }

		void hash_table_creation()	//to create hash table
		{
			
			hash_table =  new Node_chain*[usersizeofhashtable];
 			
			for(int i = 0 ; i < usersizeofhashtable ;i++)
			{
				hash_table[i] = NULL;
 			}

			unsigned int size_chain = size_of_table_chain();
			
			int power_chain = 0;

 			for(int i = 0; i < usersizeofhashtable ; i++)
			{
            	
				power_chain = 1;
			
				for (int j = 0; j < 16; j++)
				{
					
					//A==0, C==1, G==2, T==3

					if(data_array_chain[i][j]=='A')
					{
						value_chain = 0;
					}

					if(data_array_chain[i][j]=='C')
					{
						value_chain = 1;
					}
					
					if(data_array_chain[i][j]=='G')
					{
						value_chain = 2;
					}

					if(data_array_chain[i][j]=='T')
					{
						value_chain = 3;
					}

					total_chain = total_chain + (value_chain * power_chain);

					power_chain = power_chain * 4;

				}

				total_chain = total_chain % usersizeofhashtable;
				
				Node_chain *current = hash_table[total_chain];
				
             	Node_chain *temp_chain = NULL;
             	
				while (current != NULL)
				{
					temp_chain = current;
					current = current->next_chain;
				}

				if (current == NULL)
				{
					current = new Node_chain();
					current->header_chain = total_chain;
					current->hash_dataStructure_chain = new char[16];

					for(int k = 0 ; k < 16 ; k++)
					{
						current->hash_dataStructure_chain[k] = data_array_chain[i][k];
					}

					if (temp_chain == NULL)
					{
						hash_table[total_chain] = current;
					}

					else
					{
						temp_chain->next_chain = current;
					}

				}
				else
				{
					for(int m = 0 ; m < 16 ; m++)
					{
	                	(current->hash_dataStructure_chain)[m] = data_array_chain[i][m];
					}
				}
			}
		}

		void display_hash_collisions()	//to display number of collisions
		{
			Node_chain* temp_coll = new Node_chain();
			
			for(int i = 0 ; i < usersizeofhashtable ; i ++)
			{
				if(hash_table[i] != NULL)
				{
					temp_coll=hash_table[i];

					while(temp_coll->next_chain != NULL)
					{
						temp_coll = temp_coll->next_chain;
						collisions_chain++;
					}
				}
			}
			
			cout<< "Number of Collisions: " << collisions_chain << endl;
		}

		void display_reads_chain() // display function to print linked list
		{
			Node_chain* temp01 = new Node_chain(); //pointer to traverse the linked list
		
			for(int i = 0 ; i < 10 ; i ++)
			{
				if(hash_table[i] != NULL)
				{
					temp01 = hash_table[i];
					while(temp01 ->  next_chain != NULL)
					{
  						cout << temp01 ->hash_dataStructure_chain << endl ;
  						temp01 = temp01->next_chain;
					}
				}
			}
		}

	   	void read_genomic_data_chain(string filepath3)	//Read in the Bacillus anthracis genome file
		{
			string input2_line2_chain;
			ifstream input2_chain;

            if(input2_chain.is_open()) //check whether file is open already
			{
				input2_chain.close(); // closing file
			}

			input2_chain.open(filepath3.c_str()); // initialize th file

			char temp_chain[16]; // to store 50 characters in a temp forlder

			char genome_character_chain = '\0';

			int count_chain = 0;
			int num_of_records_chain = 0;

			Node_chain* current;
			
			while(genome_character_chain != '\n')
			{
				input2_chain.get(genome_character_chain);	//avoid first line from file
			}

			while (input2_chain.get(genome_character_chain))
			{
  				if(genome_character_chain == 'A' || genome_character_chain == 'C' || genome_character_chain == 'G' || genome_character_chain == 'T' || genome_character_chain == 'N')
				{
  					
					temp_chain[count_chain] = genome_character_chain;
  					count_chain++;
				
  					if(count_chain == 16)
					{
						count_chain--;	//as we are counting from 0 to last will be 15

  						num_of_records_chain ++;
  						
  						Node_chain* new_node = new Node_chain;

						new_node ->hash_dataStructure_chain = new char[16];

  						for(int k = 0; k < 16; k++)
						{
			    			(new_node -> hash_dataStructure_chain)[k] = temp_chain[k];
						}

			    		(new_node -> hash_dataStructure_chain)[16] = '\0';

			    		new_node -> next_chain = NULL;

						count_chain = 0;
			    		
			    		if(num_of_records_chain == 1)
						{
			    			data_head_chain = new_node;
						}
						else
						{
							current -> next_chain = new_node;
						}

						current = new_node;
						
					}

					if(data_head_chain != NULL)
					{
						for(int i = 1; i < 16; i++)
						{
							temp_chain[i - 1] = temp_chain[i];
						}
					}
				}  
				// count =0;
			}         
			

			cout << "Total 16-character fragments: " << num_of_records_chain << endl;
			input2_chain.close();
		}
		
		void search_genomic_data_chain()
		{
			int cnt;
			Node_chain* current = data_head_chain;

			while(current->next_chain != NULL)
			{
				cnt++;
				current=current->next_chain;
			}

			unsigned int size = cnt;
			// unsigned int total,value,hashsize,fragment_present = 0;
			int power = 0;

			Node_chain* temp = data_head_chain;
			
			while (temp!=NULL)
			{
				
				total_chain = 0;
				power = 1;

				for (int i = 0; i < 16; i++)
				{
					
					if(hash_table[i] != NULL)
					{
						temp = hash_table[i];

						while(temp->next_chain != NULL)
						{ 
							if(hash_table[i]->header_chain == i)
							{
								fragment_present++;
 							 	temp = temp->next_chain;
							}
						}

					}
				}
				
			}
		
			cout << "Genome 16-mer fragments found in read set: " << fragment_present << endl;
			
		}

		void print_genomic_data_chain() //print the genome data linked list
		{

			Node_chain* current = data_head_chain;

			while(current != NULL)
			{
				cout << current -> hash_dataStructure_chain << "\n";
				current = current -> next_chain;
			}
		}
		
        void delete_data_structure_chain() // function to print deconstructor inilialisation 
        {
            cout << "\nDeconstructor Function executed !!!\n" << endl;
        }

		void deleteList_chain(Node_chain** head_ref) // function to delete entire linked list
        {
 
            Node_chain* current = *head_ref;
            Node_chain* next = NULL;
 
            while (current != NULL) 
            {
                next = current->next_chain;
                free(current);
                current = next;
            }
 
            *head_ref = NULL;

        }
		
		void delete_hash_table() // delete the hash table
		{
			for(int i=0;i<usersizeofhashtable;i++)
			{
				Node_chain* current = hash_table[i];
				Node_chain* temp = new Node_chain();
				
				while (current != NULL)
				{
					temp = current;
					free(temp);
					current = current->next_chain;
				}

				hash_table[i]= NULL;
			}
			cout << "Hash Table deleted successfully !!! "<< endl;

		}
   
        ~FASTAreadset_Chain() //destructor 
            {
                deleteList_chain(&head_chain);
				deleteList_chain(&data_head_chain);
				delete_hash_table();
			}       
};

#endif