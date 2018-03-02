#ifndef _TRIEH_
#include "list.h"

typedef struct trie{
	char key;
	struct trie* children;
	struct trie* neighbor;
	listNode* plist;
}trieNode_t;

void CreateTrie(trieNode_t **);
trieNode_t * CreateTrieNode(char);
void AddNode(trieNode_t **,char*);
void printNode(trieNode_t **root,char *key);
void length_trie();

#endif