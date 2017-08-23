#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD 26
#define MAX_TEXT_LENGTH 100


typedef struct word {
char *str;
int freq;
struct word *pNext;
} Word;


int getNextWord(FILE *fp, char *buf, int bufsize);
void addWord(char *pWord);
void show(Word *pWordcounter);
Word* createWordCounter(char *word);


Word *pStart = NULL;

int totalcount = 0;
int uniquecount = 0;




int main () {

    /* File pointer */
    FILE * fp;
    /* Read text from here */
    fp = fopen("E:/test.txt","r");

    /* buf to hold the words */
    char buf[MAX_WORD];

    /* Size */
    int size = MAX_TEXT_LENGTH;


    /* Pointer to Word counter */
    Word *pCounter = NULL;


    /* Read all words from text file */

    while (getNextWord(fp, buf, size)) {

        /* Add the word to the list */
        addWord(buf);

        /* Increment the total words counter */
        totalcount++;
    }


    /* Loop through list and figure out the number of unique words */
    pCounter = pStart;
    while(pCounter != NULL)
    {
        uniquecount++;
        pCounter = pCounter->pNext;
    }

    /* Print Summary */

    printf("\nSUMMARY:\n\n");
    printf("   %d words\n", totalcount); /* Print total words */
    printf("   %d unique words\n", uniquecount); /* Print unique words */




    /* List the words and their counts */
    pCounter = pStart;
    while(pCounter != NULL)
    {
        show(pCounter);
        pCounter = pCounter->pNext;
    }
    printf("\n");


    /* Free the allocated  memory*/
    pCounter = pStart;
    while(pCounter != NULL)
    {
        free(pCounter->str);
        pStart = pCounter;
        pCounter = pCounter->pNext;
        free(pStart);
    }

    /* Close file */
    fclose(fp);

    return 0;

}

void show(Word *pWordcounter)
{
  /* output the word and it's count */
  printf("\n%-30s   %5d", pWordcounter->str,pWordcounter->freq);

}

void addWord(char *word)
{
  Word *pCounter = NULL;
  Word *pLast = NULL;

  if(pStart == NULL)
  {
    pStart = createWordCounter(word);
    return;
  }

  /* If the word is in the list, increment its count */
  pCounter = pStart;
  while(pCounter != NULL)
  {
    if(strcmp(word, pCounter->str) == 0)
    {
      ++pCounter->freq;

      return;
    }
    pLast = pCounter;
    pCounter = pCounter->pNext;
  }

  /* Word is not in the list, add it */
  pLast->pNext = createWordCounter(word);
}

Word* createWordCounter(char *word)
{
  Word *pCounter = NULL;
  pCounter = (Word*)malloc(sizeof(Word));
  pCounter->str = (char*)malloc(strlen(word)+1);
  strcpy(pCounter->str, word);
  pCounter->freq = 1;
  pCounter->pNext = NULL;
  return pCounter;
}

int getNextWord(FILE *fp, char *buf, int bufsize) {
    char *p = buf;
    char c;


    //skip all non-word characters
    do {
        c = fgetc(fp);
        if (c == EOF)
            return 0;
        } while (!isalpha(c));

    //read word chars

    do {
        if (p - buf < bufsize - 1)
        *p++ = tolower(c);
        c = fgetc(fp);
        } while (isalpha(c));

        //finalize word
        *p = '\0';
        return 1;
        }

