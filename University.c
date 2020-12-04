#include<malloc.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>
#include"University.h"

/*Поведение:
10. подсчет статистики:
процентное распределение студентов по курсам, по уровню обучения, по возрасту.
*/
static const int Size = 256;

University* getUniversityFromFile(const char* path) {
    FILE* file = fopen(path, "r");
    University* result = (University*) malloc(sizeof(University));
    if (file) {
        char buf;
        unsigned int i = 0;
        result->rectorName = (char*) malloc(sizeof(char) * Size);
        for (buf = fgetc(file); (buf != '\n') && (buf != EOF); buf = fgetc(file)) {
            result->rectorName[i++] = buf;
        }
        result->rectorName[i] = '\0';
        i = 0;
        for (buf = fgetc(file); (buf != '\n') && (buf != EOF); buf = fgetc(file)) {
            i *= 10;
            i += buf - '0';
        }
        result->instituteNumber = i;
        result->institutes = (Institute*) malloc(sizeof(Institute) * i);
        for (unsigned int j = 0; j < result->instituteNumber; ++j) {
            Institute* institute = result->institutes + j;
            institute->name = (char*) malloc(sizeof(char) * Size);
            i = 0;
            for (buf = fgetc(file); (buf != '\n') && (buf != EOF); buf = fgetc(file)) {
                institute->name[i++] = buf;
            }
            institute->name[i] = '\0';
            institute->directorName = (char*) malloc(sizeof(char) * Size);
            i = 0;
            for (buf = fgetc(file); (buf != '\n') && (buf != EOF); buf = fgetc(file)) {
                institute->directorName[i++] = buf;
            }
            institute->directorName[i] = '\0';
            institute->phoneNumber = (char*) malloc(sizeof(char) * Size);
            i = 0;
            for (buf = fgetc(file); (buf != '\n') && (buf != EOF); buf = fgetc(file)) {
                institute->phoneNumber[i++] = buf;
            }
            institute->phoneNumber[i] = '\0';
            i = 0;
            for (buf = fgetc(file); (buf != '\n') && (buf != EOF); buf = fgetc(file)) {
                i *= 10;
                i += buf - '0';
            }
            institute->studentNumber = i;
            institute->students = (Student*) malloc(sizeof(Student) * institute->studentNumber);
            for(unsigned int k = 0; k < institute->studentNumber; k++){
                Student* student = institute->students + k;
                i = 0;
                for(buf = fgetc(file); (buf != '-') && (buf != EOF); buf = fgetc(file)){
                    i *= 10;
                    i += buf - '0';
                }
                student->ID = i;
                student->fullName = (char*) malloc(sizeof(char) * Size);
                i = 0;
                for(buf = fgetc(file); (buf != '-') && (buf != EOF); buf = fgetc(file)){
                    student->fullName[i++] = buf;
                }
                student->fullName[i] = '\0';
                buf = fgetc(file);
                switch(buf) {
                    case 'B':
                        student->level = Bachelor;
                        break;
                    case 'S':
                        student->level = Specialty;
                        break;
                    case 'M':
                        student->level = Master;
                        break;
                    case 'P':
                        student->level = Postgraduate;
                        break;
                }
                for (buf = fgetc(file); (buf != '-') && (buf != EOF); buf = fgetc(file));
                buf = fgetc(file);
                switch(buf) {
                    case 'F':
                        student->form = FullTime;
                        break;
                    case 'P':
                        student->form = PartTime;
                        break;
                    case 'N':
                        student->form = NoneTime;
                        break;
                }
                for (buf = fgetc(file); (buf != '-') && (buf != EOF); buf = fgetc(file));
                buf = fgetc(file);
                switch(buf) {
                    case 'F':
                        student->cost = Full;
                        break;
                    case 'N':
                        student->cost = None;
                        break;
                }
                for (buf = fgetc(file); (buf != '-') && (buf != EOF); buf = fgetc(file));
                student->group = (char*) malloc(sizeof(char) * Size);
                i = 0;
                for (buf = fgetc(file); (buf != '-') && (buf != EOF); buf = fgetc(file)) {
                    student->group[i++] = buf;
                }
                student->group[i] = '\0';
                i = 0;
                for (buf = fgetc(file); (buf != '-') && (buf != EOF); buf = fgetc(file)) {
                    i *= 10;
                    i += buf - '0';
                }
                student->course = i;
                i = 0;
                for (buf = fgetc(file); (buf != '-') && (buf != EOF); buf = fgetc(file)) {
                    i *= 10;
                    i += buf - '0';
                }
                student->birthYear = i;
                student->phoneNumber = (char*) malloc(sizeof(char) * Size);
                i = 0;
                for (buf = fgetc(file); (buf != '\n') && (buf != EOF); buf = fgetc(file)) {
                    student->phoneNumber[i++] = buf;
                }
                student->phoneNumber[i] = '\0';
            }
        }
        fclose(file);
    }
    return result;
}

void printUniversity(University* university) {
    printf("Rector name: %s; Number of institutes: %d;\n", university->rectorName, university->instituteNumber);
    printf("Institutes:\n");
    for (unsigned int i = 0; i < university->instituteNumber; ++i) {
        Institute* institute = university->institutes + i;
        printf("%d) ", (i + 1));
        printInstitute(institute);
        printf("\n");
    }
}

void printInstitute(Institute* institute) {
    printf("%s institute; Director name: %s; Phone number: %s; Number of students: %d;\nStudents:\n",
            institute->name, institute->directorName, institute->phoneNumber, institute->studentNumber);
    for (unsigned int j = 0; j < institute->studentNumber; ++j) {
        Student* student = institute->students + j;
        printf("ID: %d; Name: %s; Study Level: ", student->ID, student->fullName);
        switch(student->level){
            case Bachelor:
                printf("Bachelor; ");
                break;
            case Specialty:
                printf("Specialty; ");
                break;
            case Master:
                printf("Master; ");
                break;
            case Postgraduate:
                printf("Postgraduate; ");
                break;
        }
        printf("Study Form: ");
        switch(student->form){
            case FullTime:
                printf("Full Time; ");
                break;
            case PartTime:
                printf("Part Time; ");
                break;
            case NoneTime:
                printf("None Time; ");
                break;
        }
        printf("Study Cost: ");
        switch(student->cost){
            case Full:
                printf("Full price; ");
                break;
            case None:
                printf("None price; ");
                break;
        }
        printf("Group code: %s; Course: %d; Birth Year: %d; Phone Number: %s;\n",
                student->group, student->course, student->birthYear, student->phoneNumber);
    }
}

void addInstitute(University* university, const Institute* institute) {
    university->instituteNumber += 1;
    Institute* newInstitutes = (Institute*) malloc(sizeof(Institute) * university->instituteNumber);
    for (unsigned int i = 0; i < university->instituteNumber - 1; ++i) {
        Institute* oldInstitute = university->institutes + i;
        Institute* newInstitute = newInstitutes + i;
        newInstitute->directorName = oldInstitute->directorName;
        newInstitute->name = oldInstitute->name;
        newInstitute->phoneNumber = oldInstitute->phoneNumber;
        newInstitute->studentNumber = oldInstitute->studentNumber;
        newInstitute->students = oldInstitute->students;
    }
    if (university->instituteNumber > 1) {
        free(university->institutes);
    }
    university->institutes = newInstitutes;
    Institute* newInstitute = university->institutes + university->instituteNumber - 1;
    newInstitute->directorName = (char*) malloc(sizeof(char) * (strlen(institute->directorName) + 1));
    strcpy(newInstitute->directorName, institute->directorName);
    newInstitute->name = (char*) malloc(sizeof(char) * (strlen(institute->name) + 1));
    strcpy(newInstitute->name, institute->name);
    newInstitute->phoneNumber = (char*) malloc(sizeof(char) * (strlen(institute->phoneNumber) + 1));
    strcpy(newInstitute->phoneNumber, institute->phoneNumber);
    newInstitute->studentNumber = institute->studentNumber;
    newInstitute->students = (Student*) malloc(sizeof(Student) * newInstitute->studentNumber);
    for (unsigned int i = 0; i < newInstitute->studentNumber; ++i) {
        Student* newStudent = newInstitute->students + i;
        Student* student = institute->students + i;
        newStudent->birthYear = student->birthYear;
        newStudent->cost = student->cost;
        newStudent->course = student->course;
        newStudent->form = student->form;
        newStudent->fullName = (char*) malloc(sizeof(char) * (strlen(student->fullName) + 1));
        strcpy(newStudent->fullName, student->fullName);
        newStudent->group = (char*) malloc(sizeof(char) * (strlen(student->group) + 1));
        strcpy(newStudent->group, student->group);
        newStudent->ID = student->ID;
        newStudent->level = student->level;
        newStudent->phoneNumber = (char*) malloc(sizeof(char) * (strlen(student->phoneNumber) + 1));
        strcpy(newStudent->phoneNumber, student->phoneNumber);
    }
}

void addStudent(Institute* institute, Student* student) {
    institute->studentNumber += 1;
    Student* newStudents = (Student*) malloc(sizeof(Student) * institute->studentNumber);
    for (unsigned int i = 0; i < institute->studentNumber - 1; ++i) {
        Student* newStudent = newStudents + i;
        Student* oldStudent = institute->students + i;
        newStudent->birthYear = oldStudent->birthYear;
        newStudent->cost = oldStudent->cost;
        newStudent->course = oldStudent->course;
        newStudent->form = oldStudent->form;
        newStudent->fullName = oldStudent->fullName;
        newStudent->group = oldStudent->group;
        newStudent->ID = oldStudent->ID;
        newStudent->level = oldStudent->level;
        newStudent->phoneNumber = oldStudent->phoneNumber;
    }
    if(institute->studentNumber > 1){
        free(institute->students);
    }
    institute->students = newStudents;
    Student* newStudent = institute->students + institute->studentNumber - 1;
    newStudent->birthYear = student->birthYear;
    newStudent->cost = student->cost;
    newStudent->course = student->course;
    newStudent->form = student->form;
    newStudent->fullName = (char*) malloc(sizeof(char) * (strlen(student->fullName) + 1));
    strcpy(newStudent->fullName, student->fullName);
    newStudent->group = (char*) malloc(sizeof(char) * (strlen(student->group) + 1));
    strcpy(newStudent->group, student->group);
    newStudent->ID = institute->studentNumber;
    newStudent->level = student->level;
    newStudent->phoneNumber = (char*) malloc(sizeof(char) * (strlen(student->phoneNumber) + 1));
    strcpy(newStudent->phoneNumber, student->phoneNumber);
}

void deleteStudent(Institute* institute, unsigned int ID) {
    if (institute->studentNumber == 0) {
        return;
    }
    for (unsigned int i = 0; i < institute->studentNumber; ++i) {
        if (institute->students[i].ID == ID) {
            break;
        }
        if (i == institute->studentNumber - 1) {
            return;
        }
    }
    institute->studentNumber -= 1;
    Student* newStudents = (Student*) malloc(sizeof(Student) * institute->studentNumber);
    unsigned int j = 0;
    for (unsigned int i = 0; i < institute->studentNumber; ++i) {
        Student* oldStudent = institute->students + j;
        Student* newStudent = newStudents + i;
        if (oldStudent->ID == ID){
            ++j;
            free(oldStudent->fullName);
            free(oldStudent->group);
            free(oldStudent->phoneNumber);
            oldStudent = institute->students + j;
        }
        newStudent->birthYear = oldStudent->birthYear;
        newStudent->cost = oldStudent->cost;
        newStudent->course = oldStudent->course;
        newStudent->form = oldStudent->form;
        newStudent->fullName = oldStudent->fullName;
        newStudent->group = oldStudent->group;
        newStudent->ID = i;
        newStudent->level = oldStudent->level;
        newStudent->phoneNumber = oldStudent->phoneNumber;
        ++j;
    }
    free(institute->students);
    institute->students = newStudents;
}

void deleteInstitute(University* university, char* name) {
    int instituteIndex = -1;
    for (unsigned int i = 0; i < university->instituteNumber; ++i) {
        Institute* institute = university->institutes + i;
        for (unsigned int j = 0; true; ++j) {
            if (name[j] != institute->name[j]) {
                break;
            }
            if (institute->name[j] == '\0') {
                instituteIndex = i;
                break;
            }
        }
        if (instituteIndex == -1 && i == university->instituteNumber - 1) {
            return;
        }
    }
    university->instituteNumber -= 1;
    Institute* newInstitutes = (Institute*) malloc(sizeof(Institute) * university->instituteNumber);
    int j = 0;
    for (unsigned int i = 0; i < university->instituteNumber + 1; ++i){
        Institute* oldInstitute = university->institutes + i;
        if (instituteIndex == i) {
            for (unsigned int k = 0; k < oldInstitute->studentNumber; ++k) {
                Student* student = oldInstitute->students + k;
                free(student->fullName);
                free(student->group);
                free(student->phoneNumber);
            }
            free(oldInstitute->directorName);
            free(oldInstitute->name);
            free(oldInstitute->phoneNumber);
            free(oldInstitute->students);
        }
        else {
            Institute* institute = newInstitutes + j;
            institute->directorName = oldInstitute->directorName;
            institute->name = oldInstitute->name;
            institute->phoneNumber = oldInstitute->phoneNumber;
            institute->studentNumber = oldInstitute->studentNumber;
            institute->students = oldInstitute->students;
        }
    }
}

void changeStudent(Institute* institute, Student* student) {
    Student* change;
    for (unsigned int i = 0; i < institute->studentNumber; ++i) {
        change = institute->students + i;
        if (change->ID == student->ID) {
            break;
        }
        if (i == institute->studentNumber - 1) {
            return;
        }
    }
    change->birthYear = student->birthYear;
    change->cost = student->cost;
    change->course = student->course;
    change->form = student->form;
    free(change->fullName);
    change->fullName = (char*) malloc(sizeof(char) * (strlen(student->fullName) + 1));
    strcpy(change->fullName, student->fullName);
    free(change->group);
    change->group = (char*) malloc(sizeof(char) * (strlen(student->group) + 1));
    strcpy(change->group, student->group);
    change->level = student->level;
    free(change->phoneNumber);
    change->phoneNumber = (char*) malloc(sizeof(char) * (strlen(student->phoneNumber) + 1));
    strcpy(change->phoneNumber, student->phoneNumber);
}

Student* getStudent(Institute* institute, unsigned int id) {
    Student* result;
    for (unsigned int i = 0; i < institute->studentNumber; ++i) {
        Student* student = institute->students + i;
        if (student->ID == id) {
            result->birthYear = student->birthYear;
            result->cost = student->cost;
            result->course = student->course;
            result->form = result->form;
            result->fullName = (char*) malloc(sizeof(char) * (strlen(student->fullName) + 1));
            strcpy(result->fullName, student->fullName);
            result->group = (char*) malloc(sizeof(char) * (strlen(student->group) + 1));
            strcpy(result->group, student->group);
            result->ID = id;
            result->level = student->level;
            result->phoneNumber = (char*) malloc(sizeof(char) * (strlen(student->phoneNumber) + 1));
            strcpy(result->phoneNumber, student->phoneNumber);
        }
    }
    return result;
}

void dumpInstitute(Institute* institute) {
    char* fileName = (char*) malloc(sizeof(char) * (strlen(institute->name) + 5));
    strcpy(fileName, institute->name);
    int i = strlen(institute->name);
    fileName[i++] = '.';
    fileName[i++] = 't';
    fileName[i++] = 'x';
    fileName[i++] = 't';
    fileName[i] = '\0';
    FILE* file = fopen(fileName, "w");
    if (file) {
        fprintf(file, "%s\n%s\n%s\n%d\n", institute->name,
                                          institute->directorName,
                                          institute->phoneNumber,
                                          institute->studentNumber);
        for (unsigned int i = 0; i < institute->studentNumber; ++i){
            Student* student = institute->students + i;
            fprintf(file, "%d-%s-", student->ID, student->fullName);
            switch (student->level){
                case Bachelor:
                    fprintf(file, "Bachelor-");
                    break;
                case Specialty:
                    fprintf(file, "Specialty-");
                    break;
                case Master:
                    fprintf(file, "Master-");
                    break;
                case Postgraduate:
                    fprintf(file, "Postgraduate-");
                    break;
            }
            switch (student->form) {
                case FullTime:
                    fprintf(file, "FullTime-");
                    break;
                case PartTime:
                    fprintf(file, "PartTime-");
                    break;
                case NoneTime:
                    fprintf(file, "NoneTime-");
                    break;
            }
            switch (student->cost) {
                case Full:
                    fprintf(file, "Full-");
                    break;
                case None:
                    fprintf(file, "None-");
                    break;
            }
            fprintf(file, "%s-%d-%d-%s\n", student->group,
                                           student->course,
                                           student->birthYear,
                                           student->phoneNumber);
        }
        fclose(file);
    }
}

void dumpUniversity(University* university){
    char* fileName = (char*) malloc(sizeof(char) * (strlen(university->rectorName) + 5));
    strcpy(fileName, university->rectorName);
    int i = strlen(university->rectorName);
    fileName[i++] = '.';
    fileName[i++] = 't';
    fileName[i++] = 'x';
    fileName[i++] = 't';
    fileName[i] = '\0';
    FILE* file = fopen(fileName, "w");
    if (file) {
        fprintf(file, "%s\n%d\n", university->rectorName, university->instituteNumber);
        for(unsigned int j = 0; j < university->instituteNumber; ++j) {
            Institute* institute = university->institutes + j;
            fprintf(file, "%s\n%s\n%s\n%d\n", institute->name,
                                          institute->directorName,
                                          institute->phoneNumber,
                                          institute->studentNumber);
            for (unsigned int i = 0; i < institute->studentNumber; ++i){
                Student* student = institute->students + i;
                fprintf(file, "%d-%s-", student->ID, student->fullName);
                switch (student->level){
                    case Bachelor:
                        fprintf(file, "Bachelor-");
                        break;
                    case Specialty:
                        fprintf(file, "Specialty-");
                        break;
                    case Master:
                        fprintf(file, "Master-");
                        break;
                    case Postgraduate:
                        fprintf(file, "Postgraduate-");
                        break;
                }
                switch (student->form) {
                    case FullTime:
                        fprintf(file, "FullTime-");
                        break;
                    case PartTime:
                        fprintf(file, "PartTime-");
                        break;
                    case NoneTime:
                        fprintf(file, "NoneTime-");
                        break;
                }
                switch (student->cost) {
                    case Full:
                        fprintf(file, "Full-");
                        break;
                    case None:
                        fprintf(file, "None-");
                        break;
                }
                fprintf(file, "%s-%d-%d-%s\n", student->group,
                                               student->course,
                                               student->birthYear,
                                               student->phoneNumber);
            }
        }
        fclose(file);
    }
}

void sortInstitute(Institute* institute, Filter filter) {
    for (unsigned int i = 0; i < institute->studentNumber - 1; ++i) {
        for (unsigned int j = 1; j < institute->studentNumber; ++j) {
            Student* student1 = institute->students + j;
            Student* student0 = institute->students + j - 1;
            switch (filter) {
                case ID:
                    if  (student1->ID < student0->ID) {
                        studentSwap(student0, student1);
                    }
                    break;
                case FullName:
                    if (stringsEquals(student0->fullName, student1->fullName, 0) == -1) {
                        studentSwap(student0, student1);
                    }
                    break;
                case Level:
                    if (student1->level < student0->level) {
                        studentSwap(student0, student1);
                    }
                    break;
                case Form:
                    if (student1->form < student0->form) {
                        studentSwap(student0, student1);
                    }
                    break;
                case Cost:
                    if (student1->cost < student0->cost) {
                        studentSwap(student0, student1);
                    }
                    break;
                case Group:
                    if (stringsEquals(student0->group, student1->group, 0) == -1) {
                        studentSwap(student0, student1);
                    }
                    break;
                case Course:
                    if (student1->course < student0->course) {
                        studentSwap(student0, student1);
                    }
                    break;
                case BirthYear:
                    if (student1->birthYear < student0->birthYear) {
                        studentSwap(student0, student1);
                    }
                    break;
                case PhoneNumber:
                    if (stringsEquals(student0->phoneNumber, student1->phoneNumber, 0) == -1) {
                        studentSwap(student0, student1);
                    }
                    break;
            }
        }
    }
}

int stringsEquals(const char* string1, const char* string2, const unsigned int index) {//string1 > string2 == 1, string1 = string2 == 0, string1 < string2 == -1
	if ((string1[index] == '\0') && (string2[index] == '\0')) {
		return 0;
	}
	if (string1[index] < string2[index]) {
		return 1;
	}
	else if (string1[index] > string2[index]) {
		return -1;
	}
	else {
		return stringsEquals(string1, string2, index + 1);
	}
}

void studentSwap(Student* student0, Student* student1){
    Student temp;
    temp.birthYear = student1->birthYear;
    temp.cost = student1->cost;
    temp.course = student1->course;
    temp.form = student1->form;
    temp.fullName = student1->fullName;
    temp.group = student1->group;
    temp.ID = student1->ID;
    temp.level = student1->level;
    temp.phoneNumber = student1->phoneNumber;
    student1->birthYear = student0->birthYear;
    student1->cost = student0->cost;
    student1->course = student0->course;
    student1->form = student0->form;
    student1->fullName = student0->fullName;
    student1->group = student0->group;
    student1->ID = student0->ID;
    student1->level = student0->level;
    student1->phoneNumber = student0->phoneNumber;
    student0->birthYear = temp.birthYear;
    student0->cost = temp.cost;
    student0->course = temp.course;
    student0->form = temp.form;
    student0->fullName = temp.fullName;
    student0->group = temp.group;
    student0->ID = temp.ID;
    student0->level = temp.level;
    student0->phoneNumber = temp.phoneNumber;
}

void stats(Institute* institute, Stats stats) {
    printf("Stats ");
    int* a;
    int* b;
    int size = 0;
    switch (stats) {
        case CourseStats:
            printf("course:\n");
            a = (int*) malloc(sizeof(int));
            b = (int*) malloc(sizeof(int));
            b[0] = -1;
            for (unsigned int i = 0; i < institute->studentNumber; ++i) {
                Student* student = institute->students + i;
                int index = isIn(student->course, b, size);
                if (index == -1) {
                    a = realloc(a, (size + 1));
                    b = realloc(b, (size + 1));
                    a[size] = 1;
                    b[size] = student->course;
                    ++size;
                }
                else {
                    ++a[size];
                }
            }
            for(int i = 0; i < size; ++i) {
                double percent = ((double) a[i]) / institute->studentNumber * 100;
                printf("%d - %lf%%\n", b[i], percent);
            }
            break;
        case LevelStats:
            printf("level:\n");
            a = (int*) malloc(sizeof(int) * 4);
            for (int i = 0; i < 4; ++i) {
                a[i] = 0;
            }
            for (unsigned int i = 0; i < institute->studentNumber; ++i) {
                Student* student = institute->students + i;
                switch (student->level) {
                    case Bachelor:
                        ++a[0];
                        break;
                    case Specialty:
                        ++a[1];
                        break;
                    case Master:
                        ++a[2];
                        break;
                    case Postgraduate:
                        ++a[3];
                        break;
                }
            }
            printf("Bachelor - %lf%%\n", ((double) a[0]) / institute->studentNumber * 100);
            printf("Specialty - %lf%%\n", ((double) a[1]) / institute->studentNumber * 100);
            printf("Master - %lf%%\n", ((double) a[2]) / institute->studentNumber * 100);
            printf("Postgraduate - %lf%%\n", ((double) a[3]) / institute->studentNumber * 100);
            break;
        case Age:
            printf("age:\n");
            a = (int*) malloc(sizeof(int));
            b = (int*) malloc(sizeof(int));
            b[0] = -1;
            for (unsigned int i = 0; i < institute->studentNumber; ++i) {
                Student* student = institute->students + i;
                int index = isIn(student->birthYear, b, size);
                if (index == -1) {
                    a = realloc(a, (size + 1));
                    b = realloc(b, (size + 1));
                    a[size] = 1;
                    b[size] = student->birthYear;
                    ++size;
                }
                else {
                    a[size] += 1;
                }
            }
            for(int i = 0; i < size; ++i) {
                double percent = ((double) a[i]) / institute->studentNumber * 100;
                printf("%d - %lf%%\n", b[i], percent);
            }
            break;
    }
}

int isIn(int data, int* b, int bSize) {
    for (int i = 0; i < bSize; ++i) {
        if (data == b[i]) {
            return i;
        }
    }
    return -1;
}









