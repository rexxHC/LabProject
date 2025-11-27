#include <stdio.h>
#include <string.h>

#define MAX 100




typedef struct {
    int id;
    char name[50];
    char dept[30];
    float quiz[3];
    float assignment;
    float midterm;
    float final_exam;
    float attendance;
} Student;



Student students[MAX];
int count = 0;



static void addStudent();
static void viewStudents();
static void searchStudent();



void gradeLogin();


/*
int main() {
    gradeLogin();
    return 0;
}
*/



void gradeLogin() {
    int choice;

    while (1) {
        printf("\n--- Grade System Menu ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        if (choice == 1)
            addStudent();
        else if (choice == 2)
            viewStudents();
        else if (choice == 3)
            searchStudent();
        else if (choice == 4)
            break;
        else
            printf("Invalid choice!\n");
    }
}





float readFloat(char *prompt, float min, float max) {
    float value;
    int n;
    while (1) {
        printf("%s", prompt);
        n = scanf("%f", &value);
        while (getchar() != '\n');
        if (n == 1 && value >= min && value <= max)
            return value;
        printf("Invalid input! Enter a value between %.2f and %.2f.\n", min, max);
    }
}






float calcGrade(Student s) {
    float lowestQuiz = s.quiz[0];
    if (s.quiz[1] < lowestQuiz) lowestQuiz = s.quiz[1];
    if (s.quiz[2] < lowestQuiz) lowestQuiz = s.quiz[2];

    float quizSum = s.quiz[0] + s.quiz[1] + s.quiz[2] - lowestQuiz;

    float quizAvg = quizSum / 2.0;

    float total = quizAvg * 0.20 + s.assignment * 0.10 + s.midterm * 0.30 + s.final_exam * 0.30 + s.attendance * 0.10;
    return (total / 24.0) * 100.0;
}








//add 

static void addStudent() {
    Student s;
    s.id = count + 1;

    if (count >= MAX) {
        printf("Cannot add more students. Maximum reached.\n");
        return;
    }

    printf("\n--- Add Student ---\n");

    printf("Name: ");
    scanf(" %[^\n]", s.name);

    printf("Department: ");
    scanf(" %[^\n]", s.dept);

    for (int i = 0; i < 3; i++) {
        char prompt[50];
        sprintf(prompt, "Quiz %d marks (0-20): ", i + 1);
        s.quiz[i] = readFloat(prompt, 0, 20);
    }

    s.assignment = readFloat("Assignment marks (0-10): ", 0, 10);
    s.midterm = readFloat("Midterm marks (0-30): ", 0, 30);
    s.final_exam = readFloat("Final Exam marks (0-30): ", 0, 30);
    s.attendance = readFloat("Attendance marks (0-10): ", 0, 10);

    students[count++] = s;

    printf("Student added!\n");
}




//view all
static void viewStudents() {
    if (count == 0) {
        printf("No students added yet.\n");
        return;
    }

    printf("\n--- All Students ---\n");

    for (int i = 0; i < count; i++) {
        Student s = students[i];

        printf("\nID: %d\n", s.id);
        printf("Name: %s\n", s.name);
        printf("Dept: %s\n\n", s.dept);

        printf("Quiz Scores:\n");
        printf("  Quiz 1: %.2f\n", s.quiz[0]);
        printf("  Quiz 2: %.2f\n", s.quiz[1]);
        printf("  Quiz 3: %.2f\n", s.quiz[2]);

        printf("\nAssignment Score: %.2f\n", s.assignment);
        printf("Midterm Score: %.2f\n", s.midterm);
        printf("Final Exam Score: %.2f\n", s.final_exam);
        printf("Attendance Score: %.2f\n", s.attendance);

        float grade = calcGrade(s);
        printf("\nFinal Grade: %.2f%%\n", grade);
    }
}


//search

static void searchStudent() {
    int id;
    printf("\nEnter student ID to search: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            Student s = students[i];

            printf("\n--- Student Found ---\n");
            printf("Name: %s\n", s.name);
            printf("Dept: %s\n\n", s.dept);

            printf("Quiz Scores:\n");
            printf("  Quiz 1: %.2f\n", s.quiz[0]);
            printf("  Quiz 2: %.2f\n", s.quiz[1]);
            printf("  Quiz 3: %.2f\n", s.quiz[2]);

            printf("\nAssignment Score: %.2f\n", s.assignment);
            printf("Midterm Score: %.2f\n", s.midterm);
            printf("Final Exam Score: %.2f\n", s.final_exam);
            printf("Attendance Score: %.2f\n", s.attendance);

            printf("\nFinal Grade: %.2f%%\n", calcGrade(s));
            return;
        }
    }

    printf("Student not found!\n");
}
