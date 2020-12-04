#ifndef UNIVERSITY_H
#define UNIVERSITY_H

typedef enum{
    Bachelor,
    Specialty,
    Master,
    Postgraduate
} StudyLevel;

typedef enum{
    FullTime,
    PartTime,
    NoneTime
} StudyForm;

typedef enum{
    None,
    Full
} StudyCost;

typedef enum {
    ID,
    FullName,
    Level,
    Form,
    Cost,
    Group,
    Course,
    BirthYear,
    PhoneNumber
} Filter;

typedef enum {
    CourseStats,
    LevelStats,
    Age
} Stats;

typedef struct {
    unsigned int ID;
    char* fullName;
    StudyLevel level;
    StudyForm form;
    StudyCost cost;
    char* group;
    unsigned int course;
    unsigned int birthYear;
    char* phoneNumber;
} Student;

typedef struct {
    char* name;
    char* directorName;
    char* phoneNumber;
    unsigned int studentNumber;
    Student* students;
} Institute;

typedef struct{
    char* rectorName;
    unsigned int instituteNumber;
    Institute* institutes;
} University;

University* getUniversityFromFile(const char* path);
void printUniversity(University* university);
void printInstitute(Institute* institute);
void addInstitute(University* university, const Institute* institute);
void addStudent(Institute* institute, Student* student);
void deleteStudent(Institute* institute, unsigned int ID);
void deleteInstitute(University* university, char* name);
void changeStudent(Institute* institute, Student* student);
void dumpInstitute(Institute* institute);
void dumpUniversity(University* university);
void sortInstitute(Institute* institute, Filter filter);
void stats(Institute* institute, Stats stats);
Student* getStudent(Institute* institute, unsigned int id);

#endif // UNIVERSITY_H
