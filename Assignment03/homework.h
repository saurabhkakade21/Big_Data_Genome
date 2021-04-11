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
    char dataStructure_LL[16];	//to store data
    char headercounter_LL[16];	//to store read head
	struct Node *next;
};

//main class 
class FASTAreadset_DA
{
    private:
		
		char ** header_array; //an aray used for temp purpose
		char ** data_array; //an aray used for temp purpose
		unsigned int total,value,hashtablesize,collisions = 0;
		int num_of_reads; //to read the number of reads from user
        string file_path; // to store file name
        ifstream input; //used for file operations
		Node* head; // to create new node head
		Node* data_head; // to create new node for temporary purpose
		bool bool_array[4294967295];

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
		
		int size_of_table() //to count the size of the read dataset file
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
			
			int counter = size_of_table();
			
			cout << "Number Of Lines: " << counter << endl;

			data_array = new char*[counter];
			header_array = new char*[counter];
			
						
			for(int i=0; i<counter; i++)
			{
				data_array[i] = new char[16];
				header_array[i] = new char[16];
			}

			
			Node * current_ll = new Node;	//temporary node

			char temp_input[16];	

			for(int i=0; i<counter; i++)
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
			int counter = 0;
			
			while(temp != NULL)
			{
				cout << temp -> dataStructure_LL << "\n";
				temp = temp -> next;
			}

		}

		void radix_notation() //radix function to find hash function
		{
			unsigned int size = size_of_table();
			
			int power = 0;
			
			for (int i = 0; i < size; i++)
			{
				
				total = 0;
				power = 1;

				for (int j = 0; j < 16; j++)
				{
					
					//A==0, C==1, G==2, T==3

					if(data_array[i][j]=='A')
					{
						value = 0;
					}

					if(data_array[i][j]=='C')
					{
						value = 1;
					}
					
					if(data_array[i][j]=='G')
					{
						value = 2;
					}

					if(data_array[i][j]=='T')
					{
						value = 3;
					}

					total = total + (value * power);

					power = power * 4;

				}

				if(hashtablesize > total)
				{
					//do nothing
				}
				else
				{
					hashtablesize = total;
				}

				if(bool_array[total]==true)
				{
					collisions++;
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

			char temp[16]; // to store 50 characters in a temp forlder

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
				
  					if(count == 16)
					{
						count--;	//as we are counting from 0 to last will be 15

  						num_of_records++;
  						
  						Node* new_node = new Node;

  						for(int k = 0; k < 16; k++)
						{
			    			(new_node -> dataStructure_LL)[k] = temp[k];
						}

			    		(new_node -> dataStructure_LL)[16] = '\0';

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
						for(int i = 1; i < 16; i++)
						{
							temp[i - 1] = temp[i];
						}
					}
				}  
			}         

			cout << "Total 16-character fragments: " << num_of_records << endl;
			input2.close();
		}
	   
		void search_genomic_data() //to find fragments of read data set into genome data
		{
			
			unsigned int size = size_of_table();
			unsigned int total,value,hashsize,fragment_present = 0;
			int power = 0;

			Node* temp = data_head;
			
			while (temp!=NULL)
			{
				total = 0;
				power = 1;
				for (int j = 0; j < 16; j++)
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
				
				temp = temp -> next;

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
				}
				else
				{
					//do nothing
				}
				
			}

			cout << "Genome 16-mer fragments found in read set: " << fragment_present << endl;
			
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
   
        ~FASTAreadset_DA() //destructor
            {
                deleteList(&head);
				deleteList(&data_head);
				delete[] header_array;
				delete[] data_array;

            }
        
};

#endif
