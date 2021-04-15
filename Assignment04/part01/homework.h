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

using namespace std;
     

//structure node function for linked list
struct Node 
{
    char dataStructure_LL[50];	//to store data
    char headercounter_LL[50];	//to store read head
	char dataStructure_LL_genome[70];	//to store genome data
	char headercounter_LL_genome[50];	//to store read head
    
	struct Node *next;
};

//main class 
class FASTAreadset_DA 
{
    private:
		
		char ** header_array; //an aray used for temp purpose
		char ** data_array; //an aray used for temp purpose
		char ** data_array_genome;
		unsigned int total,value,hashtablesize,collisions = 0;
		int num_of_reads; //to read the number of reads from user
        string file_path; // to store file name
        ifstream input; //used for file operations
		Node* head; // to create new node head
		Node* data_head; // to create new node for temporary purpose
		bool bool_array[20000];
		int ind; 
		double penalty=-3;
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
		
		int size_of_table(string file_path) //to count the size of the read dataset file
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

        void read_reads() // function to read number of reads from file	
        {
			
			int counter = size_of_table(file_path);
			
			cout << "Number Of Lines (reads): " << counter << endl;

			data_array = new char*[counter];
			header_array = new char*[counter];
			
						
			for(int i=0; i<counter/2; i++)
			{
				data_array[i] = new char[50];
				header_array[i] = new char[50];
			}

			
			Node * current_ll = new Node;	//temporary node

			char temp_input[50];	

			for(int i=0; i<counter/2; i++)
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

	   	void read_genomic_data(string filepath2)	//Read in the Bacillus anthracis genome
		{
			string input2_line2;
			ifstream input2;

            if(input2.is_open()) //check whether file is open already
			{
				input2.close(); // closing file
			}

			input2.open(filepath2.c_str()); // initialize thE file

			char temp[70]; // to store 50 characters in a temp forlder

			char genome_character = '\0';

			int count = 0;
			int num_of_records = 0;

			Node* current;
			
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

			cout << "Total 70-character fragments: " << num_of_records << endl;
			input2.close();
		}
	   
		void print_genomic_data() //print the genome data linked list
		{

			Node* current = data_head;

			while(current != NULL)
			{
				cout << current -> dataStructure_LL_genome << "\n";
				current = current -> next;
			}
		}

		double similarityScore(char a, char b)
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

		double findMax(double array[], int length)
		{
			double max = array[0];
			ind = 0;

			for(int i=1; i<length; i++)
			{
				if(array[i] > max)
				{
					max = array[i];
					ind=i;
				}
			}
			return max;
		}

		void SW_algorithm()
		{

			string seqA; // sequence A
			string seqB; // sequence B
			
			Node* temp_read = head; //pointer to traverse the linked list
			Node* temp_genome = data_head;

			while(temp_read != NULL)
			{
				seqA = temp_read -> dataStructure_LL;

				while(temp_genome != NULL)
				{
					// cout << temp_read -> dataStructure_LL << "\n";
					// cout << temp_genome -> dataStructure_LL_genome << "\n";
					
					
				
					
					seqB = temp_genome -> dataStructure_LL_genome;
					
					
					temp_genome = temp_genome -> next;

					// cout << seqA << endl;
					
					// cout << seqB << endl;
				
					
			

			
					// initialize some variables
					int lengthSeqA = seqA.length();
					int lengthSeqB = seqB.length();
					
					// initialize matrix
					double matrix[lengthSeqA+1][lengthSeqB+1];
					for(int i=0;i<=lengthSeqA;i++)
					{
						for(int j=0;j<=lengthSeqB;j++)
						{
							matrix[i][j]=0;
						}
					}

					double traceback[4];
					int I_i[lengthSeqA+1][lengthSeqB+1];
					int I_j[lengthSeqA+1][lengthSeqB+1];


					//start populating matrix
					for (int i=1;i<=lengthSeqA;i++)
					{
						for(int j=0;j<=lengthSeqB;j++)
						{
							// cout << i << " " << j << endl;
							traceback[0] = matrix[i-1][j-1]+similarityScore(seqA[i-1],seqB[j-1]);
							traceback[1] = matrix[i-1][j]+penalty;
							traceback[2] = matrix[i][j-1]+penalty;
							traceback[3] = 0;
							matrix[i][j] = findMax(traceback,4);
							switch(ind)
							{
								case 0:
									I_i[i][j] = i-1;
									I_j[i][j] = j-1;
									break;
								case 1:
									I_i[i][j] = i-1;
									I_j[i][j] = j;
									break;
								case 2:
									I_i[i][j] = i;
									I_j[i][j] = j-1;
									break;
								case 3:
									I_i[i][j] = i;
									I_j[i][j] = j;
									break;
							}
						}
					}

					// print the scoring matrix to console
					for(int i=1;i<lengthSeqA;i++)
					{
						for(int j=1;j<lengthSeqB;j++)
						{
							cout << matrix[i][j] << " ";
						}
						cout << endl;
					}

					// find the max score in the matrix
					double matrix_max = 0;
					int i_max=0, j_max=0;
					for(int i=1;i<lengthSeqA;i++)
					{
						for(int j=1;j<lengthSeqB;j++)
						{
							if(matrix[i][j]>matrix_max)
							{
								matrix_max = matrix[i][j];
								i_max=i;
								j_max=j;
							}
						}
					}
					// cout << i_max << endl;

					// cout << j_max << endl;

					cout << "Max score in the matrix is " << matrix_max << endl;

					// traceback
					
					int current_i=i_max,current_j=j_max; 

					int next_i=I_i[current_i][current_j];
					int next_j=I_j[current_i][current_j];

					// cout << next_i << endl;
					// cout << next_j << endl;
					
					int tick=0;
					// string data[lengthSeqA];
					char consensus_a[lengthSeqA+lengthSeqB+2],consensus_b[lengthSeqA+lengthSeqB+2];

					while(((current_i!=next_i) || (current_j!=next_j)) && (next_j!=0) && (next_i!=0))
					{

						if(next_i==current_i)
						{
							consensus_a[tick] = '_';                  // deletion in A	
							
						}  
						else
						{
							consensus_a[tick] = seqA[current_i -1];   // match/mismatch in A

						}
						if(next_j==current_j)  
						{
							consensus_b[tick] = '_';                  // deletion in B
						}
						else
						{
		                   consensus_b[tick] = seqB[current_j -1];   // match/mismatch in B
						}   

						current_i = next_i;
						current_j = next_j;
						next_i = I_i[current_i][current_j];
						next_j = I_j[current_i][current_j];
						tick++;
					}

					//print the consensus sequences
					cout<<endl<<" "<<endl;
					cout<<"Alignment:"<<endl<<endl;
					for(int i=0;i<lengthSeqA;i++){cout<<seqA[i];}; cout<<"  and"<<endl;
					for(int i=0;i<lengthSeqB;i++){cout<<seqB[i];}; cout<<endl<<endl;  
					for(int i=tick-1;i>=0;i--) cout<<consensus_a[i]; 
					cout<<endl;

					string markings[lengthSeqA+lengthSeqB+2];

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
					for(int i=tick-1;i>=0;i--) cout<<markings[i];
					cout<<endl;


					for(int j=tick-1;j>=0;j--) cout<<consensus_b[j];
					cout<<endl;
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

            }
        
};

#endif
