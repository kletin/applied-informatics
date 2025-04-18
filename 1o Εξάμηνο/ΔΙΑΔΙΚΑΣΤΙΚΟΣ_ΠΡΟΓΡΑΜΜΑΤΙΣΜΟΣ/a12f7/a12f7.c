#include <stdio.h>
#include "genlib.h"
#include "simpio.h"
#include <string.h>

#define MAX_NAMES 100
#define MAX_NAME_LENGTH 20

int main() {
char names[MAX_NAMES][MAX_NAME_LENGTH];
int nameCount = 0;
char newName[MAX_NAME_LENGTH];


while(nameCount < MAX_NAMES) {

    printf("Passenger in seat %d :",(nameCount + 1));
    scanf("%s", newName);

    if(strcmp(newName, "----") == 0) {
        break;}


    int duplicate = 0;
    for(int i = 0; i < nameCount; i++) {
        if(strcmp(newName, names[i]) == 0) {
            printf("Passenger %s already exists.\n",names[i]);
            duplicate = 1;
            break;
        }
    }

    if(!duplicate) {
        strcpy(names[nameCount], newName);
        nameCount++;
    }
}

printf("\nPassenger List\n");
printf("--------------\n");
for(int i = 0; i < nameCount; i++) {
    printf("In seat %d:%s\n", i + 1, names[i]);
}

return 0;

}
