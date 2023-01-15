#ifndef QUIZ_PAGES_H_
#define QUIZ_PAGES_H

#include "quizutils.h"

char homePage();
int questionPage(qu_Question *question, int number, int total);
char helpPage();
int topicPage();
int difficultyPage();
bool answerPage(qu_Question *question, int choice);
void resultPage(int total, int correct);

#endif
