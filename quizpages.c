#include "quizpages.h"

#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char checkExit(char ch) {
    if (ch == 'Q' || ch == 'q') {
        clrscr();
        exit(0);
        return 0;
    }

    return ch;
}

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

    printTextRight(width, 14, "You can press Q anytime to exit the game.");
    printDividers(width, 15);

    gotoRowCol(17, 4);
    printf("Enter your choice: ");

    return checkExit(toupper(getch()));
}

/**
 * Print the question page on the command prompt.
 *
 * @param question the question to print.
 */
int questionPage(qu_Question *question, int number, int total) {
    clrscr();

    int length = strlen(question->question);
    int width = strlen(question->question) > 93 ? 99 : (length + 6 > 85 ? ((length + 6) & 1 == 0 ? length + 7 : length + 6) : 85);

    printDividers(width, 4);

    char buf[64];
    snprintf(buf, sizeof(buf), "Question (%d/%d):", number, total);
    printTextCentered(width, 5, buf);

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
    do choice = checkExit(toupper(getch()));
    while (choice < 65 || choice > 68);

    return choice - 65;
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

    return checkExit(toupper(getch()));
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

    choice--;
    if (choice < 0 || choice >= categoriesCount) {
        clrscr();

        int width = 61;
        printDividers(width, 4);
        printTextCentered(width, 5, "Topic Error");
        printDividers(width, 6);

        printTextCentered(width, 7, "Please make sure you enter a valid topic number.");
        printDividers(width, 8);

        gotoRowCol(10, 4);
        printf("Press any key to continue.");

        fflush(stdin);
        checkExit(getch());
        return topicPage();
    }

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

    choice--;
    if (choice < 0 || choice >= difficultiesCount) {
        clrscr();

        int width = 61;
        printDividers(width, 4);
        printTextCentered(width, 5, "Difficulty Error");
        printDividers(width, 6);

        printTextCentered(width, 7, "Please make sure you enter a valid difficulty number.");
        printDividers(width, 8);

        gotoRowCol(10, 4);
        printf("Press any key to continue.");

        fflush(stdin);
        checkExit(getch());
        return difficultyPage();
    }

    return choice;
}

/**
 * Check if the answer the user selected was correct or not.
 *
 * @param question the question presented to the user.
 * @param choice the answer that the user selected.
 */
bool answerPage(qu_Question *question, int choice) {
    clrscr();

    int width = 61;
    printDividers(width, 4);

    if (choice == question->correctOption)
        printTextCentered(width, 5, "Correct Answer!");
    else
        printTextCentered(width, 5, "Incorrect Answer!");

    printDividers(width, 6);

    gotoRowCol(8, 4);
    printf("Press any key to continue.");

    checkExit(getch());
    return choice == question->correctOption;
}

/**
 * Prints the result of the quiz to the user.
 *
 * @param total the total questions presented to the user.
 * @param correct the number of correct questions answered.
 */
void resultPage(int total, int correct) {
    clrscr();

    int width = 75;
    char text[70];

    printDividers(width, 4);
    printTextCentered(width, 5, "Result of the quiz");
    printDividers(width, 6);

    printTextCentered(width, 7, "Thanks for playing the Ultimate Quiz Game!");
    printTextLeft(width, 8, "");

    snprintf(text, sizeof(text), "Total Questions: %d", total);
    printTextLeft(width, 9, text);

    snprintf(text, sizeof(text), "Correct Answers: %d", correct);
    printTextLeft(width, 10, text);

    snprintf(text, sizeof(text), "Incorrect Answers: %d", total - correct);
    printTextLeft(width, 11, text);

    printDividers(width, 12);

    gotoRowCol(14, 4);
    printf("Press Q to quit or any key to continue.");

    checkExit(getch());
}
