#include<stdio.h>

typedef struct node{
    char *entry;
    int count;
}node;

typedef struct hashtable{
    int capacity;
    int size;
    node **nodes;
}hashtable;

hashtable *createTable(int capacity);

hashtable *adjustLoadFactor(hashtable *hashtable);

node *createNode(char *word);

void deleteTable (hashtable *hashtable);

void deleteEntry (char *word, hashtable *hashtable);

hashtable *insert (char *word, hashtable *hashtable, int num);

int hashHelper(char *word, int capacity);

int hash(char *word, hashtable *hashtable);

int nextPrime(int num);

int primeHelper(int num);

int inTable(char *word, hashtable *hashtable);

int getCount(char *word, hashtable *hashtable);

char *getWord(char *word, hashtable *hashtable);
