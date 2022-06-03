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

void printMainMenu()
{
    printf("---------------------\n\n");

}

void main(){
    colorChange(WHITE, DARK_GREEN);
    printf("%c %c %c\n",218, 30, 191);
    printf("%c %c %c\n",17,  'O', 16);
    printf("%c %c %c\n",192, 31, 217);
    colorChange(DARK_GREEN, LIGHT_GREEN);
    for (int j = 0; j < 3; j++)
    {    
        for (int i = 0; i < 5; i++)
        {
            printf("%c", 30);
        }
        printf("\n");
    }
    colorChange(LIGHT_GREEN, DARK_GREEN);
    for (int j = 0; j < 3; j++)
    {    
        for (int i = 0; i < 5; i++)
        {
            printf("%c", 30);
        }
        printf("\n");
    }
    colorChange(DARK_GREEN, LIGHT_GREEN);
    for (int j = 0; j < 3; j++)
    {    
        for (int i = 0; i < 5; i++)
        {
            printf("%c", 30);
        }
        printf("\n");
    }
    colorChange(RESET, RESET);
    // srand(time(NULL));
    // if (rand() % 10 <= 3)

}