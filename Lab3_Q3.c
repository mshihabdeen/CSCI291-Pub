#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SQUAD_SIZE 11
#define NUM_TEAMS 8

struct age
{
    int day;
    int month;
    int year;
};

struct player_t
{
    char name[25];
    int kitnum;
    char club[30];
    struct age playerage;
    char position[20];
};

struct team_t{
    char name[20];
    struct player_t players[SQUAD_SIZE];
    int activeSize;
};

//Variables

int teamcount = 0;
struct team_t Teams[NUM_TEAMS];

//Prototypes
void menu();
int enrollclub();
void addplayer();
void searchupdate();
void displaystats();



//main
int main() {
    menu();
}


//Functions
void menu(){
    while(1){
        int i = 0;

        printf("\nMain Menu\n1. Enroll Club\n2. Add Player\n3. Search and Update Player Details\n4. Display Club Stats\n5. Exit\n\n");
        scanf("%d",&i);

        switch (i) {
            case 1:
                enrollclub();
                break;
            case 2:
                addplayer();
                break;
            case 3:
                //searchupdate();
                break;
            case 4:
                //displaystats();
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("Invalid Selection. Try Again");

        }

    }
}

int enrollclub(){
    if ((teamcount) >= NUM_TEAMS-1){
        printf("Cannot Enroll Team; No Vacancies\n");
        return 0;
    }
    else{
        printf("Enter club name: ");
        fgets(Teams[teamcount].name, 20, stdin);
        Teams[teamcount].name[strcspn(Teams[teamcount].name, "\n")] = '\0';
        Teams[teamcount].activeSize = 0;
        printf("Club enrolled successfully.\n");
        teamcount++;
        return 0;
    }
}

void addplayer(){
    int clubid;
    printf("Select Club ID (0-%d): ", teamcount);
    for (int i=0;i<NUM_TEAMS;i++){
        printf("\n%s",Teams[i].name);
    }
    scanf("%d", &clubid);

}


