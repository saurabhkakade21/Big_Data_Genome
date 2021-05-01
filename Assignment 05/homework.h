//Name: Saurabh Jawahar Kakade sk2354@nau.edu
//Assignment 05
//Large Scale Data Structures

#ifndef FASTA_P_TRIE
#define FASTA_P_TRIE

#include <iostream>
#include <fstream>
#include <time.h> 
#include <math.h>
#include <cmath>
#include <sys/time.h>
#include <cstdlib>

#define GENOME_TOTAL_SIZE_OF_CHAR 29906	//this value is the total number of genome character present in the data. 

using namespace std;

struct Node_Main 	//linked list for genomic sequences
{
	char genome_sequence[36];
	Node_Main* next_node;
};

struct Node_Trie 	//linked list for trie
{
	Node_Trie* A;
	Node_Trie* C;
	Node_Trie* G;
	Node_Trie* T;
};

class prefix_trie
{

	private:
		
		Node_Trie* Node_Root;	//initializing root node

	public: 
	
	prefix_trie()	//Default constructor
	{
		Node_Root = new Node_Trie;
		Node_Root -> A = NULL;
		Node_Root -> C = NULL;
		Node_Root -> G = NULL;
		Node_Root -> T = NULL;
	}
	
	prefix_trie(Node_Main* read_dataset) 	//Custom constructor
	{
		Node_Root = new Node_Trie;

		Node_Root -> A = NULL;
		Node_Root -> C = NULL;
		Node_Root -> G = NULL;
		Node_Root -> T = NULL;

		build_Prefix_Trie(read_dataset);
	}
	
	
	prefix_trie(const prefix_trie &const_obj) 	//Copy Constructor
	{
		cout << "\nCopy Constructor initialized !!!"<<endl;

		Node_Root = new Node_Trie;
		Node_Trie* current_node;
		Node_Trie* current_Node_Trie;

		Node_Trie** stack_Main = new Node_Trie*[GENOME_TOTAL_SIZE_OF_CHAR];
		Node_Trie** stack_Data_Trie = new Node_Trie*[GENOME_TOTAL_SIZE_OF_CHAR];

		int top_of_stack = -1;
		
		stack_Main[++top_of_stack] = const_obj.Node_Root;
		stack_Data_Trie[top_of_stack] = Node_Root;

		while(top_of_stack > -1)
		{
			current_node = stack_Main[top_of_stack];
			current_Node_Trie = stack_Data_Trie[top_of_stack];

			top_of_stack--;
			
			if(current_node->A != NULL)
			{
				stack_Main[++top_of_stack] = current_node->A;
				Node_Trie* Node_Main = new Node_Trie;
				Node_Main->A = NULL; 
				Node_Main->C = NULL;
				Node_Main->G = NULL;
				Node_Main->T = NULL;
				current_Node_Trie->A = Node_Main;
				stack_Data_Trie[top_of_stack] = current_Node_Trie->A;
			}

			if(current_node->C != NULL)
			{
				stack_Main[++top_of_stack] = current_node->C;
				Node_Trie* Node_Main = new Node_Trie;
				Node_Main->A = NULL; 
				Node_Main->C = NULL;
				Node_Main->G = NULL;
				Node_Main->T = NULL;
				current_Node_Trie->C = Node_Main;
				stack_Data_Trie[top_of_stack] = current_Node_Trie->C;
			}

			if(current_node->G != NULL)
			{
				stack_Main[++top_of_stack] = current_node->G;
				Node_Trie* Node_Main = new Node_Trie;
				Node_Main->A = NULL; 
				Node_Main->C = NULL;
				Node_Main->G = NULL;
				Node_Main->T = NULL;
				current_Node_Trie->G = Node_Main;
				stack_Data_Trie[top_of_stack] = current_Node_Trie->G;
			}

			if(current_node->T != NULL)
			{
				stack_Main[++top_of_stack] = current_node->T;
				Node_Trie* Node_Main = new Node_Trie;
				Node_Main->A = NULL; 
				Node_Main->C = NULL;
				Node_Main->G = NULL;
				Node_Main->T = NULL;
				current_Node_Trie->T = Node_Main;
				stack_Data_Trie[top_of_stack] = current_Node_Trie->T;
			}

		}

		cout << "Copy Construction Completed !!!"<<endl;	
	}
		
	int build_Prefix_Trie(Node_Main* read_dataset)
	{
		int count = 0;
		int value = 0;
		char genome_char;

		Node_Trie* current_node;
		
		while(read_dataset != NULL)
		{
			current_node = Node_Root;
			count = 0;

			genome_char = (read_dataset -> genome_sequence)[count];

			while(genome_char != '\0')
			{
				if(genome_char == 'A')
				{
					if(current_node -> A == NULL)
					{
						Node_Trie* temp_node = new Node_Trie;
						temp_node -> A = NULL;
						temp_node -> C = NULL;
						temp_node -> G = NULL;
						temp_node -> T = NULL;
						current_node -> A = temp_node;
						current_node = temp_node;
						value++;
					}
					else
					{
						current_node = current_node -> A;
					}
				}
				else if(genome_char == 'C')
				{
					if(current_node -> C == NULL)
					{
						Node_Trie* temp_node = new Node_Trie;
						temp_node -> A = NULL;
						temp_node -> C = NULL;
						temp_node -> G = NULL;
						temp_node -> T = NULL;
						current_node -> C = temp_node;
						current_node = temp_node;
						value++;
					}
					else
					{
						current_node = current_node -> C;
					}
					
				}
				else if(genome_char == 'G')
				{
					if(current_node -> G == NULL)
					{
						Node_Trie* temp_node = new Node_Trie;
						temp_node -> A = NULL;
						temp_node -> C = NULL;
						temp_node -> G = NULL;
						temp_node -> T = NULL;
						current_node -> G = temp_node;
						current_node = temp_node;
						value++;
					}
					else
					{
						current_node = current_node -> G;
					}
					
				}
				else if(genome_char == 'T')
				{
					if(current_node -> T == NULL)
					{
						Node_Trie* temp_node = new Node_Trie;
						temp_node -> A = NULL;
						temp_node -> C = NULL;
						temp_node -> G = NULL;
						temp_node -> T = NULL;
						current_node -> T = temp_node;
						current_node = temp_node;
						value++;
					}
					else
					{
						current_node = current_node -> T;
					}
				}
				count++;
				genome_char = (read_dataset -> genome_sequence)[count];		
			}
			read_dataset = read_dataset -> next_node;
		}
		return value;
	}	
	
	bool Traverse_Trie(char* genome_sequence)
	{
		char current_node;
		int count = 0;
		current_node = genome_sequence[count];
		int mismatch = 1;
		Node_Trie* temp_node = Node_Root;
		bool genome_present = false;
		
		while(current_node != '\0')
		{
			if(current_node == 'A')
			{
				if(temp_node -> A != NULL)
				{
					temp_node = temp_node -> A;	
				}
				else
				{
					break;
				}
			}
			else if(current_node == 'C')
			{
				if(temp_node -> C != NULL)
				{
					temp_node = temp_node -> C;	
				}
				else
				{
					break;
				}
			}
			else if(current_node == 'G')
			{
				if(temp_node -> G != NULL)
				{
					temp_node = temp_node -> G;	
				}
				else
				{
					break;
				}
			}
			else if(current_node == 'T')
			{
				if(temp_node -> T != NULL)
				{
					temp_node = temp_node -> T;	
				}
				else
				{
					break;
				}
			}
			current_node = genome_sequence[++count];
		}
		
		if(current_node == '\0')
		{
			genome_present = true;
		}
		else
		{
			count++;
			if(temp_node -> A != NULL)
			{
				genome_present = Traverse_Branch(genome_sequence, count, temp_node -> A);
			}
			if(!genome_present && temp_node -> C != NULL)
			{
				genome_present = Traverse_Branch(genome_sequence, count, temp_node -> C);
			}
			if(!genome_present && temp_node -> G != NULL)
			{
				genome_present = Traverse_Branch(genome_sequence, count, temp_node -> G);
			}
			if(!genome_present && temp_node -> T != NULL)
			{
				genome_present = Traverse_Branch(genome_sequence, count, temp_node -> T);
			}
		}
		return genome_present;
	}
	
	bool Traverse_Branch(char* genome_sequence, int start, Node_Trie* temp_node)
	{
		bool result = true;

		char current_node = genome_sequence[start];
		
		while(current_node != '\0' && temp_node != NULL)
		{
			if(current_node == 'A')
			{
				temp_node = temp_node -> A;
			}
			else if(current_node == 'C')
			{
				temp_node = temp_node -> C;
			}
			else if(current_node == 'G')
			{
				temp_node = temp_node -> G;
			}
			else if(current_node == 'T')
			{
				temp_node = temp_node -> T;
			}
			current_node = genome_sequence[++start];
		}
		if(current_node != '\0')
		{
			result = false;
		}
		return result;
	}
	
	void Random_Fragments(char* filepath01, int number, int error)
	{
		ifstream input01;
		char genome_char;
		int size = 36;
		int total_char_in_genome = 0;
		int counter = 0;
		int start = 0;
		int value;
		int random;

		Node_Main* head_Main = NULL;
		Node_Main* temp_node = NULL;
		
		if(input01.is_open())
		{
			input01.close();
		}
		
		input01.open(filepath01);
		
		while(input01.get(genome_char))
		{
			if(genome_char == 'A' || genome_char == 'C' || genome_char == 'G' || genome_char == 'T')
			{
				
				total_char_in_genome++;
			}
		}	

		char genome_array[total_char_in_genome];

		if(input01.is_open())
		{
			input01.close();
		}
		
		input01.open(filepath01);
		
		while(input01.get(genome_char))
		{
			if(genome_char == 'A' || genome_char == 'C' || genome_char == 'G' || genome_char == 'T')
			{
				genome_array[counter] = genome_char;
				counter++;
			}
		}	
		
		for(int i = 0; i < number; i++)
		{
			start = rand() % (total_char_in_genome - size + 1);

			Node_Main* Node_Main_temp = new Node_Main;
			
			for(int j = 0; j < size; j++)
			{
				Node_Main_temp->genome_sequence[j] = genome_array[start + j];		
				
				if(error == 5)
				{
					random = rand() % 100;
					
					if(random < 5)
					{
						if(Node_Main_temp->genome_sequence[j] == 'A')
						{
							Node_Main_temp->genome_sequence[j] = 'A';
						}
						else if(Node_Main_temp->genome_sequence[j] == 'C')
						{
							Node_Main_temp->genome_sequence[j] = 'G';
						}
						else if(Node_Main_temp->genome_sequence[j] == 'G')
						{
							Node_Main_temp->genome_sequence[j] = 'C';
						}
						else if(Node_Main_temp->genome_sequence[j] == 'T')
						{
							Node_Main_temp->genome_sequence[j] = 'T';
						}
					}	
				}
			}

			Node_Main_temp->genome_sequence[36] = '\0';
			Node_Main_temp->next_node = NULL;
			
			if(i == 0)
			{
				head_Main = Node_Main_temp;
			}
			else
			{
				temp_node->next_node = Node_Main_temp;
			}
			temp_node = Node_Main_temp;
		}
		value = build_Prefix_Trie(head_Main);
		cout << "Number of Prefix Trie Nodes are: " << value << endl;
	}

	void Search_Trie(char* filepath01)
	{
		ifstream input01;
		char c;
		char genome[GENOME_TOTAL_SIZE_OF_CHAR];
		int index = 0;
		char genome_sequence[36];
		int matches=0;
		
		if(input01.is_open())
		{
			input01.close();
		}
		
		input01.open(filepath01);
		
		while(input01.get(c) && index < GENOME_TOTAL_SIZE_OF_CHAR)
		{
			if(c == 'A' || c == 'C' || c == 'G' || c == 'T')
			{
				genome[index] = c;
				index++;
			}
		}	
		for(int i = 0; i < (GENOME_TOTAL_SIZE_OF_CHAR - 36); i++)
		{
			for(int j = 0; j < 36; j++)
			{
				genome_sequence[j] = genome[i + j];
			}	
			genome_sequence[36] = '\0';
			if(Traverse_Trie(genome_sequence))
			{
				matches++;
			}	
		}
		cout << "Total matches found are: " << matches << endl;
	}

	
	~prefix_trie()	//destructor
	{
			
		Node_Trie* temp_node;
		Node_Trie* A;
		Node_Trie* C;
		Node_Trie* G;
		Node_Trie* T;
		
		Node_Trie** stack = new Node_Trie*[GENOME_TOTAL_SIZE_OF_CHAR];
		int top_of_stack = -1;
		stack[++top_of_stack] = Node_Root;
		
		while(top_of_stack >= 0)
		{
			temp_node = stack[top_of_stack];
			top_of_stack--;
			if(temp_node->A != NULL)
			{
				stack[++top_of_stack] = temp_node->A;
			}
			if(temp_node->C != NULL)
			{
				stack[++top_of_stack] = temp_node->C;
			}
			if(temp_node->G != NULL)
			{
				stack[++top_of_stack] = temp_node->G;
			}
			if(temp_node->T != NULL)
			{
				stack[++top_of_stack] = temp_node->T;
			}
			delete temp_node;
		}
		
		cout << "Successfully de-allocated the memory used for Trie!! "<<endl;	
	
	}
	
};

#endif