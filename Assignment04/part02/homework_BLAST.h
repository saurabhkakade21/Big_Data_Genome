//Name: Saurabh Jawahar Kakade sk2354@nau.edu
//Assignment 03
//Large Scale Data Structures


#ifndef FASTA_BLAST_H
#define FASTA_BLAST_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <cstring>

#include <math.h>
#include "homework.h"

using namespace std;

struct Node_blast 
{
    char dataStructure_LL[11];	//to store data
    char headercounter_LL[7];	//to store read head
    char dataStructure_LL_random[50];
	char dataStructure_LL_genome[11];	//to store genome data
	char headercounter_LL_genome[40];	//to store genome head
	char *hash_dataStructure;		//to store data
    unsigned int header_Hash;
	struct Node_blast *next_BLAST;
};
     

//structure node_hash function for linked list
// struct Node_Hash 
// {
//     char *hash_dataStructure;		//to store data
//     unsigned int header_Hash;			//to store read head
// 	struct Node_Hash *next_hash;
// };

//main class 
class FASTAreadset_BLAST
{
    private:
		
		char ** header_array_BLAST; //an aray used for temp purpose
		char ** data_array_BLAST; //an aray used for temp purpose
		char ** data_array_genome;// an array used to genome sequences
		char head_array_genome[38]; //to store head of genome
		char ** queries_stack;

		unsigned int total = 0;
		unsigned int power = 0;
		unsigned int value_BLAST = 0;
		unsigned int value = 0;
		unsigned int hashtablesize = 0;
		unsigned int fragment_present = 0;
		unsigned int collisions_BLAST = 0;
		unsigned int total_BLAST = 0;
		unsigned int collisions = 0;
		int usersizeofhashtable; //to read the number of reads from user
		int index; //to store max value of Dij matrix
		double GAP_penalty=-3;
		double match = 2;
		double mismatch = -1;
		// bool bool_array[4294967295];
		bool bool_array[4200000]; //size of hash table 4194271

        string file_path_BLAST; // to store file name
        string file_path_BLAST_02; // to store file name
        
        ifstream input_BLAST; //used for file operations

        Node_blast* head_BLAST; // to create new node head
		Node_blast* data_head_BLAST; // to create new node for temporary purpose

// 		bool bool_array_BLAST[2];
		char query_stack_array[40][11];

    public:

		Node_blast **hash_table;

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
        
        double similarity_score_matrix(char a, char b)
		{
		     
			double result;
			if(a==b)
			{
				result=match;
			}
			else
			{
				result=mismatch;
			}
			return result;
		}

		double find_max_Dij(double array[], int length)
		{
			double max = array[0];
			index = 0;

			for(int i=1; i<length; i++)
			{
				if(array[i] > max)
				{
					max = array[i];
					index=i;
				}
			}
			return max;
		}

		void SW_algorithm(string query, string genome) //Smith Waterman Algorithm
		{

			string sequence_A; // sequence A
			string sequence_B; // sequence B
			
		
				sequence_A = query;

				sequence_B = genome;
					
					
					cout<<"Sequence 01 and Sequence 02: \n"<<endl;
					cout << sequence_A << endl;
					cout << sequence_B << endl;
			
					int length_of_sequence_A = sequence_A.length();
					int length_of_sequence_B = sequence_B.length();
					double matrix[length_of_sequence_A+1][length_of_sequence_B+1];

					for(int i=0;i<=length_of_sequence_A;i++)
					{
						for(int j=0;j<=length_of_sequence_B;j++)
						{
							matrix[i][j]=0;
				// 			cout << matrix[i][j];
						}
				// 		cout << endl;
					}
					

					double traceback_array[4];
					int I_i[length_of_sequence_A+1][length_of_sequence_B+1];
					int I_j[length_of_sequence_A+1][length_of_sequence_B+1];


                    
					for (int i=1;i<=length_of_sequence_A;i++)
					{
						for(int j=0;j<=length_of_sequence_B;j++)
						{
						   
							traceback_array[0] = matrix[i-1][j-1] + similarity_score_matrix(sequence_A[i-1],sequence_B[j]);
				// 			cout << "hello" << endl;
							traceback_array[1] = matrix[i-1][j]+GAP_penalty;
							traceback_array[2] = matrix[i][j-1]+GAP_penalty;
							traceback_array[3] = 0;
							matrix[i][j] = find_max_Dij(traceback_array,4);
							
							//value of index changes from find_max_Dij function
							if(index==0)
							{							
								I_i[i][j] = i-1;
								I_j[i][j] = j-1;
							}
							else if(index==1)
							{	
								I_i[i][j] = i-1;
								I_j[i][j] = j;
							}
							else if(index==2)
							{
								I_i[i][j] = i;
								I_j[i][j] = j-1;
							}
							else if(index==3)
							{
								I_i[i][j] = i;
								I_j[i][j] = j;
							}
							
						}
					}
					cout<<endl;
					// cout << "Print the scoring matrix to console: \n" << endl;

					// print the scoring matrix to console
						// for(int i=1;i<length_of_sequence_A;i++)
						// {
						// 	for(int j=1;j<length_of_sequence_B;j++)
						// 	{
						// 		cout << matrix[i][j] << " ";
						// 	}
						// 	cout << endl;
						// }

					// find the max score in the matrix
					double matrix_max = 0;
					int i_max=0, j_max=0;
					for(int i=1;i<length_of_sequence_A;i++)
					{
						for(int j=1;j<length_of_sequence_B;j++)
						{
							if(matrix[i][j]>matrix_max)
							{
								matrix_max = matrix[i][j];
								i_max=i;
								j_max=j;
							}
						}
					}

					cout << "Max score in the matrix is: " << matrix_max << endl;

					// traceback_array
					
					int current_i=i_max,current_j=j_max; 

					int next_i = I_i[current_i][current_j];
					int next_j = I_j[current_i][current_j];

					int tick=0;

					char consensus_a[length_of_sequence_A + length_of_sequence_B + 2];
					char consensus_b[length_of_sequence_A + length_of_sequence_B + 2];

					while(((current_i!=next_i) || (current_j!=next_j)) && (next_j!=0) && (next_i!=0))
					{

						if(next_i==current_i)
						{
							consensus_a[tick] = '_';                  	
							
						}  
						else
						{
							consensus_a[tick] = sequence_A[current_i - 1]; 

						}
						if(next_j==current_j)  
						{
							consensus_b[tick] = '_';                 
						}
						else
						{
		                   consensus_b[tick] = sequence_B[current_j - 1]; 
						}   

						current_i = next_i;
						current_j = next_j;
						next_i = I_i[current_i][current_j];
						next_j = I_j[current_i][current_j];
						tick++;
					}

					cout<<"\nAlignment of sequence 01 and sequence 02: (traceback_array)\n"<<endl;

					for(int i=tick-1;i>=0;i--) cout<<consensus_a[i]; cout<<endl;

					string markings[length_of_sequence_A+length_of_sequence_B+2];

					for(int i=tick-1;i>=0;i--)
					{
						if(consensus_a[i]==consensus_b[i])
						{
							markings[i]="|";
						}
						else if (consensus_a[i]== '_' || consensus_b[i] == '_')
						{
							markings[i]=" ";
						}
						else if (consensus_a[i] != consensus_b[i])
						{
							markings[i]="x";
						}
						
					}
					for(int i=tick-1;i>=0;i--) cout<<markings[i]; cout<<endl;


					for(int j=tick-1;j>=0;j--) cout<<consensus_b[j]; cout<<endl;

				// 	cout << "\n****************************************************" <<endl;
					
				
				
// 			return matrix_max;	
			
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
								// 	for (int k = 0; k < 11; k++)
								// 	{
								// 		// cout << query_stack_array[m][k];
										
								// 	}
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

		int radix_notation(string filepath02) //radix function to find hash function
		{
			unsigned int size = size_of_table_genome_BLAST(filepath02);

			int power = 0;
			int demo_counter = 0;
			

			Node_blast* current = data_head_BLAST;

			while(current != NULL)
			{
		
				total = 0;
				power = 1;

					for (int j = 0; j < 11; j++)
					{
					
						//A==0, C==1, G==2, T==3 values for radix calculations

						// cout << (current -> dataStructure_LL_genome)[0] << endl;

						if((current -> dataStructure_LL_genome)[j]=='A')
						{
							value = 0;
						}

						if((current -> dataStructure_LL_genome)[j]=='C')
						{
							value = 1;
						}
						
						if((current -> dataStructure_LL_genome)[j]=='G')
						{
							value = 2;
						}

						if((current -> dataStructure_LL_genome)[j]=='T')
						{
							value = 3;
						}

						total = total + (value * power);

						power = power * 4;

					}
					
				// 	cout << current -> dataStructure_LL_genome << endl;
				// 	cout << demo_counter << endl;
                    // demo_counter++;    

					current = current -> next_BLAST;


					if(hashtablesize > total)
					{
						//do nothing
					}
					else
					{
						hashtablesize = total;
				// 		cout << hashtablesize << endl;
					}



					if(bool_array[total]==true)
					{
						collisions++;
						// cout << "hello" << endl;

					}
					else
					{
						bool_array[total]=true;

					}

			}

			
					
			
			int unique_seq = 0;

			for(int i = 0; i < hashtablesize; i++)
			{
				
				if(bool_array[i] == true)
				{
					unique_seq++;
				}
			}
			
			cout << "Size of HASH table :" << hashtablesize << endl;
			cout << "Collisions :" << collisions << endl;
			cout << "Number of UNIQUE sequences: " << unique_seq<< endl;
			return hashtablesize;
		}
	
		int size_of_table_genome_BLAST(string filepath_genome) //to count the size of the read dataset file
		{
			string input_line_BLAST;
			int counter1_BLAST = 0;
			ifstream input_BLAST;
			file_path_BLAST_02 = filepath_genome;
			input_BLAST.open(file_path_BLAST_02.c_str()); 

			while(getline(input_BLAST,input_line_BLAST))
			{
				counter1_BLAST++;
			} 

			return counter1_BLAST;
		}

	   	void read_genome_11mers(string filepath2)	
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
								// 	for (int k = 0; k < 11; k++)
								// 	{
								// 		// cout << query_stack_array[m][k];
										
								// 	}
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
			input2_BLAST.close();
		}
		
		void hash_table_creation(string filepath2)	//to create hash table
		{
		    
		    int hashtablevalue_return = radix_notation(filepath2);
			
			hash_table =  new Node_blast*[hashtablevalue_return]; //size is calculated from highest radix value
 			
			for(int i = 0 ; i < hashtablevalue_return ;i++)
			{
				hash_table[i] = NULL;
 			}

			Node_blast* current = data_head_BLAST;

     		while(current != NULL)
			{
		
				total = 0;
				power = 1;
				// 	cout << (current -> dataStructure_LL_genome) << endl;

					for (int j = 0; j < 11; j++)
					{
					
						//A==0, C==1, G==2, T==3 values for radix calculations

				// 		cout << (current -> dataStructure_LL_genome)[0] << endl;

						if((current -> dataStructure_LL_genome)[j]=='A')
						{
							value = 0;
						}

						if((current -> dataStructure_LL_genome)[j]=='C')
						{
							value = 1;
						}
						
						if((current -> dataStructure_LL_genome)[j]=='G')
						{
							value = 2;
						}

						if((current -> dataStructure_LL_genome)[j]=='T')
						{
							value = 3;
						}

						total = total + (value * power);

						power = power * 4;

					}
					
				// 	cout << total << endl;
					
					
					
				// total = total % hashtablevalue_return;
				
				Node_blast *current02 = hash_table[total];
				
             	Node_blast *temp_chain = NULL;
             	
				while (current02 != NULL)
				{
					temp_chain = current02;
				// 	cout << temp_chain;
					current02 = current02->next_BLAST;
				}

				if (current02 == NULL)
				{
					current02 = new Node_blast();
					current02->header_Hash = total;
					current02->hash_dataStructure = new char[11];
					
				// 	cout << "hello" << endl;

					for(int k = 0 ; k < 11 ; k++)
					{
						current02->hash_dataStructure[k] = (current -> dataStructure_LL_genome)[k];
						
				// 		cout << current->dataStructure_LL_genome[k];
					}
				// 	cout << endl;

					if (temp_chain == NULL)
					{
						hash_table[total] = current02;
					}

					else
					{
						temp_chain->next_BLAST = current02;
					}

				}
				else
				{
					for(int m = 0 ; m < 11 ; m++)
					{
	                	(current02->hash_dataStructure)[m] = current -> dataStructure_LL_genome[m];
					}
				}
				// cout << current02->hash_dataStructure << endl;
				current = current -> next_BLAST;
			}
			
// 			for(int i = 0 ; i < hashtablevalue_return ;i++)
// 			{
// 			    if(hash_table[i] != 0)
// 			    {
// 			        cout << hash_table[i] <<endl;
// 			    }
				
//  			}
			
			
		}
		
		void search_query_seed_in_hashtable(string filepath2)
		{
			unsigned int size = size_of_table_BLAST();
			int counter_BLAST = size_of_table_genome_BLAST(filepath2);
			unsigned int total,value,hashsize,fragment_present = 0;
			int power = 0;
			char sequence_from_hashtable_genome[70];

			Node_blast* temp = head_BLAST;
			
			while (temp!=NULL)
			{
				total = 0;
				power = 1;
				for (int j = 0; j < 11; j++)
				{
					
					//A==0, C==1, G==2, T==3

					if(temp->dataStructure_LL[j]=='A')
					{
						value = 0;
					}

					if(temp->dataStructure_LL[j]=='C')
					{
						value = 1;
					}
					
					if(temp->dataStructure_LL[j]=='G')
					{
						value = 2;
					}

					if(temp->dataStructure_LL[j]=='T')
					{
						value = 3;
					}

					total = total + (value * power);

					power = power * 4;

				}
				
				

				if(hashsize > total)
				{
					//do nothing
				}
				else
				{
					hashsize = total;
				}
				
				
				

				if(bool_array[total]==true)
				{
					fragment_present++;
					
					Node_blast* current02 = hash_table[total];
				// 	dataseq[50];
					
				// 	Node_blast* temp02 = data_head;
					
					char dataseq[50];
					int counter = 0;
					int val = 1;
					while(current02 != NULL)
					{
    					
    					if(strcmp(temp -> dataStructure_LL, current02 -> hash_dataStructure)==0)
    					{
    					   // cout << temp -> dataStructure_LL << "....."<< current02 -> hash_dataStructure <<endl;
    					    
    					    for(int l = 0; l< 11 ; l++)
    					    {
    					        dataseq[l] = (temp -> dataStructure_LL)[l];
    					       // cout << "***********"<<dataseq[l];
    					    }
    					    cout << endl;
    					    Node_blast* current03 = data_head_BLAST;
    					    
    					    while(current03 != NULL)
    					    {
    					        if(strcmp(temp -> dataStructure_LL, current03 -> dataStructure_LL_genome)==0)
    					        {
    					            
    					           // for(int t = 0; t < (50-11);t++)
    					           // {
    					                for(int z = 11; z < 50; z++)
    					                {
    					                    current03 = current03 -> next_BLAST;
    					                    dataseq[z] = (current03 -> dataStructure_LL_genome)[0];
    					                    
    					                   // cout << dataseq[z];
    					                }
    					                cout << endl;
    					           // }
    					        
    					        }
    					        current03 = current03 -> next_BLAST;
    					    }
    					    
    					   // cout << temp -> dataStructure_LL << "..." << dataseq << endl;
    					   // SW_algorithm(temp -> dataStructure_LL, dataseq);
    					   
    					   
    					        
    					        
    					    
    					}   
    				// 	cout << "....."<< current02 -> hash_dataStructure << endl;
    					
    					current02 = current02->next_BLAST;
    					
    					
					}
					 SW_algorithm(temp -> dataStructure_LL, dataseq);
        				
				}
				else
				{
					//do nothing
				}
				temp = temp -> next_BLAST;
				
			}
			
			
			

			cout << "Query 11-mer fragments found in genome set: " << fragment_present << endl;
		}
		
		void random_seq_generator(int user_defined_values) // random sequence generator as per the user size of total queries.
		{
			
			Node_blast * current_ll = new Node_blast;
			
			srand(time(0));

			for (int i = 0; i < user_defined_values; i++)
			{
				Node_blast * new_node = new Node_blast;
				
				for (int j = 0; j < 50; j++)
				{
					int result = ( rand() % 4 );

					if(result==0)
					{
						new_node->dataStructure_LL_random[j] = 'A';
					}
					else if(result==1)
					{
						new_node->dataStructure_LL_random[j] = 'C';
					}
					else if(result==2)
					{
						new_node->dataStructure_LL_random[j] = 'G';
					}
					else if(result==3)
					{
						new_node->dataStructure_LL_random[j] = 'T';
					}

				}
				
				// cout << new_node->dataStructure_LL_random << endl;

				new_node->next_BLAST = NULL;

				if(current_ll != NULL)
				{
					current_ll->next_BLAST = new_node;
				}

				current_ll = new_node;

				if(i == 0)
				{
					head_BLAST = new_node;
				}

			}
		}
		
		void search_random_query_seed_in_hashtable(string filepath2)
		{
			unsigned int size = size_of_table_BLAST();
			int counter_BLAST = size_of_table_genome_BLAST(filepath2);
			unsigned int total,value,hashsize,fragment_present = 0;
			int power = 0;
			char sequence_from_hashtable_genome[70];

			Node_blast* temp = data_head_BLAST;
			Node_blast* temp_random = head_BLAST;
			int counter_random = 0;
			char dataseq[50];
			
			
			while (temp_random!=NULL)
			{
			    
			    	while (temp!=NULL)
			        {
			            for(int l = 0; l< 11 ; l++)
					    {
					        dataseq[l] = (temp -> dataStructure_LL_genome)[l];
					       // cout << "***********"<<dataseq[l];
					    }
    					 for(int z = 11; z < 50; z++)
		                {
		                    temp = temp -> next_BLAST;
		                    dataseq[z] = (temp -> dataStructure_LL_genome)[0];
		                    
		                   
		                }
		                cout << "\nRandom sequence index number: " << counter_random << endl;
					    
				
			            SW_algorithm(temp_random -> dataStructure_LL_random, dataseq);
    			
				        temp = temp -> next_BLAST;
				        counter_random++;
			        }
			        
			        
			        
				        temp_random = temp_random -> next_BLAST;
				
			}
			
			
			

			cout << "Query 11-mer fragments found in genome set: " << fragment_present << endl;
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

		void deleteList_hash(Node_blast** head_ref) // function to delete entire linked list
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
				Node_blast* current = hash_table[i];
				Node_blast* temp = new Node_blast();
				
				while (current != NULL)
				{
					temp = current;
					free(temp);
					current = current->next_BLAST;
				}

				hash_table[i]= NULL;
			}
// 			cout << "Hash Table deleted successfully !!! "<< endl;

		}
   
        ~FASTAreadset_BLAST() //destructor 
            {
                deleteList_BLAST(&head_BLAST);
				deleteList_BLAST(&data_head_BLAST);
				// deleteList_hash(&head_hash);
				// deleteList_hash(&data_head_hash);



				delete_hash_table();
				// delete[] query_stack_array;
			}       
};

#endif