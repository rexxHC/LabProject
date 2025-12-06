#include <stdio.h>
#include <string.h>

typedef struct {
  char *username;
  char *id_number;
  char *password;
} user;

typedef struct {
  char *admin_name;
  char *admin_password;
} admin;

void registerUser(void);
int login(char *input_name, char *input_password, user users[], admin admins[]);
void insertName(char *name);
void insertPassword(char *password);
void saveUsers(void);
void loadUsers(void);
void studentMenu(void);
void adminMenu(void);


user users[100];

int userSize = 0;

admin admins[] = {
    {"RejuanaIslam115", "admin123"},  // Added password for testing
    {"meowLord67", "admin456"}
};

int adminSize = sizeof(admins) / sizeof(admins[0]);

void registerUser(void) {

  if(userSize >= 100) {
    printf("user limit reached\n");
    return;
  }

  char username[20];
  printf("enter username: ");
  scanf("%19s", username);

  char id[10];
  printf("enter your NSU id number: ");
  scanf("%9s", id);

  char password_1[50];
  printf("enter password: ");
  scanf("%49s", password_1);

  char password_2[50];
  printf("enter password again: ");
  scanf("%49s", password_2);
  
  if(strcmp(password_1, password_2) == 0) {
    users[userSize].username = strdup(username);
    users[userSize].id_number = strdup(id);
    users[userSize].password = strdup(password_2);
    userSize++;
    saveUsers();
    printf("registry successful!!\n\n\n");
  } else {
    printf("passwords do not match!!!!\n\n");
  }
}

int login(char *input_name, char *input_password, user users[], admin admins[]) {

  for(int i = 0; i < adminSize; i++){
    if(admins[i].admin_password != NULL && strcmp(admins[i].admin_name, input_name) == 0) {
      if(strcmp(admins[i].admin_password, input_password) == 0) {
        return 2;
      }
    }
  }

  for(int i = 0; i < userSize; i++) {
    if(strcmp(users[i].username, input_name) == 0 || strcmp(users[i].id_number, input_name) == 0) {
      if(strcmp(users[i].password, input_password) == 0) {
        return 1;
      }
    }
  }

  return 0;
}

void insertName(char *name){
  printf("enter username / nsu id: ");
  scanf("%49s", name);
}

void insertPassword(char *password){
  printf("enter password: ");
  scanf("%49s", password);
}

void saveUsers(void) {
    FILE *f = fopen("users.txt", "w");
    if (!f) {
        printf("error!!\n\n");
        return;
    }

    for(int i = 0; i < userSize; i++) {
          fprintf(f, "%d %s %s %s\n", i, users[i].username, users[i].id_number, users[i].password);
    }
        
    fclose(f);
}

void loadUsers(void) {
    FILE *f = fopen("users.txt", "r");
    if (!f) {
        return;
    }

    char uname[50], id[20], pass[50];
    int i;

    while (userSize < 100 && fscanf(f, "%d %s %s %s", &i, uname, id, pass) == 4) {
        users[userSize].username  = strdup(uname);
        users[userSize].id_number = strdup(id);
        users[userSize].password  = strdup(pass);
        userSize++;
    }

    fclose(f);
}

void studentMenu(void) {
    int nav = 0;
    
    while(nav != 4) {
        printf("\n Student Main Menu \n");
        printf("1. student resources\n");
        printf("2. calculation resources\n");
        printf("3. miscellaneous\n");
        printf("4. logout\n");
        printf("choose an option: ");
        scanf("%d", &nav);

        switch (nav) {
            case 1: {
                int sub = -1;
                while (sub != 0) {
                    printf("\n resources menu**\n");
                    printf("1. notes\n");
                    printf("2. study materials\n");
                    printf("0. back\n");
                    printf("choose an option: ");
                    scanf("%d", &sub);
                    
                    switch (sub) {
                        case 1:
                            printf("Showing Notes...\n");
                            break;
                        case 2:
                            printf("Showing Study Materials...\n");
                            break;
                        case 0:
                            printf("returning ...\n");
                            break;
                        default:
                            printf("invalid option.\n");
                    }
                }
                break;
            }
            
            case 2: {
                int sub = -1;
                while (sub != 0) {
                    printf("\n calculation menu \n");
                    printf("1. calculator\n");
                    printf("2. converter\n");
                    printf("0. back\n");
                    printf("choose an option: ");
                    scanf("%d", &sub);
                    
                    switch (sub) {
                        case 1:
                            printf("Calculator selected...\n");
                            break;
                        case 2:
                            printf("Converter selected...\n");
                            break;
                        case 0:
                            printf("returning ...\n");
                            break;
                        default:
                            printf("invalid option.\n");
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
                printf("Logging out...\n\n");
                break;
                
            default:
                printf("Invalid option. Please choose again.\n\n");
        }
    }
}

void adminMenu(void) {
    int nav = 0;
    
    while(nav != 3) {
        printf("\n admin menu \n\n");
        printf("1. attendance\n");
        printf("2. student files\n");
        printf("3. logout\n");
        printf("choose an option: ");
        scanf("%d", &nav);

        switch (nav) {
            case 1: {
                int sub = -1;
                while (sub != 0) {
                    printf("\n**attendance menu**\n\n");
                    printf("1. view attendance\n");
                    printf("2. mark attendance\n");
                    printf("0. back\n");
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
                int sub = -1;
                while (sub != 0) {
                    printf("\n student files \n\n");
                    printf("1. view Files\n");
                    printf("0. Back to Main Menu\n");
                    printf("Choose an option: ");
                    scanf("%d", &sub);
                    
                    switch (sub) {
                        case 1:
                            printf("viewing student files...\n");
                            break;
                        case 0: 
                            printf("returning to admin main menu...\n");
                            break;
                        default:
                            printf("invalid option.\n");
                    }
                }
                break;
            }
            
                
            case 3:
                printf("logging out...\n\n");
                break;
                
            default:
                printf("invalid option\n\n");
        }
    }
}

int main() {
  
  loadUsers();  
  
  int loginMenu = 0;
  while(loginMenu != 3){
    printf("\n RDSv2 \n\n");
    printf("1. register\n2. login\n3. terminate\n");
    printf("→ ");
    scanf("%d", &loginMenu);
    printf("\n");

    char username[50];
    char password[50];  
    int logged_in = 0;
  
    switch(loginMenu) {
      case 1:
        registerUser();
        break;

      case 2: {
        int count = 0;

        while(logged_in == 0 && count < 3) {  // Fixed: changed <= to <
          insertName(username);
          insertPassword(password);
          logged_in = login(username, password, users, admins);

          if(logged_in == 0) {
            printf("invalid login attempt\n\n");
            count++;
          }
        }

        if(count >= 3 && logged_in == 0) {
          printf("too many failed attempts\n\n");
        }

        if(logged_in == 1) {
          printf("student log in success\n\n");
          studentMenu(); 
        }

        if(logged_in == 2) {
          printf("admin login successful\n\n");
          adminMenu();  
        }
        break;
      }

      case 3:
        printf("terminating program.....\n\n");
        break;

      default:
        printf("invalid input!\n\n");
        break;
    }
  }
}

