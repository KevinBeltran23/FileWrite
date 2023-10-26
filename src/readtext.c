/*Kevin Beltran Monroy*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hashtable.h"

extern char *optarg;
int getopt(int arg, char *const[], const char*);
char *read_word(FILE *file);
int isalpha(int argument);
int tolower(int argument);

int main(int argc, char *argv[]){
    char *currentword = NULL;
    char *end;
    node *biggest;
    int i, n, k, num;
    FILE *infile;

    const int DEFAULT = 10;
    const int STDARGSIZE1 = 3;
    const int STDARGSIZE2 = 1;
    const int TABLESIZE = 11;
    const int NUMLOCATION = 2;
    const int NLOCATION = 1;

    /*
     * I tried to manually parse. Doing this fixes test #1 but breaks 2 more.
     * I figure functionality is more important
     *
    while ((o = getopt(argc, argv, "n: ") != -1)){
        if (o == 'n'){
            do nothing
            }
        else{   
            fprintf(stderr, "usage: fw [-n num] [file 1 [ file2 ...] ]");
            return 0;
        }
    }
    */
            
    /*initializes loop values and K user input*/
    if(argv[2]){
        /*
         * Doing this fixes test #2 but breaks 2 more.
         *
        if(!strcmp(argv[NLOCATION], "-n") 
        && (!isdigit(*argv[NUMLOCATION]) || *argv[NUMLOCATION] < 0)){
               fprintf(stderr, "usage: fw [-n num] [file 1 [ file2 ...] ]");
               exit(EXIT_FAILURE);
        }
        */
        else if (isdigit(*argv[2])){
            k = atoi(argv[2]);
            i = 3;
        }else{
            k = 10;
            i = 1;
        }
    }
    else{
        k = 10;
        i = 1;
    }
    hashtable *table = createTable(10);
    /* if using standard in*/
    if(argc == 1 || (argc == 1) 
    && !strcmp(argv[1], "-n") && isdigit(*argv[2])){
        infile = stdin;
        while(!feof(infile)){
            currentword = read_word(infile);
            if(isalpha(*currentword)){
                table = insert(currentword, table, 1);
            }
            free(currentword);
        }
    }
    /* if using file input */
    else{
        for (i; i < argc; i++){
            if(!(infile = (FILE*)fopen(argv[i], "r"))){
                /*do nothing if empty file*/
            }
            /*this will simply get the word*/
            else{ 
                while (!feof(infile)){
                    currentword = read_word(infile);
                    if(isalpha(*currentword)){
                        table = insert(currentword, table, 1);
                    }
                    free(currentword);
                }
                fclose(infile);
            }
        }
    }
    printf("The top %d words (out of %d) are:\n", k, table -> size);

    /*iterates user input times*/
    for(n = 0; (n < k) && (n < table -> size); n++){
        biggest = NULL;
        /*iterates through table to find next most common word*/
        for(i = 0; i < table -> capacity; i++){
            if(table -> nodes[i]){
                /*checks for biggest*/
                if(!biggest){
                    biggest = table -> nodes[i];
                }
                if(table -> nodes[i] -> count > biggest -> count){
                    biggest = table -> nodes[i];
                }  
                else if((table -> nodes[i] -> count > 0) 
                && (table -> nodes[i] -> count == biggest -> count)){
                    if(strcmp(table->nodes[i]->entry, biggest->entry)>0){
                        biggest = table -> nodes[i];
                    }
                } 
            }    
        }
        /*edgecase*/
        if (biggest -> count <= 0){
            break;
        }
        printf("%9d ", biggest -> count);
        printf(biggest -> entry);
        biggest -> count = 0;
        putchar('\n');
    }
    deleteTable(table);
    return 0;
}

/*returns a char pointer. Only alpha chars*/
char *read_word(FILE *infile){
    int c, counter, size;
    char *word = NULL;
    const int BLOCK = 10;

    size = 0;
    counter = 0;

    while ((c = fgetc(infile)) != EOF){
        if (counter >= size){
            size += BLOCK;
            if (!(word = (char*)realloc(word, (sizeof(char)*size)))){
                perror("malloc");
                exit(EXIT_FAILURE);
                }
            }
        if (!(isalpha(c))){
            break;
        }
        c = tolower(c);
        word[counter++] = c;
    }
    if(counter >= size){
        size += BLOCK;
        if(!(word = (char*)realloc(word, (sizeof(char)*size)))){
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }
    word[counter++] = '\0';
    return word;  
}
