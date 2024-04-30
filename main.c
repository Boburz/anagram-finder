#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// receives a letter and returns the corresponding position in the list for countLetters()
int getPosition(char letter){
	int position = letter;

	if(position > 64 && position < 91){
		position -= 65;
	} else if(position > 96 && position < 123){
		position -= 97;
	} else {
		printf("\n%c : word may only contain letters a-z and A-Z.\n", letter);
		position = 0;
	}

	return position;
}

// count all the letters in a given word and return a list with the number of hits for each letter
void countLetters(char *word, int *list){
	int i;

	for(i=0;i<strlen(word);i++){
		list[ getPosition(word[i]) ] += 1;
	}
}


bool compareLetters(int *word1, int *word2){
	int i;

	for(i=0;i<26;i++){
		if (word1[i] != word2[i]){
			return false;
		}
	}

	return true;
}

int main(){
	int i=0, j=0;
	int maxLenOfWord = 100;
	
	////////////////////////
	// get word from user //
	////////////////////////

	char userWord[maxLenOfWord];
	printf("Enter a word to find matching anagrams:\n");
	scanf("%s", userWord);

	// count letters in user word
	int userLetters[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	countLetters(userWord, userLetters);

	////////////////////////////////////////
	// read in the list of possible words //
	////////////////////////////////////////

	char *fileName = "words.txt";
	FILE *inFile;
	inFile = fopen(fileName, "r");
	
	char word[maxLenOfWord];
	int wordLetters[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	bool foundSomething = false; // turns true once we found our first anagram

	// check all the words in inFile for match with userWord
	while(fgets(word, maxLenOfWord, inFile)){
		// reset wordLetters to zeros
		for(i=0;i<26;i++){
			wordLetters[i] = 0;
		}
		word[ strlen( word ) - 1 ] = '\0';

		// count its letters ...
		countLetters(word, wordLetters);

		// ... and compare to userWord
		if (compareLetters(userLetters, wordLetters) == true){
			if(foundSomething == true){
				printf(", %s", word);
			} else {
				printf("\nFound anagram(s): %s", word);
				foundSomething = true;
			}
		}
	}

	// if no anagrams were found, say so
	if (foundSomething == false){
		printf("\nNo anagrams found.");
	}

	/////////////
	// the end //
	/////////////

	printf("\n\nDone.\n");
	return 0;
}
