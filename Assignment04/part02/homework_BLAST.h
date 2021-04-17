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

struct Node_blast 
{
    char dataStructure_LL[11];	//to store data
    char headercounter_LL[7];	//to store read head
	char dataStructure_LL_genome[11];	//to store genome data
	char headercounter_LL_genome[40];	//to store genome head
	struct Node_blast *next_BLAST;
};
     

//structure node_hash function for linked list
struct Node_Hash 
{
    char *hash_dataStructure_BLAST;		//to store data
    unsigned int header_BLAST;			//to store read head
	struct Node_Hash *next_hash;
};

//main class 
class FASTAreadset_BLAST
{
    private:
		
		char ** header_array_BLAST; //an aray used for temp purpose
		char ** data_array_BLAST; //an aray used for temp purpose
		char ** data_array_genome;// an array used to genome sequences
		char head_array_genome[38]; //to store head of genome
		char ** queries_stack;

		unsigned int total_BLAST,value_BLAST,hashtablesize_BLAST,fragment_present,collisions_BLAST = 0;
		int usersizeofhashtable; //to read the number of reads from user

        string file_path_BLAST; // to store file name
        ifstream input_BLAST; //used for file operations

        Node_blast* head_BLAST; // to create new node head
		Node_blast* data_head_BLAST; // to create new node for temporary purpose

		Node_Hash* head_hash; // to create new node head
		Node_Hash* data_head_hash; // to create new node for temporary purpose
		bool bool_array_BLAST[2];
		char query_stack_array[40][11];

    public:

		Node_Hash **hash_table;

        
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

			head_hash = NULL;
			data_head_hash = NULL;
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

        void read_queries_11mers() // function to read number of reads from file	
        {
			
			int counter_BLAST = size_of_table_BLAST();
			
			cout << "Number of lines in read query dataset: " << counter_BLAST << endl;

			header_array_BLAST = new char*[counter_BLAST/2];
			data_array_BLAST = new char*[counter_BLAST/2];	

			for(int i=0;i<counter_BLAST/2;i++)
			{
				header_array_BLAST[i] = new char[50];
				data_array_BLAST[i] = new char[50];
			}

			for(int i=0;i<counter_BLAST/2;i++)
			{

				input_BLAST >> header_array_BLAST[i];		//read read sequence		
				input_BLAST >> data_array_BLAST[i];		//read data sequence

			}

			char query_seed = '\0';
			
			char temp[50];

			int LL_counter_to_header = 0;

			Node_blast * current_ll_blast = new Node_blast;

			for (int i = 0; i < counter_BLAST/2; i++)
			{
				int count = 0;

				for (int m = 0; m < 41; m++)
				{
				
					for (int j = m; j <= (m + 11); j++)
					{
						Node_blast * new_node_blast = new Node_blast;

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
										(new_node_blast->dataStructure_LL)[k] = temp[k];
										// cout << temp[k];
									}
									// cout << endl;
									for (int k = 0; k < 11; k++)
									{
										// cout << query_stack_array[m][k];
										
									}
									new_node_blast->next_BLAST = NULL;

									if(current_ll_blast != NULL)
									{
										current_ll_blast->next_BLAST = new_node_blast;
									}

									current_ll_blast = new_node_blast;

									if(LL_counter_to_header == 0)
									{
										head_BLAST = new_node_blast;
									}
									LL_counter_to_header++;
									// cout << endl;
									count = 0;
									
								}
								
							}

					}
					// count = 0;
					// cout << query_stack_array[m];
					
					// cout << endl;
				}
				// cout << endl;
				// query_stack_array = delete[];

        	}
        }

        void display_read_queries_blast() // display function to print linked list
		{
			Node_blast* temp; //pointer to traverse the linked list
			temp = head_BLAST;
			while(temp != NULL)
			{
				cout << temp -> dataStructure_LL << "\n";
				temp = temp -> next_BLAST;
			}
		}
		

		void hash_table_creation()	//to create hash table
		{
			
			hash_table =  new Node_Hash*[usersizeofhashtable];
 			
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
				
				Node_Hash *current = hash_table[total_BLAST];
				
             	Node_Hash *temp_BLAST = NULL;
             	
				while (current != NULL)
				{
					temp_BLAST = current;
					current = current->next_hash;
				}

				if (current == NULL)
				{
					current = new Node_Hash();
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
						temp_BLAST->next_hash = current;
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
			Node_Hash* temp_coll = new Node_Hash();
			
			for(int i = 0 ; i < usersizeofhashtable ; i ++)
			{
				if(hash_table[i] != NULL)
				{
					temp_coll=hash_table[i];

					while(temp_coll->next_hash != NULL)
					{
						temp_coll = temp_coll->next_hash;
						collisions_BLAST++;
					}
				}
			}
			
			cout<< "Number of Collisions: " << collisions_BLAST << endl;
		}

		void display_reads_BLAST() // display function to print linked list
		{
			Node_Hash* temp01 = new Node_Hash(); //pointer to traverse the linked list
		
			for(int i = 0 ; i < 10 ; i ++)
			{
				if(hash_table[i] != NULL)
				{
					temp01 = hash_table[i];
					while(temp01 ->  next_hash != NULL)
					{
  						cout << temp01 ->hash_dataStructure_BLAST << endl ;
  						temp01 = temp01->next_hash;
					}
				}
			}
		}

		int size_of_table_genome_BLAST(string filepath_genome) //to count the size of the read dataset file
		{
			string input_line_BLAST;
			int counter1_BLAST = 0;
			ifstream input_BLAST;
			file_path_BLAST = filepath_genome;
			input_BLAST.open(file_path_BLAST.c_str()); 

			while(getline(input_BLAST,input_line_BLAST))
			{
				counter1_BLAST++;
			} 

			return counter1_BLAST;
		}

	   	void read_genome_11mers(string filepath2)	//Read in the Bacillus anthracis genome file
		{
			string input2_line2_BLAST;
			ifstream input2_BLAST;
			int counter_BLAST = size_of_table_genome_BLAST(filepath2);
			data_array_genome = new char * [counter_BLAST];
			
			cout << "Number of lines in read genome dataset: " << counter_BLAST << endl;


            if(input2_BLAST.is_open()) //check whether file is open already
			{
				input2_BLAST.close(); // closing file
			}

			input2_BLAST.open(filepath2.c_str()); // initialize th file

			// char genome_character_BLAST = '\0';

			// while(genome_character_BLAST != '\n')
			// {
			// 	input2_BLAST.get(genome_character_BLAST);	//avoid first line from file
			// }

			for (int i = 0; i < counter_BLAST-1; ++i)
			{
				data_array_genome[i] = new char[70];
			}

			input2_BLAST >> head_array_genome;
			
			for(int i=0;i<counter_BLAST-1;i++)
			{

				input2_BLAST >> data_array_genome[i];		//read data sequence

			}

			char query_seed = '\0';
			
			char temp[70];

			int LL_counter_to_header = 0;

			Node_blast * current_ll_blast = new Node_blast;

			for (int i = 0; i < counter_BLAST-1; i++)
			{
				int count = 0;

				for (int m = 0; m < 61; m++)
				{
				
					for (int j = m; j <= (m + 11); j++)
					{
						Node_blast * new_node_blast = new Node_blast;

						query_seed = data_array_genome[i][j];	
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
										(new_node_blast->dataStructure_LL_genome)[k] = temp[k];
										// cout << temp[k];
									}
									// cout << endl;
									for (int k = 0; k < 11; k++)
									{
										// cout << query_stack_array[m][k];
										
									}
									new_node_blast->next_BLAST = NULL;

									if(current_ll_blast != NULL)
									{
										current_ll_blast->next_BLAST = new_node_blast;
									}

									current_ll_blast = new_node_blast;

									if(LL_counter_to_header == 0)
									{
										data_head_BLAST = new_node_blast;
									}
									LL_counter_to_header++;
									// cout << endl;
									count = 0;
									
								}
								
							}

					}
					// count = 0;
					// cout << query_stack_array[m];
					
					// cout << endl;
				}
				// cout << endl;
				// query_stack_array = delete[];

        	}





			// while (input2_BLAST.get(genome_character_BLAST))
			// {
  	// 			if(genome_character_BLAST == 'A' || genome_character_BLAST == 'C' || genome_character_BLAST == 'G' || genome_character_BLAST == 'T' || genome_character_BLAST == 'N')
			// 	{
  					
			// 		temp_BLAST[count_BLAST] = genome_character_BLAST;
  	// 				count_BLAST++;
				
  	// 				if(count_BLAST == 12)
			// 		{
			// 			count_BLAST--;	//as we are counting from 0 to last will be 15

  	// 					num_of_records_BLAST ++;
  						
  	// 					Node_Hash* new_node = new Node_Hash;

			// 			new_node ->hash_dataStructure_BLAST = new char[16];

  	// 					for(int k = 0; k < 11; k++)
			// 			{
			//     			(new_node -> hash_dataStructure_BLAST)[k] = temp_BLAST[k];
			// 			}

			//     		(new_node -> hash_dataStructure_BLAST)[16] = '\0';

			//     		new_node -> next_BLAST = NULL;

			// 			count_BLAST = 0;
			    		
			//     		if(num_of_records_BLAST == 1)
			// 			{
			//     			data_head_BLAST = new_node;
			// 			}
			// 			else
			// 			{
			// 				current -> next_BLAST = new_node;
			// 			}

			// 			current = new_node;
						
			// 		}

			// 		if(data_head_BLAST != NULL)
			// 		{
			// 			for(int i = 1; i < 16; i++)
			// 			{
			// 				temp_BLAST[i - 1] = temp_BLAST[i];
			// 			}
			// 		}
			// 	}  
			// 	// count =0;
			// }         
			

			input2_BLAST.close();
		}
		
		void search_genomic_data_BLAST()
		{
			int cnt;
			Node_Hash* current = data_head_hash;

			while(current->next_hash != NULL)
			{
				cnt++;
				current=current->next_hash;
			}

			unsigned int size = cnt;
			// unsigned int total,value,hashsize,fragment_present = 0;
			int power = 0;

			Node_Hash* temp = data_head_hash;
			
			while (temp!=NULL)
			{
				
				total_BLAST = 0;
				power = 1;

				for (int i = 0; i < 16; i++)
				{
					
					if(hash_table[i] != NULL)
					{
						temp = hash_table[i];

						while(temp->next_hash != NULL)
						{ 
							if(hash_table[i]->header_BLAST == i)
							{
								fragment_present++;
 							 	temp = temp->next_hash;
							}
						}

					}
				}
				
			}
		
			cout << "Genome 16-mer fragments found in read set: " << fragment_present << endl;
			
		}

		void print_genomic_data_BLAST() //print the genome data linked list
		{

			Node_blast* current = data_head_BLAST;

			while(current != NULL)
			{
				cout << current -> dataStructure_LL_genome << "\n";
				current = current -> next_BLAST;
			}
		}
		
        void delete_data_structure_BLAST() // function to print deconstructor inilialisation 
        {
            cout << "\nDeconstructor Function executed !!!\n" << endl;
        }

		void deleteList_hash(Node_Hash** head_ref) // function to delete entire linked list
        {
 
            Node_Hash* current = *head_ref;
            Node_Hash* next_hash = NULL;
 
            while (current != NULL) 
            {
                next_hash = current->next_hash;
                free(current);
                current = next_hash;
            }
 
            *head_ref = NULL;

        }
        void deleteList_BLAST(Node_blast** head_ref) // function to delete entire linked list
        {
 
            Node_blast* current = *head_ref;
            Node_blast* next_BLAST = NULL;
 
            while (current != NULL) 
            {
                next_BLAST = current->next_BLAST;
                free(current);
                current = next_BLAST;
            }
 
            *head_ref = NULL;

        }
		
		void delete_hash_table() // delete the hash table
		{
			for(int i=0;i<usersizeofhashtable;i++)
			{
				Node_Hash* current = hash_table[i];
				Node_Hash* temp = new Node_Hash();
				
				while (current != NULL)
				{
					temp = current;
					free(temp);
					current = current->next_hash;
				}

				hash_table[i]= NULL;
			}
			cout << "Hash Table deleted successfully !!! "<< endl;

		}
   
        ~FASTAreadset_BLAST() //destructor 
            {
                deleteList_BLAST(&head_BLAST);
				deleteList_BLAST(&data_head_BLAST);
				deleteList_hash(&head_hash);
				deleteList_hash(&data_head_hash);



				delete_hash_table();
				// delete[] query_stack_array;
			}       
};

#endif