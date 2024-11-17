#include <stdio.h>
#include <string.h>

#define NUM_TEAMS 8
#define SQUAD_SIZE 13

typedef struct {
    int day;
    int month;
    int year;
} date_t;

typedef struct {
    char name[26]; // 25 Char + Null end
    int kitnum;
    char club[30];
    date_t DOB;
    char position[20]; 
} player_t;

typedef struct {
    char name[21]; 
    player_t players[SQUAD_SIZE];
    int activeSize;
} team_t;

//Prototypes

int display_menu();
void enroll_club(team_t teams[], int *teamcount);
void add_player(team_t teams[], int teamcount);
void search_update(team_t teams[], int teamcount);
void displayclubstats(team_t teams[], int teamcount);
void errormessage(const char *message);

int main() {
    team_t teams[NUM_TEAMS];
    int teamcount = 0;
    int choice;

    while (1) {
        choice = display_menu();
        
        switch (choice) {
            case 1:
                enroll_club(teams, &teamcount);
                break;
            case 2:
                add_player(teams, teamcount);
                break;
            case 3:
                search_update(teams, teamcount);
                break;
            case 4:
                displayclubstats(teams, teamcount);
                break;
            default:
                printf("Exiting program. Goodbye!\n");
                return 0;
        }
    }
}

int display_menu() {
    int num;
    printf("||Menu||\n\n");
    printf("1. Enroll Club\n2. Add Player\n3. Search and Update Player\n4. Display Club Statistics\nAny other number to exit\n\n");
    printf("Enter your choice: ");
    scanf("%d", &num);
    return num;
}

void enroll_club(team_t teams[], int *teamcount) {
    if (*teamcount >= NUM_TEAMS) {
        errormessage("Maximum number of teams reached.");
        return;
    }

    printf("Enter club name: ");
    scanf(" %[^\n]", teams[*teamcount].name);
    teams[*teamcount].activeSize = 0;
    (*teamcount)++;
    printf("Club enrolled successfully.\n");
}

void add_player(team_t teams[], int teamcount) {
    if (teamcount == 0) {
        errormessage("No clubs enrolled yet.");
        return;
    }

    printf("Pick a club (1 to %d): ", teamcount);
    int clubid = -1;
    scanf("%d", &clubid);

    if (clubid < 0 || clubid >= teamcount) {
        errormessage("Invalid club ID.");
        return;
    }

    if (teams[clubid].activeSize >= SQUAD_SIZE) {
        errormessage("Squad is full.");
        return;
    }

    player_t newplayer;
    printf("Enter player name: ");
    scanf(" %[^\n]", newplayer.name);
    printf("Enter kit number: ");
    scanf("%d", &newplayer.kitnum);
    printf("Enter birth date (dd mm yyyy): ");
    scanf("%d %d %d", &newplayer.DOB.day, &newplayer.DOB.month, &newplayer.DOB.year);
    printf("Enter position: ");
    scanf(" %[^\n]", newplayer.position);

    // Check for duplicates
    for (int i = 0; i < teams[clubid].activeSize; i++) {
        if (strcmp(teams[clubid].players[i].name, newplayer.name) == 0 || teams[clubid].players[i].kitnum == newplayer.kitnum) {
            errormessage("Duplicate player name or kit number found.");
            return;
        }
    }

    teams[clubid].players[teams[clubid].activeSize] = newplayer;
    teams[clubid].activeSize++;
    printf("Player added successfully.\n");
}

void displayclubstats(team_t teams[], int teamcount) {
    if (teamcount == 0) {
        errormessage("No clubs enrolled yet.");
        return;
    }

    for (int i = 0; i < teamcount; i++) {
        printf("Club: %s\n", teams[i].name);
        printf("Number of players: %d\n", teams[i].activeSize);

        if (teams[i].activeSize > 0) {
            int total_age = 0;
            int current_year = 2024; // Update this to the current year

            for (int j = 0; j < teams[i].activeSize; j++) {
                int age = current_year - teams[i].players[j].DOB.year;
                total_age += age;
            }

            double average_age = (double)total_age / teams[i].activeSize;
            printf("Average age of players: %.2f\n", average_age);
        } else {
            printf("No players in this club.\n");
        }

        printf("\n");
    }
}


void search_update(team_t teams[], int teamcount) {
    if (teamcount == 0) {
        errormessage("No clubs enrolled yet.");
        return;
    }

    char search_name[26];
    int search_kitnum;
    int choice;

    printf("Search by:\n1. Player Name\n2. Kit Number\nEnter your choice: ");
    scanf("%d", &choice);

    int found = 0;
    player_t *player = NULL;
    team_t *team = NULL;

    if (choice == 1) {
        printf("Enter player name: ");
        scanf(" %[^\n]", search_name);

        for (int i = 0; i < teamcount; i++) {
            for (int j = 0; j < teams[i].activeSize; j++) {
                if (strcmp(teams[i].players[j].name, search_name) == 0) {
                    player = &teams[i].players[j];
                    team = &teams[i];
                    found = 1;
                    break;
                }
            }
            if (found) break;
        }
    } else if (choice == 2) {
        printf("Enter kit number: ");
        scanf("%d", &search_kitnum);

        for (int i = 0; i < teamcount; i++) {
            for (int j = 0; j < teams[i].activeSize; j++) {
                if (teams[i].players[j].kitnum == search_kitnum) {
                    player = &teams[i].players[j];
                    team = &teams[i];
                    found = 1;
                    break;
                }
            }
            if (found) break;
        }
    } else {
        errormessage("Invalid choice.");
        return;
    }

    if (!found) {
        errormessage("Player not found.");
        return;
    }

    printf("Player found in club: %s\n", team->name);
    printf("1. Update Name\n2. Update Kit Number\n3. Update Birth Date\n4. Update Position\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf(" %[^\n]", player->name);
            break;
        case 2:
            printf("Enter new kit number: ");
            scanf("%d", &player->kitnum);
            break;
        case 3:
            printf("Enter new birth date (dd mm yyyy): ");
            scanf("%d %d %d", &player->DOB.day, &player->DOB.month, &player->DOB.year);
            break;
        case 4:
            printf("Enter new position: ");
            scanf(" %[^\n]", player->position);
            break;
        default:
            errormessage("Invalid choice.");
            return;
    }

    printf("Player details updated successfully.\n");
}


void errormessage(const char *message) {
    printf("Error: %s\n", message);
}
