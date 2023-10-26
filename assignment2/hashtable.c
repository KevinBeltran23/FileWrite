#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashtable.h"
/*ran out of time to comment :((*/


hashtable *createTable(int capacity){   
    hashtable *table;
    node **nodes;

    if(!(table = (hashtable*)malloc(sizeof(hashtable)))){
        perror("malloc");
        exit(EXIT_FAILURE);
    }   
    table -> capacity = capacity;
    table -> size = 0;
    
    if(!(nodes = (node**)calloc(capacity, sizeof(node*)))){
        perror("malloc");
        exit(EXIT_FAILURE);
    }   
    table -> nodes = nodes;
    return table;
}

node *createNode(char *word){
    node *newnode;
    if(!(newnode = (node*)malloc(sizeof(node)))){
        perror("malloc");
        exit(EXIT_FAILURE);
    }   

    if(!(newnode -> entry = (char*)malloc((strlen(word) + 1)*sizeof(char)))){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(newnode -> entry, word);
    newnode -> count = 1;
    return newnode;
}

int hashHelper(char *word, int capacity){
    int key, i;
    
    key = 0;
    for (i = 1; word[i] != '\0'; i++){
        key = (word[i] + 31*key) % capacity;
    }
    return key;
}

void deleteTable(hashtable *table){ 
    int i;

    for(i = 0; i < table -> capacity; i++){
        if(table -> nodes[i]){
            free(table -> nodes[i] -> entry);
            free(table -> nodes[i]);
        }
    }
    free(table -> nodes);
    free(table);
}

void deleteEntry(char *word, hashtable *table){
    int key;
    key = hash(word, table);  
    free(table -> nodes[key]);
    free(table -> nodes[key] -> entry);
}

hashtable *insert(char *word, hashtable *table, int num){
    int key;
    node *n;

    key = hash(word, table);
    n = createNode(word);
    
    /*key doesnt exist yet*/
    if (!(table -> nodes[key])){
        table -> nodes[key] = n;
        table -> nodes[key] -> count = num;
        table -> size += 1;
    }
    /*key exists*/
    else{
        table -> nodes[key] -> count += 1;
        free(n -> entry);
        free(n);
    }
    return adjustLoadFactor(table);   
}

int hash(char *word, hashtable *table){
    int collisions, key;

    key = hashHelper(word, table -> capacity);
    collisions = 1;

    while (table -> nodes[key] && strcmp(table -> nodes[key] -> entry, word)){
        key = (key + (collisions * collisions)) % (table -> capacity);
        collisions += 1;
    }
    return key;
}


int nextPrime(int num){
    if(num <= 1){
        return 2;
    }
    while(!primeHelper(num)){
        num += 1;
    }
    return num;
}

int primeHelper(int num){
    int i;
    if (num <= 1){
        return 0;
    }
    if (num <= 3){
        return 1;
    }
    if (((num % 2) == 0) || ((num % 3) == 0)){
        return 0;
    }
    for (i = 5; (i*i) <= num; i += 6){
        if ((num % i) == 0 || (num % (i + 2) == 0)){
            return 0;
        }
    }
    return 1;
}

int inTable(char *word, hashtable *table){
    int key;
    key = hash(word, table);
    if(table -> nodes[key]){
        if (table -> nodes[key] -> entry){
            return 1;
        }
    }
    return 0;
}

hashtable *adjustLoadFactor(hashtable *table){
    double loadlimit;
    double load;
    hashtable *newtable;
    int prime, i;

    loadlimit = 0.5;
    load = ((double)(table -> size)) / ((double)(table -> capacity));
    
    if (load >= loadlimit){
        prime = nextPrime(2 * (table -> capacity));
        newtable = createTable(prime);
        for(i = 0; i < table -> capacity; i++){
            if(table -> nodes[i]){
                insert(table -> nodes[i] -> entry, 
                newtable, table -> nodes[i] -> count);    
            }
        }
        deleteTable(table);
        return newtable;
    }
    return table;
}

char *getWord(char *word, hashtable *table){
    int key;
    key = hash(word, table);
    word = table -> nodes[key] -> entry;
    return word;
}

int getCount(char *word, hashtable *table){
    int key;
    key = hash(word, table);
    if (table -> nodes[key]){
        return table -> nodes[key] -> count;
    }
    return 0;
}

