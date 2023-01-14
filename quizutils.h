#ifndef QUIZ_UTILS_H_
#define QUIZ_UTILS_H_

#include <stdbool.h>

struct qu_Question {
    char *question;
    char **options;
    int correctOption;
};

typedef struct qu_Question qu_Question;

char *qu_getRawQuestion(const char *category, const char *difficulty);
qu_Question *qu_getRandomQuestion(const char *category, const char *difficulty);

bool gotoRowCol(int row, int column);

void printDividers(int width, int row);
void printTextCentered(int width, int row, char *text);
void printTextLeft(int width, int row, char *text);
void printTextRight(int width, int row, char *text);

#endif
