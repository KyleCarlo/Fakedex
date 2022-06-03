#include <stdio.h>
#include <string.h>
#define listsize 150

typedef struct{
    char name[12];
    char shortName[6];
    char desc[301];
    char gender[8];
    char caught[4];
} Entry;

void functionalities(){
    printf("[1] Fakedex\n[2] Exploration\n[3] Box\n[4] Settings\n\n[0] Exit\n");
}

void fakedex(){
    printf("[1] Add Dex Entry\n[2] View Dex Entries\n[3] Update Dex Entry\n[4] Remove Dex Entry\n");

}

int search(){
    
}

void addEntry(){
    char tempName[12];
    printf("Enter name: ");
    scanf("%s", tempName);
    if(search() == 0){                    //check if name exists
        if(strlen(tempName) > 11){          //name length
            printf("NAME FIELD CAN HAVE AT MOST 11 CHARACTERS.\n");
        }
        else if(){                          //letter checker

        }
        else{                               //if valid
            
        }
    }
    else{
        //pompt for overwrite
    }
}

int main(){
    Entry entry[listsize];
    int nInput;
    functionalities();
    scanf("%d", &nInput);
    switch(nInput){
        case 1:                         //fakedex
            fakedex();
            scanf("%d", &nInput);
            switch(nInput){
                case 1:                     //add dex entry
                    addEntry();
                    break;
                case 2:                     //view dex entries
                    break;
                case 3:                     //update dex entries
                    break;
                case 4:                     //remove dex entries
                    break;
            }
            break;
        case 2:                         //exploration
        case 3:                         //box
        case 4:                         //settings
        case 0:                         //exit
    }
}