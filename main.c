#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.141592653589793
#define max 100

// --- STRUCTS ---
typedef struct {
  char *username;
  char *id_number;
  char *password;
  int attendance;
} user;

typedef struct {
  char *admin_name;
  char *admin_password;
} admin;

typedef struct {
    char title[max];
    char author[max];
} book;

typedef struct {
    char course_name[max];
    char faculty[max];
} course;

// --- GLOBAL VARIABLES ---
user users[100];
int userSize = 0;

admin admins[] = {
    {"RejuanaIslam115", "admin123"},
    {"meowLord67", "admin456"}
};

int adminSize = sizeof(admins) / sizeof(admins[0]);

// --- PROTOTYPES ---
void clearBuffer();
void registerUser(void);
int login(char *input_name, char *input_password, user users[], admin admins[], int *userIndex, int *adminIndex);
void insertName(char *name);
void insertPassword(char *password);
void saveUsers(void);
void loadUsers(void);
void studentMenu(int userIndex);
void adminMenu(void);
void logBooks(int userIndex);
void logCourses(int userIndex);
void viewBooks(int userIndex);
void viewCourses(int userIndex);
void calculator();


// --- HELPER FUNCTIONS ---

void clearBuffer() {
  int c;
  while((c = getchar()) != '\n' && c != EOF);
}

void registerUser(void) {
  if(userSize >= max) {
    printf("user limit reached\n");
    return;
  }

  char username[20];
  printf("enter username: ");
  scanf("%19s", username);

  char id[10];
  printf("enter your NSU id number: ");
  scanf("%9s", id);
  
  clearBuffer();
        
  char password_1[50];
  printf("enter password: ");
  scanf("%49s", password_1);

  clearBuffer();
  
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

int login(char *input_name, char *input_password, user users[], admin admins[], int *userIndex, int *adminIndex) {
  for(int i = 0; i < adminSize; i++){
    if(admins[i].admin_password != NULL && strcmp(admins[i].admin_name, input_name) == 0) {
      if(strcmp(admins[i].admin_password, input_password) == 0) {
        *adminIndex = i;
        return 2;
      }
    }
  }

  for(int i = 0; i < userSize; i++) {
    if(strcmp(users[i].username, input_name) == 0 || strcmp(users[i].id_number, input_name) == 0) {
      if(strcmp(users[i].password, input_password) == 0) {
        *userIndex = i;
        return 1;
      }
    }
  }
  return 0;
}

void insertName(char *name){
  clearBuffer();
  printf("enter username / nsu id: ");
  scanf("%49s", name);
}

void insertPassword(char *password){
  clearBuffer();
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
    if (!f) return;

    char uname[50], id[20], pass[50];
    int i;

    while (userSize < max && fscanf(f, "%d %s %s %s", &i, uname, id, pass) == 4) {
        users[userSize].username  = strdup(uname);
        users[userSize].id_number = strdup(id);
        users[userSize].password  = strdup(pass);
        userSize++;
    }
    fclose(f);
}

// --- LOGGING FUNCTIONS ---

void logBooks(int userIndex) {
    int n;
    printf("enter number of books: ");
    scanf("%d", &n);
    clearBuffer(); 

    book *library = (book *)malloc(n * sizeof(book));
    if(library == NULL) {
        printf("error\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        char temp[100];
        
        printf("\n--- Book %d ---\n", i+1);
        printf("enter title: ");
        if(fgets(temp, 100, stdin)) {
            temp[strcspn(temp, "\n")] = 0;
            strcpy(library[i].title, temp);
        }

        printf("enter author: ");
        if(fgets(temp, max, stdin)) {
            temp[strcspn(temp, "\n")] = 0;
            strcpy(library[i].author, temp);
        }
    }

    char filename[max];
    strcpy(filename, users[userIndex].id_number);
    strcat(filename, "_books.txt"); 

    FILE *lib = fopen(filename, "w");
    if (lib != NULL) {
        for (int i = 0; i < n; i++) {
            fprintf(lib, "title: %s | author: %s\n", library[i].title, library[i].author);
        }
        fclose(lib);
        printf("\nData written to %s\n", filename);
    } else {
        printf("\nerror opening file!\n");
    }

    free(library);
}

void logCourses(int userIndex) {
    int n;
    printf("enter number of courses: ");
    scanf("%d", &n);
    clearBuffer(); 

    course *courseList = (course *)malloc(n * sizeof(course));
    if(courseList == NULL) {
        printf("Memory allocation error\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        char temp[max];
        
        printf("\n--- Course %d ---\n", i+1);
        printf("enter course name (e.g. CSE115): ");
        if(fgets(temp, 100, stdin)) {
            temp[strcspn(temp, "\n")] = 0;
            strcpy(courseList[i].course_name, temp);
        }

        printf("enter faculty initial: ");
        if(fgets(temp, max, stdin)) {
            temp[strcspn(temp, "\n")] = 0;
            strcpy(courseList[i].faculty, temp);
        }
    }

    char filename[max];
    strcpy(filename, users[userIndex].id_number);
    strcat(filename, "_courses.txt"); 

    FILE *f = fopen(filename, "w");
    if (f != NULL) {
        for (int i = 0; i < n; i++) {
            fprintf(f, "course: %s | faculty: %s\n", courseList[i].course_name, courseList[i].faculty);
        }
        fclose(f);
        printf("\nData written to %s\n", filename);
    } else {
        printf("\nError opening file!\n");
    }

    free(courseList);
}

//Viewing functions
void viewBooks(int userIndex) {
    char bookFile[max];
    strcpy(bookFile, users[userIndex].id_number);
    strcat(bookFile, "_books.txt");

    FILE *view = fopen(bookFile,"r");
    if(view == NULL) {
        printf("no books logged\n");
        return;
    } else {
        char ch;
        while((ch =fgetc(view)) != EOF) {
            printf("%c",ch);
        }
    }

    fclose(view);
}

void viewCourses(int userIndex) {
    char courseFile[max];
    strcpy(courseFile, users[userIndex].id_number);
    strcat(courseFile, "_courses.txt");

    FILE *view = fopen(courseFile,"r");
    if(view == NULL) {
        printf("no courses logged\n");
        return;
    } else {
        char ch;
        while((ch = fgetc(view)) != EOF) {
            printf("%c",ch);
        }
    }

    fclose(view);
}


// --- CALCULATOR ---
void calculator() {
    int choice = 0;

    while (choice != 3) {
        printf("\n----------------------------------\n");
        printf("Press 1 to perform two number calculations: \n");
        printf("Press 2 to perform function operations: \n");
        printf("Press 3 to Exit\n");
        printf("→ ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearBuffer();
            continue;
        }

        if (choice == 3) {
            printf("Exiting program.\n");
            break;
        }

        if (choice == 1) {
            float num1, num2; 
            char op;

            printf("Enter your first number: ");
            scanf("%f", &num1); // Changed %d to %f

            printf("Enter your second number: ");
            scanf("%f", &num2); // Changed %d to %f

            printf("Choose your operator (+, -, *, /): ");
            scanf(" %c", &op);

            switch (op) {
                case '+':
                    printf("%.2f + %.2f = %.2f\n", num1, num2, num1 + num2);
                    break;

                case '-':
                    printf("%.2f - %.2f = %.2f\n", num1, num2, num1 - num2);
                    break;

                case '*':
                    printf("%.2f * %.2f = %.2f\n", num1, num2, num1 * num2);
                    break;

                case '/':
                    if (num2 == 0) {
                        printf("error!! divisor cannot be zero\n");
                    } else {
                        printf("%.2f / %.2f = %.2f\n", num1, num2, num1 / num2);
                    }
                    break;
                
                default:
                    printf("invalid operator\n");
            }
        } 
        else if (choice == 2) {
            float x;
            float x_in_radians;
            char opar;
            float result;

            printf("Enter angle in degrees: ");
            scanf("%f", &x);
            
            printf("choose function: \n");
            printf("sinx (press s)\n");
            printf("cosx (press c)\n");
            printf("tanx (press t)\n");
            printf("→ ");
            scanf(" %c", &opar);

            x_in_radians = x * (pi / 180.0);

            switch (opar) {
                case 's':
                    result = sin(x_in_radians);
                    printf("Result: %f\n", result);
                    break;

                case 'c':
                    result = cos(x_in_radians);
                    printf("Result: %f\n", result);
                    break;

                case 't':
                    result = tan(x_in_radians);
                    printf("Result: %f\n", result);
                    break;

                default:
                    printf("Invalid trigonometric operation.\n");
            }
        } 
        else {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }
}

// --- MENUS ---

void studentMenu(int userIndex) {
    int nav = 0;
    
    while(nav != 4) {
        printf("\n Student Main Menu \n");
        printf("1. student resources\n");
        printf("2. calculation resources\n");
        printf("3. logout\n");

        printf("→ ");
        scanf("%d", &nav);

        clearBuffer();
            
        switch (nav) {
            case 1: {
                int sub = -1;
                while (sub != 0) {
                    printf("\n resources menu**\n");
                    printf("1. log books\n");
                    printf("2. log courses\n");
                    printf("3. view books\n");
                    printf("4. view courses\n");
                    printf("0. back\n");
                    printf("→ ");
                    scanf("%d", &sub);
                    
                    switch (sub) {
                        case 1:
                            printf("book logger...\n");
                            logBooks(userIndex);
                            break;
                        case 2:
                            printf("course logger...\n");
                            logCourses(userIndex);
                            break;
                        case 3:
                            printf("view books\n");
                            viewBooks(userIndex);
                            break;
                        case 4:
                            printf("view courses...\n");
                            viewCourses(userIndex);
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
                    printf("\n calculations menu**\n");
                    printf("1. calculator\n");
                    printf("2. converter\n");
                    printf("0. back\n");
                    printf("→ ");
                    scanf("%d", &sub);
                    
                    switch (sub) {
                        case 1:
                            printf("calculator\n");
                            calculator();
                            break;
                        case 2:
                            printf("converter\n");
                            break;
                        case 0:
                            printf("returning\n");
                            break;
                        default:
                            printf("invalid option.\n");
                    }
                 }
                 break;

            }
            
            case 3:
                printf("Logging out...\n\n");
                return; 
                
            default:
                printf("Invalid option. Please choose again.\n\n");
        }
    }
}

void adminMenu(void) {
    int nav = 0;
    while(nav != 3) {
        printf("\n admin menu \n\n");
        printf("1. attendance\n2. logout\n");
        scanf("%d", &nav);
        clearBuffer();
        
        if(nav == 2) return;
    }
}

// --- MAIN ---
int main() {
  
  loadUsers();  
  
  int loginMenu = 0;
  while(loginMenu != 3){
    printf("\n RDSv2 \n\n");
    printf("1. register\n2. login\n3. terminate\n");
    printf("→ ");
    
    scanf("%d", &loginMenu);
    clearBuffer();
    
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
        int currentUser = -1;
        int currentAdmin = -1;

        while(logged_in == 0 && count < 3) {
          insertName(username);
          insertPassword(password);
          logged_in = login(username, password, users, admins, &currentUser, &currentAdmin);

          if(logged_in == 0) {
            printf("invalid login attempt\n\n");
            count++;
          }
        }

        if(count >= 3 && logged_in == 0) {
          printf("too many failed attempts\n\n");
        }

        if(logged_in == 1) {
          printf("\n\nstudent login success\n\nlogged in as [%s]\n\n", users[currentUser].username);
          studentMenu(currentUser); 
        }

        if(logged_in == 2) {
          printf("admin login success\nlogged in as %s\n\n", admins[currentAdmin].admin_name);
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
  return 0;
}
