#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    struct Trie *children[26];
    int isEndOfWord;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;
    
    // Traverse through each character of the word
    for (int i = 0; i < strlen(word); i++)
    {

    if (word[i] < 'a' || word[i] > 'z') {
        return;
    }

        int index = word[i] - 'a';
        
        // Create a new node if the path doesn't exist
        if (current->children[index] == NULL)
        {
            current->children[index] = (struct Trie *)malloc(sizeof(struct Trie));
            current->children[index]->isEndOfWord = 0;
            
            // Initialize all children pointers to NULL
            for (int j = 0; j < 26; j++)
            {
                current->children[index]->children[j] = NULL;
            }
        }
        
        // Move to the next node
        current = current->children[index];
    }
    
    // Mark the last node as the end of the word
    current->isEndOfWord += 1;
}

// computes the number of occurrences of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    struct Trie *current = pTrie;
    
    // Traverse through each character of the word
    for (int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';
        
        // If the path doesn't exist, the word doesn't exist in the trie
        if (current->children[index] == NULL)
        {
            return 0;
        }
        
        // Move to the next node
        current = current->children[index];
    }
    
    // If this is the end of a word, return the count
    if (current->isEndOfWord > 0)
        return current->isEndOfWord;

    return 0; // If the word is not found, return 0

    // If the last node is marked as the end of a word, the word exists in the trie
    if (current->isEndOfWord)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    if (pTrie == NULL) {
        return NULL;
    }
    
    // Recursively deallocate all children nodes
    for (int i = 0; i < 26; i++) {
        if (pTrie->children[i] != NULL) {
            pTrie->children[i] = deallocateTrie(pTrie->children[i]);
        }
    }
    
    // Free the current node
    free(pTrie);
    
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *root = (struct Trie *)malloc(sizeof(struct Trie));
    root->isEndOfWord = 0;
    
    // Initialize all children pointers to NULL
    for (int i = 0; i < 26; i++)
    {
        root->children[i] = NULL;
    }
    
    return root;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 0;
    }
    
    int numWords = 0;
    char word[256];
    
    while (fgets(word, sizeof(word), file)) {
        // Remove newline character from the word5
        word[strcspn(word, "\n")] = '\0';
        
        // Allocate memory for the word and copy it
        pInWords[numWords] = (char *)malloc(strlen(word) + 1);
        strcpy(pInWords[numWords], word);
        
        numWords++;
    }
    
    fclose(file);
    
    return numWords;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}