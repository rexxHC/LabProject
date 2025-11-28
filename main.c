#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *username;
    unsigned long long ID;
} user;

typedef struct {
    char *admin;
} Admin;

user users[] = {
    {"AbiraSorowar", 2513491630ULL},
    {"MstNurAAfsanur", 2532692642ULL},
    {"AnilBanik", 2534231642ULL},
    {"RatulBanik", 2533081642ULL},
    {"ArnobBiswas", 2532531042ULL},
    {"NehanChowdhury", 2534512642ULL},
    {"MdNaofilIslamEmon", 2534017642ULL},
    {"KhandakerAhnafTahmidEnan", 2531312642ULL},
    {"AnikGhosh", 2534167042ULL},
    {"KaziMdInjamamulHoque", 2531183642ULL},
    {"MahbubIntisar", 2533512042ULL},
    {"AbdullahMohammadJubayer", 2531483042ULL},
    {"TahsinZamanMashrim", 2531753642ULL},
    {"MdTahsanMasud", 2534470642ULL},
    {"KhandakerJannatulMawa", 2531368042ULL},
    {"JasiyaMohayra", 2533672042ULL},
    {"TahiyaMohayra", 2533632042ULL},
    {"MdMarufRabbiMoon", 253192842ULL},
    {"SyadaNusratNahar", 2531955042ULL},
    {"AbdullahAlNahian", 2531681642ULL},
    {"SheikhNahianNaji", 2533163042ULL},
    {"MdAdnanSiddiqueNeon", 2532222042ULL},
    {"LamiaMehzadNirbindha", 2531016642ULL},
    {"AtifUlQuadir", 2533574042ULL},
    {"SadmanRahatRafi", 2532371042ULL},
    {"SkRakinulHaque", 2532182642ULL},
    {"ANSamiullah", 2531751042ULL},
    {"MymunaSarker", 2531428642ULL},
    {"AliHasanShadman", 2531451042ULL},
    {"MashrikaMuntahinSiddiqui", 2531731042ULL},
    {"TamimSadiqSneho", 2531929642ULL},
    {"TawfiqueOmarTazwar", 2533259642ULL},
    {"TarannumBinteMatiur", 2311647643ULL}
};

Admin keys[] = {
    {"RejuanaIslam115"},
    {"RajeshPalitRJP115"},
    {"meowLord67"}
};

int userSize = sizeof(users) / sizeof(users[0]);
int adminSize = sizeof(keys) / sizeof(keys[0]);


int loginUser(user users[], int userSize, char *input_name, Admin keys[], int adminSize);
int loginID(user users[], int userSize, unsigned long long input_id);
  


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

int loginID(user users[], int userSize, unsigned long long input_id) {
    for (int i = 0; i < userSize; i++) {
        if (users[i].ID == input_id) {
            return 1;
        }
    }
    return 0;
}


// attendance + grade 

//grade
void grade(void);

typedef struct {        //for grade + attendance
    unsigned long long ID; 
    float grade;           
    int attendance;        
} Record;

Record records[100]; 
int recordCount = 0; 


void load_gradeFile(void);
void save_gradeFile(void);
void searchgrade(void);
void viewgrade(void);
void inputgrade(void);


void load_gradeFile() {

    FILE *file = fopen("records.dat", "rb"); 


    if (!file) {
        printf("No saved grade records found. Starting fresh.\n");
        recordCount = 0;
        return;
    }



    fread(&recordCount, sizeof(int), 1, file);        
    fread(records, sizeof(Record), recordCount, file); 

    fclose(file);
    printf("Grade records loaded successfully.\n");
}


void save_gradeFile() {

    FILE *file = fopen("records.dat", "wb"); 
    
    
    if (!file) {
        printf("Error opening grade file for saving.\n");
        return;
    }



    fwrite(&recordCount, sizeof(int), 1, file);         
    fwrite(records, sizeof(Record), recordCount, file); 

    fclose(file);
    printf("Grade Records saved successfully.\n");
}


void inputgrade() {

    unsigned long long id;
    float grade;
    int n = 1;

    while(1){

        int found = 0;

        printf("Enter 0 to return or any numeric key to continue\n");
        printf("Choice: ");
        scanf("%d", &n);

        if (n == 0) {
            return;
        }

        printf("Enter student ID: ");
        scanf("%llu", &id);

      
        for (int i = 0; i < recordCount; i++) {
            if (records[i].ID == id) {
              
                printf("Enter grade: ");
                scanf("%f", &grade);


                records[i].grade = grade;
                found = 1;
                break;
            }
        }

       
        if (!found) {
            printf("Enter grade: ");
            scanf("%f", &grade);
            records[recordCount].ID = id;
            records[recordCount].grade = grade;
            
            recordCount++;
        }

        
        save_gradeFile(); 
    }
}


void viewgrade() {



    if (recordCount == 0) {
        printf("No grades found yet.\n");
        return;
    }

    printf("\nAll Student Grades:\n");
    printf("%s %s %s %s\n", "Name", "ID", "Grade", "Letter");

    for (int i = 0; i < recordCount; i++) {
        unsigned long long id = records[i].ID;
        char *name = "no idea";

       
        for (int j = 0; j < userSize; j++) {
            if (users[j].ID == id) {
                name = users[j].username;
                break;
            }
        }

        float grade = records[i].grade;
        char letter;

        
        if (grade >= 90) letter = 'A';
        else if (grade >= 85) letter = 'B'; 
        else if (grade >= 80) letter = 'C';
        else if (grade >= 75) letter = 'D';
        else if (grade >= 70) letter = 'E';
        else letter = 'F';

        printf("%s %llu %.2f %c\n", name, id, records[i].grade, letter);
    }

    
}


void searchgrade() {

    int n = 1;

    if (recordCount == 0) {
        printf("No grade records available.\n");
        return;
    }

    while (1) {

        int found = 0;

        printf("Enter 0 to return or any numeric key to continue\n");
        printf("Choice: ");
        scanf("%d", &n);

        if (n == 0) {
            return;
        }

        unsigned long long inputID;
        printf("Enter student ID: ");
        scanf("%llu", &inputID);

        for (int i = 0; i < recordCount; i++) {
            if (records[i].ID == inputID) {
                found = 1;

                char *name = "no idea";
                for (int j = 0; j < userSize; j++) {
                    if (users[j].ID == inputID) {
                        name = users[j].username;
                        break;
                    }
                }

                float grade = records[i].grade;
                char letter;

                if (grade >= 90) letter = 'A';
                else if (grade >= 85) letter = 'B';
                else if (grade >= 80) letter = 'C';
                else if (grade >= 75) letter = 'D';
                else if (grade >= 70) letter = 'E';
                else letter = 'F';

                printf("\nStudent: %s\nID: %llu\nGrade: %.2f\nLetter: %c\n",
                       name, inputID, grade, letter);

                break;
            }
        }

        if (!found) {
            printf("No grade record found for this student.\n");
        }
    }
}


void grade()
{
    int choice;

    do{

    printf("\nGrade management\n");
    
    printf("1. Input grades\n");
    printf("2. View all grades\n");
    printf("3. Search student grade\n");
    printf("4. EXIT\n\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);


        switch(choice)
        {   
            case 1: inputgrade(); break;
            case 2: viewgrade(); break;
            case 3: searchgrade(); break;
            case 4: printf("EXITING.........\n"); return;
            default: printf("INVALID CHOICE! Choose again.\n");

        }
    
            }while(choice!= 4);
}

////////




//attendance

typedef struct {
    unsigned long long ID;
    int daysPresent;
    int attendanceMarks;   
} AttendanceRecord;

AttendanceRecord attendanceRecords[100];
int attendanceCount = 0;


void attendance(void);

void load_attendanceFile(void);
void save_attendanceFile(void);
void inputattendance(void);
void viewattendance(void);



void load_attendanceFile()
{
    
    FILE *file = fopen("records2.dat", "rb"); 


    if (!file) {
        printf("No saved attendance records found. Starting fresh.\n");
        attendanceCount = 0;
        return;
    }



    fread(&attendanceCount, sizeof(int), 1, file);        
    fread(attendanceRecords, sizeof(AttendanceRecord), attendanceCount, file); 

    fclose(file);
    printf("Attendance records loaded successfully.\n");

}


void save_attendanceFile()
{

    FILE *file = fopen("records2.dat", "wb"); 
    
    
    if (!file) {
        printf("Error opening attendance file for saving.\n");
        return;
    }



    fwrite(&attendanceCount, sizeof(int), 1, file);        
    fwrite(attendanceRecords, sizeof(AttendanceRecord), attendanceCount, file);  

    fclose(file);
    printf("Attendance records saved successfully.\n");

}


void inputattendance(void)
{

    unsigned long long id;
    int days,marks;
    int n = 1;

    while(1){

        int found = 0;

        printf("Enter 0 to return or any numeric key to continue\n");
        printf("Choice: ");
        scanf("%d", &n);

        if (n == 0) {
            return;
        }

        printf("Enter student ID: ");
        scanf("%llu", &id);

        printf("Enter days present: ");
        scanf("%d", &days);

        if(days < 0) days = 0;
        if(days > 20) days = 20;

        if(days >= 17) marks = 5;
        else if(days >= 13) marks = 4;
        else if(days >= 10) marks = 3;
        else if(days >= 7)  marks = 2;
        else if(days >= 1)  marks = 1;
        else marks = 0;

        found = 0;

      
        for (int i = 0; i < attendanceCount; i++) {

            if (attendanceRecords[i].ID == id) {
              
                attendanceRecords[i].daysPresent = days;
                attendanceRecords[i].attendanceMarks = marks;
                
                found = 1;
                break;
            }

        }

       
        if (!found) {
            
            attendanceRecords[attendanceCount].ID = id;
            attendanceRecords[attendanceCount].daysPresent = days;
            attendanceRecords[attendanceCount].attendanceMarks = marks;
            
            attendanceCount++;
        }

        
        save_attendanceFile(); 
    }


}


void viewattendance()
{

    if (attendanceCount == 0) {
        printf("No attendance found yet.\n");
        return;
    }

    printf("\nAll Student Attendance:\n");
    printf("%s %s %s %s\n", "Name", "ID", "Days", "Marks");

    for (int i = 0; i < attendanceCount; i++) {
        unsigned long long id = attendanceRecords[i].ID;
        char *name = "no idea";

       
        for (int j = 0; j < userSize; j++) {
            if (users[j].ID == id) {
                name = users[j].username;
                break;
            }
        }

        

        printf("%s %llu %d %d\n", name, id, attendanceRecords[i].daysPresent, attendanceRecords[i].attendanceMarks);
    }




}
//

void attendance()
{

    int choice;

    do{

    printf("\nAttendance management\n");
    
    printf("1. Input attendance\n");
    printf("2. View all attendance\n");
    
    printf("3. EXIT\n\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);


        switch(choice)
        {   
            case 1: inputattendance(); break;
            case 2: viewattendance(); break;
            
            case 3: printf("EXITING.........\n"); return;
            default: printf("INVALID CHOICE! Choose again.\n");

        }
    
            }while(choice!= 3);


}




////////// end ig






int main() {
    char name[100];
    unsigned long long id;
    int loginMenu = 1;
    int programMenu = 0;

    load_gradeFile();       //file loads 1st 
    load_attendanceFile();

    while(loginMenu) {
        int logUser = 0;
        int logID = 0;

        while(logUser == 0) {
            printf("Enter username: ");
            scanf("%99s", name);

            logUser = loginUser(users, userSize, name, keys, adminSize);

            if(logUser == 0) {
                printf("Invalid username\n\n");
            }

            int tryID = 0;

            if(logUser == 1) {
                while(logID == 0) {
                    printf("Enter ID: ");
                    scanf("%llu", &id);

                    logID = loginID(users, userSize, id);

                    if(logID == 0) {
                        printf("Invalid ID\n\n");
                        tryID++;
                    }

                    if(tryID > 3) {
                        printf("Too many tries.\n");
                        loginMenu = 0;
                        break;
                    }
                }
                if(logID == 1) {
                    programMenu = 1;
                    printf("Login successful!\n\n");
                    logUser = -1;
                }
            }

            if(logUser == 2) {
                loginMenu = 0;
                break;
            }

            if(logUser == 3) {
                printf("Admin permissions granted.\n\n");
                programMenu = 2;
                logUser = -1;
            }
        }

        if(loginMenu == 0) break;

        
        while(programMenu == 1) {
            int nav = 0;
            printf("\nStudent Menu (no functional options)\n");
            printf("4. Logout\nChoose: ");
            scanf("%d", &nav);
            if(nav == 4) programMenu = 0;
        }

       
        while(programMenu == 2) {
            int nav = 0;
            printf("\nAdmin Main Menu:\n");
            printf("1. Attendance\n");
            printf("2. Grade Management\n");
            printf("3. Logout\nChoose: ");
            scanf("%d", &nav);

            switch(nav) {
                case 1:
                    attendance();
                    break;
                case 2:
                   grade();
                    break;
                case 3:
                    programMenu = 0;
                    break;
                default:
                    printf("Invalid option.\n");
            }
        }
    }

    printf("Program terminated.\n");
    return 0;
}
