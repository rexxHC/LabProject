#include <arm/types.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    long int ID;
} user;

typedef struct {
    char *admin;
} Admin;

Admin keys[] = { // implement the djb2 hash for this
    {"RejuanaIslam115"},
    {"RajeshPalitRJP115"},
    {"meowLord67"}
}; //load this from a file figure ts out

int adminSize = sizeof(keys) / sizeof(keys[0]);

user users[] = { // djb2 hash for the usernames and uint32 or uint64 for ID hashing
    {"AbiraSorowar", 2513491630},
    {"MstNurAAfsanur", 2532692642},
    {"AnilBanik", 2534231642},
    {"RatulBanik", 2533081642},
    {"ArnobBiswas", 2532531042},
    {"NehanChowdhury", 2534512642},
    {"MdNaofilIslamEmon", 2534017642},
    {"KhandakerAhnafTahmidEnan", 2531312642},
    {"AnikGhosh", 2534167042},
    {"KaziMdInjamamulHoque", 2531183642},
    {"MahbubIntisar", 2533512042},
    {"AbdullahMohammadJubayer", 2531483042},
    {"TahsinZamanMashrim", 2531753642},
    {"MdTahsanMasud", 2534470642},
    {"KhandakerJannatulMawa", 2531368042},
    {"JasiyaMohayra", 2533672042},
    {"TahiyaMohayra", 2533632042},
    {"MdMarufRabbiMoon", 253192842},
    {"SyadaNusratNahar", 2531955042},
    {"AbdullahAlNahian", 2531681642},
    {"SheikhNahianNaji", 2533163042},
    {"MdAdnanSiddiqueNeon", 2532222042},
    {"LamiaMehzadNirbindha", 2531016642},
    {"AtifUlQuadir", 2533574042},
    {"SadmanRahatRafi", 2532371042},
    {"SkRakinulHaque", 2532182642},
    {"ANSamiullah", 2531751042},
    {"MymunaSarker", 2531428642},
    {"AliHasanShadman", 2531451042},
    {"MashrikaMuntahinSiddiqui", 2531731042},
    {"TamimSadiqSneho", 2531929642},
    {"TawfiqueOmarTazwar", 2533259642},
    {"TarannumBinteMatiur", 2311647643}
};

int userSize = sizeof(users) / sizeof(users[0]);

int loginUser(user users[], int userSize, char *input_name, Admin keys[], int adminSize) {
    char end[10] = "exit";

    for(int i = 0; i < adminSize; i++){
        if(strcmp(keys[i].admin, input_name) == 0){
            return 3;
        }
    }
    
    if (strcmp(end, input_name) == 0) {
        return 2;
    }

    for (int i = 0; i < userSize; i++) {
        if (strcmp(users[i].username, input_name) == 0) {
            return 1;
        }
    }
    return 0;
}

int loginID(user users[], int userSize, long int input_id) {
    for (int i = 0; i < userSize; i++) {
        if (users[i].ID == input_id) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char name[100];
    long int id;
    int loginMenu = 1; // Controls the primary login loop
    int programMenu = 0; // Controls which main menu (Student: 1, Admin: 2, None: 0) is active

    while (loginMenu == 1) {
        int logUser = 0;
        int logID = 0;

        // --- 1. Login Authentication Loop (Username/Admin Check) ---
        // This loop continues until a valid username, admin key, or 'exit' is entered.
        while (logUser == 0) {
            printf("enter username: ");
            scanf("%99s", name);

            logUser = loginUser(users, userSize, name, keys, adminSize);

            if (logUser == 0) {
                printf("invalid username\n\n");
            }

            int try = 0;

            // Handle successful Student Login
            if (logUser == 1) {
                while (logID == 0) {
                    printf("enter ID: ");
                    scanf("%ld", &id);

                    logID = loginID(users, userSize, id);

                    if (logID == 0) {
                        printf("invalid ID\n\n");
                        try++;
                    }

                    if (try > 3) {
                        printf("too many tries \n");
                        loginMenu = 0; // Terminate entirely
                        break;
                    }
                }

                if (logID == 1) {
                    programMenu = 1; // Student Menu
                    printf("Login successful!!\n\n");
                    // We need to exit the inner logUser loop immediately
                    logUser = -1; 
                }
            }

            // Handle 'exit' command
            if (logUser == 2) {
                loginMenu = 0; // Terminate entirely
                break;
            }

            // Handle successful Admin Login 
            if (logUser == 3){
                printf("admin perms granted \n\n");
                programMenu = 2; // Admin Menu
                // We need to exit the inner logUser loop immediately
                logUser = -1;
            }
        }
        
        // If we broke out due to 'exit' or too many ID tries, jump to end of outer loop
        if (loginMenu == 0) {
            break;
        }

        // --- 2. Program Menu Loop (Student: programMenu == 1) ---
        // Once the user logs in, they enter this loop.
        while (programMenu == 1) {
            int nav = 0;
            printf("\nMain Menu:\n");
            printf("1. Student Resources\n");
            printf("2. Calculation Resources\n");
            printf("3. Miscellaneous\n");
            printf("4. Logout\n");
            printf("Choose an option: ");
            scanf("%d", &nav);

            switch (nav) {
                case 1: {
                    int sub = -1;
                    while (sub != 0) {
                        printf("\n**Student Resources Menu**\n");
                        printf("1. Notes\n");
                        printf("2. Study Materials\n");
                        printf("0. Back to Main Menu\n");
                        printf("Choose an option: ");
                        scanf("%d", &sub);
                        
                        switch (sub) {
                            case 1:
                                printf("Showing Notes...\n");
                                break;
                            case 2:
                                printf("Showing Study Materials...\n");
                                break;
                            case 0:
                                printf("Returning to Main Menu...\n");
                                break;
                            default:
                                printf("Invalid option.\n");
                        }
                    }
                    break;
                }
                
                case 2: {
                    int sub = -1;
                    while (sub != 0) {
                        printf("\n**Calculation Resources Menu**\n");
                        printf("1. Calculator\n");
                        printf("2. Converter\n");
                        printf("0. Back to Main Menu\n");
                        printf("Choose an option: ");
                        scanf("%d", &sub);
                        
                        switch (sub) {
                            case 1:
                                printf("Calculator selected...\n");
                                break;
                            case 2:
                                printf("Converter selected...\n");
                                break;
                            case 0:
                                printf("Returning to Main Menu...\n");
                                break;
                            default:
                                printf("Invalid option.\n");
                        }
                    }
                    break;
                }
                
                case 3: {
                    int sub = -1;
                    while (sub != 0) {
                        printf("\n**Miscellaneous Menu**\n");
                        printf("1. Random Facts\n");
                        printf("2. Jokes\n");
                        printf("0. Back to Main Menu\n");
                        printf("Choose an option: ");
                        scanf("%d", &sub);
                        
                        switch (sub) {
                            case 1:
                                printf("Random Facts...\n");
                                break;
                            case 2:
                                printf("Jokes...\n");
                                break;
                            case 0:
                                printf("Returning to Main Menu...\n");
                                break;
                            default:
                                printf("Invalid option.\n");
                        }
                    }
                    break;
                }
                
                case 4:
                    printf("Logging out from Student Menu.\n\n");
                    programMenu = 0; // Exits this loop and goes back to loginMenu loop
                    break;
                    
                default:
                    printf("Invalid option. Please choose again.\n\n");
            }
        }
        
        // --- 3. Program Menu Loop (Admin: programMenu == 2) ---
        // Once the admin logs in, they enter this loop.
        while (programMenu == 2) {
            int nav = 0;
            printf("\nAdmin Main Menu:\n");
            printf("1. Attendance\n");
            printf("2. Student files\n");
            printf("3. Add participants\n");
            printf("4. Logout\n");
            printf("Choose an option: ");
            scanf("%d", &nav);

            switch (nav) {
                case 1: {
                    // --- Attendance Sub-menu ---
                    int sub = -1;
                    while (sub != 0) {
                        printf("\n**Attendance Menu**\n");
                        printf("1. View Attendance\n");
                        printf("2. Mark Attendance\n");
                        printf("0. Back to Main Menu\n");
                        printf("Choose an option: ");
                        scanf("%d", &sub);
                        
                        switch (sub) {
                            case 1:
                                printf("Viewing attendance records...\n");
                                break;
                            case 2:
                                printf("Marking attendance...\n");
                                break;
                            case 0:
                                printf("Returning to Admin Main Menu...\n");
                                break;
                            default:
                                printf("Invalid option.\n");
                        }
                    }
                    break;
                }
                
                case 2: {
                    // --- Student Files Sub-menu ---
                    int sub = -1;
                    while (sub != 0) {
                        printf("\n**Student Files Menu**\n");
                        printf("1. View Files\n");
                        printf("2. Edit Files\n");
                        printf("0. Back to Main Menu\n");
                        printf("Choose an option: ");
                        scanf("%d", &sub);
                        
                        switch (sub) {
                            case 1:
                                printf("Viewing student files...\n");
                                break;
                            case 2:
                                printf("Editing student files...\n");
                                break;
                            case 0:
                                printf("Returning to Admin Main Menu...\n");
                                break;
                            default:
                                printf("Invalid option.\n");
                        }
                    }
                    break;
                }
                
                case 3: {
                    // --- Add Participants Action (No Sub-menu needed) ---
                    printf("\nAdding new participants...\n");
                    break;
                }
                
                case 4:
                    printf("Logging out from Admin Menu.\n\n");
                    programMenu = 0; // FIX 2: Exits this loop, but the outer 'while (loginMenu == 1)' loop restarts the process.
                    break;
                    
                default:
                    printf("Invalid option. Please choose again.\n\n");
            }
        }
        // Since loginMenu is still 1 here, the loop restarts, prompting for username again.
    }
    
    printf("Program terminated.\n");
    return 0;
}
