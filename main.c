#include <stdio.h>
#include <string.h>

typedef struct {
    char *username;
    long int ID;
} user;

user users[] = {
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

int num = sizeof(users) / sizeof(users[0]);

int loginUser(user users[], int num, char *input_name) {
    char end[10] = "exit";

    if (strcmp(end, input_name) == 0) {
        return 2;
    }

    for (int i = 0; i < num; i++) {
        if (strcmp(users[i].username, input_name) == 0) {
            return 1;
        }
    }
    return 0;
}

int loginID(user users[], int num, long int input_id) {
    for (int i = 0; i < num; i++) {
        if (users[i].ID == input_id) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char name[100];
    long int id;
    int pRun = 1;
    int run = 0;

    while (pRun == 1) {
        int logUser = 0;
        int logID = 0;

        while (logUser == 0) {
            printf("enter username: ");
            scanf("%99s", name);

            logUser = loginUser(users, num, name);

            if (logUser == 0) {
                printf("invalid username\n\n");
            }

            int count = 0;

            if (logUser == 1) {
                while (logID == 0) {
                    printf("enter ID: ");
                    scanf("%ld", &id);

                    logID = loginID(users, num, id);

                    if (logID == 0) {
                        printf("invalid ID\n\n");
                        count++;
                    }

                    if (count > 3) {
                        printf("too many tries \n");
                        pRun = 0;
                        break;
                    }
                }

                if (logID == 1) {
                    run = 1;
                }
            }

            if (logUser == 2) {
                pRun = 0;
                break;
            }
        }

        while (run) {
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
                    printf("Logging out.\n\n");
                    run = 0;
                    break;
                    
                default:
                    printf("Invalid option. Please choose again.\n\n");
            }
        }
    }
    
    return 0;
}

