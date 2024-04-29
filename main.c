#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// opens a file and counts all the words in it, assuming
// that each word has its own line and vice versa
int countWords(char *fileName, int maxLenOfWord){
	FILE* inFile;
	inFile = fopen(fileName, "r");

	int numOfWords = 0;
	char word[maxLenOfWord];

	while(fgets(word, maxLenOfWord, inFile)) {
		numOfWords++;
	}

	fclose(inFile);

	return numOfWords;
}

// receives a letter and returns the corresponding position in the list for countLetters()
int getPosition(char letter){
	int position = letter;

	if(position > 64 && position < 91){
		position -= 65;
	} else if(position > 96 && position < 123){
		position -= 97;
	} else {
		printf("word may only contain letters a-z and A-Z.\n");
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

	////////////////////////////////////////
	// read in the list of possible words //
	////////////////////////////////////////

	char *fileName = "words.txt";
	char word[maxLenOfWord];

	// to set the required array size, count the number of words
	int numOfWords = countWords(fileName, maxLenOfWord);
	char allWords[numOfWords][maxLenOfWord];

	// we later want to know how many of each letter a word has, so we put them in an array
	int allLetters[numOfWords][26];
	for(i=0;i<numOfWords;i++){
		for(j=0;j<26;j++){
			allLetters[i][j] = 0;
		}
	}

	// read in all the words
	FILE *inFile;
	inFile = fopen(fileName, "r");

	i=0;
	while(fgets(word, maxLenOfWord, inFile)){
		// save the word...
		word[ strlen( word ) - 1 ] = '\0';
		strcpy(allWords[i], word);

		// ... and count its letters
		countLetters(word, allLetters[i]);

		i++;
	}

	////////////////////////
	// get word from user //
	////////////////////////

	char userWord[maxLenOfWord];
	printf("Enter a word to find matching anagrams:\n");
	scanf("%s", userWord);

	// count letters in user word
	int userLetters[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	countLetters(userWord, userLetters);

	///////////////////////////////////////////
	// check if there are anagrams available //
	///////////////////////////////////////////

	printf("\n");
	bool foundSomething = false;

	for(i=0; i<numOfWords; i++){
		if (compareLetters(userLetters, allLetters[i])){
			if(foundSomething == true){
				printf(", %s", allWords[i]);
			} else {
				printf("Found anagram(s): %s", allWords[i]);
				foundSomething = true;
			}
		}
	}

	if (foundSomething == false){
		printf("No anagrams found.");
	}

	printf("\n");




	// finish
	printf("\nDone.\n");
	return 0;
}
