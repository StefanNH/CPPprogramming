#include "bst.h"
#include <iostream>
#include <numeric>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

//function to turn every char into lower case
void ignoreCase(char* str)
{
	for(int i = 0; i < strlen(str); i++)
	{
		str[i] = tolower(str[i]);
	}
}

int main(int argc, char **argv)
{
	BinarySearchTree *dictionaryTree = new BinarySearchTree();
	char *token;
	char *token2;
	std::string strDictionary = "dictionary.txt";
	
	std::string fileName;
	cout << "Enter file name: ";
	cin >> fileName;
	
	//ifstream to save dictonary file into single string
	std::ifstream dictionaryStream(strDictionary);
	std::string data((std::istreambuf_iterator<char>(dictionaryStream)), 
		std::istreambuf_iterator<char>());
		
	//copying the string into char*
	char *buffC = new char[data.size() + 1];
	std::copy(data.begin(),data.end(), buffC);
	buffC[data.size()] = '\0';
	
	// toenizing the char* and inserting each token into binary search tree object
	token = strtok(buffC, " .,!?\n\t");
		while (token != NULL) 
		{
			ignoreCase(token);
			std::string insertToken(token);
			dictionaryTree->insert(insertToken);
		
			token = strtok(NULL, " .,!?\n\t");
		}
	
	/* second ifstream getting the file name as variable from cin
	and saving the content into single string
	*/
	std::ifstream inputStream(fileName);
	std::string inputData((std::istreambuf_iterator<char>(inputStream)), 
		std::istreambuf_iterator<char>());
	
	//copying the content of the string into char*
	char *inputBuff = new char[inputData.size() + 1];
	std::copy(inputData.begin(), inputData.end(), inputBuff);
	inputBuff[inputData.size()] = '\0';
	
	cout << "Misspelt words are: \n";
	
	// tokenazing the char* and checking if the tokens exist in the tree class
	// if not printing the token to the console
	token2 = strtok(inputBuff, " .,!?\n\t");
		while (token2 != NULL) 
		{
			ignoreCase(token2);
			std::string tokenCheck(token2);
			dictionaryTree->exists(tokenCheck);
			if(dictionaryTree->exists(tokenCheck) == false)
			{
				cout << tokenCheck << " ";
			}
			
			token2 = strtok(NULL, " .,!?\n\t");
		}
	
	//freeing any resources used
	delete[] inputBuff;
	delete[] buffC;
	delete dictionaryTree;
	return 0;
}