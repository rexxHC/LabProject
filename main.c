//library functions
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//implicit definitions
#define pi 3.141592653
#define max 100
#define icap 20

//structures
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

//global variables
user users[max];
int userSize = 0;

admin admins[] = {
  {"rejuanaIslam", "admin123"},
  {"meowMeow67", "mew2"}
}; //hardcoded admins
int adminSize = sizeof(admins) / sizeof(admins[0]);

//function prototypes
void clearBuffer();
int bookError(book *p);
int courseError(course *p);
int fileError(FILE *f);
void registerUser(void);
int login(char *input_name, char *input_password, user users[], admin admins[], int *userIndex, int *adminIndex);
void insertName(char *name);
void insertPassword(char *password);
void saveUsers(void);
void loadUsers(void);
void studentMenu(int userIndex);
void logBooks(int userIndex);
void logCourses(int userIndex);
void logAttendance(void);
void viewBooks(int userIndex);
void viewCourses(int userIndex);
void viewAttendance(int userIndex);
void calculator();
void converter();
void adminMenu(int adminIndex, user users[]);

//minor functions
void clearBuffer() {
  int c;
  while((c = getchar()) != '\n' && c != EOF); //checks for the newline character or the EOF(end of file) character while cleaning junk values
}

int fileError(FILE *f) {
  if(f == NULL) {
    printf("error opening file\n");
    return 1;
  }
  return 0;
}

int bookError(book *p) {
  if(p == NULL) {
    printf("error!!!\n");
    return 1;
  }
  return 0;
}

int courseError(course *p) {
  if(p == NULL) {
    printf("error!!!\n");
    return 1;
  }
  return 0;
}


//user-handler functions
void registerUser(void) {
  if(userSize >= max) {
    printf("max users reached!\nregistry unsuccessful!\n");
    return;
  }

  char uname[icap];
  printf("enter username: ");
  scanf("%19s", uname);

  char id[icap];
  printf("enter nsu id: ");
  scanf("%19s", id);

  clearBuffer(); //call this function to handle the newline character from scanf() or fgets()

  char pass1[icap];
  printf("enter password: ");
  scanf("%19s", pass1);

  char pass2[icap];
  printf("enter password again: ");
  scanf("%19s", pass2);

  if(strcmp(pass1, pass2) == 0) { //strcmp() returns 0 if pass1 and pass2 are identical
    users[userSize].username = strdup(uname);
    users[userSize].id_number = strdup(id);
    users[userSize].password = strdup(pass2);
    users[userSize].attendance = 0;
    //strdup() is the same function as strcpy() but it handles memory allocation and returns the target string
    userSize++;
    saveUsers(); //new user saved to file
    printf("new user successfully registered!\n\n");
  } else {
   printf("passwords do not match");
   return; 
  }
}

int login(char *input_name, char *input_password, user users[], admin admins[], int *userIndex, int *adminIndex) { //login() returns 1 for student, 2 for admin and 0 for a failed attempt

  for(int i = 0; i < adminSize; i++) {
    if(strcmp(admins[i].admin_name, input_name) == 0) {
      if(strcmp(admins[i].admin_password, input_password) == 0) {
        *adminIndex = i;
        return 2;
      }
    }
  }

  for(int i = 0; i < userSize; i++) {
    if((strcmp(users[i].username, input_name) == 0) || (strcmp(users[i].id_number, input_name) == 0)) {
      if(strcmp(users[i].password, input_password) == 0) {
        *userIndex = i;
        return 1;
      }
    }
  }
  return 0;
}

//input functions
void insertName(char *name) {
  clearBuffer();
  printf("enter username / nsu id: ");
  scanf("%19s", name);
}

void insertPassword(char *pass) {
  clearBuffer();
  printf("enter password: ");
  scanf("%19s", pass);
}

//user database file functions
void saveUsers(void) {
  FILE *userBase = fopen("database.txt", "w");
  if(fileError(userBase)) {
    return;
  }  

  for(int i = 0; i < userSize; i++) {
    fprintf(userBase, "%d %s %s %s %d\n", i, users[i].username, users[i].id_number, users[i].password, users[i].attendance); //could have used fwrite() in binary for minimal safety
  }

  fclose(userBase);
}

void loadUsers(void) {
  FILE *userBase = fopen("database.txt", "r");
  if(fileError(userBase)) {
    return;
  }

  char uname[icap], id[icap], pass[icap];
  int i, attendance;

  while (userSize < max && fscanf(userBase, "%d %s %s %s %d", &i, uname, id, pass, &attendance) == 5) { // first condition ensures we dont overflow the array
    // second condition reads every line and check if it has read five elements
    users[userSize].username  = strdup(uname);
    users[userSize].id_number = strdup(id);
    users[userSize].password  = strdup(pass);
    users[userSize].attendance = attendance;
    userSize++;
  }

  fclose(userBase);
}
//**IMPORTANT PLEASE READ**
// registerUsers() stores the new users in the memory while the program is running, users are lost upon program termination
// saveUsers() stores the users[] array in a formatted text file, but it overwrites the existing users everytime it is called
// loadUsers() solves the saveUsers() problem by reading the text file, and storing the contents into the users[] array
// the global variable [userSize] exists outside this loop to maintain the usercount properly
// these three functions work together so that we do not lose user information everytime we terminate the program

void logBooks(int userIndex) {
  int n;
  printf("enter number of books: ");
  scanf("%d", &n);
  clearBuffer();

  book *library = (book *)malloc(n *sizeof(book));//malloc allocates sizeof(book) worth of memory multiplied by the number of books (n)
  if(bookError(library)) {
    return;
  }

  for(int i = 0; i < n; i++) {
    char book_name[max];
    char author_name[max];
    
    printf("\nbook--%d\n", i + 1);
    printf("enter book name: ");
    fgets(book_name, max, stdin);
    strcpy(library[i].title, book_name);

    printf("enter author: ");
    fgets(author_name, max, stdin);
    strcpy(library[i].author, author_name);
  }

  char filename[max];
  strcpy(filename, users[userIndex].username);
  strcat(filename, users[userIndex].id_number);
  strcat(filename, "_books.txt");

  FILE *lib = fopen(filename, "a");
  if(fileError(lib)) {
    return;
  }

  for(int i =0; i < n; i++) {
    fprintf(lib, "%d title: %sauthor: %s\n",i + 1, library[i].title, library[i].author);
  }

  printf("books logged to %s", filename);
  fclose(lib);
  free(library); // free the memory allocated to the malloc'd array
}

void logCourses(int userIndex) {
  int n;
  printf("enter number of courses: ");
  scanf("%d", &n);
  clearBuffer();

  course *cr = (course *)malloc(n * sizeof(course));
  if(courseError(cr)) {
    return;
  }

  for(int i = 0; i < n; i++) {
    char course_name[max];
    char faculty_name[max];
    
    printf("\ncourse--%d\n", i + 1);
    printf("enter course name: ");
    fgets(course_name, max, stdin);
    strcpy(cr[i].course_name, course_name);

    printf("enter faculty name: ");
    fgets(faculty_name, max, stdin);
    strcpy(cr[i].faculty, faculty_name);
  }

  char filename[max];
  strcpy(filename, users[userIndex].username);
  strcat(filename, users[userIndex].id_number);
  strcat(filename, "_courses.txt");

  FILE *cor = fopen(filename, "w");
  if(fileError(cor)) {
    return;
  }

  for(int i =0; i < n; i++) {
    fprintf(cor, "%s by %s\n", cr[i].course_name, cr[i].faculty);
  }

  printf("courses logged to %s", filename);
  fclose(cor);
  free(cr);
}

void logAttendance(void) {
  if(userSize == 0) {
    printf("not enough users to grade attendance");
    return;
  } else {
    for(int i = 0; i < userSize; i++) {
    printf("%s's attendance grades: ", users[i].username);
    scanf("%d", &users[i].attendance);
    clearBuffer();
    }
    saveUsers();
    printf("attendance updated\n");
  }
  
}

//viewing functions
void viewBooks(int userIndex) {
  char bookFile[max];
  strcpy(bookFile, users[userIndex].username);
  strcat(bookFile, users[userIndex].id_number);
  strcat(bookFile, "_books.txt");

  FILE *view = fopen(bookFile, "r");
  if(fileError(view)) {
    printf("no books logged\n");
    return;
  } else {
    char ch;
    while((ch = fgetc(view)) != EOF) {
      printf("%c", ch);
    }
  }
  
  fclose(view);
}

void viewCourses(int userIndex) {
  char courseFile[max];
  strcpy(courseFile, users[userIndex].username);
  strcat(courseFile, users[userIndex].id_number);
  strcat(courseFile, "_courses.txt");

  FILE *view = fopen(courseFile, "r");
  if(fileError(view)) {
    printf("no courses logged\n");
    return;
  } else {
    char ch;
    while((ch = fgetc(view)) != EOF) {
      printf("%c", ch);
    }
  }

  fclose(view);
}

void viewAttendance(int userIndex) {
  printf("attendance for user [%s] : %d\n\n",users[userIndex].username, users[userIndex].attendance);
}

//calculation and converter functions
void calculator() {
  int choice = 0;

  while(choice != 3) {
    printf("\n--calculator--\n");
    printf("1. two number calculations\n");
    printf("2. trigonometric calculations\n");
    printf("3. exit\n");

    printf("→ ");
    scanf("%d", &choice);
    clearBuffer();

    if(choice == 3) {
      printf("exiting..");
      break;
    }

    if(choice == 1) {
      float num1, num2;
      char op;

      printf("enter your first number: ");
      scanf("%f", &num1);

      printf("enter your second number: ");
      scanf("%f", &num2);

      printf("choose your operator (+, -, *, /): ");
      scanf(" %c", &op);

      switch(op) {
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
          if(num2 == 0) {
            printf("error!! divisor cannot be zero\n");
          } else {
            printf("%.2f / %.2f = %.2f\n", num1, num2, num1 / num2);
          }
          break;

        default:
          printf("invalid operator\n");
      }
    } else if(choice == 2) {
      float x;
      float x_in_radians;
      char opar;
      float result;

      printf("enter angle in degrees: ");
      scanf("%f", &x);

      printf("choose function: \n");
      printf("sinx (press s)\n");
      printf("cosx (press c)\n");
      printf("tanx (press t)\n");
      printf("→ ");
      scanf(" %c", &opar);

      x_in_radians = x * (pi / 180.0);

      switch(opar) {
        case 's':
          result = sin(x_in_radians);
          printf("result: %f\n", result);
          break;

        case 'c':
          result = cos(x_in_radians);
          printf("result: %f\n", result);
          break;

        case 't':
          result = tan(x_in_radians);
          printf("result: %f\n", result);
          break;

        default:
          printf("invalid operation.\n");
      }
    } else {
      printf("invalid choice\n");
    }
  }
}

void converter() {
  int choice = 0;
  float input, result;

  while(choice != 7) {
    printf("\n--unit converter--\n");
    printf("1. celsius to fahrenheit\n");
    printf("2. fahrenheit to celsius\n");
    printf("3. pounds to kilograms\n");
    printf("4. kilograms to pounds\n");
    printf("5. feet to metre\n");
    printf("6. metre to feet\n");
    printf("7. back\n");

    printf("→ ");
    scanf("%d", &choice);
    clearBuffer();

    if(choice == 7) {
      printf("returning...\n");
      break;
    }

    if(choice < 1 || choice > 7) {
      printf("invalid choice\n");
      continue;
    }

    printf("enter value: ");
    scanf("%f", &input);
    clearBuffer(); // clears buffer after reading float

    switch(choice) {
      case 1:
        result = (input * 9.0 / 5.0) + 32.0;
        printf("converted: %.2f fahrenheit\n", result);
        break;

      case 2:
        result = (input - 32.0) * 5.0 / 9.0;
        printf("converted: %.2f celsius\n", result);
        break;

      case 3:
        if(input < 0) {
          printf("error: weight cannot be negative\n");
        } else {
          result = input * 0.453592;
          printf("converted: %.2f kilograms\n", result);
        }
        break;

      case 4:
        if(input < 0) {
          printf("error: weight cannot be negative\n");
        } else {
          result = input * 2.20462;
          printf("converted: %.2f pounds\n", result);
        }
        break;

      case 5:
        if(input < 0) {
          printf("error: length cannot be negative\n");
        } else {
          result = input * 0.3048;
          printf("converted: %.2f metre\n", result);
        }
        break;

      case 6:
        if(input < 0) {
          printf("error: length cannot be negative\n");
        } else {
          result = input * 3.28084;
          printf("converted: %.2f feet\n", result);
        }
        break;
      
      default:
        printf("error\n");
    }
  }
}

//menu functions
void studentMenu(int userIndex) {
  int nav = 0;

  while(nav != max) {
    printf("\n--student main menu--\n");
    printf("1. student resources\n");
    printf("2. calculation resources\n");
    printf("3. logout\n");

    printf("→ ");
    scanf("%d", &nav);
    clearBuffer();

    switch(nav) {
      case 1: {
          int sub = -1;
          while(sub != 0) {
            printf("\n--resources--\n");
            printf("1. log books\n");
            printf("2. view books\n");
            printf("3. log courses\n");
            printf("4. view courses\n");
            printf("5. view attendance\n");
            printf("0. back\n");
            printf("→ ");
            scanf("%d", &sub);

            switch(sub) {
              case 1:
                printf("--book logger--\n");
                logBooks(userIndex);
                break;
              case 2:
                printf("--view books--\n");
                viewBooks(userIndex);
                break;
              case 3:
                printf("--log courses--\n");
                logCourses(userIndex);
                break;
              case 4:
                printf("--view courses--\n");
                viewCourses(userIndex);
                break;
              case 5:
                printf("--view attendance--\n");
                viewAttendance(userIndex);
                break;
              case 0:
                printf("returning...\n");
                break;
              default:
                printf("invalid\n");
            }
          }
        break;
      }
  
      case 2: {
          int sub = -1;
          while(sub != 0) {
            printf("\n--calculations--\n");
            printf("1. calculator\n");
            printf("2. converter\n");
            printf("0. back\n");
            printf("→ ");
            scanf("%d", &sub);

            switch(sub) {
              case 1:
                printf("--calculator--\n");
                calculator();
                break;
              case 2:
                printf("--converter--\n");
                converter();
                break;
              case 0:
                printf("returning...\n");
                break;
              default:
                printf("invalid\n");
            }
          }
        break;  
      }

      case 3:
        printf("logging out..\n\n");
        return;

      default:
        printf("invalid option\n\n");      
    }
  }
}

void adminMenu(int adminIndex, user users[]) {
  int nav = 0;
  while(nav != max) {
  printf("\n admin menu \n\n");
  printf("1. attendance\n2. logout\n");
  scanf("%d", &nav);
  clearBuffer();

  switch(nav) {
    case 1:
      printf("--attendance log--\n");
      logAttendance();
      break;
    case 2:
      printf("logging out...\n");
      return;
    default:
      printf("invalid option\n");
  }
  }
}

//main
int main() {
  loadUsers();//loads users to memory

  int loginMenu = 0;
  while(loginMenu != 3) {
    printf("\nRDSv2\n\n");
    printf("1. register\n2. login\n3. terminate\n\n");
    printf("→ ");
    scanf("%d", &loginMenu);
    clearBuffer();

    char username[icap];
    char password[icap];
    int logged_in = 0;

    switch(loginMenu) {
      case 1:
        registerUser();
        break;
      case 2: {
          int count = 0, currentUser = -1, currentAdmin = -1;

          while(logged_in == 0 && count < 3) {
            insertName(username);
            insertPassword(password);
            logged_in = login(username, password, users, admins, &currentUser, &currentAdmin);

            if(logged_in == 0) {
              printf("invalid login attempt\n\n");
              count++;
            }
          }

          if(count >= 3 && logged_in == 0) { //this part checks if login attempts exceed 3 attempts
            printf("too many failed attempts\n\n");
          }

          if(logged_in == 1) { //student
            printf("\n\nstudent login success\n\n");
            printf("logged in as[%s]\n\n", users[currentUser].username);
            studentMenu(currentUser);
          }

          if(logged_in == 2) { //admin
            printf("\n\nadmin login success\n\n");
            printf("logged in as [%s]", admins[currentAdmin].admin_name);
            adminMenu(currentAdmin, users);
            }        
        break;
        }
      case 3: //terminate
        printf("terminating program...\n\n");
        break;
      default:
        printf("invalid input\n");
        break;
        }
    }

    return 0;
  }

