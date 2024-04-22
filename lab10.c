#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct TrieNode {
    struct TrieNode *children[26];
    int count;
};

struct TrieNode *createTrieNode(){
    struct TrieNode *newNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (newNode){
        newNode->count = 0;
        for (int i = 0; i < 26; i++){
            newNode->children[i] = NULL;
        }
    }
    return newNode;
}

struct Trie {
    struct TrieNode *root;
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word){
    struct TrieNode *current = pTrie->root;
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]){
            current->children[index] = createTrieNode();
        }
        current = current->children[index];
    }
    current->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word){
    struct TrieNode *current = pTrie->root;
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (!current->children[index]) {
            return 0;
        }
        current = current->children[index];
    }
    return current->count;
}

// deallocate the trie structure
void deallocateTrie(struct TrieNode *node){
    if(node) {
        for (int i = 0; i < 26; i++){
            deallocateTrie(node->children[i]);
        }
        free(node);
    }
}

// Initializes a trie structure
struct Trie *createTrie(){
    struct Trie *pTrie = (struct Trie *)malloc(sizeof(struct Trie));
    if (pTrie){
        pTrie->root = createTrieNode();
    }
    return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords){
    FILE *file = fopen("dictionary.txt", "r");
    if (!file) {
        exit(1);
    }

    int count = 0;
    char word[100];

    fscanf(file, "%d", &count);

    while (fscanf(file, "%s", word) != EOF) {
        pInWords[count] = strdup(word);
        count++;
    }
    fclose(file);
    return count;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i = 0; i < numWords; ++i) {
		printf("%s\n", inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i = 0; i < numWords; i++) {
		insert(pTrie, inWords[i]);
	}
	
    // parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i = 0; i < 5; i++) {
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	
    deallocateTrie(pTrie->root);
	free(pTrie);
	return 0;
}