#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_NUM_WORDS 21
#define FILE_NAME "tagalogwords.txt"


bool guessing(const char* sagot, const char* angsagot) {
char clue[6] = {'_','_','_','_','_','\0'};

bool sagotFlags[5] = {false, false, false, false, false};

for(int i = 0; i < 5; i++){
    if(angsagot[i] == sagot[i]) {
        clue[i] = 'G';
        sagotFlags[i] = true;
    }
}
for (int i = 0; i < 51; i++ ) {
    if(clue[i] == '-') {
        for (int j = 0; j < 5; j++) {
            if(angsagot[i] == sagot[j] && !sagotFlags[j]) {
                clue[i] = 'Y';
                sagotFlags[j] = true;
                break;
            }
        }
    }
}
printf("%s\n", clue);
return strcmp(clue, "WWWWW") == 0;
}


int main() {

    char** wordlist = calloc(MAX_NUM_WORDS, sizeof(char*));
    int WordCount = 0;
    char* limaLetterWord = malloc(6* sizeof(char));
    FILE* wordsfile = fopen("mgasalita.txt", "r");
    while (fscanf(wordsfile, "%s",limaLetterWord) != EOF && WordCount < MAX_NUM_WORDS) {
        wordlist[WordCount] = limaLetterWord;
        WordCount++;
        limaLetterWord = malloc(6*sizeof(char));
    }
    fclose(wordsfile);
    //start screen
    srand(time(NULL));
    char* sagot = wordlist[rand()%WordCount];

    //guess loop
    int ilang_guess = 0;
    bool guessed_correctly = false;
    char* guess = malloc(6*sizeof(char));

    while(ilang_guess < 6 && !guessed_correctly) {
        printf("WELCOME TO TARDLE!");
        printf("PLEASE INPUT A 5 LETTER WORD GUESS (all caps):");
        scanf("%s", guess);
        printf("WORD GUESSED: %s\n", guess);
        ilang_guess += 1;

        guessed_correctly = guessing(sagot, guess);
    }
    if (guessed_correctly) {
        printf("Congratulations! You have completed today's tardle!\n");
        printf("Guessed in %d times", ilang_guess);
    } else {
        printf("Insufficient guess count. Word is %s\n", sagot);
    }
    for (int i = 0; i < WordCount; i++) {
        free(wordlist[i]);
    }
    free(wordlist);
    free(limaLetterWord);
    free(guess);
    return 0;
}
