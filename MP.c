#include <stdio.h>      //library where basic c functions are defined
#include <stdlib.h>     //library where srand, rand, clear screen functions are defined
#include <string.h>     //library where functions for string manipulation are defined
#include <conio.h>      //library where getch function is defined
#include <time.h>       //library where time function is defined

#define MAX_ENTRY 150   //max entry for fakedex
#define BOX_CAP 100     //max capacity for box (for caught fakemons)

/*COLORS DEFINED*/
#define RESET -1        //for resetting terminal color

#define WHITE 15
#define BLACK 0

#define RED 9
#define BLUE 19

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

#define LL_LINE 192     // └
#define LL_DLINE 200    // ╚
#define LR_LINE 217     // ┘
#define LR_DLINE 188    // ╝

#define LM_DLINE 204    // ╠
#define LM_DsLINE 199   // ╟
#define RM_DLINE 185    // ╣
#define RM_DsLine 182   // ╢

#define L_SELECTOR 175  // »
#define R_SELECTOR 174  // «

/*VARIATIONS IN E (for fakedex)*/
#define e 130   //lowercase variation for e
#define E 144   //uppercase variateion for e

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

void UI(char *type, int max)
{
    int i;
    
    if (!strcmp(type, "upper double border"))
        for (i = 0; i < max; i++)
        {
            if (i == 0)
                printf("%c", UL_DLINE);
            else if (i == max - 1)
                printf("%c", UR_DLINE);
            else    
                printf("%c", D_HORLINE);
        }
    
    else if (!strcmp(type, "lower double border"))
        for (i = 0; i < max; i++)
        {
            if (i == 0)
                printf("%c", LL_DLINE);
            else if (i == max - 1)
                printf("%c", LR_DLINE);
            else    
                printf("%c", D_HORLINE);
        }
        
    else if (!strcmp(type, "mid dsd border"))
        for (i = 0; i < max; i++)
        {
            if (i == 0)
                printf("%c", LM_DsLINE);
            else if (i == max - 1)
                printf("%c", RM_DsLine);
            else    
                printf("%c", HORLINE);
        }

    else if (!strcmp(type, "mid hollow double"))
        for (i = 0; i < max; i++)
        {
            if (i == 0 || i == max - 1)
                printf("%c", D_VERLINE);
            else    
                printf(" ");
        }
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

void checkString(char *input, int minLen, int maxLen)
{
    int i, 
        isAllChar = 1; //checks if all the characters are letters
        // isGminLen,  //checks if greater than the minLen
        // isLmaxLen;  //checks if less than the maxLen
    for (i = 0; *(input + i) != '\0'; i++)
    {
        if(*(input + i) < 'A' || 
          (*(input + i) > 'Z' && *(input + i) < 'a') || 
           *(input + i) > 'z')
        {
            isAllChar = !isAllChar;
            i = strlen(input);
        }
    }
    
    if (!isAllChar)
    {
        printf("INVALID INPUT\n");
    }
}

int printMainMenu()
{
    int nChoice = 0, i, nReturn = 0;
    
    while(nChoice != ENTER)
    {
        colorChange(WHITE, DARK_GREEN);
        UI("upper double border", 23);
        printf("\n%c      MAIN MENU      %c\n", D_VERLINE, D_VERLINE);

        UI("mid dsd border", 23);
        printf("\n");

        for(i = 0; i < 5; i++)
        {
            printf("%c    ", D_VERLINE);
            
            if (nChoice == i)
            {
                printf("%c ", 175);
                colorChange(BLACK, LIGHT_GREEN);
            }
            
            switch (i)
            {
                case 0: printf("Fak%cdex", e); colorChange(WHITE, DARK_GREEN); printf("       "); break;
                case 1: printf("Exploration"); colorChange(WHITE, DARK_GREEN); printf("   "); break;
                case 2: printf("Box");         colorChange(WHITE, DARK_GREEN); printf("           "); break;
                case 3: printf("Settings");    colorChange(WHITE, DARK_GREEN); printf("      "); break;
                case 4: printf("Exit");        colorChange(WHITE, DARK_GREEN); printf("          "); break;
            }
            colorChange(WHITE, DARK_GREEN);

            if (nChoice == i)
                printf(" %c\n", D_VERLINE);
            else printf("   %c\n", D_VERLINE);
        }
        UI("lower double border", 23);
        nChoice = arrowKey(nChoice, 5);
        colorChange(RESET, RESET);
        system("cls");

        if (nChoice != ENTER)
            nReturn = nChoice;
    }

    return nReturn + 1;
}

int printFDMenu()
{
    int nChoice = 0, i, nReturn = 0;
    
    while(nChoice != ENTER)
    {
        colorChange(WHITE, BLUE);
        UI("upper double border", 23);
        printf("\n%c       FAK%cDEX       %c\n", D_VERLINE, E, D_VERLINE);
        UI("mid dsd border", 23);
        printf("\n");

        for(i = 0; i < 5; i++)
        {
            printf("%c    ", D_VERLINE);
            
            if (nChoice == i)
            {
                colorChange(BLACK, CYAN);
                printf("%c ", 175);
            }
            
            switch (i)
            {
                case 0: printf("Add Entry");    colorChange(WHITE, BLUE); printf("     "); break;
                case 1: printf("View Entry");   colorChange(WHITE, BLUE); printf("    "); break;
                case 2: printf("Update Entry"); colorChange(WHITE, BLUE); printf("  "); break;
                case 3: printf("Remove Entry"); colorChange(WHITE, BLUE); printf("  "); break;
                case 4: printf("Exit");         colorChange(WHITE, BLUE); printf("          "); break;
            }

            if (nChoice == i)
                printf(" %c\n", D_VERLINE);
            else printf("   %c\n", D_VERLINE);
        }
        UI("lower double border", 23);
        nChoice = arrowKey(nChoice, 5);
        colorChange(RESET, RESET);
        system("cls");

        if (nChoice != ENTER)
            nReturn = nChoice;
    }

    return nReturn + 1;
}

void addEntry (Entry fakemon)
{
    int nChoice = 0, i, nReturn = 0;
    char *descsamp = "abcdefghjiklmnopqrstuvwxyz";
    
    colorChange(WHITE, BLUE);
    UI("upper double border", 32);
    printf("\n%c           ADD ENTRY          %c\n", D_VERLINE, D_VERLINE);
    UI("mid dsd border", 32); 
    printf("\n%c [NAME]: 123456789012         %c\n", D_VERLINE, D_VERLINE);
    printf("%c [NICKNAME]: 12345            %c\n", D_VERLINE, D_VERLINE);
    UI("mid hollow double", 32); printf("\n");
    printf("%c         [DESCRIPTION]        %c\n", D_VERLINE, D_VERLINE);
    for (i = 0; i < strlen(descsamp) / 28 + 1; i++)
    {
        printf("%c %.28s %c\n", D_VERLINE, descsamp + 28 * i, D_VERLINE);
    }
    
    UI("lower double border", 32);
    colorChange(RESET, RESET);
    printf("%d", strlen(descsamp));
}

void main()
{
    /* CHOICES FOR MAIN MENU
        1 - fakedex
        2 - exploration
        3 - box
        4 - settings
        5 - exit
    */
    int mainMenuChoice,

    /* CHOICES FOR FAKEDEX MENU
        1 - add entry
        2 - view entry
        3 - update entry
        4 - remove entry
        5 - exit
    */ 
        fakedexChoice,
        fakemonCount = 0;
    
    Entry fakemons[MAX_ENTRY];
    Entry boxmons[BOX_CAP]; 

    system("cls");
    mainMenuChoice = printMainMenu();

    switch (mainMenuChoice)
    {
    case 1: //FAKEDEX
        fakedexChoice = printFDMenu();
            switch (fakedexChoice)
            {
            case 1: //ADD ENTRY
                addEntry(fakemons[fakemonCount]);
                break;
            case 2: //VIEW ENTRY
                break;
            case 3: //UPDATE ENTRY
                break;
            case 4: //REMOVE ENTRY
                break;
            case 5: //EXIT FAKEDEX
                break;
            }
        break;
    case 2: //EXPLORATION
        break;
    case 3: //BOX
        break;
    case 4: //SETTINGS
        break;
    case 5: //EXIT MENU || TERMINATE
        break;
    }
}