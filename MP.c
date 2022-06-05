#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define MAX_ENTRY 150
#define BOX_CAP 100

/*COLORS DEFINED*/
#define RESET -1

#define WHITE 15
#define BLACK 0

#define RED 9
#define BLUE 12

#define GREEN 2
#define DARK_GREEN 22
#define LIGHT_GREEN 10

#define PINK 199
#define CYAN 86

/*ARROW KEYS DEFINED*/
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

/*ENTER KEY DEFINED*/
#define ENTER 13

/*UI (ascii symbol) DEFINED*/
#define TRIANGLE 30     // ▲
#define I_TRIANGLE 31   // ▼
#define L_TRIANGLE 17   // ◄
#define R_TRIANGLE 16   // ►

#define HORLINE 196     // ─
#define D_HORLINE 205   // ═
#define VERLINE 179     // │
#define D_VERLINE 186   // ║

#define UL_LINE 218     // ┌
#define UL_DLINE 201    // ╔
#define UR_LINE 191     // ┐
#define UR_DLINE 187    // ╗

#define L_SELECTOR 175  // »

typedef struct ENTRY{
    char name[12];
    char shortName[6];
    char desc[301];
    char gender[8];
    char caught[4];
} Entry;

void colorChange(int foreground, int background)
{
    if (foreground != -1 || background != -1)
    {
        printf("\x1b[38;5;%dm", foreground); //changes the foreground color
        printf("\x1b[48;5;%dm", background); //changes the background color
    } 
    else printf("\x1b[0m"); //resets the foreground and background color
}

int arrowKey(int key, int numChoices)
{
    int arrowKey;
    if (getch() == 224)
    {    
        arrowKey = getch();
        switch (arrowKey)
        {
        case UP:
        case LEFT:
            if (key - 1 >= 0)
                return (key - 1) % numChoices;
            else
                return numChoices - 1;
        case DOWN:
        case RIGHT:
            return (key + 1) % numChoices;
        default:
            return key;
        }
    }
    else return ENTER;
}

void printMainMenu()
{
    int choice = 0, i;
    
    while(choice != ENTER)
    {
        colorChange(BLACK, WHITE);
        printf("     MAIN MENU       \n");

        for(i = 0; i < 21; i++)
            printf("%c", HORLINE);
        printf("\n");

        for(i = 0; i < 5; i++)
        {
            printf("     ");
            
            if (choice == i)
                printf("%c ", 175);
            
            switch (i)
            {
                case 0: printf("Fak%cdex       ", 130); break;
                case 1: printf("Exploration   "); break;
                case 2: printf("Box           "); break;
                case 3: printf("Settings      "); break;
                case 4: printf("Exit          "); break;
            }

            if (choice == i)
                printf("\n");
            else printf("  \n");
        }
        choice = arrowKey(choice, 5);
        colorChange(RESET, RESET);
        system("cls");
    }
}

void main()
{
    int mainChoice;
    system("cls");
    printMainMenu();
}