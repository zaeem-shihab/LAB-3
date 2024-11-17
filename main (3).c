
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// --- CORE CONSTANTS --- //
#define NUM_TEAMS 10          // Maximum number of teams in the league
#define SQUAD_SIZE 15         // Maximum players per team as per rules
#define KIT_MIN 1             // Minimum kit number as per rules
#define KIT_MAX 99            // Maximum kit number as per rules
#define AGE_MIN 16            // Minimum player age as per the rules
#define AGE_MAX 45            // Maximum player age as per the rules

// --- STRUCTURE DEFINITIONS --- //
typedef struct {
    int day, month, year;     // Date of Birth format: Day, Month, Year
} age_t;

typedef struct {
    char name[25];            // Full player name with limit
    int kit_number;           // Unique kit number
    char club[30];            // Club name
    age_t dob;                // Player's date of birth
    char position[20];        // Player's preferred position
} player_t;

typedef struct {
    char name[20];            // Team name
    player_t players[SQUAD_SIZE]; // Array of players
    int active_size;          // Number of players in the team
} team_t;

// --- GLOBAL VARIABLES --- //
team_t league_teams[NUM_TEAMS]; // League teams array
int current_team_count = 0;     // Number of teams enrolled in the league

// --- FUNCTION PROTOTYPES --- //
void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void handle_error(const char *message);
int validate_kit_number(int kit_number);
int validate_age(int birth_year);
int get_club_index();

// --- MAIN FUNCTION --- //
int main() {
    int choice;

    while (1) {
        display_menu();
        if (scanf("%d", &choice) != 1) { // Validates the numeric input
            while (getchar() != '\n');   // Clears invalid input
            handle_error("[ ! ] Invalid input");
            continue;
        }

        switch (choice) {
            case 1: enroll_club(); break;
            case 2: add_player(); break;
            case 3: search_update(); break;
            case 4: display_club_statistics(); break;
            case 5: printf("\n[ > ] System shutting down...\n"); return 0;
            default: handle_error("[ ! ] Invalid input");
        }
    }
}

// --- DISPLAY MAIN MENU --- //
void display_menu() {
    printf("\n==== LEAGUE SYSTEM CONTROL PANEL ===\n");
    printf(" [1] Enroll New Club            \n");
    printf(" [2] Add Player to Club         \n");
    printf(" [3] Search & Update Player     \n");
    printf(" [4] Display Statistics         \n");
    printf(" [5] Exit System                \n");
    printf("====================================\n");
    printf("[SYS] Choose your option: ");
}

// --- ENROLL A NEW CLUB --- //
void enroll_club() {
    if (current_team_count >= NUM_TEAMS) {
        handle_error("Club limit reached. Enrollment not possible.");
        return;
    }

    printf("> [SYSTEM] Enter the club name (MAX CHAR 20): ");
    scanf(" %[^\n]", league_teams[current_team_count].name);

    // Enforces character limit for a clubs name
    if (strlen(league_teams[current_team_count].name) > 20) {
        handle_error("[ALERT] Club name exceeds Max Char Limit (20). Please revise your entry.");
        return;
    }

    league_teams[current_team_count].active_size = 0; // Initializes the player count
    current_team_count++;
    printf(">> [STATUS UPDATE] Club '%s' has been successfully enrolled in the system.\n", league_teams[current_team_count - 1].name);
}

// --- ADD PLAYER TO CLUB --- //
void add_player() {
    if (current_team_count == 0) {
        handle_error("No clubs detected! Enroll a club to proceed.");
        return;
    }

    int club_index = get_club_index(); // Asks the user to select a valid club
    if (club_index == -1) return;     // Exits if the club selection fails

    if (league_teams[club_index].active_size >= SQUAD_SIZE) {
        handle_error("Team capacity exceeded. No more players can be added.");
        return;
    }

    player_t new_player;

    printf("> [ACTION] Enter player's full name: ");
    scanf(" %[^\n]", new_player.name);

    printf("> [ACTION] Enter kit number (%d-%d): ", KIT_MIN, KIT_MAX);
    if (scanf("%d", &new_player.kit_number) != 1 || !validate_kit_number(new_player.kit_number)) {
        handle_error("Invalid kit number. Range: 1 - 99.");
        return;
    }

    printf("> [ACTION] Enter position: ");
    scanf(" %[^\n]", new_player.position);

    printf("> [ACTION] Enter date of birth (dd mm yyyy): ");
    if (scanf("%d %d %d", &new_player.dob.day, &new_player.dob.month, &new_player.dob.year) != 3 ||
        !validate_age(new_player.dob.year)) {
        handle_error("Invalid date of birth. Age range: 16 - 45 years.");
        return;
    }

    // Checks for duplicates
    for (int i = 0; i < league_teams[club_index].active_size; i++) {
        if (strcmp(league_teams[club_index].players[i].name, new_player.name) == 0 ||
            league_teams[club_index].players[i].kit_number == new_player.kit_number) {
            handle_error("Duplicate entry detected! Player name or kit number must be unique.");
            return;
        }
    }

    // Adds a player to the club
    league_teams[club_index].players[league_teams[club_index].active_size++] = new_player;
    printf(">> [STATUS UPDATE] Player '%s' added to '%s'.\n", new_player.name, league_teams[club_index].name);
}

// --- GET VALID CLUB INDEX --- //
int get_club_index() {
    int choice;
    printf("\n========== SELECT A CLUB ==========\n");
    for (int i = 0; i < current_team_count; i++) {
        printf("[%d] %s\n", i + 1, league_teams[i].name);
    }
    printf("===================================\n");
    printf("> [ACTION] Choose a club by number: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > current_team_count) {
        while (getchar() != '\n'); // Clears the invalid input
        handle_error("Invalid selection! Please choose a valid club to proceed.");
        return -1;
    }
    return choice - 1; // Returns a valid club index
}

// --- VALIDATE KIT NUMBER --- //
int validate_kit_number(int kit_number) {
    return (kit_number >= KIT_MIN && kit_number <= KIT_MAX);
}

// --- VALIDATE PLAYER AGE --- //
int validate_age(int birth_year) {
    int current_year = 2024;
    int age = current_year - birth_year;
    return (age >= AGE_MIN && age <= AGE_MAX);
}

// --- ERROR HANDLING --- //
void handle_error(const char *message) {
    printf("[ERROR] %s\n", message);
}

// --- SEARCH AND UPDATE PLAYER DETAILS --- //
void search_update() {
    if (current_team_count == 0) {
        handle_error("No clubs identified! Please enroll a club first.");
        return;
    }

    printf("\n========== SEARCH PLAYER ==========\n");
    printf("[1] Search by Name\n");
    printf("[2] Search by Kit Number\n");
    printf("===================================\n");
    printf("> [ACTION] Choose a search option: ");

    int search_option;
    if (scanf("%d", &search_option) != 1 || (search_option != 1 && search_option != 2)) {
        while (getchar() != '\n'); // Clears the invalid input
        handle_error("Invalid selection! Please choose either option 1 or option 2.");
        return;
    }

    if (search_option == 1) {
        char search_name[25];
        printf("> [ACTION] Enter player name to search: ");
        scanf(" %[^\n]", search_name);

        for (int i = 0; i < current_team_count; i++) {
            for (int j = 0; j < league_teams[i].active_size; j++) {
                if (strcasecmp(league_teams[i].players[j].name, search_name) == 0) {
                    printf("[INFO] Player found in Club '%s':\n", league_teams[i].name);
                    printf("       Name: %s\n", league_teams[i].players[j].name);
                    printf("       Kit Number: %d\n", league_teams[i].players[j].kit_number);
                    printf("       Position: %s\n", league_teams[i].players[j].position);

                    printf("> [ACTION] Enter new position for the player: ");
                    scanf(" %[^\n]", league_teams[i].players[j].position);
                    printf(">> [STATUS UPDATE] Player details updated successfully.\n");
                    return;
                }
            }
        }
        handle_error("Player not found. Please recheck your input.");
    } else if (search_option == 2) {
        int kit_number;
        printf("> [ACTION] Enter kit number to search: ");
        if (scanf("%d", &kit_number) != 1) {
            while (getchar() != '\n'); // Clears the invalid input
            handle_error("Invalid input for kit number.");
            return;
        }

        for (int i = 0; i < current_team_count; i++) {
            for (int j = 0; j < league_teams[i].active_size; j++) {
                if (league_teams[i].players[j].kit_number == kit_number) {
                    printf("[INFO] Player found in Club '%s':\n", league_teams[i].name);
                    printf("       Name: %s\n", league_teams[i].players[j].name);
                    printf("       Kit Number: %d\n", league_teams[i].players[j].kit_number);
                    printf("       Position: %s\n", league_teams[i].players[j].position);

                    printf("> [ACTION] Enter new position for the player: ");
                    scanf(" %[^\n]", league_teams[i].players[j].position);
                    printf(">> [STATUS UPDATE] Player details updated successfully.\n");
                    return;
                }
            }
        }
        handle_error("Player not found.");
    }
}

// --- DISPLAY CLUB STATISTICS --- //
void display_club_statistics() {
    if (current_team_count == 0) {
        handle_error("No clubs are available! Please enroll a club first.");
        return;
    }

    printf("\n========== LEAGUE STATISTICS ==========\n");
    for (int i = 0; i < current_team_count; i++) {
        printf("\n[TEAM] Club: %s\n", league_teams[i].name);
        printf("[INFO] Number of Players: %d\n", league_teams[i].active_size);

        if (league_teams[i].active_size == 0) {
            printf("[ALERT] This team has no players yet.\n");
            continue;
        }

        int total_age = 0;
        for (int j = 0; j < league_teams[i].active_size; j++) {
            int age = 2024 - league_teams[i].players[j].dob.year;
            total_age += age;

            printf("[PLAYER] Name: %s\n", league_teams[i].players[j].name);
            printf("         Kit Number: %d\n", league_teams[i].players[j].kit_number);
            printf("         Age: %d\n", age);
            printf("         Position: %s\n", league_teams[i].players[j].position);
        }

        float average_age = (float)total_age / league_teams[i].active_size;
        printf("[STATS] Average Player Age: %.2f\n", average_age);
    }
    printf("========================================\n");
}
