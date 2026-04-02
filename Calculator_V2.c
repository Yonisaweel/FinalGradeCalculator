#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct
{
    char name[100];
    float weight;
    float maxPoints;
} Component;

typedef struct
{
    char name[100];
    float *scores;
    float finalGrade;
} Student;

void mainMenu(void);
int getChoice(void);
void clearBuffer(void);
void readText(char text[], int size);
int sameTextIgnoreCase(const char first[], const char second[]);

Component *readComponents(int *componentCount);
Student *readStudents(Component components[], int componentCount, int *studentCount, int choice);

float totalWeight(Component components[], int componentCount);
float finalGrade(float scores[], Component components[], int componentCount, int index);
char *letterGrade(float numericGrade);

float maximum(Student students[], int studentCount);
float average(Student students[], int studentCount);
void sort(float arr[], int size);
float median(Student students[], int studentCount);

int validatePositive(float value);
int validateScore(float score, float maxPoints);
int searchStudent(Student students[], int studentCount, char target[]);
void sortStudentsByGrade(Student students[], int studentCount);

void displayStudent(Student student);
void displaySummary(Student students[], int studentCount);
void displayTopStudents(Student students[], int studentCount);
void freeStudents(Student *students, int studentCount);

int main(void)
{
    Component *components = NULL;
    Student *students = NULL;
    int componentCount = 0;
    int studentCount = 0;
    int choice;

    do
    {
        char target[100];
        int found;

        mainMenu();
        choice = getChoice();

        switch (choice)
        {
        case 1:
            free(components);
            freeStudents(students, studentCount);
            students = NULL;
            studentCount = 0;

            components = readComponents(&componentCount);
            students = readStudents(components, componentCount, &studentCount, choice);

            if (studentCount > 0)
            {
                printf("\n-- Student Summary --\n");
                printf("Final Weighted Grade: %.0f%%\n", students[0].finalGrade);
                printf("Letter Grade: %s\n\n", letterGrade(students[0].finalGrade));
            }
            break;

        case 2:
            free(components);
            freeStudents(students, studentCount);
            students = NULL;
            studentCount = 0;

            components = readComponents(&componentCount);
            students = readStudents(components, componentCount, &studentCount, choice);

            if (studentCount > 0)
            {
                printf("\n-- Class Summary --\n");
                displaySummary(students, studentCount);
            }
            break;

        case 3:
            if (students == NULL || studentCount == 0)
            {
                printf("No student records available.\n");
            }
            else
            {
                sortStudentsByGrade(students, studentCount);
                puts("======================================");
                puts("  Sorting students by final grade...  ");
                puts("======================================\n");
                puts("Class Ranking:");
                for (int i = 0; i < studentCount; i++)
                {
                    printf("%d. ", i + 1);
                    displayStudent(students[i]);
                }
            }
            break;

        case 4:
            if (students == NULL || studentCount == 0)
            {
                puts("No student records available.");
            }
            else
            {
                printf("Enter student name to search: ");
                readText(target, 100);
                found = searchStudent(students, studentCount, target);
                if (found >= 0)
                {
                    printf("Result: ");
                    displayStudent(students[found]);
                }
                else
                {
                    puts("Student not found.");
                }
            }
            break;

        case 5:
            puts("      --- HAVE A GOOD DAY! ---      ");
            printf("      ========================      ");
            break;
        }
    } while (choice != 5);

    free(components);
    freeStudents(students, studentCount);
    return 0;
}

void mainMenu(void)
{
    puts("======================================");
    puts("  Weighted Grade Calculation Program  ");
    puts("======================================");
    puts("1. Single Student Grades");
    puts("2. Multiple Students Grades");
    puts("3. Sort Students by Grade");
    puts("4. Search for a Student");
    puts("5. Exit");
}

int getChoice(void)
{
    int choice;
    int valid;

    do
    {
        printf("Enter your choice (1/2/3/4/5): ");
        valid = scanf("%d", &choice);

        if (valid != 1)
        {
            puts("Invalid input. Please enter a number between 1 and 5.");
            clearBuffer();
            continue;
        }

        clearBuffer();

        if (choice < 1 || choice > 5)
        {
            puts("Invalid choice. Please try again.");
            valid = 0;
        }
    } while (valid != 1);

    return choice;
}

void clearBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

void readText(char text[], int size)
{
    if (fgets(text, size, stdin) != NULL)
    {
        text[strcspn(text, "\n")] = '\0';
    }
}

int sameTextIgnoreCase(const char first[], const char second[])
{
    int i = 0;

    while (first[i] != '\0' && second[i] != '\0')
    {
        if (tolower((unsigned char)first[i]) != tolower((unsigned char)second[i]))
        {
            return 0;
        }
        i++;
    }

    return first[i] == '\0' && second[i] == '\0';
}

int validatePositive(float value)
{
    if (value > 0)
    {
        return 1;
    }
    printf("Error: Value must be positive.\n");
    return 0;
}

int validateScore(float score, float maxPoints)
{
    if (score < 0)
    {
        printf("Error: Earned points cannot be negative. Please re-enter.\n");
        return 0;
    }
    if (score > maxPoints)
    {
        printf("Error: Earned points cannot exceed maximum allocated points.\n");
        printf("Please re-enter.\n");
        return 0;
    }
    return 1;
}

Component *readComponents(int *componentCount)
{
    Component *components;
    int count;
    float weightInput;
    float maxInput;

    do
    {
        printf("Enter number of course components: ");
        while (scanf("%d", &count) != 1 || count <= 0)
        {
            printf("Error: Please enter a valid number.\n");
            clearBuffer();
            printf("Enter number of course components: ");
        }
        clearBuffer();

        components = (Component *)malloc(count * sizeof(Component));
        if (components == NULL)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        for (int i = 0; i < count; i++)
        {
            printf("Component %d:\n", i + 1);
            printf("Name: ");
            readText(components[i].name, 100);

            do
            {
                printf("Weight (as percentage): ");
                while (scanf("%f", &weightInput) != 1)
                {
                    printf("Error: Please enter a valid number.\n");
                    clearBuffer();
                    printf("Weight (as percentage): ");
                }
                clearBuffer();
            } while (!validatePositive(weightInput));
            components[i].weight = weightInput;

            do
            {
                printf("Max Allocated Points: ");
                while (scanf("%f", &maxInput) != 1)
                {
                    printf("Error: Please enter a valid number.\n");
                    clearBuffer();
                    printf("Max Allocated Points: ");
                }
                clearBuffer();
            } while (!validatePositive(maxInput));
            components[i].maxPoints = maxInput;
        }

        if (fabs(totalWeight(components, count) - 100.0) > 0.01)
        {
            printf("Error: Total weight exceeds 100%%! Please re-enter all components.\n");
            free(components);
        }
        else
        {
            break;
        }
    } while (1);

    *componentCount = count;
    return components;
}

Student *readStudents(Component components[], int componentCount, int *studentCount, int choice)
{
    Student *students = NULL;
    char nameInput[100];
    int count = 0;

    while (1)
    {
        Student *temp;

        printf("Enter student's full name");
        if (choice == 2)
        {
            printf(" (or type DONE to stop)");
        }
        printf(": ");
        readText(nameInput, 100);

        if (choice == 2 && sameTextIgnoreCase(nameInput, "DONE"))
        {
            break;
        }

        temp = (Student *)realloc(students, (count + 1) * sizeof(Student));
        if (temp == NULL)
        {
            printf("Memory reallocation failed.\n");
            freeStudents(students, count);
            exit(1);
        }
        students = temp;

        strcpy(students[count].name, nameInput);
        students[count].scores = (float *)malloc(componentCount * sizeof(float));
        if (students[count].scores == NULL)
        {
            printf("Memory allocation failed.\n");
            freeStudents(students, count + 1);
            exit(1);
        }

        for (int i = 0; i < componentCount; i++)
        {
            do
            {
                printf("Score for \"%s\": ", components[i].name);
                while (scanf("%f", &students[count].scores[i]) != 1)
                {
                    printf("Error: Please enter a valid number.\n");
                    clearBuffer();
                    printf("Score for \"%s\": ", components[i].name);
                }
                clearBuffer();
            } while (!validateScore(students[count].scores[i], components[i].maxPoints));
        }

        students[count].finalGrade = finalGrade(students[count].scores, components, componentCount, 0);
        students[count].finalGrade = roundf(students[count].finalGrade);

        if (choice == 2){
            displayStudent(students[count]);}
        count++;

        if (choice != 2)
        {
            break;
        }
    }

    *studentCount = count;
    return students;
}

float totalWeight(Component components[], int componentCount)
{
    float sum = 0;

    for (int i = 0; i < componentCount; i++)
    {
        sum += components[i].weight;
    }

    return sum;
}

float finalGrade(float scores[], Component components[], int componentCount, int index)
{
    if (index == componentCount)
    {
        return 0;
    }

    return ((scores[index] / components[index].maxPoints) * components[index].weight) +
           finalGrade(scores, components, componentCount, index + 1);
}

char *letterGrade(float numericGrade)
{
    if (numericGrade >= 90 && numericGrade <= 100)
        return "A+";
    else if (numericGrade >= 85 && numericGrade <= 89)
        return "A";
    else if (numericGrade >= 80 && numericGrade <= 84)
        return "A-";
    else if (numericGrade >= 75 && numericGrade <= 79)
        return "B+";
    else if (numericGrade >= 70 && numericGrade <= 74)
        return "B";
    else if (numericGrade >= 65 && numericGrade <= 69)
        return "C+";
    else if (numericGrade >= 60 && numericGrade <= 64)
        return "C";
    else if (numericGrade >= 50 && numericGrade <= 59)
        return "D";
    else
        return "F";
}

float maximum(Student students[], int studentCount)
{
    float max = students[0].finalGrade;

    for (int i = 1; i < studentCount; i++)
    {
        if (students[i].finalGrade > max)
        {
            max = students[i].finalGrade;
        }
    }
    return max;
}

float average(Student students[], int studentCount)
{
    float sum = 0;

    for (int i = 0; i < studentCount; i++)
    {
        sum += students[i].finalGrade;
    }
    return roundf(sum / studentCount);
}

void sort(float arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

float median(Student students[], int studentCount)
{
    float *grades = (float *)malloc(studentCount * sizeof(float));
    float result;

    if (grades == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < studentCount; i++)
    {
        grades[i] = students[i].finalGrade;
    }

    sort(grades, studentCount);

    if (studentCount % 2 == 0)
    {
        result = roundf((grades[studentCount / 2 - 1] + grades[studentCount / 2]) / 2.0);
    }
    else
    {
        result = grades[studentCount / 2];
    }

    free(grades);
    return result;
}

int searchStudent(Student students[], int studentCount, char target[])
{
    for (int i = 0; i < studentCount; i++)
    {
        if (sameTextIgnoreCase(students[i].name, target))
        {
            return i;
        }
    }
    return -1;
}

void sortStudentsByGrade(Student students[], int studentCount)
{
    for (int i = 0; i < studentCount - 1; i++)
    {
        for (int j = 0; j < studentCount - i - 1; j++)
        {
            if (students[j].finalGrade < students[j + 1].finalGrade)
            {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

void displayStudent(Student student)
{
    printf("%s - %.0f%% (%s)\n", student.name, student.finalGrade, letterGrade(student.finalGrade));
}

void displayTopStudents(Student students[], int studentCount)
{
    float max = maximum(students, studentCount);
    int first = 1;

    printf("Maximum: %.0f%% (Students: ", max);
    for (int i = 0; i < studentCount; i++)
    {
        if (fabs(students[i].finalGrade - max) < 0.01)
        {
            if (!first)
            {
                printf(", ");
            }
            printf("%s", students[i].name);
            first = 0;
        }
    }
    printf(")\n");
}

void displaySummary(Student students[], int studentCount)
{
    for (int i = 0; i < studentCount; i++)
    {
        displayStudent(students[i]);
    }

    displayTopStudents(students, studentCount);
    printf("Average: %.0f%%\n", average(students, studentCount));
    printf("Median: %.0f%%\n", median(students, studentCount));
}

void freeStudents(Student *students, int studentCount)
{
    if (students == NULL)
    {
        return;
    }

    for (int i = 0; i < studentCount; i++)
    {
        free(students[i].scores);
    }
    free(students);
}
