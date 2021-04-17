//Name: Saurabh Jawahar Kakade sk2354@nau.edu
//Assignment 03
//Large Scale Data Structures


#ifndef FASTA_BLAST_H
#define FASTA_BLAST_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "homework.h"

using namespace std;
     

//structure node_BLAST function for linked list
struct Node_BLAST 
{
    char *hash_dataStructure_BLAST;		//to store data
    unsigned int header_BLAST;			//to store read head
	struct Node_BLAST *next_BLAST;
};

//main class 
class FASTAreadset_BLAST
{
    private:
		
		char ** header_array_BLAST; //an aray used for temp purpose
		char ** data_array_BLAST; //an aray used for temp purpose
		char ** queries_stack;

		unsigned int total_BLAST,value_BLAST,hashtablesize_BLAST,fragment_present,collisions_BLAST = 0;
		int usersizeofhashtable; //to read the number of reads from user

        string file_path_BLAST; // to store file name
        ifstream input_BLAST; //used for file operations

		Node_BLAST* head_BLAST; // to create new node head
		Node_BLAST* data_head_BLAST; // to create new node for temporary purpose
		bool bool_array_BLAST[2];
		char query_stack_array[40][11];

    public:

		Node_BLAST **hash_table;

        
        FASTAreadset_BLAST() //constructor
        {
            cout << "Constructor Function executed !!!" << endl;
			head_BLAST = NULL;
			data_head_BLAST = NULL;
        }    
        
        FASTAreadset_BLAST(string filepath)  //default constructor
        {
            file_path_BLAST = filepath;
			// usersizeofhashtable = user_sizeofhashtable;

            if(input_BLAST.is_open()) //check whether file is open already
			{
				input_BLAST.close(); // closing file
			}

			input_BLAST.open(file_path_BLAST.c_str()); 

			head_BLAST = NULL;
			data_head_BLAST = NULL;

        }
		
		int size_of_table_BLAST() //to count the size of the read dataset file
		{
			string input_line_BLAST;
			int counter1_BLAST = 0;
			ifstream input_BLAST;
			input_BLAST.open(file_path_BLAST.c_str()); 

					
			while(getline(input_BLAST,input_line_BLAST))
			{
				counter1_BLAST++;
			} 

			return counter1_BLAST;
		}

        void read_reads_BLAST() // function to read number of reads from read dataset
        {
            
			int counter_BLAST = size_of_table_BLAST();
			
			cout << "Number of lines in read dataset: " << counter_BLAST << endl;

			header_array_BLAST = new char*[counter_BLAST/2];
			data_array_BLAST = new char*[counter_BLAST/2];	

					

			for(int i=0;i<counter_BLAST/2;i++)
			{
				header_array_BLAST[i] = new char[50];
				data_array_BLAST[i] = new char[50];
				// query_stack_array[i] = new char[11];
			}


			char temp_input_BLAST[16];	

			for(int i=0;i<counter_BLAST/2;i++)
			{

				input_BLAST >> header_array_BLAST[i];		//read read sequence		
				input_BLAST >> data_array_BLAST[i];		//read data sequence

				// cout << data_array_BLAST[i]<<endl;

			}

			char query_seed = '\0';
			
			char temp[50];


			int demo;

			cout << "*********" << endl;
			cout << demo;

			cout << &demo << endl;

			cout << "*********" << endl;	
			
			



			for (int i = 0; i < 1; i++)
			{
				int count = 0;

				for (int m = 0; m < 41; m++)
				{
				
					for (int j = m; j <= (m + 11); j++)
					{

						query_seed = data_array_BLAST[i][j];	
						// query_stack_array[m][j] = data_array_BLAST[i][j];
						// cout << query_seed;
										
						
			  				if(query_seed == 'A' || query_seed == 'C' || query_seed == 'G' || query_seed == 'T')
							{
			  					
								temp[count] = query_seed;
								count++;
			  					


							
			  					if(count == 12)
								{

									for (int k = 0; k < 11; k++)
									{
										query_stack_array[m][k] = temp[k];
										// cout << temp[k];
									}
									// cout << endl;
									for (int k = 0; k < 11; k++)
									{
										// cout << query_stack_array[m][k];
										
									}
									cout << endl;
									count = 0;
									
								}
								
							}

					}
					// count = 0;
					// cout << query_stack_array[m];
					
					// cout << endl;
				}
				cout << endl;
				// query_stack_array = delete[];

			}
			
			
			
			


			input_BLAST.close(); //closing the file
			// queries_11mers();

        }

   //      void queries_11mers()
   //      {
   //      	queries_stack = new char*[39];

   //      	for (int i = 0; i < 39; i++)
			// {
			// 	queries_stack[i] = new char[11];
			// }
   //      	cout << "HELLO" << endl;

   //      }

		

		void hash_table_creation()	//to create hash table
		{
			
			hash_table =  new Node_BLAST*[usersizeofhashtable];
 			
			for(int i = 0 ; i < usersizeofhashtable ;i++)
			{
				hash_table[i] = NULL;
 			}

			unsigned int size_BLAST = size_of_table_BLAST();
			
			int power_BLAST = 0;

 			for(int i = 0; i < usersizeofhashtable ; i++)
			{
            	
				power_BLAST = 1;
			
				for (int j = 0; j < 16; j++)
				{
					
					//A==0, C==1, G==2, T==3

					if(data_array_BLAST[i][j]=='A')
					{
						value_BLAST = 0;
					}

					if(data_array_BLAST[i][j]=='C')
					{
						value_BLAST = 1;
					}
					
					if(data_array_BLAST[i][j]=='G')
					{
						value_BLAST = 2;
					}

					if(data_array_BLAST[i][j]=='T')
					{
						value_BLAST = 3;
					}

					total_BLAST = total_BLAST + (value_BLAST * power_BLAST);

					power_BLAST = power_BLAST * 4;

				}

				total_BLAST = total_BLAST % usersizeofhashtable;
				
				Node_BLAST *current = hash_table[total_BLAST];
				
             	Node_BLAST *temp_BLAST = NULL;
             	
				while (current != NULL)
				{
					temp_BLAST = current;
					current = current->next_BLAST;
				}

				if (current == NULL)
				{
					current = new Node_BLAST();
					current->header_BLAST = total_BLAST;
					current->hash_dataStructure_BLAST = new char[16];

					for(int k = 0 ; k < 16 ; k++)
					{
						current->hash_dataStructure_BLAST[k] = data_array_BLAST[i][k];
					}

					if (temp_BLAST == NULL)
					{
						hash_table[total_BLAST] = current;
					}

					else
					{
						temp_BLAST->next_BLAST = current;
					}

				}
				else
				{
					for(int m = 0 ; m < 16 ; m++)
					{
	                	(current->hash_dataStructure_BLAST)[m] = data_array_BLAST[i][m];
					}
				}
			}
		}

		void display_hash_collisions()	//to display number of collisions
		{
			Node_BLAST* temp_coll = new Node_BLAST();
			
			for(int i = 0 ; i < usersizeofhashtable ; i ++)
			{
				if(hash_table[i] != NULL)
				{
					temp_coll=hash_table[i];

					while(temp_coll->next_BLAST != NULL)
					{
						temp_coll = temp_coll->next_BLAST;
						collisions_BLAST++;
					}
				}
			}
			
			cout<< "Number of Collisions: " << collisions_BLAST << endl;
		}

		void display_reads_BLAST() // display function to print linked list
		{
			Node_BLAST* temp01 = new Node_BLAST(); //pointer to traverse the linked list
		
			for(int i = 0 ; i < 10 ; i ++)
			{
				if(hash_table[i] != NULL)
				{
					temp01 = hash_table[i];
					while(temp01 ->  next_BLAST != NULL)
					{
  						cout << temp01 ->hash_dataStructure_BLAST << endl ;
  						temp01 = temp01->next_BLAST;
					}
				}
			}
		}

	   	void read_genomic_data_BLAST(string filepath3)	//Read in the Bacillus anthracis genome file
		{
			string input2_line2_BLAST;
			ifstream input2_BLAST;

            if(input2_BLAST.is_open()) //check whether file is open already
			{
				input2_BLAST.close(); // closing file
			}

			input2_BLAST.open(filepath3.c_str()); // initialize th file

			char temp_BLAST[16]; // to store 50 characters in a temp forlder

			char genome_character_BLAST = '\0';

			int count_BLAST = 0;
			int num_of_records_BLAST = 0;

			Node_BLAST* current;
			
			while(genome_character_BLAST != '\n')
			{
				input2_BLAST.get(genome_character_BLAST);	//avoid first line from file
			}

			while (input2_BLAST.get(genome_character_BLAST))
			{
  				if(genome_character_BLAST == 'A' || genome_character_BLAST == 'C' || genome_character_BLAST == 'G' || genome_character_BLAST == 'T' || genome_character_BLAST == 'N')
				{
  					
					temp_BLAST[count_BLAST] = genome_character_BLAST;
  					count_BLAST++;
				
  					if(count_BLAST == 16)
					{
						count_BLAST--;	//as we are counting from 0 to last will be 15

  						num_of_records_BLAST ++;
  						
  						Node_BLAST* new_node = new Node_BLAST;

						new_node ->hash_dataStructure_BLAST = new char[16];

  						for(int k = 0; k < 16; k++)
						{
			    			(new_node -> hash_dataStructure_BLAST)[k] = temp_BLAST[k];
						}

			    		(new_node -> hash_dataStructure_BLAST)[16] = '\0';

			    		new_node -> next_BLAST = NULL;

						count_BLAST = 0;
			    		
			    		if(num_of_records_BLAST == 1)
						{
			    			data_head_BLAST = new_node;
						}
						else
						{
							current -> next_BLAST = new_node;
						}

						current = new_node;
						
					}

					if(data_head_BLAST != NULL)
					{
						for(int i = 1; i < 16; i++)
						{
							temp_BLAST[i - 1] = temp_BLAST[i];
						}
					}
				}  
				// count =0;
			}         
			

			cout << "Total 16-character fragments: " << num_of_records_BLAST << endl;
			input2_BLAST.close();
		}
		
		void search_genomic_data_BLAST()
		{
			int cnt;
			Node_BLAST* current = data_head_BLAST;

			while(current->next_BLAST != NULL)
			{
				cnt++;
				current=current->next_BLAST;
			}

			unsigned int size = cnt;
			// unsigned int total,value,hashsize,fragment_present = 0;
			int power = 0;

			Node_BLAST* temp = data_head_BLAST;
			
			while (temp!=NULL)
			{
				
				total_BLAST = 0;
				power = 1;

				for (int i = 0; i < 16; i++)
				{
					
					if(hash_table[i] != NULL)
					{
						temp = hash_table[i];

						while(temp->next_BLAST != NULL)
						{ 
							if(hash_table[i]->header_BLAST == i)
							{
								fragment_present++;
 							 	temp = temp->next_BLAST;
							}
						}

					}
				}
				
			}
		
			cout << "Genome 16-mer fragments found in read set: " << fragment_present << endl;
			
		}

		void print_genomic_data_BLAST() //print the genome data linked list
		{

			Node_BLAST* current = data_head_BLAST;

			while(current != NULL)
			{
				cout << current -> hash_dataStructure_BLAST << "\n";
				current = current -> next_BLAST;
			}
		}
		
        void delete_data_structure_BLAST() // function to print deconstructor inilialisation 
        {
            cout << "\nDeconstructor Function executed !!!\n" << endl;
        }

		void deleteList_BLAST(Node_BLAST** head_ref) // function to delete entire linked list
        {
 
            Node_BLAST* current = *head_ref;
            Node_BLAST* next = NULL;
 
            while (current != NULL) 
            {
                next = current->next_BLAST;
                free(current);
                current = next;
            }
 
            *head_ref = NULL;

        }
		
		void delete_hash_table() // delete the hash table
		{
			for(int i=0;i<usersizeofhashtable;i++)
			{
				Node_BLAST* current = hash_table[i];
				Node_BLAST* temp = new Node_BLAST();
				
				while (current != NULL)
				{
					temp = current;
					free(temp);
					current = current->next_BLAST;
				}

				hash_table[i]= NULL;
			}
			cout << "Hash Table deleted successfully !!! "<< endl;

		}
   
        ~FASTAreadset_BLAST() //destructor 
            {
                deleteList_BLAST(&head_BLAST);
				deleteList_BLAST(&data_head_BLAST);
				delete_hash_table();
				// delete[] query_stack_array;
			}       
};

#endif