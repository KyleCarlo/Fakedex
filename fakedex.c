/*
    Description:    This program simulates a simple pokemon game.
                    The user will enter a pokemon information and try
                    to catch them during exploration.

    Programmed by:  Kyle Carlo C. Lasala        Section: S17A
                    Adam Martin S. Mendoza      Section: S17A

    Last modified:  June 16, 2022
*/

#include <stdio.h>      //library where basic c functions are defined
#include <stdlib.h>     //library where srand, rand, clear screen functions are defined
#include <string.h>     //library where functions for string manipulation are defined
#include <strings.h>    //library where functions for advanced string manipulation are defined
#include <conio.h>      //library where getch function is defined
#include <time.h>       //library where time function is defined
#include <dirent.h>     //library where the functions needed for scanning directory is defined

#define MAX_ENTRY 150   //max entry for fakedex
#define BOX_CAP 100     //max capacity for box (for caught fakemons)
#define MAX_SAVFILE 5   //max saved file for the user

/*COLORS DEFINED*/
#define RESET -1        //for resetting terminal color

#define WHITE 15        
#define BLACK 0

#define BLUE 19
#define LIGHT_BLUE 45
#define LIGHTER_BLUE 123

#define CYAN 86
#define PINK 199

#define DARK_GREEN 22
#define LIGHT_GREEN 10

#define BRONZE 58
#define LIGHT_BRONZE 180

#define DARK_RED 52
#define LIGHT_RED 198

/*ARROW KEYS DEFINED*/
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

/*OTHER KEY DEFINED*/
#define BACK 8
#define ENTER 13
#define ESC 27

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
#define RM_DsLINE 182   // ╢

#define SHADE 219       // █
#define L_SHADE 221     // ▌
#define R_SHADE 222     // ▐
#define UP_SHADE 223    // ▀
#define LOW_SHADE 220   // ▄


#define L_SELECTOR 175  // »
#define R_SELECTOR 174  // «

/*VARIATIONS IN E (for fakedex)*/
#define e 130   //lowercase variation for e
#define E 144   //uppercase variateion for e

/*Struct of Fakemon entries stored in the FakeDex*/
typedef struct ENTRY{
    int slotNo;
    char name[12];
    char shortName[6];
    char desc[301];
    char gender[8];
    char caught[4];
} Entry;

/*Struct of caught Fakemon stored in the Box*/
typedef struct BOX{
    int slotNo;
    char name[12];
    char shortName[5];
} Box;

/* UI/UX */

/*  colorChange changes the color of the terminal

    Precondition - predefined and valid values for terminal color

    @param foreground - foreground color value
    @param background - background color value
*/
void colorChange(int foreground, int background);

/*  UI prints predefined borders depending on the length (max)

    Precondition - valid types and valid length

    @param *type - type of predefined borders
    @param max - length of border
*/
void UI(char *type, int max);

/*  timeDelay delays how long to pause before displaying the next line

    Precondition - valid input value

    @param seconds - time delay in seconds
*/
void timeDelay(float seconds);

/*  arrowKey takes the input of arrows by the user

    Precondition - arrow key input and valid number of choices

    @param key - the variable that takes the input
    @param numChoices - the variable that stores the number of choices

    @return <no specific variable> returns the choice of the user
*/
int arrowKey(int key, int numChoices);

/*  inputChar checks an enteredcharacterg if it's a valid name, short name, and description
    and assigns     

    Precondition - there is an input character of the user

    @param name[] - string that contains the input of the user
    @param *counter - stores the character count
    @param max - variable that contains the max length of name, short name, and description
    @param *inputDesignator - specifies whether the user input will be stored in name, short name, or description
    @param breaker - the number that serves as escape for the function
*/
void inputChar(char name[], int *counter, int max, int *inputDesignator, int breaker);

/* HELPERS */

/*  stringSearch searches for case-sensitive or case-insensitive strings

    Precondtion - input should be a valid string

    @param stringArr[][FILENAME_MAX] - string array that contains 
    @param *stringKey - string that contains the input of the user
    @param arrSize - variable that contains the size of a certain array
    @param isCaseSensitive - checks whether to search with case-sensitivity or case-insensitivity

    @return <no specific variable> returns the index of the array where the string is found, else returns -1
*/
int stringSearch(char stringArr[][FILENAME_MAX], char *stringKey, int arrSize, int isCaseSensitive);

/*  dexSearch searches the FakeDex for Fakemons entries

    Precondition - input should be a valid string

    @param fakemons[] - the array containing the entries of Fakemons
    @param *stringKey - string that contains the input of the user
    @param keyIndex - the index of the current key if the key exists in the array
    @param arrSize - variable that contains the size of a certain array
    @param isCaseSensitive - checks whether to search with case-sensitivity or case-insensitivity
    @param *searchfor - whether to search for name or short name

    @return <no specific variable> returns the index of the array where the string is found, else returns -1
*/
int dexSearch(Entry fakemons[], char *stringKey, int keyIndex, int arrSize, int isCaseSensitive, char *searchfor);

/*  boxSearch searches the box for caught Fakemons

    Precondition - input should be a valid string and array of string is in the Box struct

    @param boxmons[] - the array containing caught Fakemons
    @param *stringKey - string that contains the input of the user
    @param keyIndex - the index of the current key if the key exists in the array
    @param arrSize - variable that contains the size of a certain array
    @param isCaseSensitive - checks whether to search with case-sensitivity or case-insensitivity
    @param *searchfor - whether to search for name or short name

    @return <no specific variable> returns the index of the array where the string is found in Entry struct, else returns -1
*/
int boxSearch(Box boxmons[], char *stringKey, int keyIndex, int arrSize, int isCaseSensitive, char *searchfor);

/*  boxSort sorts the box depending on how the user wants it

    Precondition - input should be a valid string and array of string is in the Entry struct

    @param boxmons[] - the array containing caught Fakemons
    @param nSize - the variable that contains the current amount of caught fakemons
    @param isIncreasing - checks whether to search by increasing or decreasing order

    @return <no specific variable> returns the index of the array where the string is found in Box struct, else returns -1
*/
void boxSort(Box boxmons[], int nSize, int isIncreasing);

/*  resetEntrynBox deletes all data the Entry struct and Box struct

    Precondition - Box and Entry struct should be passed as an array of structure

    @param fakemons[] - the array containing the entries of Fakemons
    @param boxmons[] - the array containing caught Fakemons
    @param *fakemonCounter - the variable that contains the current amount of entries of fakemons in the FakeDex
    @param *boxCounter - the variable that contains the current amount of caught fakemons
*/
void resetEntryNBox(Entry fakemons[], Box boxmons[], int *fakemonCounter, int *boxCounter);

/*  eraseChar sets the value of the specified string to null

    Precondition - there is a valid string

    @param string[] - the string to be erased
    @param size - the size of the string to be erased
*/
void eraseChar(char string[], int size);

/*  removeDex removes a Fakemon entry from the Fakedex

    Precondition - the Fakedex should at least contain one UNCAUGHT entry to remove

    @param fakemons[] - the array containing the entries of Fakemons
    @param index - the index of the fakemon to be removed
    @param *fakemonCounter - the variable that contains the current amount of entries of fakemons in the Fakedex
*/
void removeDex(Entry fakemons[], int index, int *fakemonCounter);

/*  removeBox removes/frees a Fakemon from the box

    Precondition - the box should at least contain one CAUGHT Fakemon to remove/free

    @param boxmons[] - the array containing caught Fakemons
    @param index - the index of the fakemon to be removed
    @param *boxCounter - the variable that contains the current amount of fakemons
*/
void removeBox(Box boxmons[], int index, int *boxCounter);

/*  printBox prints the box feature

    Precondition - function should be inside a loop to properly print the contents of the box
    
    @param lineNumber - determines the row number of the box
    @param isSelected - determines if the current box selected
    @param slotNo - prints the slot numbers of 
    @param *shortName - prints the short name of a fakemon in the box
*/
void printBox(int lineNumber, int isSelected, int slotNo, char *shortName);

/*  printTiles print the tiles in the exploration

    Precondition - function should be inside a loop to properly print the contents of the tiles

    @param rowNumber - determines the row number of the tiles
    @param colNumber - determines the column number of the tiles
    @param isSelected - determines if the current tile contains the player
*/
void printTiles(int rowNumber, int colNumber, int isSelected);

/*  printPoke prints the fakemon in the exploration 

    Precondition - function should be inside a loop to properly print the contents of the box

    @param rowNumber - determines the row number of the fakemon
*/
void printPoke(int rowNumber);

/*  printBall prints the fakeball in the exploration

    Precondition - function should be inside a loop to properly print the contents of the ball

    @param rowNumber - determines the row number of the fakemon
*/
void printBall(int rowNumber);

/* MAIN FEATURES */

/*  printMainMenu prints the main menu

    Precondition - first function to call within the loop and assigned to a variable

    @return nReturn - determines the choice of the user
*/
int printMainMenu();

/*  printFDMenu prints the FadeDex menu

    Precondition - assigned to a variable

    @return nReturn - determines the choice of the user
*/
int printFDMenu();

/*  printSetMenu prints the settings menu

    Precondition - assigned to a variable

    @return nReturn - determines the choice of the user
*/
int printSetMenu();

/*  addEntry adds an entry to the FakeDex

    Precondition - assigned to a variable

    @param fakemons[] - the array containing the list of entries in the Fakedex
    @param *fakemonCounter - the variable that contains the current amount of entries in the Fakedex
*/
void addEntry(Entry fakemons[], int *fakemonCounter);

/*  overwriteEntry overwrites the entry if there is a detected same name

    Precondition - there should be same name in the addEntry 

    @param fakemons[] - the array containing the list of entries in the Fakedex
    @param similarNameIndex - the index where similar name is found
    @param *fakemonCounter - the pointer variable containing the fakemon count
*/
void overwriteEntry(Entry fakemons[], int similarNameIndex, int *fakemonCounter);

/*  viewEntry views the dex entry of the user

    Precondition - enableKey should be a valid number and identifies which function called

    @param fakemons[] - the array containing the list of entries in the Fakedex
    @param fakemonCounter - the variable containing the fakemon count
    @param enableKey - determines the function who called and changes the UI accordingly
    @param initial_index - the index where the dex should start showing

    @return index - return the index of the viewed entry depending to enableKey
*/
int viewEntry(Entry fakemons[], int fakemonCounter, int enableKey, int initial_index);

/*  updateEntry updates the entry from the Fakedex

    Precondition - there should be atleast one fakedex entry

    @param fakemons[] - the array containing the list of entries in the Fakedex
    @param boxmons[] - the array containing the caught fakemons
    @param fakemonCounter - the variable that contains the current number of entries in the fakedex
    @param boxCounter - the variable that contains the number of caught fakemons
*/
void updateEntry(Entry fakemons[], Box boxmons[], int fakemonCounter, int boxCounter);

/*  removeEntry removes the entry from the Fakedex

    Precondition - there should be atleast one fakedex entry

    @param fakemons[] - the struct array containing the list of entries in the Fakedex
    @param *fakemonCounter - the pointer variable that contains the current number of entries in the fakedex
*/
void removeEntry(Entry fakemons[], int *fakemonCounter);

/*  viewBox views the box that contains the caught pokemons

    Precondition - there should be atleast one caught fakemon

    @param fakemons[] - the struct array containing the list of entries in the Fakedex
    @param boxmons[] - the array containing the caught fakemons
    @param *boxCounter - the pointer variable that contains the current number of caught fakemons in the box
    @param fakemonCounter - the variable that contains the current number of entries in the fakedex
*/
void viewBox(Entry fakemons[], Box boxmons[], int *boxCounter, int fakemonCounter);

/*  explore prints exploration page

    Precondition - there should be at least one entry in the fakedex
    
    @param fakemons[] - the struct array containing the list of entries in the Fakedex
    @param boxmons[] - the array containing the caught fakemons
    @param *boxCounter - the pointer variable that contains the current number of caught fakemons in the box
    @param fakemonCounter - the variable that contains the current number of entries in the fakedex
*/
void explore(Entry fakemons[], Box boxmons[], int *boxCounter, int fakemonCounter);

/* SAVE AND LOAD */
/*  SaveProgress saves the progress of the user to a specific filename

    Precondition - filename should be a valid string

    @param fakemons[] - the struct array containing the list of entries in the Fakedex
    @param boxmons[] - the struct array containing the list of caught pokemons in the Fakedex
    @param fakemonCounter - the variable that contain the number of entries in the Fakedex
    @param boxCounter - the variable that contain the number of caught fakemon in the Fakedex
*/
void SaveProgress (Entry fakemons[], Box boxmons[], int fakemonCounter, int boxCounter);

/*  LoadProgress reads the directory and loads the specific filename

    Precondition - filename should correspond to a specific format

    @param fakemons[] - the struct array containing the list of entries in the Fakedex
    @param boxmons[] - the struct array containing the list of caught pokeons in the Fakedex 
    @param *fakemonCounter - the pointer variable that contains the current number of entries in the fakedex
    @param *boxCounter - the pointer variable that contains the current number of the caught fakemons in the box
*/
void LoadProgress (Entry fakemons[], Box boxmons[], int *fakemonCounter, int *boxCounter);

int main()
{
    // FILE *fp;
    /* CHOICES FOR MAIN MENU
        1 - fakedex
            1 - add entry
            2 - view entry
            3 - update entry
            4 - remove entry
            5 - exit    
        2 - exploration
        3 - box
        4 - settings
        5 - exit
    */
    int nChoices[2],
        fakemonCount = 0,
        boxCount = 0,
        key = 0, nChoice = 0;
    
    Entry fakemons[MAX_ENTRY];
    Box boxmons[BOX_CAP]; 

    srand(time(NULL));

    do    
    {
        system("cls");
        nChoices[0] = printMainMenu();

        switch (nChoices[0])
        {
        case 1: //FAKEDEX
            do
            {
                nChoices[1] = printFDMenu();
                key = 0;
                nChoice = 0;
                switch (nChoices[1])
                {
                case 1: //ADD ENTRY
                    if(fakemonCount < MAX_ENTRY)
                        addEntry(fakemons, &fakemonCount);
                    else
                    {
                        while (key != ENTER)
                        {
                            system("cls");
                            colorChange(WHITE, BLUE);
                            UI("upper double border", 32);
                            printf("\n");
                            UI("mid hollow double", 32);
                            printf("\n");
                            printf("%c        FAKEDEX IS FULL.      %c\n", D_VERLINE, D_VERLINE);
                            printf("%c   WOULD YOU LIKE TO REMOVE   %c\n", D_VERLINE, D_VERLINE);
                            printf("%c           AN ENTRY?          %c\n", D_VERLINE, D_VERLINE);
                            UI("mid hollow double", 32);
                            printf("\n");

                            switch(nChoice){
                                case 0: //no
                                    printf("%c      YES          %c ", D_VERLINE, L_SELECTOR);
                                    colorChange(BLACK, LIGHT_BLUE);
                                    printf("NO");
                                    colorChange(RESET, RESET);
                                    colorChange(WHITE, BLUE);
                                    printf(" %c     %c", R_SELECTOR, D_VERLINE);
                                    printf("\n");
                                    break;
                                case 1: //yes
                                    printf("%c     %c ", D_VERLINE, L_SELECTOR);
                                    colorChange(BLACK, LIGHT_BLUE);
                                    printf("YES");
                                    colorChange(RESET, RESET);
                                    colorChange(WHITE, BLUE);
                                    printf(" %c          NO      %c", R_SELECTOR, D_VERLINE);
                                    printf("\n");
                                    break;
                            }
                            
                            UI("mid hollow double", 32);
                            printf("\n");
                            UI("lower double border", 32);
                            printf("\n");
                            colorChange(RESET, RESET);

                            key = arrowKey(key, 2);
                            if (key != ENTER)
                                nChoice = key;
                        }

                        system("cls");

                        if(nChoice == 1)
                            removeEntry(fakemons, &fakemonCount);
                    }
                    break;
                case 2: //VIEW ENTRY
                    if(fakemonCount > 0)
                        viewEntry(fakemons, fakemonCount, 1, 0);
                    else
                    {
                        colorChange(WHITE, BLUE);
                        UI("upper double border", 32);
                        printf("\n");
                        UI("mid hollow double", 32);
                        printf("\n");
                        printf("%c    FAKEDEX CURRENTLY HAS     %c\n", D_VERLINE, D_VERLINE);
                        printf("%c         NO ENTRIES.          %c\n", D_VERLINE, D_VERLINE);
                        UI("mid hollow double", 32);
                        printf("\n");
                        UI("lower double border", 32);
                        printf("\n");
                        colorChange(RESET, RESET);
                        timeDelay(1);
                        system("cls");
                    }
                    break;
                case 3: //UPDATE ENTRY
                    if(fakemonCount > 0)
                        updateEntry(fakemons, boxmons, fakemonCount, boxCount);
                    else
                    {
                        colorChange(WHITE, BLUE);
                        UI("upper double border", 32);
                        printf("\n");
                        UI("mid hollow double", 32);
                        printf("\n");
                        printf("%c    FAKEDEX CURRENTLY HAS     %c\n", D_VERLINE, D_VERLINE);
                        printf("%c         NO ENTRIES.          %c\n", D_VERLINE, D_VERLINE);
                        UI("mid hollow double", 32);
                        printf("\n");
                        UI("lower double border", 32);
                        printf("\n");
                        colorChange(RESET, RESET);
                        timeDelay(1);
                        system("cls");
                    }
                    break;
                case 4: //REMOVE ENTRY
                    if(fakemonCount > 0)
                        removeEntry(fakemons, &fakemonCount);
                    else 
                    {
                        colorChange(WHITE, BLUE);
                        UI("upper double border", 32);
                        printf("\n");
                        UI("mid hollow double", 32);
                        printf("\n");
                        printf("%c    FAKEDEX CURRENTLY HAS     %c\n", D_VERLINE, D_VERLINE);
                        printf("%c         NO ENTRIES.          %c\n", D_VERLINE, D_VERLINE);
                        UI("mid hollow double", 32);
                        printf("\n");
                        UI("lower double border", 32);
                        printf("\n");
                        colorChange(RESET, RESET);
                        timeDelay(1);
                        system("cls");
                    }
                    break;
                case 5: //EXIT FAKEDEX
                    break;
                }
            } while (nChoices[1] != 5);
            break;
        case 2: //EXPLORATION
            if(fakemonCount > 0 && boxCount < BOX_CAP)
                explore(fakemons, boxmons, &boxCount, fakemonCount);
            else if (fakemonCount == 0)
            {
                colorChange(WHITE, DARK_GREEN);
                UI("upper double border", 32);
                printf("\n");
                UI("mid hollow double", 32);
                printf("\n");
                printf("%c    FAKEDEX CURRENTLY HAS     %c\n", D_VERLINE, D_VERLINE);
                printf("%c         NO ENTRIES.          %c\n", D_VERLINE, D_VERLINE);
                UI("mid hollow double", 32);
                printf("\n");
                printf("%c    FAKEDEX NEEDS TO HAVE     %c\n", D_VERLINE, D_VERLINE);
                printf("%c    AT LEAST ONE ENTRY TO     %c\n", D_VERLINE, D_VERLINE);
                printf("%c     ACCESS THIS FEATURE.     %c\n", D_VERLINE, D_VERLINE);
                UI("mid hollow double", 32);
                printf("\n");
                UI("lower double border", 32);
                printf("\n");
                colorChange(RESET, RESET);
                timeDelay(3);
                system("cls");
            }
            else if (boxCount == BOX_CAP)
            {
                colorChange(WHITE, DARK_GREEN);
                UI("upper double border", 32);
                printf("\n");
                UI("mid hollow double", 32);
                printf("\n");
                printf("%c      BOX CURRENTLY HAS       %c\n", D_VERLINE, D_VERLINE);
                printf("%c         NO CAPCITY.          %c\n", D_VERLINE, D_VERLINE);
                UI("mid hollow double", 32);
                printf("\n");
                printf("%c   RELEASE A POKEMON FIRST    %c\n", D_VERLINE, D_VERLINE);
                UI("mid hollow double", 32);
                printf("\n");
                UI("lower double border", 32);
                printf("\n");
                colorChange(RESET, RESET);
                timeDelay(3);
                system("cls");
            }
            break;
        case 3: //BOX
            if(boxCount < 1)
            {
                colorChange(WHITE, DARK_GREEN);
                UI("upper double border", 32);
                printf("\n");
                UI("mid hollow double", 32);
                printf("\n");
                printf("%c    YOU CURRENTLY HAVE NO     %c\n", D_VERLINE, D_VERLINE);
                printf("%c       CAUGHT POKEMONS.       %c\n", D_VERLINE, D_VERLINE);
                UI("mid hollow double", 32);
                printf("\n");
                UI("lower double border", 32);
                printf("\n");
                colorChange(RESET, RESET);
                timeDelay(1);
                system("cls");
            }
            else 
                viewBox(fakemons, boxmons, &boxCount, fakemonCount);
            break;
        case 4: //SETTINGS
            do
            {
                nChoices[1] = printSetMenu();
                switch (nChoices[1])
                {
                case 1: //SAVE PROGRESS
                    SaveProgress(fakemons, boxmons, fakemonCount, boxCount);
                    break;
                case 2: //LOAD PROGRESS
                    LoadProgress(fakemons, boxmons, &fakemonCount, &boxCount);
                    break;
                case 3: //EXIT
                    break;
                }
            } while(nChoices[1] != 3);
            break;
        case 5: //EXIT MENU || TERMINATE
            break;
        }
    } while(nChoices[0] != 5);

    return 0;
}

/* UI/UX */

void colorChange(int foreground, int background)
{
    if (foreground != RESET || background != RESET)
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
                printf("%c", RM_DsLINE);
            else    
                printf("%c", HORLINE);
        }
    else if (!strcmp(type, "mid dsd border 2"))
        for (i = 0; i < max; i++)
        {
            if (i == 0)
                printf("%c", LM_DLINE);
            else if (i == max - 1)
                printf("%c", RM_DLINE);
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

    else if (!strcmp(type, "mid hollow double 2"))
        for (i = 0; i < max; i++)
        {
            if (i == 0 || i == max - 1)
                printf("%c", VERLINE);
            else    
                printf(" ");
        }

    else if (!strcmp(type, "spacing"))
        for (i = 0; i < max; i++)
            printf(" ");

    else if (!strcmp(type, "upper dsd border"))
        for (i = 0; i < max; i++)
        {
            if (i == 0)
                printf("%c", UL_DLINE);
            else if (i == max - 1)
                printf("%c", UR_DLINE);
            else    
                printf("%c", HORLINE);
        }
    
    else if (!strcmp(type, "lower dsd border"))
        for (i = 0; i < max; i++)
        {
            if (i == 0)
                printf("%c", LL_DLINE);
            else if (i == max - 1)
                printf("%c", LR_DLINE);
            else    
                printf("%c", HORLINE);
        }
}

void timeDelay(float seconds)
{
    float mseconds = 1000.0 * seconds;
    clock_t startTime = clock();
    while (clock() < startTime + mseconds);
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

void inputChar(char name[], int *counter, int max, int *inputDesignator, int breaker)
{
    int isConCat = 0;
    int input = getch();
    if (*inputDesignator == 3 && 
        (input >= ' ' && input <= '~'))
    {        
        isConCat = 1;
    }
    else if (*inputDesignator == 2 &&
            (input >= 'A' && input <= 'Z'))
    {
        isConCat = 1;
    }
    else if (*inputDesignator == 1 && ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')))
    {
        isConCat = 1;
    }    
    else if (input == BACK)
    {
        if (*counter > 0)
            *counter -= 1;
        name[*counter] = '\0';
    }
    else if (input == ENTER)
    {
        if (*inputDesignator == 2 && strlen(name) == 5)
        {
            *inputDesignator += 1;
            *counter = 0;
        }
        else if (*inputDesignator == 2 && strlen(name) != 5)
        {
            system("cls");
            UI("upper double border", 32);
            printf("\n");
            UI("mid hollow double", 32);
            printf("\n");
            printf("%c !!!     Exactly FIVE     !!! %c\n", D_VERLINE, D_VERLINE);
            printf("%c !!!     letters only     !!! %c\n", D_VERLINE, D_VERLINE);
            UI("mid hollow double", 32);
            printf("\n");
            UI("lower double border", 32);
            timeDelay(1);
        }
        else if (*inputDesignator != 2 && strlen(name) != 0)
        {
            *inputDesignator += 1;
            *counter = 0;
        }
        else if (*inputDesignator != 2 && strlen(name) == 0)
        {
            system("cls");
            UI("upper double border", 32);
            printf("\n");
            UI("mid hollow double", 32);
            printf("\n");
            printf("%c !!!   CANNOT BE EMPTY    !!! %c\n", D_VERLINE, D_VERLINE);
            UI("mid hollow double", 32);
            printf("\n");
            UI("lower double border", 32);
            timeDelay(1);
        }
        
    }
    else if (input == ESC)
    {
        *inputDesignator = breaker;
        *counter = 0;
    }
    else if (*inputDesignator == 1 && ((input < 'a' || input > 'z') && (input < 'A' || input > 'Z')))
    {
        system("cls");
        UI("upper double border", 32);
        printf("\n");
        UI("mid hollow double", 32);
        printf("\n");
        printf("%c !!!     a-z and A-Z      !!! %c\n", D_VERLINE, D_VERLINE);
        printf("%c !!!     letters only     !!! %c\n", D_VERLINE, D_VERLINE);
        UI("mid hollow double", 32);
        printf("\n");
        UI("lower double border", 32);
        timeDelay(1);
    }
    else if (*inputDesignator == 2 && (input < 'A' || input > 'Z'))
    {
        system("cls");
        UI("upper double border", 32);
        printf("\n");
        UI("mid hollow double", 32);
        printf("\n");
        printf("%c !!!          A-Z         !!! %c\n", D_VERLINE, D_VERLINE);
        printf("%c !!!     letters only     !!! %c\n", D_VERLINE, D_VERLINE);
        UI("mid hollow double", 32);
        printf("\n");
        UI("lower double border", 32);
        timeDelay(1);
    }

    if (isConCat)
    {
        name[*counter] = input;
        if (*counter < max - 1)
            *counter += 1;
        else if (*counter == max - 1)
        {
            system("cls");
            UI("upper double border", 32);
            printf("\n");
            UI("mid hollow double", 32);
            printf("\n");
            if (max < 10)
                printf("%c !!!     Maximum of %d     !!! %c\n", D_VERLINE, max-1, D_VERLINE);
            else
                printf("%c !!!     Maximum of %d    !!! %c\n", D_VERLINE, max-1, D_VERLINE);
            printf("%c !!!     letters only     !!! %c\n", D_VERLINE, D_VERLINE);
            UI("mid hollow double", 32);
            printf("\n");
            UI("lower double border", 32);
            timeDelay(1);
        }
    }
    name[max - 1] = '\0';
}

void removeDex(Entry fakemons[], int index, int *fakemonCounter)
{
    int i;

    fakemons[index].slotNo = 0;
    eraseChar(fakemons[index].name, 12);
    eraseChar(fakemons[index].shortName, 6);
    eraseChar(fakemons[index].desc, 301);
    eraseChar(fakemons[index].gender, 8);
    eraseChar(fakemons[index].caught, 4);

    for (i = index; i < *fakemonCounter; i++)
        fakemons[i] = fakemons[i + 1];

    *fakemonCounter -= 1;

    for (i = 0; i < *fakemonCounter; i++)
        fakemons[i].slotNo = i;
}

void removeBox(Box boxmons[], int index, int *boxCounter)
{
    int i;

    boxmons[index].slotNo = 0;
    eraseChar(boxmons[index].name, 12);
    eraseChar(boxmons[index].shortName, 6);

    for (i = index; i < *boxCounter; i++)
        boxmons[i] = boxmons[i + 1];

    *boxCounter -= 1;

    for (i = 0; i < *boxCounter; i++)
        boxmons[i].slotNo = i;
}

void printBox(int lineNumber, int isSelected, int slotNo, char *shortName)
{
    int i;
    
    switch (lineNumber)
    {
    case 1:
        if (isSelected)
            colorChange(PINK, RESET);
        if(slotNo >= 0)    
        {
            printf("%c%c ", UL_DLINE, D_HORLINE);
            if (slotNo + 1 < 10)
                printf("00%d", slotNo + 1);
            else if (slotNo + 1 < 100)
                printf("0%d", slotNo + 1);
            else
                printf("%d", slotNo + 1);
            printf(" %c%c", D_HORLINE, UR_DLINE);
        }
        else
        {
            for (i = 0; i < 9; i++)
            {
                switch (i)
                {
                case 0:
                    printf("%c", UL_DLINE);
                    break;
                case 8:
                    printf("%c", UR_DLINE);
                    break;
                default:
                    printf("%c", D_HORLINE);
                    break;
                }
            }
            
        }
        break;
    case 2:
    case 4:
        if (isSelected && lineNumber == 2)
            colorChange(PINK, RESET);
        else if (isSelected && lineNumber == 4)
            colorChange(CYAN, RESET);
        printf("%c", VERLINE);
        for (int i = 0; i < 7; i++)
            printf("%c", SHADE);
        printf("%c", VERLINE);
        break;
    case 3:
        printf("%c%c%s%c%c", VERLINE, L_SHADE, shortName, R_SHADE, VERLINE);
        break;
    case 5:
        if (isSelected)
            colorChange(CYAN, RESET);
        printf("%c", LL_DLINE);
        for (int i = 0; i < 7; i++)
            printf("%c", D_HORLINE);
        printf("%c", LR_DLINE);
        break;
    }
    colorChange(RESET, RESET);
}

void printTiles(int rowNumber, int colNumber, int isSelected)
{
    int i, 
        colors[2] = {DARK_GREEN, LIGHT_GREEN};

    switch (rowNumber)
    {
    case 0:
        if (isSelected == colNumber)
            printf("%c%c%c %d %c%c%c", UL_DLINE, D_HORLINE, D_HORLINE, colNumber, D_HORLINE, D_HORLINE, UR_DLINE);
        else
            printf("%c%c%c %d %c%c%c", UL_LINE, HORLINE, HORLINE, colNumber, HORLINE, HORLINE, UR_LINE);
        break;
    
    case 1:
    case 2:
    case 3:
        if (isSelected == colNumber)
        {
            switch (rowNumber)
            {
            case 1:
                printf("%c", D_VERLINE);
                colorChange(WHITE, DARK_GREEN);
                printf(" %c %c %c ", UL_LINE, TRIANGLE, UR_LINE);
                colorChange(RESET, RESET);
                printf("%c", D_VERLINE);
                break;
            case 2:
                printf("%c", D_VERLINE);
                colorChange(WHITE, DARK_GREEN);
                printf(" %c O %c ", L_TRIANGLE, R_TRIANGLE);
                colorChange(RESET, RESET);
                printf("%c", D_VERLINE);
                break;
            case 3:
                printf("%c", D_VERLINE);
                colorChange(WHITE, DARK_GREEN);
                printf(" %c %c %c ", LL_LINE, I_TRIANGLE, LR_LINE);
                colorChange(RESET, RESET);
                printf("%c", D_VERLINE);
                break;
            }
        }
        else
        {
            printf("%c", VERLINE);
            colorChange(colors[!(colNumber % 2)], colors[colNumber % 2]);
            for (i = 0; i < 7; i++)
                printf("%c", TRIANGLE);
            colorChange(RESET, RESET);
            printf("%c", VERLINE);
        }
        break;
    case 4:
        if (isSelected == colNumber)
            printf("%c%c YOU %c%c", LL_DLINE, D_HORLINE, D_HORLINE, LR_DLINE);
        else
        {
            printf("%c", LL_LINE);
            for (i = 0; i < 7; i++)
                printf("%c", HORLINE);
            printf("%c", LR_LINE);
        }
        break;
    }
}

void printPoke(int rowNumber)
{
    switch (rowNumber)
    {
    case 0:
        printf("  ");
        colorChange(LIGHT_GREEN, RESET);
        printf("%c", LOW_SHADE);
        colorChange(LIGHT_GREEN, DARK_GREEN);
        printf("%c%c%c%c", UP_SHADE, UP_SHADE, UP_SHADE, UP_SHADE );
        colorChange(RESET, RESET);
        colorChange(LIGHT_GREEN, RESET);
        printf("%c", LOW_SHADE);
        colorChange(RESET, RESET);
        printf("\n");
        break;
    
    case 1:
        colorChange(LIGHT_GREEN, RESET);
        printf(" %c", SHADE);
        colorChange(DARK_GREEN, WHITE);
        printf("%c%c%c%c%c", SHADE, SHADE, SHADE, LOW_SHADE, SHADE);
        colorChange(RESET, RESET);
        colorChange(LIGHT_GREEN, RESET);
        printf("%c", SHADE);
        colorChange(RESET, RESET);
        printf("\n");
        break;

    case 2:
        colorChange(LIGHT_GREEN, RESET);
        printf(" %c%c%c", UP_SHADE, UP_SHADE, UP_SHADE);
        colorChange(LIGHT_GREEN, DARK_GREEN);
        printf("%c%c%c%c%c", SHADE, UP_SHADE, UP_SHADE, UP_SHADE, SHADE);
        colorChange(RESET, RESET);
        printf("\n");
        break;
    
    case 3:
        colorChange(LIGHT_GREEN, RESET);
        printf("%c  %c", LOW_SHADE, SHADE);
        colorChange(RESET, WHITE);
        printf("  ");
        colorChange(DARK_GREEN, RESET);
        printf("%c%c", SHADE, SHADE);
        colorChange(LIGHT_GREEN, RESET);
        printf("%c", SHADE);
        colorChange(RESET, RESET);
        printf("\n");
        break;

    case 4:
        colorChange(LIGHT_GREEN, RESET);
        printf(" %c%c", UP_SHADE, LOW_SHADE);
        colorChange(LIGHT_GREEN, WHITE);
        printf("%c%c%c", SHADE, LOW_SHADE, LOW_SHADE);
        colorChange(LIGHT_GREEN, DARK_GREEN);
        colorChange(RESET, RESET);
        colorChange(LIGHT_GREEN, DARK_GREEN);
        printf("%c%c", LOW_SHADE, LOW_SHADE);
        colorChange(RESET, RESET);
        colorChange(LIGHT_GREEN, RESET);
        printf("%c", UP_SHADE);
        colorChange(RESET, RESET);
        printf("\n");
        break;
    }
}

void printBall(int rowNumber)
{
    int i;
    switch (rowNumber)
    {
    case 0:
        colorChange(PINK, RESET);   
        printf("%c", UL_DLINE);
        for (i = 0; i < 7; i++)
            printf("%c", D_HORLINE);
        printf("%c", UR_DLINE);
        colorChange(RESET, RESET);
        break;
    case 1:
        printf(" ");
        colorChange(PINK, RESET);
        printf("%c", SHADE);
        for (i = 0; i < 5; i++)
            printf("%c", UP_SHADE);
        printf("%c", SHADE);
        colorChange(RESET, RESET);
        break;
    case 2:
        printf("   %c%c%c", SHADE, SHADE, SHADE);
        break;
    case 3:
        printf(" ");
        colorChange(CYAN, RESET);
        printf("%c", SHADE);
        for (i = 0; i < 5; i++)
            printf("%c", LOW_SHADE);
        printf("%c", SHADE);
        colorChange(RESET, RESET);
        break;
    case 4:
        colorChange(CYAN, RESET);   
        printf("%c", LL_DLINE);
        for (i = 0; i < 7; i++)
            printf("%c", D_HORLINE);
        printf("%c", LR_DLINE);
        colorChange(RESET, RESET);
        break;
    }
}

/* MAIN FEATURES */
int stringSearch(char stringArr[][FILENAME_MAX], char *stringKey, int arrSize, int isCaseSensitive)
{
    int i;
    if (isCaseSensitive)
    {
        for (i = 0; i < arrSize; i++)
            if(!strcmp(stringArr[i], stringKey))
                return i;
    }
    else
    {
        for (i = 0; i < arrSize; i++)
            if(!strcasecmp(stringArr[i], stringKey))
                return i;
    }
    return -1;
}   

int dexSearch(Entry fakemons[], char *stringKey, int keyIndex, int arrSize, int isCaseSensitive, char *searchfor)
{
    int i;
    if (isCaseSensitive && !strcmp(searchfor, "name"))
    {
        for (i = 0; i < arrSize; i++)
            if(!strcmp(fakemons[i].name, stringKey) && i != keyIndex)
                return i;
    }
    else if (!isCaseSensitive && !strcmp(searchfor, "short name"))
    {
        for (i = 0; i < arrSize; i++)
            if(!strcasecmp(fakemons[i].shortName, stringKey) && i != keyIndex)
                return i;
    }
    else if (!isCaseSensitive && !strcmp(searchfor, "name"))
    {
        for (i = 0; i < arrSize; i++)
            if(!strcasecmp(fakemons[i].name, stringKey) && i != keyIndex)
                return i;     
    }
    else if (isCaseSensitive && !strcmp(searchfor, "short name"))
    {
        for (i = 0; i < arrSize; i++)
            if(!strcmp(fakemons[i].shortName, stringKey) && i != keyIndex)
                return i;     
    }
    return -1;
}

int boxSearch(Box boxmons[], char *stringKey, int keyIndex, int arrSize, int isCaseSensitive, char *searchfor)
{
    int i;
    if (!isCaseSensitive && !strcmp(searchfor, "name"))
    {
        for (i = 0; i < arrSize; i++)
            if(!strcasecmp(boxmons[i].name, stringKey) && i != keyIndex)
                return i;        
    }

    if (isCaseSensitive && !strcmp(searchfor, "name"))
    {
        for (i = 0; i < arrSize; i++)
            if(!strcmp(boxmons[i].name, stringKey) && i != keyIndex)
                return i;    
    }
    
    if (isCaseSensitive && !strcmp(searchfor, "short name"))
    {
        for (i = 0; i < arrSize; i++)
            if(!strcmp(boxmons[i].shortName, stringKey) && i != keyIndex)
                return i;
    }
    
    return -1;
}

void boxSort(Box boxmons[], int nSize, int isIncreasing)
{
    int i, j;
    Box temp;

    for (i = 0; i < nSize - 1; i++)
    {   
        for (j = 0; j < nSize - i - 1; j++)
        {
            if (isIncreasing)
            {            
                if (strcmp(boxmons[j].shortName, boxmons[j + 1].shortName) > 0)
                {
                    temp = boxmons[j];
                    boxmons[j] = boxmons[j + 1];
                    boxmons[j + 1] = temp;
                }
            }
            else
            {
                if (strcmp(boxmons[j].shortName, boxmons[j + 1].shortName) < 0)
                {
                    boxmons[i].slotNo = i + 1;
                    temp = boxmons[j];
                    boxmons[j] = boxmons[j + 1];
                    boxmons[j + 1] = temp;
                }
            }
        }
    }
    
    for (i = 0; i < nSize; i++)
        boxmons[i].slotNo = i;
}

void resetEntryNBox(Entry fakemons[], Box boxmons[], int *fakemonCounter, int *boxCounter)
{
    int i;

    *fakemonCounter = 0;
    *boxCounter = 0;
    for (i = 0; i < MAX_ENTRY; i++)
    {
        fakemons[i].slotNo = 0;
        eraseChar(fakemons[i].name, 12);
        eraseChar(fakemons[i].shortName, 6);
        eraseChar(fakemons[i].desc, 301);
        eraseChar(fakemons[i].gender, 8);
        eraseChar(fakemons[i].caught, 4);
    }
    for (i = 0; i < BOX_CAP; i++)
    {
        boxmons[i].slotNo = 0;
        eraseChar(boxmons[i].name, 12);
        eraseChar(boxmons[i].shortName, 6);
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
                printf("%c ", L_SELECTOR);
                colorChange(BLACK, LIGHT_BLUE);
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

int printSetMenu()
{
    int nChoice = 0, nReturn = 0, key;
    while(nChoice != ENTER)
    {
        colorChange(WHITE, BRONZE);
        UI("upper double border", 23);
        printf("\n%c       SETTINGS      %c\n", D_VERLINE, D_VERLINE);
        UI("mid dsd border", 23);
        printf("\n");
        switch (nChoice)
        {
        case 0:
            printf("%c %c ", D_VERLINE, L_SELECTOR);
            colorChange(BLACK, LIGHT_BRONZE);
            printf("Save");
            colorChange(WHITE, BRONZE);
            printf(" %c      Load  %c\n", R_SELECTOR, D_VERLINE);
            printf("%c         Exit        %c\n", D_VERLINE, D_VERLINE);
            break;
        case 1:
            printf("%c  Save      %c ", D_VERLINE, L_SELECTOR);
            colorChange(BLACK, LIGHT_BRONZE);
            printf("Load");
            colorChange(WHITE, BRONZE);
            printf(" %c %c\n", R_SELECTOR, D_VERLINE);
            printf("%c         Exit        %c\n", D_VERLINE, D_VERLINE);
            break;
        case 2:
            printf("%c  Save         Load  %c\n", D_VERLINE, D_VERLINE);
            printf("%c       %c ", D_VERLINE, L_SELECTOR);
            colorChange(BLACK, LIGHT_BRONZE);
            printf("Exit");
            colorChange(WHITE, BRONZE);
            printf(" %c      %c\n", R_SELECTOR, D_VERLINE);
            break;
        }
        UI("lower double border", 23);

        if(getch() == 224)
        {
            key = getch();
            if ((nChoice == 0 || nChoice == 1) && (key == DOWN || key == UP))
                nChoice = 2;
            else if (nChoice == 2 && (key == UP || key == DOWN))
                nChoice = 0;
            else if ((nChoice == 0 || nChoice == 1) && (key == LEFT || key == RIGHT))
                nChoice = !nChoice;
            else if (nChoice == 2 && key == LEFT)
                nChoice = 0;
            else if (nChoice == 2 && key == RIGHT)
                nChoice = 1;
        } else nChoice = ENTER;
        
        if (nChoice != ENTER)
            nReturn = nChoice;

        colorChange(RESET,RESET);
        system("cls");
    }
    
    return nReturn + 1;
}

void eraseChar(char string[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        string[i] = '\0';
}

void addEntry (Entry fakemons[], int *fakemonCounter)
{
    int nChoice = 0, i,
        charCount = 0,
        inputDesignator = 1,
        indexGender = 0,
        similarNameIndex,
        similarSNIndex,
        isOverwrite = 0;
    char *gender[] = {"FEMALE", "MALE", "UNKNOWN", "Cancel"};

    /*INITIALIZATION*/
    fakemons[*fakemonCounter].slotNo = *fakemonCounter;
    eraseChar(fakemons[*fakemonCounter].name, 12);
    eraseChar(fakemons[*fakemonCounter].shortName, 6);
    eraseChar(fakemons[*fakemonCounter].desc, 301);
    eraseChar(fakemons[*fakemonCounter].gender, 8);
    eraseChar(fakemons[*fakemonCounter].caught, 4);
    strcpy(fakemons[*fakemonCounter].caught, "NO");

    while(inputDesignator <= 5)
    {
        colorChange(BLACK, WHITE);
        UI("upper double border", 32);
        printf("\n%c           ADD ENTRY          %c\n", D_VERLINE, D_VERLINE);
        UI("mid dsd border", 32); 

        printf("\n%c [NAME]: %s", D_VERLINE, fakemons[*fakemonCounter].name);
        if (inputDesignator == 1)
        {
            printf("|");        
            UI("spacing", 20 - strlen(fakemons[*fakemonCounter].name));
        }
        else UI("spacing", 21 - strlen(fakemons[*fakemonCounter].name));
        printf("%c\n", D_VERLINE);

        if (inputDesignator >= 2) 
        {
            printf("%c [NICKNAME]: %s", D_VERLINE, fakemons[*fakemonCounter].shortName);
            if (inputDesignator == 2) 
            {
                printf("|"); 
                UI("spacing", 16 - strlen(fakemons[*fakemonCounter].shortName));
            }
            else UI("spacing", 17 - strlen(fakemons[*fakemonCounter].shortName));
            printf("%c\n", D_VERLINE); 
        }

        UI("mid hollow double", 32);

        if (inputDesignator >= 3) 
        {
            printf("\n%c         [DESCRIPTION]        %c\n", D_VERLINE, D_VERLINE);
            for (i = 0; i < strlen(fakemons[*fakemonCounter].desc) / 28 + 1; i++)
            {    
                if (inputDesignator == 3)
                {
                    printf("%c %.28s", D_VERLINE, fakemons[*fakemonCounter].desc + 28 * i);
                    if (strlen(fakemons[*fakemonCounter].desc + 28 * i) < 28)
                        printf("|");
                    else printf(" ");
                }
                else printf("%c %.28s ", D_VERLINE, fakemons[*fakemonCounter].desc + 28 * i);
                UI("spacing", 28 - strlen(fakemons[*fakemonCounter].desc + 28 * i));
                printf("%c", D_VERLINE);
                printf("\n");
            } 
        } 
        else printf("\n");

        UI("mid hollow double", 32);

        if (inputDesignator >= 4)
        {
            if (inputDesignator == 4)
            {
                printf("\n%c [GENDER]: %c %s %c", D_VERLINE, R_SELECTOR, gender[nChoice], L_SELECTOR);
                UI("spacing", 15 - strlen(gender[indexGender]));
            }
            else
            {
                printf("\n%c [GENDER]: %s", D_VERLINE, fakemons[*fakemonCounter].gender);
                UI("spacing", 19 - strlen(fakemons[*fakemonCounter].gender));
            }
            
            printf("%c\n", D_VERLINE);
            UI("mid hollow double", 32);
        }

        if (inputDesignator == 5)
            printf("\n%c  Entry added successfully!   %c", D_VERLINE, D_VERLINE);
        else if (inputDesignator <= 3)
            printf("\n%c     (Enter ESC to cancel)    %c", D_VERLINE, D_VERLINE);
        printf("\n");
        UI("lower double border", 32);
        colorChange(RESET, RESET);

        if (inputDesignator == 5)
            timeDelay(2);

        switch (inputDesignator)
        {
        case 1:
            inputChar(fakemons[*fakemonCounter].name, &charCount, 12, &inputDesignator, 7);
            break;
        case 2: 
            inputChar(fakemons[*fakemonCounter].shortName, &charCount, 6, &inputDesignator, 7);
            break;
        case 3:
            similarNameIndex = dexSearch(fakemons, fakemons[*fakemonCounter].name, -1, *fakemonCounter, 1, "name");
            similarSNIndex = dexSearch(fakemons, fakemons[*fakemonCounter].shortName, -1, *fakemonCounter, 1, "short name");
            printf("%s", fakemons[similarNameIndex].caught);
            
            if (similarNameIndex != -1 || similarSNIndex != -1)
            {
                if ((similarNameIndex == similarSNIndex) || similarNameIndex != -1)
                    if (!strcmp(fakemons[similarNameIndex].caught, "NO"))
                        inputDesignator = 8;
                    else
                    {
                        inputDesignator = 1;
                        eraseChar(fakemons[*fakemonCounter].name, 12);
                        eraseChar(fakemons[*fakemonCounter].shortName, 5);
                        system("cls");
                        UI("upper double border", 32);
                        printf("\n");
                        UI("mid hollow double", 32);
                        printf("\n");
                        printf("%c !!!   POKEMON  ALREADY   !!! %c\n", D_VERLINE, D_VERLINE);
                        printf("%c !!!        CAUGHT        !!! %c", D_VERLINE, D_VERLINE);
                        printf("\n");
                        UI("mid hollow double", 32);
                        printf("\n");
                        UI("lower double border", 32);
                        timeDelay(2);
                    }
                else if (similarSNIndex != -1)
                {
                    inputDesignator = 2;
                    eraseChar(fakemons[*fakemonCounter].shortName, 5);
                    system("cls");
                    UI("upper double border", 32);
                    printf("\n");
                    UI("mid hollow double", 32);
                    printf("\n");
                    printf("%c !!!   NICKNAME ALREADY   !!! %c\n", D_VERLINE, D_VERLINE);
                    printf("%c !!!        EXISTS        !!! %c", D_VERLINE, D_VERLINE);
                    printf("\n");
                    UI("mid hollow double", 32);
                    printf("\n");
                    UI("lower double border", 32);
                    timeDelay(2);
                }
            }
            else
                inputChar(fakemons[*fakemonCounter].desc, &charCount, 301, &inputDesignator, 7);
            break;
        case 4:
            nChoice = arrowKey(nChoice, 4);
            if (nChoice != ENTER)
                indexGender = nChoice;
            else if (indexGender == 3)
                inputDesignator = 7;
            else 
            {
                strcpy(fakemons[*fakemonCounter].gender, gender[indexGender]);
                inputDesignator++;            
            }
            break;
        case 5:
            inputDesignator++;
            *fakemonCounter += 1;
            break;
        }

        if(inputDesignator == 7)
        {
            eraseChar(fakemons[*fakemonCounter].name, 12);
            eraseChar(fakemons[*fakemonCounter].shortName, 5);
            eraseChar(fakemons[*fakemonCounter].desc, 301);
            eraseChar(fakemons[*fakemonCounter].gender, 8);
        }

        if (inputDesignator == 8)
        {
            
            nChoice = 0;
            while (nChoice != ENTER)
            {
                system("cls");
                colorChange(BLACK, WHITE);
                UI("upper double border", 32);
                printf("\n%c           ADD ENTRY          %c\n", D_VERLINE, D_VERLINE);
                UI("mid dsd border", 32); 

                printf("\n%c [NAME]: %s", D_VERLINE, fakemons[similarNameIndex].name);
                UI("spacing", 21 - strlen(fakemons[similarNameIndex].name));
                printf("%c\n", D_VERLINE);
                printf("%c [NICKNAME]: %s", D_VERLINE, fakemons[similarNameIndex].shortName);
                UI("spacing", 17 - strlen(fakemons[similarNameIndex].shortName));
                printf("%c\n", D_VERLINE); 
                UI("mid hollow double", 32);
                printf("\n%c         [DESCRIPTION]        %c\n", D_VERLINE, D_VERLINE);
                for (i = 0; i < strlen(fakemons[similarNameIndex].desc) / 28 + 1; i++)
                {
                    printf("%c %.28s ", D_VERLINE, fakemons[similarNameIndex].desc + 28 * i);
                    UI("spacing", 28 - strlen(fakemons[similarNameIndex].desc + 28 * i));
                    printf("%c", D_VERLINE);
                    printf("\n");
                } 
                UI("mid hollow double", 32);
                printf("\n");
                printf("%c     Pokemon name exists.     %c\n", D_VERLINE, D_VERLINE);
                printf("%c Would you like to overwrite  %c\n", D_VERLINE, D_VERLINE);
                printf("%c       the entry above?       %c\n", D_VERLINE, D_VERLINE);
                UI("mid hollow double", 32);
                printf("\n");

                switch(isOverwrite)
                {
                    case 0:                 //no
                        printf("%c      YES         ", D_VERLINE);
                        printf("%c ", L_SELECTOR);
                        colorChange(WHITE, BLACK);
                        printf("NO");
                        colorChange(BLACK, WHITE);
                        printf(" %c      %c", R_SELECTOR, D_VERLINE);
                        break;
                    case 1:                 //yes
                        printf("%c      %c ", D_VERLINE, L_SELECTOR);
                        colorChange(WHITE, BLACK);
                        printf("YES");
                        colorChange(BLACK, WHITE);
                        printf(" %c         NO      %c", R_SELECTOR, D_VERLINE);
                        break;
                }

                printf("\n");
                UI("lower double border", 32);

                nChoice = arrowKey(nChoice, 2);
                if (nChoice != ENTER)
                    isOverwrite = nChoice;

                colorChange(RESET, RESET);
            }

            eraseChar(fakemons[*fakemonCounter].name, 12);
            eraseChar(fakemons[*fakemonCounter].shortName, 5);
            eraseChar(fakemons[*fakemonCounter].desc, 301);
            eraseChar(fakemons[*fakemonCounter].gender, 8);

            if (isOverwrite)
                overwriteEntry(fakemons, similarNameIndex, fakemonCounter);
        }
        
        system("cls");
        colorChange(RESET, RESET);
    }
}

void overwriteEntry (Entry fakemons[], int similarNameIndex, int *fakemonCounter)
{
    int i,
        inputDesignator = 2,
        nChoice = 0,
        indexGender = 0,
        charCount = 0,
        similarSNIndex;
    char *gender[] = {"FEMALE", "MALE", "UNKNOWN", "Cancel"};

    Entry currentEntry;

    strcpy(currentEntry.shortName, fakemons[similarNameIndex].shortName);
    strcpy(currentEntry.desc, fakemons[similarNameIndex].desc);
    strcpy(currentEntry.gender, fakemons[similarNameIndex].gender);

    eraseChar(fakemons[similarNameIndex].shortName, 5);
    eraseChar(fakemons[similarNameIndex].desc, 301);
    eraseChar(fakemons[similarNameIndex].gender, 8);

    while(inputDesignator <= 5)
    {
        system("cls");
        colorChange(BLACK, WHITE);
        UI("upper double border", 32);
        printf("\n%c           ADD ENTRY          %c\n", D_VERLINE, D_VERLINE);
        UI("mid dsd border", 32); 
        printf("\n%c [NAME]: %s", D_VERLINE, fakemons[similarNameIndex].name);    
        UI("spacing", 21 - strlen(fakemons[similarNameIndex].name));
        printf("%c\n", D_VERLINE);    
        if (inputDesignator >= 2) 
        {
            printf("%c [NICKNAME]: %s", D_VERLINE, fakemons[similarNameIndex].shortName);
            if (inputDesignator == 2) 
            {
                printf("|"); 
                UI("spacing", 16 - strlen(fakemons[similarNameIndex].shortName));
            }
            else UI("spacing", 17 - strlen(fakemons[similarNameIndex].shortName));
            printf("%c\n", D_VERLINE); 
        }

        UI("mid hollow double", 32); 

        if (inputDesignator >= 3) 
        {
            printf("\n%c         [DESCRIPTION]        %c\n", D_VERLINE, D_VERLINE);
            for (i = 0; i < strlen(fakemons[similarNameIndex].desc) / 28 + 1; i++)
            {    
                if (inputDesignator == 3)
                {
                    printf("%c %.28s", D_VERLINE, fakemons[similarNameIndex].desc + 28 * i);
                    if (strlen(fakemons[similarNameIndex].desc + 28 * i) < 28)
                        printf("|");
                    else printf(" ");
                }
                else printf("%c %.28s ", D_VERLINE, fakemons[similarNameIndex].desc + 28 * i);
                UI("spacing", 28 - strlen(fakemons[similarNameIndex].desc + 28 * i));
                printf("%c", D_VERLINE);
                printf("\n");
            } 
        } 
        else printf("\n");

        UI("mid hollow double", 32);

        if (inputDesignator >= 4)
        {
            if (inputDesignator == 4)
            {
                printf("\n%c [GENDER]: %c %s %c", D_VERLINE, R_SELECTOR, gender[indexGender], L_SELECTOR);
                UI("spacing", 15 - strlen(gender[indexGender]));
            }
            else
            {
                printf("\n%c [GENDER]: %s", D_VERLINE, fakemons[similarNameIndex].gender);
                UI("spacing", 19 - strlen(fakemons[similarNameIndex].gender));
            }       
            printf("%c\n", D_VERLINE);
            UI("mid hollow double", 32);     
        }

        if (inputDesignator == 5)
            printf("\n%c  Entry added successfully!   %c", D_VERLINE, D_VERLINE);
        else if (inputDesignator <= 3)
            printf("\n%c     (Enter ESC to cancel)    %c", D_VERLINE, D_VERLINE);
        printf("\n");
        UI("lower double border", 32);
        colorChange(RESET, RESET);

        if (inputDesignator == 5)
            timeDelay(2);

        switch (inputDesignator)
        {
        case 2: 
            inputChar(fakemons[similarNameIndex].shortName, &charCount, 6, &inputDesignator, 7);
            break;
        case 3:
            similarSNIndex = dexSearch(fakemons, fakemons[similarNameIndex].shortName, similarNameIndex, *fakemonCounter, 1, "short name");
            
            if (similarSNIndex != -1)
            {
                inputDesignator = 2;
                eraseChar(fakemons[similarNameIndex].shortName, 5);
                system("cls");
                UI("upper double border", 32);
                printf("\n");
                UI("mid hollow double", 32);
                printf("\n");
                printf("%c !!!   NICKNAME ALREADY   !!! %c\n", D_VERLINE, D_VERLINE);
                printf("%c !!!        EXISTS        !!! %c", D_VERLINE, D_VERLINE);
                printf("\n");
                UI("mid hollow double", 32);
                printf("\n");
                UI("lower double border", 32);
                timeDelay(2);
            }
            else
                inputChar(fakemons[similarNameIndex].desc, &charCount, 301, &inputDesignator, 7);
            break;
        case 4:
            nChoice = arrowKey(nChoice, 4);
            if (nChoice != ENTER)
                indexGender = nChoice;
            else if (indexGender == 3)
                inputDesignator = 7;
            else 
            {
                strcpy(fakemons[similarNameIndex].gender, gender[indexGender]);
                inputDesignator++;            
            }
            break;
        case 5:
            inputDesignator++;
            fakemons[*fakemonCounter] = fakemons[similarNameIndex];
            *fakemonCounter += 1;
            removeDex(fakemons, similarNameIndex, fakemonCounter);
            break;
        }

        if(inputDesignator == 7)
        {
            strcpy(fakemons[similarNameIndex].shortName, currentEntry.shortName);
            strcpy(fakemons[similarNameIndex].desc, currentEntry.desc);
            strcpy(fakemons[similarNameIndex].gender, currentEntry.gender);
        }
        colorChange(RESET, RESET);
    }
}

int viewEntry (Entry fakemons[], int fakemonCounter, int enableKey, int initial_index)
{
    int i,
        index = initial_index, 
        key = 0,
        inputDesignator,
        charCount = 0,
        searchIndex;
    char inputName[12] = "";

    while (key != ENTER)
    {
        if (enableKey == 1)
        {
            colorChange(WHITE, BLACK);
            UI("upper double border", 32);
            if (fakemons[index].slotNo + 1 < 10)
                printf("\n%c        POKEMON No00%d         %c\n", D_VERLINE, fakemons[index].slotNo + 1, D_VERLINE);
            else if (fakemons[index].slotNo + 1 < 100)
                printf("\n%c        POKEMON No0%d         %c\n", D_VERLINE, fakemons[index].slotNo + 1, D_VERLINE);
            else
                printf("\n%c        POKEMON No%d         %c\n", D_VERLINE, fakemons[index].slotNo + 1, D_VERLINE);
            UI("mid dsd border", 32); 
        }
        else if (enableKey == 2)
        {
            colorChange(WHITE, DARK_RED);
            UI("upper double border", 32);
            printf("\n%c         REMOVE ENTRY         %c\n", D_VERLINE, D_VERLINE);
            UI("mid dsd border", 32); 

            if (fakemons[index].slotNo + 1 < 10)
                printf("\n%c        POKEMON No00%d         %c\n", D_VERLINE, fakemons[index].slotNo + 1, D_VERLINE);
            else if (fakemons[index].slotNo + 1 < 100)
                printf("\n%c        POKEMON No0%d         %c\n", D_VERLINE, fakemons[index].slotNo + 1, D_VERLINE);
            else
                printf("\n%c        POKEMON No%d         %c\n", D_VERLINE, fakemons[index].slotNo + 1, D_VERLINE);
            UI("mid hollow double", 32);
        }
        else if (enableKey == 3)
        {
            colorChange(BLACK, LIGHTER_BLUE);
            UI("upper double border", 32);
            printf("\n%c         UPDATE ENTRY         %c\n", D_VERLINE, D_VERLINE);
            UI("mid dsd border", 32); 

            if (fakemons[index].slotNo + 1 < 10)
                printf("\n%c        POKEMON No00%d         %c\n", D_VERLINE, fakemons[index].slotNo + 1, D_VERLINE);
            else if (fakemons[index].slotNo + 1 < 100)
                printf("\n%c        POKEMON No0%d         %c\n", D_VERLINE, fakemons[index].slotNo + 1, D_VERLINE);
            else
                printf("\n%c        POKEMON No%d         %c\n", D_VERLINE, fakemons[index].slotNo + 1, D_VERLINE);
            UI("mid hollow double", 32);
        }
        else if (enableKey == 4)
        {
            colorChange(PINK, RESET);
            UI("upper dsd border", 32);
            printf("\n%c          DEX  ENTRY          %c\n", VERLINE, VERLINE);
            UI("mid dsd border 2", 32);

            colorChange(CYAN, RESET);
            if (fakemons[index].slotNo + 1 < 10)
                printf("\n%c        POKEMON No00%d         %c\n", VERLINE, fakemons[index].slotNo + 1, VERLINE);
            else if (fakemons[index].slotNo + 1 < 100)
                printf("\n%c        POKEMON No0%d         %c\n", VERLINE, fakemons[index].slotNo + 1, VERLINE);
            else
                printf("\n%c        POKEMON No%d         %c\n", VERLINE, fakemons[index].slotNo + 1, VERLINE);
            UI("mid hollow double 2", 32);
            printf("\n%c [NAME]: %s", VERLINE, fakemons[index].name);
        }
        
        if (enableKey == 4)
        {
            UI("spacing", 21 - strlen(fakemons[index].name));
            printf("%c\n", VERLINE);
        }
        else
        {
            printf("\n%c [NAME]: %s", D_VERLINE, fakemons[index].name);
            UI("spacing", 21 - strlen(fakemons[index].name));
            printf("%c\n", D_VERLINE);
        }

        if (!strcmp(fakemons[index].caught, "YES"))
        {
            if (enableKey == 4)
            {
                printf("%c [NICKNAME]: %s", VERLINE, fakemons[index].shortName);
                UI("spacing", 17 - strlen(fakemons[index].shortName));
                printf("%c\n", VERLINE); 
                UI("mid hollow double 2", 32);
                printf("\n%c         [DESCRIPTION]        %c\n", VERLINE, VERLINE);
                
                for (i = 0; i < strlen(fakemons[index].desc) / 28 + 1; i++)
                {    
                    printf("%c %.28s ", VERLINE, fakemons[index].desc + 28 * i);
                    UI("spacing", 28 - strlen(fakemons[index].desc + 28 * i));
                    printf("%c", VERLINE);
                    printf("\n");
                } 

                UI("mid hollow double 2", 32);
                printf("\n%c [GENDER]: %s", VERLINE, fakemons[index].gender);
                UI("spacing", 19 - strlen(fakemons[index].gender));
                printf("%c\n", VERLINE);
            }
            else 
            {
                printf("%c [NICKNAME]: %s", D_VERLINE, fakemons[index].shortName);
                UI("spacing", 17 - strlen(fakemons[index].shortName));
                printf("%c\n", D_VERLINE); 
                UI("mid hollow double", 32);
                printf("\n%c         [DESCRIPTION]        %c\n", D_VERLINE, D_VERLINE);
                
                for (i = 0; i < strlen(fakemons[index].desc) / 28 + 1; i++)
                {    
                    printf("%c %.28s ", D_VERLINE, fakemons[index].desc + 28 * i);
                    UI("spacing", 28 - strlen(fakemons[index].desc + 28 * i));
                    printf("%c", D_VERLINE);
                    printf("\n");
                } 
                UI("mid hollow double", 32);
                printf("\n%c [GENDER]: %s", D_VERLINE, fakemons[index].gender);
                UI("spacing", 19 - strlen(fakemons[index].gender));
                printf("%c\n", D_VERLINE);
            }
        }
        else
        {
            if (enableKey == 4)
            {
                printf("%c [NICKNAME]: ? ? ?            %c\n", VERLINE, VERLINE);
                UI("mid hollow double 2", 32);
                printf("\n%c         [DESCRIPTION]        %c\n", VERLINE, VERLINE);
                printf("%c            ?  ?  ?           %c\n", VERLINE, VERLINE);
                UI("mid hollow double 2", 32);  
                printf("\n%c [GENDER]: ? ? ?              %c\n", VERLINE, VERLINE);
            }
            else
            {
                printf("%c [NICKNAME]: ? ? ?            %c\n", D_VERLINE, D_VERLINE);
                UI("mid hollow double", 32);
                printf("\n%c         [DESCRIPTION]        %c\n", D_VERLINE, D_VERLINE);
                printf("%c            ?  ?  ?           %c\n", D_VERLINE, D_VERLINE);
                UI("mid hollow double", 32);  
                printf("\n%c [GENDER]: ? ? ?              %c\n", D_VERLINE, D_VERLINE);
            }
        }

        if (enableKey == 4)
        {
            UI("mid hollow double 2", 32);
            printf("\n");
            colorChange(PINK, RESET);
            UI("mid dsd border 2", 32);
        }
        else 
        {
            UI("mid hollow double", 32);  
            printf("\n");
            UI("mid dsd border", 32);  
        }
        
        printf("\n");
        if (enableKey != 4)
        {       
            printf("%c            SEARCH            %c\n", D_VERLINE, D_VERLINE);
            printf("%c               %c              %c\n", D_VERLINE, TRIANGLE, D_VERLINE);
            printf("%c PREV. PKMN  %c O %c  NEXT PKMN %c\n", D_VERLINE, L_TRIANGLE, R_TRIANGLE, D_VERLINE);
            printf("%c               %c              %c\n", D_VERLINE, I_TRIANGLE, D_VERLINE);
        }

        switch (enableKey)
        {
        case 1:
            printf("%c              EXIT            %c\n", D_VERLINE, D_VERLINE);
            break;
        case 2:
        case 3:
            printf("%c             CANCEL           %c\n", D_VERLINE, D_VERLINE);
            break;
        }
        
        if (enableKey == 1)
        {
            UI("mid hollow double", 32);
            printf("\n%c    Press any key to exit     %c\n", D_VERLINE, D_VERLINE);
        }
        else if (enableKey == 2)
        {
            UI("mid hollow double", 32);
            printf("\n%c    Press any key to remove   %c", D_VERLINE, D_VERLINE);
            printf("\n%c          the entry           %c\n", D_VERLINE, D_VERLINE);
        }
        else if (enableKey == 3)
        {
            UI("mid hollow double", 32);
            printf("\n%c    Press any key to update   %c", D_VERLINE, D_VERLINE);
            printf("\n%c          the entry           %c\n", D_VERLINE, D_VERLINE);
        }
        
        if (enableKey == 4)
        {
            UI("mid hollow double 2", 32);
            printf("\n%c    Press any key to exit     %c\n", VERLINE, VERLINE);
            UI("mid hollow double 2", 32);
        }
        
        if (enableKey == 4)
        {
            printf("\n");
            UI("lower dsd border", 32);
        }
        else
            UI("lower double border", 32);
        colorChange(RESET, RESET);

        if (enableKey == 1 || enableKey == 2 || enableKey == 3)
        {
            key = getch();
            if(key == 224)
            {
                switch(getch())
                {
                case LEFT:
                    key = 0; 
                    break;
                case RIGHT:
                    key = 1;
                    break;
                case UP:
                    key = -1;
                    break;
                case DOWN:
                    system("cls");
                    return -1;
                    break;
                }
            }
            else key = ENTER;

            if (key != ENTER)
            {  
                if (key == -1)
                {
                    system("cls");
                    inputDesignator = 1;
                    charCount = 0;
                    while (inputDesignator == 1)
                    {
                        switch (enableKey)
                        {
                        case 1:
                            colorChange(WHITE, BLACK);
                            UI("upper double border", 32);
                            printf("\n%c          VIEW ENTRY          %c\n", D_VERLINE, D_VERLINE);
                            break;
                        case 2:
                            colorChange(WHITE, DARK_RED);
                            UI("upper double border", 32);
                            printf("\n%c         REMOVE ENTRY         %c\n", D_VERLINE, D_VERLINE);
                            break;
                        case 3:
                            colorChange(BLACK, LIGHTER_BLUE);
                            UI("upper double border", 32);
                            printf("\n%c         UPDATE ENTRY         %c\n", D_VERLINE, D_VERLINE);
                            break;
                        }
                        UI("mid dsd border", 32); 
                        printf("\n%c            SEARCH            %c\n", D_VERLINE, D_VERLINE);
                        UI("mid hollow double", 32);
                        printf("\n%c   Enter the Pokemon name:    %c", D_VERLINE, D_VERLINE);
                        printf("\n%c         %s|", D_VERLINE, inputName);
                        UI("spacing", 20 - strlen(inputName));
                        printf("%c\n", D_VERLINE);
                        UI("mid hollow double", 32);
                        printf("\n%c     (Enter ESC to cancel)    %c\n", D_VERLINE, D_VERLINE);
                        UI("lower double border", 32);
                        colorChange(RESET, RESET);
                        inputChar(inputName, &charCount, 12, &inputDesignator, 3);
                        system("cls");
                    }
                    if (inputDesignator != 3)
                    {
                        searchIndex = dexSearch(fakemons, inputName, -1, fakemonCounter, 1, "name");
                        if (searchIndex == -1)
                        {
                            UI("upper double border", 32);
                            printf("\n");
                            UI("mid hollow double", 32);
                            printf("\n");
                            printf("%c !!!    NAME NOT FOUND    !!! %c\n", D_VERLINE, D_VERLINE);
                            UI("mid hollow double", 32);
                            printf("\n");
                            UI("lower double border", 32);
                            timeDelay(2);
                        }
                        else
                            index = searchIndex;
                    }
                    else key = 0;
                    
                    eraseChar(inputName, 12);
                }     
                else if (key && index + 1 <= fakemonCounter - 1)
                    index++;
                else if (key && index + 1 > fakemonCounter - 1)
                    index = 0;
                else if (!key && index - 1 >= 0)
                    index--;
                else if (!key && index - 1 < 0)
                    index = fakemonCounter - 1;     
            } 
        }
        else if (enableKey == 4)
        {
            key = ENTER;
            getch();
        }

        system("cls");
    }
    return index;
}

void updateEntry(Entry fakemons[], Box boxmons[], int fakemonCounter, int boxCounter)
{
    int update_index = viewEntry(fakemons, fakemonCounter, 3, 0),
        i, similarSNIndex,
        charCount = 0, 
        inputDesignator = 1,
        nChoice = 0,
        indexGender = 0,
        boxIndex;
    char *gender[] = {"FEMALE", "MALE", "UNKNOWN", "Cancel"};

    Entry currentEntry;

    if (update_index != -1)
    {    
        strcpy(currentEntry.name, fakemons[update_index].name);
        strcpy(currentEntry.shortName, fakemons[update_index].shortName);
        strcpy(currentEntry.desc, fakemons[update_index].desc);
        strcpy(currentEntry.gender, fakemons[update_index].gender);

        eraseChar(fakemons[update_index].name, 12);
        eraseChar(fakemons[update_index].shortName, 5);
        eraseChar(fakemons[update_index].desc, 301);
        eraseChar(fakemons[update_index].gender, 8);

        while (inputDesignator <= 5)
        {
            system("cls");
            colorChange(BLACK, LIGHTER_BLUE);
            UI("upper double border", 32);
            printf("\n%c         UPDATE ENTRY         %c\n", D_VERLINE, D_VERLINE);
            UI("mid dsd border", 32); 
            
            printf("\n%c [NAME]: %s", D_VERLINE, fakemons[update_index].name);
            if (inputDesignator == 1)
            {
                printf("|");        
                UI("spacing", 20 - strlen(fakemons[update_index].name));
            }
            else UI("spacing", 21 - strlen(fakemons[update_index].name));
            printf("%c\n", D_VERLINE);

            if (inputDesignator >= 2) 
            {
                if (inputDesignator == 2)
                {
                    printf("%c [NICKNAME]: %s", D_VERLINE, fakemons[update_index].shortName);
                    printf("|"); 
                    UI("spacing", 16 - strlen(fakemons[update_index].shortName));
                }
                else
                {
                    printf("%c [NICKNAME]: %s", D_VERLINE, fakemons[update_index].shortName);
                    UI("spacing", 17 - strlen(fakemons[update_index].shortName));
                }
            }
            else 
            {
                printf("%c [NICKNAME]: %s", D_VERLINE, currentEntry.shortName);
                UI("spacing", 17 - strlen(currentEntry.shortName));
            }
            printf("%c\n", D_VERLINE); 

            UI("mid hollow double", 32);
            printf("\n%c         [DESCRIPTION]        %c\n", D_VERLINE, D_VERLINE);
            
            if (inputDesignator >= 3)
                for (i = 0; i < strlen(fakemons[update_index].desc) / 28 + 1; i++)
                {    
                    if (inputDesignator == 3)
                    {
                        printf("%c %.28s", D_VERLINE, fakemons[update_index].desc + 28 * i);
                        if (strlen(fakemons[update_index].desc + 28 * i) < 28)
                            printf("|");
                        else printf(" ");
                    }
                    else printf("%c %.28s ", D_VERLINE, fakemons[update_index].desc + 28 * i);
                    UI("spacing", 28 - strlen(fakemons[update_index].desc + 28 * i));
                    printf("%c", D_VERLINE);
                    printf("\n");
                }
            else
                for (i = 0; i < strlen(currentEntry.desc) / 28 + 1; i++)
                {    
                    printf("%c %.28s ", D_VERLINE, currentEntry.desc + 28 * i);
                    UI("spacing", 28 - strlen(currentEntry.desc + 28 * i));
                    printf("%c\n", D_VERLINE);
                } 

            UI("mid hollow double", 32);

            if (inputDesignator >= 4)
            {
                if (inputDesignator == 4)
                {
                    printf("\n%c [GENDER]: %c %s %c", D_VERLINE, R_SELECTOR, gender[nChoice], L_SELECTOR);
                    UI("spacing", 15 - strlen(gender[indexGender]));
                }
                else
                {
                    printf("\n%c [GENDER]: %s", D_VERLINE, fakemons[update_index].gender);
                    UI("spacing", 19 - strlen(fakemons[update_index].gender));
                }
            }
            else
            {
                printf("\n%c [GENDER]: %s", D_VERLINE, currentEntry.gender);
                UI("spacing", 19 - strlen(currentEntry.gender));
            }
            printf("%c\n", D_VERLINE);
            UI("mid hollow double", 32);

            if (inputDesignator == 5)
            {
                if (!strcmp(fakemons[update_index].caught, "YES"))
                {
                    boxIndex = boxSearch(boxmons, currentEntry.name, -1, boxCounter, 1, "name");
                    strcpy(boxmons[boxIndex].name, fakemons[update_index].name);
                    strcpy(boxmons[boxIndex].shortName, fakemons[update_index].shortName);
                }
                printf("\n%c     SUCCESSFULLY UPDATED     %c\n", D_VERLINE, D_VERLINE);
                printf("%c           ENTRY!             %c", D_VERLINE, D_VERLINE);
            }
            else if (inputDesignator <= 3)
                printf("\n%c     (Enter ESC to cancel)    %c", D_VERLINE, D_VERLINE);

            printf("\n");

            UI("lower double border", 32);
            colorChange(RESET, RESET);

            if (inputDesignator == 5)
                timeDelay(2);

            switch (inputDesignator)
            {
            case 1:
                inputChar(fakemons[update_index].name, &charCount, 12, &inputDesignator, 7);
                break;
            case 2: 
                inputChar(fakemons[update_index].shortName, &charCount, 6, &inputDesignator, 7);
                break;
            case 3:
                similarSNIndex = dexSearch(fakemons, fakemons[update_index].shortName, update_index, fakemonCounter, 1, "short name");
                
                if (similarSNIndex != -1)
                {
                    inputDesignator = 2;
                    eraseChar(fakemons[update_index].shortName, 5);
                    system("cls");
                    UI("upper double border", 32);
                    printf("\n");
                    UI("mid hollow double", 32);
                    printf("\n");
                    printf("%c !!!   NICKNAME ALREADY   !!! %c\n", D_VERLINE, D_VERLINE);
                    printf("%c !!!        EXISTS        !!! %c", D_VERLINE, D_VERLINE);
                    printf("\n");
                    UI("mid hollow double", 32);
                    printf("\n");
                    UI("lower double border", 32);
                    timeDelay(2);
                }
                else
                    inputChar(fakemons[update_index].desc, &charCount, 301, &inputDesignator, 7);
                break;
            case 4:
                nChoice = arrowKey(nChoice, 4);
                if (nChoice != ENTER)
                    indexGender = nChoice;
                else if (indexGender == 3)
                    inputDesignator = 7;
                else 
                {
                    strcpy(fakemons[update_index].gender, gender[indexGender]);
                    inputDesignator++;            
                }
                break;
            case 5:
                inputDesignator++;
                break;
            }

            if (inputDesignator == 7)
            {
                strcpy(fakemons[update_index].name, currentEntry.name);
                strcpy(fakemons[update_index].shortName, currentEntry.shortName);
                strcpy(fakemons[update_index].desc, currentEntry.desc);
                strcpy(fakemons[update_index].gender, currentEntry.gender);
            }
        }
        system("cls");
    }
}

void removeEntry(Entry fakemons[], int *fakemonCounter)
{
    int remove_index = viewEntry(fakemons, *fakemonCounter, 2, 0);

    if (remove_index != -1)
    {
        system("cls");
        if (!strcmp(fakemons[remove_index].caught, "NO"))
        {
            removeDex(fakemons, remove_index, fakemonCounter);
            
            colorChange(WHITE, DARK_RED);
            UI("upper double border", 32);
            printf("\n");
            UI("mid hollow double", 32);
            printf("\n");
            printf("%c     SUCCESSFULLY REMOVED     %c\n", D_VERLINE, D_VERLINE);
            printf("%c           ENTRY!             %c\n", D_VERLINE, D_VERLINE);
            UI("mid hollow double", 32);
            printf("\n");
            UI("lower double border", 32);
            colorChange(RESET, RESET);
            timeDelay(1);
        }
        else
        {
            colorChange(WHITE, DARK_RED);
            UI("upper double border", 32);
            printf("\n");
            UI("mid hollow double", 32);
            printf("\n");
            printf("%c    CAUGHT POKEMONS CANNOT    %c\n", D_VERLINE, D_VERLINE);
            printf("%c         BE REMOVED!          %c\n", D_VERLINE, D_VERLINE);
            UI("mid hollow double", 32);
            printf("\n");
            UI("lower double border", 32);
            colorChange(RESET, RESET);
            timeDelay(1);
            system("cls");
            removeEntry(fakemons, fakemonCounter);
        }
        system("cls");
    }
}

void viewBox (Entry fakemons[], Box boxmons[], int *boxCounter, int fakemonCounter)
{
    int i, j, layers,
        selector = 0,
        starter = 0,
        charCount = 0,
        key, nChoice,
        inputDesignator,
        searchIndex;
    char inputName[12] = "",
         inputSN[6] = "";
    
    while (key != ESC)
    {
        system("cls");
        printf("  ");
        colorChange(PINK, RESET);
        UI("upper dsd border", 42);
        colorChange(RESET, RESET);
        printf("\n  ");
        colorChange(WHITE, RESET);
        printf("%c                  BOX                   %c", VERLINE, VERLINE);
        colorChange(RESET, RESET);
        printf("\n  ");
        colorChange(CYAN, RESET);
        UI("lower dsd border", 42);
        colorChange(RESET, RESET);
        printf("\n");
        for (i = 0; i < 3; i++)
        {
            for (layers = 1; layers <= 5; layers++)
            {
                for (j = starter; j < starter + 4; j++)
                {
                    if (j + i * 4 < BOX_CAP)
                    {
                        if (selector == j + i * 4)
                        {
                            printf(" %c", L_SELECTOR);
                            if (j + i * 4 < *boxCounter)
                                printBox(layers, 1, boxmons[j + i * 4].slotNo, boxmons[j + i * 4].shortName);
                            else
                                printBox(layers, 1, -1, "EMPTY");
                            printf("%c ", R_SELECTOR);
                        }
                        else 
                        {
                            if (!(selector == j + i * 4 - 1) || !((selector + 1) % 4))
                                printf("  ");
                            if (j + i * 4 < *boxCounter)
                                printBox(layers, 0, boxmons[j + i * 4].slotNo, boxmons[j + i * 4].shortName);
                            else 
                                printBox(layers, 0, -1, "EMPTY");
                        }
                    }
                }
                printf("\n");
            }
        }

        printf("    ");
        colorChange(CYAN, RESET);
        printf("%c              ", TRIANGLE);
        colorChange(CYAN, RESET);
        printf("1 -");
        colorChange(PINK, RESET);
        printf(" Search by Name");
        colorChange(RESET, RESET);
        printf("\n");

        printf("  ");
        colorChange(CYAN, RESET);
        printf("%c", L_TRIANGLE);
        colorChange(RESET, RESET);
        printf(" O ");
        colorChange(CYAN, RESET);
        printf("%c  -", R_TRIANGLE);
        colorChange(PINK, RESET);
        printf("  MOVE   ");
        colorChange(CYAN, RESET);
        printf("2 -");
        colorChange(PINK, RESET);
        printf(" Search by Nickname");
        colorChange(RESET, RESET);
        printf("\n");

        printf("    ");
        colorChange(CYAN, RESET);
        printf("%c              ", I_TRIANGLE);
        printf("3 -");
        colorChange(PINK, RESET);
        printf(" Sort by Nickname");
        colorChange(RESET, RESET);
        printf("\n");

        UI("spacing", 19);
        colorChange(CYAN, RESET);
        printf("4 -");
        colorChange(PINK, RESET);
        printf(" Release Pokemon");
        colorChange(RESET, RESET);
        printf("\n");
        
        printf("\n");
        printf("  ENTER - View Dex Entry     ESC - Exit\n");

        inputDesignator = 0;
        key = getch();
        if(key == 224)
        {
            switch(getch())
            {
            case LEFT:
                if (selector - 1 >= starter)
                    selector -= 1;       
                else if (starter - 12 >= 0)
                {
                    selector -= 1;
                    starter -= 12;
                }
                break;
            case RIGHT:
                if (selector + 1 < starter + 12 && selector + 1 < BOX_CAP)
                    selector += 1;
                else if (starter + 12 < *boxCounter)
                {
                    selector += 1;
                    starter += 12;
                }
                break;
            case UP:
                if (selector - 4 >= starter)
                    selector -= 4;
                else if (starter - 12 >= 0)
                {
                    selector -= 4;
                    starter -= 12;
                }
                break;
            case DOWN:                
                if (selector + 4 < starter + 12 && selector + 4 < BOX_CAP - 4)
                    selector += 4;
                else if (starter + 12 < *boxCounter)
                {
                    selector += 4;
                    starter += 12;
                }
                break;
            }
        }
        else if (key == '1')
            inputDesignator = 1;
        else if (key == '2')
            inputDesignator = 2;
        else if (key == '3')
        {
            key = 0;
            nChoice = 0;
            while (key != ENTER)
            {
                system("cls");
                UI("upper double border", 32);
                printf("\n");
                UI("mid hollow double", 32);
                printf("\n");
                for (i = 0; i < 3; i++)
                {
                    switch (i)
                    {
                    case 0:
                        if(nChoice == i)
                        {
                            printf("%c     %c ", D_VERLINE, L_SELECTOR);
                            colorChange(BLACK, WHITE);
                            printf("Increasing Order");
                            colorChange(RESET, RESET);
                            printf(" %c     %c", R_SELECTOR, D_VERLINE);
                        }
                        else
                            printf("%c       Increasing Order       %c", D_VERLINE, D_VERLINE);
                        break;
                    case 1:
                        if(nChoice == i)
                        {
                            printf("%c     %c ", D_VERLINE, L_SELECTOR);
                            colorChange(BLACK, WHITE);
                            printf("Decreasing Order");
                            colorChange(RESET, RESET);
                            printf(" %c     %c", R_SELECTOR, D_VERLINE);
                        }
                        else
                            printf("%c       Decreasing Order       %c", D_VERLINE, D_VERLINE);
                        break;
                    case 2:
                        if(nChoice == i)
                        {
                            printf("%c          %c ", D_VERLINE, L_SELECTOR);
                            colorChange(BLACK, WHITE);
                            printf("Cancel");
                            colorChange(RESET, RESET);
                            printf(" %c          %c", R_SELECTOR, D_VERLINE);
                        }
                        else
                            printf("%c            Cancel            %c", D_VERLINE, D_VERLINE);
                        break;
                    }
                    printf("\n");
                }
                UI("mid hollow double", 32);
                printf("\n");
                UI("lower double border", 32);
                key = arrowKey(key, 3);
                if (key != ENTER)
                    nChoice = key;
                
                if (nChoice != 2)      
                {          
                    if (nChoice == 0)
                        boxSort(boxmons, *boxCounter, 1);
                    else boxSort(boxmons, *boxCounter, 0);
                }
            }
            key = 0;
        }
        else if (key == '4')
        {
            key = 0;
            nChoice = 0;
            while (key != ENTER)
            {
                system("cls");
                UI("upper double border", 32);
                printf("\n");
                UI("mid hollow double", 32);
                printf("\n%c        Do you want to        %c", D_VERLINE, D_VERLINE);
                printf("\n%c           release            %c", D_VERLINE, D_VERLINE);
                printf("\n%c            %s             %c\n", D_VERLINE, boxmons[selector].shortName, D_VERLINE);
                UI("mid hollow double", 32);
                switch (nChoice)
                {
                case 0:
                    printf("\n%c       YES        %c ", D_VERLINE, L_SELECTOR);
                    colorChange(BLACK, WHITE);
                    printf("NO");
                    colorChange(RESET, RESET);
                    printf(" %c      %c", R_SELECTOR, D_VERLINE);
                    break;
                case 1:
                    printf("\n%c      %c ", D_VERLINE, L_SELECTOR);
                    colorChange(BLACK, WHITE);
                    printf("YES");
                    colorChange(RESET, RESET);
                    printf(" %c        NO       %c", R_SELECTOR, D_VERLINE);
                    break;
                }
                printf("\n");
                UI("mid hollow double", 32);
                printf("\n");
                UI("lower double border", 32);
                key = arrowKey(key, 2);
                if (key != ENTER)
                    nChoice = key;
                else if (nChoice)
                {
                    system("cls");
                    removeBox(boxmons, selector, boxCounter);
                    UI("upper double border", 32);
                    printf("\n");
                    UI("mid hollow double", 32);
                    printf("\n");
                    printf("%c    SUCCESSFULLY RELEASED!    %c\n", D_VERLINE, D_VERLINE);
                    UI("mid hollow double", 32);
                    printf("\n");
                    UI("lower double border", 32);
                    timeDelay(1);
                }
            }
            key = 0;
        }
        else if (key == ESC)
            inputDesignator = 0;
        else if (key == ENTER)
        {
            searchIndex = dexSearch(fakemons, boxmons[selector].name, -1, fakemonCounter, 1, "name");
            system("cls");
            if (searchIndex != -1)
            {
                viewEntry(fakemons, fakemonCounter, 4, searchIndex);
                key = 0;
            }
            else
            {
                UI("upper double border", 32);
                printf("\n");
                UI("mid hollow double", 32);
                printf("\n");
                printf("%c !!!      EMPTY  BOX      !!! %c\n", D_VERLINE, D_VERLINE);
                UI("mid hollow double", 32);
                printf("\n");
                UI("lower double border", 32);
                timeDelay(2);
                key = 0;
            }   
        }
        
        while (inputDesignator == 1)
        {
            system("cls");
            UI("upper double border", 32);
            printf("\n%c          BOX SEARCH          %c\n", D_VERLINE, D_VERLINE);
            UI("mid dsd border", 32); 
            printf("\n");
            UI("mid hollow double", 32);
            printf("\n%c   Enter the Pokemon name:    %c", D_VERLINE, D_VERLINE);
            printf("\n%c         %s|", D_VERLINE, inputName);
            UI("spacing", 20 - strlen(inputName));
            printf("%c\n", D_VERLINE);
            UI("mid hollow double", 32);
            printf("\n%c     (Enter ESC to cancel)    %c\n", D_VERLINE, D_VERLINE);
            UI("lower double border", 32);
            colorChange(RESET, RESET);
            inputChar(inputName, &charCount, 12, &inputDesignator, 4);
            
            if (inputDesignator == 2)
            {
                searchIndex = boxSearch(boxmons, inputName, -1, *boxCounter, 0, "name");
                if (searchIndex == -1)
                {
                    UI("upper double border", 32);
                    printf("\n");
                    UI("mid hollow double", 32);
                    printf("\n");
                    printf("%c !!!    NAME NOT FOUND    !!! %c\n", D_VERLINE, D_VERLINE);
                    UI("mid hollow double", 32);
                    printf("\n");
                    UI("lower double border", 32);
                    timeDelay(2);
                    inputDesignator = 1;
                    charCount = 0;
                }
                else
                {
                    selector = searchIndex;
                    starter = 12 * (searchIndex / 12);
                    inputDesignator = 3;
                }
                charCount = 0;
                eraseChar(inputName, 12);
            }
        }

        while (inputDesignator == 2)
        {
            system("cls");
            UI("upper double border", 32);
            printf("\n%c          BOX SEARCH          %c\n", D_VERLINE, D_VERLINE);
            UI("mid dsd border", 32); 
            printf("\n");
            UI("mid hollow double", 32);
            printf("\n%c       Enter the Pokemon      %c", D_VERLINE, D_VERLINE);
            printf("\n%c           nickname:          %c", D_VERLINE, D_VERLINE);
            printf("\n%c            %s|", D_VERLINE, inputSN);
            UI("spacing", 17 - strlen(inputSN));
            printf("%c\n", D_VERLINE);
            UI("mid hollow double", 32);
            printf("\n%c     (Enter ESC to cancel)    %c\n", D_VERLINE, D_VERLINE);
            UI("lower double border", 32);
            colorChange(RESET, RESET);
            inputChar(inputSN, &charCount, 6, &inputDesignator, 4);

            if (inputDesignator == 3)
            {
                searchIndex = boxSearch(boxmons, inputSN, -1, *boxCounter, 1, "short name");
                if (searchIndex == -1)
                {
                    UI("upper double border", 32);
                    printf("\n");
                    UI("mid hollow double", 32);
                    printf("\n");
                    printf("%c !!!    NAME NOT FOUND    !!! %c\n", D_VERLINE, D_VERLINE);
                    UI("mid hollow double", 32);
                    printf("\n");
                    UI("lower double border", 32);
                    timeDelay(2);
                    inputDesignator = 2;
                }
                else
                {
                    selector = searchIndex;
                    starter = 12 * (searchIndex / 12);
                }
                charCount = 0;
                eraseChar(inputSN, 6);
            }
        }
    }
}

void explore(Entry fakemons[], Box boxmons[], int *boxCounter, int fakemonCounter)
{
    int i, j, 
        selector = 0,
        key = 0,
        nChoice = 0,
        isValidMove = 0,
        encounter,
        pokemonSelector,
        catch;

    while (key != ESC)
    {
        system("cls");
        printf("  ");
        UI("upper dsd border", 63);
        printf("\n  %c                         EXPLORATION                         %c\n  ", VERLINE, VERLINE);
        UI("lower dsd border", 63);
        printf("\n");
        for (i = 0; i < 5; i++)
        {
            printf("  ");
            for (j = 0; j < 7; j++)
                printTiles(i, j, selector);
            printf("\n");
        }

        printf("\n");
        colorChange(CYAN, RESET);
        printf("                  %c\n", TRIANGLE);
        printf("                ");
        colorChange(CYAN, RESET);
        printf("%c", L_TRIANGLE);
        colorChange(RESET, RESET);
        printf(" O ");
        colorChange(CYAN, RESET);
        printf("%c  -", R_TRIANGLE);
        colorChange(DARK_GREEN, RESET);
        printf("  MOVE   ");
        colorChange(RESET, RESET);
        printf("      ESC - Exit\n");
        printf("                  ");
        colorChange(CYAN, RESET);
        printf("%c\n", I_TRIANGLE);
        colorChange(RESET, RESET);

        isValidMove = 1;
        key = getch();
        if (key == 224)
        {
            switch (getch())
            {
            case LEFT:
            case UP:
                selector -= 1;
                break;
            case RIGHT:
            case DOWN:
                selector += 1;
                break;
            }
            if (selector > 6)
            {
                isValidMove = 0;
                selector--;
            }
            if (selector < 0)
            {
                isValidMove = 0;
                selector++;
            }
        }
        else isValidMove = 0;

        if (isValidMove)
        {
            encounter = rand() % 10;
            if (encounter < 4)              //40% chance to encounter
            {
                encounter = 1;
                nChoice = 0;
                pokemonSelector = rand() % fakemonCounter;

                while (key != ENTER)
                {
                    system("cls");
                    if (encounter)          
                    {          
                        for (j = 0; j <= 40; j++)
                        {
                            system("cls");
                            for (i = 0; i < 5; i++)
                            {
                                UI("spacing", j);
                                printPoke(i);
                            }
                            timeDelay(0.001);
                        }
                        encounter = 0;
                        UI("upper double border", 32);
                        printf("\n");
                        UI("mid hollow double", 32);
                        printf("\n%c  Wild %s appeared!", D_VERLINE, fakemons[pokemonSelector].name);
                        UI("spacing", 13 - strlen(fakemons[pokemonSelector].name));
                        printf("%c\n", D_VERLINE);
                        UI("mid hollow double", 32);
                        printf("\n");
                        UI("lower double border", 32);
                        timeDelay(2);
                    } 
                    else
                    {
                        for (i = 0; i < 5; i++)
                        {
                            UI("spacing", 40);
                            printPoke(i);
                        }
                    }
                    
                    system("cls");

                    for (i = 0; i < 5; i++)
                    {
                        UI("spacing", 40);
                        printPoke(i);
                    }

                    UI("upper double border", 32);
                    printf("\n");
                    UI("mid hollow double", 32);
                    printf("\n");
                    printf("%c  WHAT WOULD YOU LIKE TO DO?  %c", D_VERLINE, D_VERLINE);
                    printf("\n");
                    UI("mid hollow double", 32);
                    printf("\n");
                    
                    switch(nChoice)
                    {
                        case 0:
                            printf("%c     CATCH          %c ", D_VERLINE, L_SELECTOR);
                            colorChange(BLACK, WHITE);
                            printf("RUN");
                            colorChange(RESET, RESET);
                            printf(" %c   %c", R_SELECTOR, D_VERLINE);
                            printf("\n");
                            break;
                        case 1:
                            printf("%c   %c ", D_VERLINE, L_SELECTOR);
                            colorChange(BLACK, WHITE);
                            printf("CATCH");
                            colorChange(RESET, RESET);
                            printf(" %c         RUN      %c", R_SELECTOR, D_VERLINE);
                            printf("\n");
                            break;
                    }
                    UI("mid hollow double", 32);
                    printf("\n");
                    UI("lower double border", 32);
                    
                    key = arrowKey(key, 2);
                    if (key != ENTER)
                        nChoice = key;
                }
                key = 0;

                system("cls");
                for (i = 0; i < 5; i++)
                {
                    UI("spacing", 40);
                    printPoke(i);
                }

                if (nChoice == 1)
                {
                    system("cls");
                    for (j = 0; j <= 40; j++)
                    {
                        system("cls");
                        for (i = 0; i < 5; i++)
                        {
                            UI("spacing", j);
                            printBall(i);
                            printf("\n");
                        }
                        timeDelay(0.001);
                    }

                    catch = rand() % 10;
                    
                    timeDelay(2);
                    if (catch < 8)
                    {
                        UI("upper double border", 32);
                        printf("\n");
                        UI("mid hollow double", 32);
                        printf("\n%c  You caught the Pokemon!!!   %c\n", D_VERLINE, D_VERLINE);
                        UI("mid hollow double", 32);
                        printf("\n");
                        UI("lower double border", 32);
                        timeDelay(2);

                        boxmons[*boxCounter].slotNo = *boxCounter;
                        strcpy(boxmons[*boxCounter].name, fakemons[pokemonSelector].name);
                        strcpy(boxmons[*boxCounter].shortName, fakemons[pokemonSelector].shortName);
                        *boxCounter += 1;

                        if (!strcmp(fakemons[pokemonSelector].caught, "NO"))
                        {
                            strcpy(fakemons[pokemonSelector].caught, "YES");
                            system("cls");
                            viewEntry(fakemons, fakemonCounter, 4, pokemonSelector);
                        }
                    }
                    else
                    {
                        UI("upper double border", 32);
                        printf("\n");
                        UI("mid hollow double", 32);
                        printf("\n%c  The Pokemon broke free!!!   %c\n", D_VERLINE, D_VERLINE);
                        UI("mid hollow double", 32);
                        printf("\n");
                        UI("lower double border", 32);
                    }
                    timeDelay(2);
                }
                else if (nChoice == 0)
                {
                    UI("upper double border", 32);
                    printf("\n");
                    UI("mid hollow double", 32);
                    printf("\n%c  Wild %s fled!",D_VERLINE, fakemons[pokemonSelector].name);
                    UI("spacing", 17 - strlen(fakemons[pokemonSelector].name));
                    printf("%c\n", D_VERLINE);
                    UI("mid hollow double", 32);
                    printf("\n");
                    UI("lower double border", 32);
                    timeDelay(2);
                }
            }
        }
    }
}

/* SAVE AND LOAD */
void SaveProgress (Entry fakemons[], Box boxmons[], int fakemonCounter, int boxCounter)
{
    FILE *fp;                                   //file pointer
    char filename[12] = "",                     //name of the saved file
         playername[12],                        //name of the player
         savedFiles[MAX_SAVFILE][FILENAME_MAX]; //contains the name of saved files
    int key = 0,
        inputDesignator = 1,
        fileCounter = 0,
        i,
        isSave = 1;
    DIR *directory;                 //structure for reading directory

    directory = opendir(".");       //opens the current directory
    struct dirent *entity;          //structure for file information
    entity = readdir(directory);

    /*READING DIRECTORY*/
    while (entity != NULL && fileCounter < MAX_SAVFILE)
    {
        if (!strcmp(&entity->d_name[strlen(entity->d_name) - 8], "_sav.txt") &&
             entity->d_name[0] == '`')
        {
            strcpy(savedFiles[fileCounter], entity->d_name);
            fileCounter++;
        }     
        entity = readdir(directory);   
    }
    /*FILE NAMES SAVED*/    
    
    while (inputDesignator < 3)
    {
        UI("upper double border", 32);
        printf("\n%c         ...SAVING...         %c\n", D_VERLINE, D_VERLINE);
        UI("mid dsd border", 32);
        printf("\n%c       Enter your name:       %c", D_VERLINE, D_VERLINE);
        printf("\n%c         ", D_VERLINE);
        if (inputDesignator == 1)
        {
            printf("%s|", filename);
            UI("spacing", 20 - strlen(filename));
            printf("%c", D_VERLINE);
        }
        printf("\n");
        UI("mid hollow double", 32);
        printf("\n%c    (Enter ESC to cancel)     %c\n", D_VERLINE, D_VERLINE);
        UI("lower double border", 32);

        if (inputDesignator == 1)
            inputChar(filename, &key, 11, &inputDesignator, 3);

        if (inputDesignator == 2) 
        {
            strcpy(playername, filename);
            /*SAVED FILE MARKER*/
            filename[strlen(filename) + 1] = '\0';
            for (i = strlen(filename); i > 0; i--)
                filename[i] = filename[i-1];
            filename[0] = '`';
            strcat(filename, "_sav.txt");
            inputDesignator++;
        }
        else if (inputDesignator == 3)
            isSave = 0;
        system("cls");        
    }

    if (isSave && inputDesignator == 3)
    {
        /*SEARCH FOR DUPLICATE NAME*/
        if(stringSearch(savedFiles, filename, fileCounter, 0) != -1)
        {
            isSave = 0;
            system("cls");
            key = 0;                //initialized to the choice NO
            while (key != ENTER)
            {
                UI("upper double border", 32);
                printf("\n%c         ...SAVING...         %c\n", D_VERLINE, D_VERLINE);
                UI("mid dsd border", 32);
                printf("\n");
                UI("mid hollow double", 32);
                printf("\n%c   Matching filename found!   %c\n", D_VERLINE, D_VERLINE);
                UI("mid hollow double", 32);
                printf("\n%c   Would you like             %c\n", D_VERLINE, D_VERLINE);
                printf("%c   to overwrite the           %c\n", D_VERLINE, D_VERLINE);
                printf("%c   ", D_VERLINE);
                colorChange(BLACK, WHITE);
                printf("%s", playername);
                colorChange(RESET, RESET);
                printf("'s progress?");
                UI("spacing", 15 - strlen(playername));
                printf("%c\n", D_VERLINE);
                UI("mid hollow double", 32);
                printf("\n");
                if (key)
                {
                    printf("%c     %c ", D_VERLINE, L_SELECTOR);
                    colorChange(BLACK, WHITE);
                    printf("YES");
                    colorChange(RESET, RESET);
                    printf(" %c         NO       %c", R_SELECTOR, D_VERLINE);
                }
                else
                {
                    printf("%c      YES         %c ", D_VERLINE, L_SELECTOR);
                    colorChange(BLACK, WHITE);
                    printf("NO");
                    colorChange(RESET, RESET);
                    printf(" %c      %c", R_SELECTOR, D_VERLINE);
                }
                printf("\n");
                UI("mid hollow double", 32);
                printf("\n");
                UI("lower double border", 32);

                key = arrowKey(key, 2);
                if (key != ENTER)
                    isSave = key;
        
                system("cls");
            }
            if (!isSave) //if the user DOES NOT WANT TO OVERWRITE
                SaveProgress(fakemons, boxmons, fakemonCounter, boxCounter);
            else         //if the user OVERWRITE THE EXISTING FILE
            {
                UI("upper double border", 32);
                printf("\n%c         ...SAVING...         %c\n", D_VERLINE, D_VERLINE);
                UI("mid dsd border", 32);
                printf("\n");
                UI("mid hollow double", 32);
                printf("\n%c    File was overwritten.     %c\n", D_VERLINE, D_VERLINE);  
                UI("mid hollow double", 32);
                printf("\n");
                UI("lower double border", 32);
                timeDelay(2);
                isSave = 1;
            }
        }
        else
        {
            UI("upper double border", 32);
            printf("\n%c         ...SAVING...         %c\n", D_VERLINE, D_VERLINE);
            UI("mid dsd border", 32);
            printf("\n");
            UI("mid hollow double", 32);
            if (fileCounter < MAX_SAVFILE)
            {
                printf("\n%c   File saved successfully.   %c\n", D_VERLINE, D_VERLINE); 
                isSave = 1;
            }
            else 
            {
                printf("\n%c    !!!Max save reached!!!    %c\n", D_VERLINE, D_VERLINE); 
                isSave = 0;
            }
            UI("mid hollow double", 32);
            printf("\n");
            UI("lower double border", 32);
            timeDelay(2);
        }

        if (isSave)
        {
            fp = fopen(filename, "w");
            for(i = 0; i < fakemonCounter; i++)
            {
                fprintf(fp, "SLOT: %d\n", fakemons[i].slotNo);
                fprintf(fp, "NAME: %s\n", fakemons[i].name);
                fprintf(fp, "SHORT NAME: %s\n", fakemons[i].shortName);
                fprintf(fp, "DESCRIPTION: %s\n", fakemons[i].desc);
                fprintf(fp, "GENDER: %s\n", fakemons[i].gender);
                fprintf(fp, "CAUGHT: %s\n\n", fakemons[i].caught);
            }
            fprintf(fp, "--------- DEX END ---------\n");
            for(i = 0; i < boxCounter; i++)
            {
                fprintf(fp, "SLOT: %d\n", boxmons[i].slotNo);
                fprintf(fp, "NAME: %s\n", boxmons[i].name);
                fprintf(fp, "SHORT NAME: %s\n\n", boxmons[i].shortName);
            }
            fprintf(fp, "--------- BOX END ---------\n");
            fclose(fp);
        }

        system("cls");
    }
}

void LoadProgress (Entry fakemons[], Box boxmons[], int *fakemonCounter, int *boxCounter)
{
    int fileCounter = 0,            //file counter and identifier
        key = 0,
        choice = 0,
        i, j;
    char savedFiles[MAX_SAVFILE][FILENAME_MAX];  //contains the name of saved files
    char players[MAX_SAVFILE + 1][25];           //contains the name of the players - derived from the saved file
    char loadmarker[10];

    FILE *fp;                       //file pointer
    DIR *directory;                 //structure for reading directory

    directory = opendir(".");       //opens the current directory
    struct dirent *entity;          //structure for file information
    entity = readdir(directory);

    /*READING DIRECTORY*/
    while (entity != NULL && fileCounter < MAX_SAVFILE)
    {
        if (!strcmp(&entity->d_name[strlen(entity->d_name) - 8], "_sav.txt") &&
             entity->d_name[0] == '`')
        {
            strcpy(savedFiles[fileCounter], entity->d_name);
            fileCounter++;
        }     
        entity = readdir(directory);   
    }
    /*FILE NAMES SAVED*/

    /*EDITING THE FILES DETECTED - removing the prefix and suffix*/
    for (i = 0; i < fileCounter; i++)
    {
        strcpy(players[i], savedFiles[i]);
        for (j = 0; players[i][j] != '\0'; j++)
        {
            players[i][j] = players[i][j+1];
            if (players[i][j] == '_')
            {
                players[i][j] = '\0';
                players[i][j+1] = '\0';
            }
        }
    }
    strcpy(players[i], "Exit");

    if (fileCounter > 0) //if files are detected
    {
        while (key != ENTER)
        {       
            UI("upper double border", 32);
            printf("\n%c  Select a saved file below   %c\n", D_VERLINE, D_VERLINE);
            UI("mid dsd border", 32);
            for (i = 0; i <= fileCounter; i++)
            {
                printf("\n%c", D_VERLINE);
                if(i == choice)
                {
                    UI("spacing", 8);
                    printf("%c ", L_SELECTOR);
                    colorChange(BLACK, WHITE);
                    printf("%s", players[i]);
                    colorChange(RESET, RESET);
                    printf(" %c", R_SELECTOR);
                    UI("spacing", 18 - strlen(players[i]));
                }
                else
                {
                    UI("spacing", 10);
                    printf("%s", players[i]);
                    UI("spacing", 20 - strlen(players[i]));
                }
                printf("%c", D_VERLINE);
            }
            printf("\n");
            UI("lower double border", 32);
            key = arrowKey(key, fileCounter + 1);
            if (key != ENTER)
                choice = key;
            system("cls");
        }
        system("cls");
    }   
    else 
    {
        UI("upper double border", 32);
        printf("\n%c      You do not have any     %c\n", D_VERLINE, D_VERLINE);
        printf("%c          saved file.         %c\n", D_VERLINE, D_VERLINE);
        UI("lower double border", 32);
        timeDelay(2);
    }
    system("cls");

    /* LOADING PROPER 
        loads the fakemons from saved file
    */
    if (key == ENTER && choice != fileCounter)
    {
        resetEntryNBox(fakemons, boxmons, fakemonCounter, boxCounter);
        fp = fopen(savedFiles[choice],"r");
        fscanf(fp, "%s", loadmarker);
        for (i = 0; strcmp(loadmarker, "---------"); i++)
        {
            fscanf(fp, "%d", &fakemons[i].slotNo);
            fscanf(fp, "%*s %s", fakemons[i].name);
            fscanf(fp, "%*s %*s %s", fakemons[i].shortName);
            fscanf(fp, "%*s%*c");
            fgets(fakemons[i].desc, 301, fp);
            fscanf(fp, "%*s %s", fakemons[i].gender);
            fscanf(fp, "%*s %s", fakemons[i].caught);
            fscanf(fp, "%s", loadmarker);
            fakemons[i].desc[strlen(fakemons[i].desc) - 1] = '\0';
        }
        *fakemonCounter = i;
        fscanf(fp, "%*s %*s %*s"); //skips the fakedex end marker
        fscanf(fp, "%s", loadmarker);
        for (i = 0; strcmp(loadmarker, "---------"); i++)
        {
            fscanf(fp, "%d", &boxmons[i].slotNo);
            fscanf(fp, "%*s %s", boxmons[i].name);
            fscanf(fp, "%*s %*s %s", boxmons[i].shortName);
            fscanf(fp, "%s", loadmarker);
        }
        *boxCounter = i;
        fclose(fp);

        UI("upper double border", 32);
        printf("\n");
        UI("mid hollow double", 32);
        printf("\n%c   File loaded successfully!  %c\n", D_VERLINE, D_VERLINE);
        UI("mid hollow double", 32);
        printf("\n");
        UI("lower double border", 32);
        timeDelay(2);
        system("cls");
    } 
}