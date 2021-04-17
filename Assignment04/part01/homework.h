//Name: Saurabh Jawahar Kakade sk2354@nau.edu
//Assignment 03
//Large Scale Data Structures

#ifndef FASTA_H
#define FASTA_H

// header files
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctime>
#include <cstdlib>

using namespace std;
     

//structure node function for linked list
struct Node 
{
    char dataStructure_LL[50];	//to store data
    char headercounter_LL[50];	//to store read head
	char dataStructure_LL_genome[70];	//to store genome data
	char headercounter_LL_genome[50];	//to store genome head
	struct Node *next;
};

//main class 
class FASTAreadset_DA 
{
    private:
		
		char ** header_array; //an aray used for temp purpose
		char ** data_array; //an aray used for temp purpose
		char ** data_array_genome;// an array used to genome sequences
		char ** data_random_seq; // an array used to store random genomic squeries
		char ** queries_stack; // 
		
		unsigned int total,value,hashtablesize,collisions = 0; //common variables
		int num_of_reads; //to read the number of reads from user
        string file_path; // to store file name
        ifstream input; //used for file operations
		Node* head; // to create new node head
		Node* data_head; // to create new node for temporary purpose

		int index; //to store max value of Dij matrix
		double GAP_penalty=-3;
		double match = 2;
		double mismatch = -1;

    public:
        
        FASTAreadset_DA() //constructor
        {
            cout << "Constructor Function executed !!!" << endl;
			head = NULL;
			data_head = NULL;
        }    
        
        FASTAreadset_DA(string filepath)  //default constructor
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
		
		int size_of_table(string file_path) //to count the size of the read queries file
		{
			string input_line;
			int counter1 = 0;
			ifstream input;
			input.open(file_path.c_str()); 

			while(getline(input,input_line))
			{
				counter1++;
			} 

			return counter1;
		}

        void read_queries() // function to read number of reads from file	
        {
			
			int counter = size_of_table(file_path);
			cout << "Number Of Read Query Lines (reads): " << counter << endl;

			Node * current_ll = new Node;	//temporary node
			char temp_input[50]; //temp variable	
			
			for(int i=0; i<counter/2; i++)
			{
				Node * new_node = new Node;

				input >> new_node->headercounter_LL;		//read read sequence		
				input >> new_node->dataStructure_LL;		//read data sequence

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

		void display_read_queries() // display function to print linked list
		{
			Node* temp; //pointer to traverse the linked list
			temp = head;
			while(temp != NULL)
			{
				cout << temp -> dataStructure_LL << "\n";
				temp = temp -> next;
			}
		}

		void display_random_queries() // display function to print linked list
		{
			cout << "\nRandom genomic sequences: \n" << endl;
			display_read_queries();
		}

	   	void read_genomic_data(string filepath2)	//Read in the Bacillus anthracis genome
		{
			string input2_line2;
			ifstream input2;
			char temp[70]; // to store 70 characters in a temp folder
			char genome_character = '\0';
			int count = 0;
			int num_of_records = 0;
			Node* current;

            if(input2.is_open()) //check whether file is open already
			{
				input2.close(); // closing file
			}

			input2.open(filepath2.c_str()); // initialize thE file
			
			while(genome_character != '\n')
			{
				input2.get(genome_character);	//avoid first line from file
			}

			while (input2.get(genome_character))
			{
  				if(genome_character == 'A' || genome_character == 'C' || genome_character == 'G' || genome_character == 'T' || genome_character == 'N')
				{
  					
					temp[count] = genome_character;
  					count++;
				
  					if(count == 70)
					{
						count--;	//as we are counting from 0 to last will be 69

  						num_of_records++;
  						
  						Node* new_node = new Node;

  						for(int k = 0; k < 70; k++)
						{
			    			(new_node -> dataStructure_LL_genome)[k] = temp[k];
						}

			    		(new_node -> dataStructure_LL_genome)[70] = '\0';

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
						for(int i = 1; i < 70; i++)
						{
							temp[i - 1] = temp[i];
						}
					}
				}  
			}         

			cout << "\nTotal 70-character fragments: " << num_of_records << endl;
			input2.close();
		}
	   
		void print_genomic_data() //print the genome data linked list
		{
			cout<< "\n The genomic sequences are: " <<endl;

			Node* current = data_head;

			while(current != NULL)
			{
				cout << current -> dataStructure_LL_genome << "\n";
				current = current -> next;
			}
		}

		void random_seq_generator(int user_defined_values) // random sequence generator as per the user size of total queries.
		{
			
			Node * current_ll = new Node;
			
			srand(time(0));

			for (int i = 0; i < user_defined_values; i++)
			{
				Node * new_node = new Node;
				
				for (int j = 0; j < 50; j++)
				{
					int result = ( rand() % 4 );

					if(result==0)
					{
						new_node->dataStructure_LL[j] = 'A';
					}
					else if(result==1)
					{
						new_node->dataStructure_LL[j] = 'C';
					}
					else if(result==2)
					{
						new_node->dataStructure_LL[j] = 'G';
					}
					else if(result==3)
					{
						new_node->dataStructure_LL[j] = 'T';
					}

				}

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

		void SW_algorithm() //Smith Waterman Algorithm
		{

			string sequence_A; // sequence A
			string sequence_B; // sequence B
			
			Node* temp_read = head; //pointer to traverse the linked list
			Node* temp_genome = data_head;

			while(temp_read != NULL)
			{
				sequence_A = temp_read -> dataStructure_LL;

				while(temp_genome != NULL)
				{
				
					cout << "\n****************************************************\n" <<endl;
					
					sequence_B = temp_genome -> dataStructure_LL_genome;
					
					temp_genome = temp_genome -> next;
					
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
						}
					}

					double traceback_array[4];
					int I_i[length_of_sequence_A+1][length_of_sequence_B+1];
					int I_j[length_of_sequence_A+1][length_of_sequence_B+1];


					for (int i=1;i<=length_of_sequence_A;i++)
					{
						for(int j=0;j<=length_of_sequence_B;j++)
						{
							traceback_array[0] = matrix[i-1][j-1]+similarity_score_matrix(sequence_A[i-1],sequence_B[j-1]);
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

					cout << "\n****************************************************" <<endl;
					
				}
				temp_read = temp_read -> next;
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
   
        ~FASTAreadset_DA() //destructor
            {
                deleteList(&head);
				deleteList(&data_head);
				delete[] header_array;
				delete[] data_array;
				delete[] data_array_genome;
				delete[] data_random_seq;
            }
        
};

#endif
