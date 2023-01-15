#ifndef QUIZ_UTILS_H_
#define QUIZ_UTILS_H_

#include <stdbool.h>
#include <stddef.h>

#define clrscr() printf("\e[1;1H\e[2J")

extern const char *categories[];
extern const char *difficulties[];

extern const size_t categoriesCount;
extern const size_t difficultiesCount;

struct qu_Question {
    char *question;
    char **options;
    int correctOption;
    int questionIndex;
};

typedef struct qu_Question qu_Question;

char *qu_getRawQuestion(const char *category, const char *difficulty, int questionsDone, int questionIndices[]);
qu_Question *qu_getRandomQuestion(const char *category, const char *difficulty, int questionsDone, int questionIndices[]);

bool gotoRowCol(int row, int column);

void printDividers(int width, int row);
void printTextCentered(int width, int row, char *text);
void printTextLeft(int width, int row, char *text);
void printTextRight(int width, int row, char *text);

#endif
