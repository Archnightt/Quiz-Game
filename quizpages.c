#include "quizpages.h"

#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Print the home page of the quiz game to the command prompt.
 */
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

    return toupper(getch());
}

/**
 * Print the question page on the command prompt.
 *
 * @param question the question to print.
 */
char questionPage(qu_Question *question) {
    clrscr();

    int length = strlen(question->question);
    int width = strlen(question->question) > 93 ? 99 : (length + 6 > 75 ? ((length + 6) & 1 == 0 ? length + 7 : length + 6) : 75);

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

    char choice;
    do choice = toupper(getch());
    while (choice < 65 || choice > 68);

    return choice;
}

/**
 * Describe how to play the game to the user by printing the help page
 * on the command line.
 */
char helpPage() {
    clrscr();

    int width = 81;

    printDividers(width, 4);
    printTextCentered(width, 5, "Welcome to Ultimate Quiz Game");
    printDividers(width, 6);

    printTextCentered(width, 7, "In this quiz, you will be given a list of topics to choose from.");
    printTextCentered(width, 8, "Choose the topic and the difficulty level you want.");
    printTextLeft(width, 9, "");
    printTextCentered(width, 10, "Each question will be a multiple-choice question based on the topic and");
    printTextCentered(width, 11, "dificulty level you selected with only one correct answer.");
    printTextCentered(width, 12, "Select your answer carefully!");

    printTextLeft(width, 13, "");
    printTextRight(width, 14, "Best of luck!");
    printDividers(width, 15);

    gotoRowCol(17, 4);
    printf("Press any key to continue.");

    return toupper(getch());
}

/**
 * Prints the list of topics available in the quiz game on the command line.
 */
int topicPage() {
    clrscr();

    int width = 81;
    printDividers(width, 4);
    printTextCentered(width, 5, "Select the topic");
    printDividers(width, 6);
    printTextLeft(width, 7, "Please choose one of the following topics:");
    printTextLeft(width, 8, "");

    for (int i = 0; i < categoriesCount; i++) {
        char text[75];

        snprintf(text, sizeof(text), "%d. %s", i + 1, categories[i]);
        printTextLeft(width, i + 9, text);
    }

    printDividers(width, categoriesCount + 9);
    gotoRowCol(categoriesCount + 11, 4);

    printf("Enter the topic number you choose: ");
    int choice;
    scanf("%d", &choice);

    return choice;
}

/**
 * Prints the list of available difficulties in the quiz.
 */
int difficultyPage() {
    clrscr();

    int width = 81;
    printDividers(width, 4);
    printTextCentered(width, 5, "Select the difficulty");
    printDividers(width, 6);
    printTextLeft(width, 7, "Please choose one of the following difficulties:");
    printTextLeft(width, 8, "");

    for (int i = 0; i < difficultiesCount; i++) {
        char text[75];

        snprintf(text, sizeof(text), "%d. %s", i + 1, difficulties[i]);
        printTextLeft(width, i + 9, text);
    }

    printDividers(width, difficultiesCount + 9);
    gotoRowCol(difficultiesCount + 11, 4);

    printf("Enter the difficulty level: ");
    int choice;
    scanf("%d", &choice);

    return choice;
}
