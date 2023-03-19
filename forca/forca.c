#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STR_SIZE 1024
#define ARRAY_BASE_SIZE 20

int allocate_word(char** word, char* aux_word){
    int word_size = strlen(aux_word);

    if ( !((*word)= malloc(sizeof(char)*word_size+1)) )
        return 0;

    strcpy((*word),aux_word);

    return 1;
}

void* realloc_word_array(void* array,int size, int max){
    return realloc(array, size*max);
}

int add_word_to_array(char** word_array[], char* aux_word, int* word_count, int* max_word_num){
    if( (*word_count) == (*max_word_num) ){
        (*max_word_num) = (*max_word_num)+ARRAY_BASE_SIZE;
        if(!((*word_array) = (char**)realloc_word_array((*word_array), sizeof(char*), *max_word_num)))
            return 0;
    }

    if (!allocate_word(&((*word_array)[(*word_count)]), aux_word))
        return 0;

    (*word_count)++;
    return 1;
}

int test_input(char* prompt, char* forca, char input){

    int forca_size = strlen(forca);
    int correct = 0;

    for (int i = 0; i < forca_size; i++)
        if (prompt[i] == input)
            if (forca[i]!= input){
                forca[i] = input;
                correct++;
            }
    return correct;
}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("Uso: %s <arquivo de palavras>\n", argv[0]);
        return 1;
    }

    int max_word_num = ARRAY_BASE_SIZE;
    char** word_array;
    char* file_name = argv[1];
    FILE* file;
    file = fopen(file_name, "r");

    if (!file){
        fprintf(stderr,"Erro ao abrir arquivo %s\n", file_name);
        return 1;
    }

    if ( !(word_array = malloc( sizeof(char*) * max_word_num)) ){
        fprintf(stderr,"Erro ao alocar vetor de palavras\n");
        return 1;
    }

    int word_count = 0;
    char aux_word[STR_SIZE];
    fscanf(file,"%[^\n]",aux_word);
    while (!feof(file)){

        if (!add_word_to_array(&word_array, aux_word, &word_count, &max_word_num)){
            fprintf(stderr,"Erro ao alocar palavra\n");
            return 1;
        }

        getc(file);
        fscanf(file,"%[^\n]",aux_word);
    }

    srand(clock());
    int ind = random()%word_count;
    int forca_size = strlen(word_array[ind]);
    char* forca;

    if ( !(forca = malloc(sizeof(char)*forca_size+1)) ){
        fprintf(stderr,"Erro ao alocar string da forca\n");
        return 1;
    }

    for (int i = 0; i < forca_size; i++)
        forca[i] = '_';
    forca[forca_size] = '\0';

    char input;
    int attempts = 0;
    int correct_letters = 0;
    //char aux_str[STR_SIZE];
    while( correct_letters < forca_size ){

        fflush(stdout);
        printf("\r%s    input:", forca);
        scanf(" %c", &input);
        //scanf("%s", aux_str);
        //input = aux_str[0];
        
        correct_letters += test_input(word_array[ind], forca, input);
        attempts++;

    }
    fflush(stdout);
    printf("\r================================================|\n");
    printf("%s\n", forca);
    printf("Numero de tentativas: %d                  \n", attempts);

    //deallocate variables
    free(forca);
    for (int i = 0; i < word_count; i++)
        free(word_array[i]);
    free(word_array);
    fclose(file);
    return 0;
}
