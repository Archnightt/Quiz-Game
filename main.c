#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quizutils.h"

#define clrscr() printf("\e[1;1H\e[2J")

const char *categories[] = {"computers", "sports"};
const char *difficulties[] = {"easy", "medium", "hard"};

char homePage() {
    int width = 71;

    clrscr();

    printDividers(width, 4);
    printTextCentered(width, 5, "Ultimate Quiz Game");
    printTextCentered(width, 6, "Made by the students of group G7");

    printDividers(width, 7);

    printTextLeft(width, 8, "Please choose a following option:");
    printTextLeft(width, 9, "");
    printTextLeft(width, 10, "> Press S to start the game.");
    printTextLeft(width, 11, "> Press H for help.");
    printTextLeft(width, 12, "> Press Q to quit the game.");
    printTextLeft(width, 13, "");

    printTextRight(width, 14, "Enjoy the game.");
    printDividers(width, 15);

    gotoRowCol(17, 4);
    printf("Enter your choice: ");

    return getch();
}

char questionPage(qu_Question *question) {
    clrscr();

    int length = strlen(question->question);
    int width = strlen(question->question) > 93 ? 99 : (length + 6 > 75 ? length + 6 : 75);

    printDividers(width, 4);

    printTextCentered(width, 5, "Question:");
    printDividers(width, 6);

    // Hard-wrap question if the question length exceeds the width.
    int excess = 0, pos = 0;
    while (pos < length) {
        char part[width - 4];
        strncpy(part, question->question + pos, width - 4);

        printTextLeft(width, excess + 7, part);

        excess++;
        pos += width - 4;
    }

    excess--;
    printTextLeft(width, excess + 8, "");
    printTextLeft(width, excess + 9, "Options: ");

    int i;
    for (i = 0; i < 4; i++) {
        char buf[100];
        snprintf(buf, sizeof(buf), "%c. %s", 65 + i, question->options[i]);
        printTextLeft(width, excess + i + 10, buf);
    }

    printDividers(width, excess + i + 10);

    gotoRowCol(excess + i + 12, 4);
    printf("Enter your choice: ");

    return getch();
}

int main(void) {
    // char selected = toupper(homePage());
    qu_Question *question = qu_getRandomQuestion(categories[0], difficulties[1]);
    char selected = toupper(questionPage(question));
    clrscr();
    printf("Option selected is: %c\n", selected);
    return 0;
}
