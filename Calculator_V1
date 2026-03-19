#include <stdio.h>
#include <math.h>
#include <string.h>

void mainMenu(void);
int getChoice(void);
int readComponents(char names[][50], float weights[], float maxPoints[], int components);

void singleStudent(char compNames[][50], float compWeights[], float compMaxPoints[], int components);
void multipleStudents(char compNames[][50], float compWeights[], float compMaxPoints[], int components);

float totalWeight(float weights[], int components);
char *letterGrade(float numericGrade);

float maximum(float grades[], int students);
float average(float grades[], int students);
void sort(float arr[], int size);
float median(float grades[], int students);

int validateScore(float score, float maxPoints);
int validatePositive(float value);

// Recursion Function
float finalGrade(float scores[], float weights[], float maxPoints[], int components, int index);

int main()
{
    char componentNames[50][50];
    float componentWeights[50];
    float componentMaxPoints[50];
    int components;
    int choice;

    do
    {
        mainMenu();
        choice = getChoice();
        switch (choice)
        {
        case 1:
            printf("Number of components: ");
            scanf("%d", &components);

            readComponents(componentNames, componentWeights,
                           componentMaxPoints, components);

            if (fabs(totalWeight(componentWeights, components) - 100.0) > 0.01)
            {
                printf("Error: Total weight must be 100%%\n");
                break;
            }
            singleStudent(componentNames, componentWeights,
                          componentMaxPoints, components);
            break;

        case 2:
            printf("Number of components: ");
            scanf("%d", &components);

            readComponents(componentNames, componentWeights,
                           componentMaxPoints, components);

            if (fabs(totalWeight(componentWeights, components) - 100.0) > 0.01)
            {
                printf("Error: Total weight must be 100%%\n");
                break;
            }

            multipleStudents(componentNames, componentWeights,
                             componentMaxPoints, components);
            break;

        case 3:
            printf("--- HAVE A GOOD DAY! ---\n");
            printf("========================");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}

void mainMenu(void)
{
    puts("==================================");
    puts("Weighted Grade Calculation Program");
    puts("1. Single Student Grades");
    puts("2. Multiple Students Grades");
    puts("3. Exit");
    puts("==================================");
    printf("Enter your choice (1/2/3):");
}

int getChoice(void)
{
    int choice;
    scanf("%d", &choice);
    return choice;
}

// Recursive Function
float finalGrade(float scores[], float weights[],
                 float maxPoints[], int components, int index)
{
    if (index >= components)
    {
        return 0;
    }

    float contribution = (scores[index] / maxPoints[index]) * (weights[index] / 100.0);
    return contribution + finalGrade(scores, weights, maxPoints, components, index + 1);
}

int readComponents(char names[][50], float weights[],
                   float maxPoints[], int components)
{
    for (int i = 0; i < components; i++)
    {
        printf("\nComponent %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", names[i]);

        do
        {
            printf("Weight: ");
            scanf("%f", &weights[i]);
        } while (!validatePositive(weights[i]));

        do
        {
            printf("Max Allocated Point: ");
            scanf("%f", &maxPoints[i]);
        } while (!validatePositive(maxPoints[i]));
    }
    return 0;
}

float totalWeight(float weights[], int components)
{
    float total = 0;
    for (int i = 0; i < components; i++)
    {
        total += weights[i];
    }
    return total;
}

void singleStudent(char compNames[][50], float compWeights[],
                   float compMaxPoints[], int components)
{
    float scores[50];
    float final;

    printf("\n-- Summary of Score --\n");

    for (int i = 0; i < components; i++)
    {
        do
        {
            printf("Score for \"%s\": ", compNames[i]);
            scanf("%f", &scores[i]);
        } while (!validateScore(scores[i], compMaxPoints[i]));
    }

    final = finalGrade(scores, compWeights, compMaxPoints, components, 0) * 100;
    final = round(final);

    printf("\nFinal Weighted Grade: %.0f%%\nLetter Grade: %s\n\n",
           final, letterGrade(final));
}

void multipleStudents(char compNames[][50], float compWeights[],
                      float compMaxPoints[], int components)
{
    int students;
    float studentScores[100][50];
    float finalGrades[100];

    printf("Number of students: ");
    scanf("%d", &students);

    for (int i = 0; i < students; i++)
    {
        printf("\nStudent %d\n", i + 1);

        for (int j = 0; j < components; j++)
        {
            do
            {
                printf("Score for \"%s\": ", compNames[j]);
                scanf("%f", &studentScores[i][j]);
            } while (!validateScore(studentScores[i][j], compMaxPoints[j]));
        }

        finalGrades[i] = finalGrade(studentScores[i], compWeights,
                                    compMaxPoints, components, 0) *
                         100;
        finalGrades[i] = round(finalGrades[i]);

        printf("Final Weighted Grade: %.0f%%\nLetter Grade: %s\n",
               finalGrades[i], letterGrade(finalGrades[i]));
    }

    printf("\nClass Summary:\n");
    printf("Maximum: %.2f\n", maximum(finalGrades, students));
    printf("Average: %.2f\n", average(finalGrades, students));
    printf("Median: %.2f\n", median(finalGrades, students));
    printf("\n");
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

float maximum(float grades[], int students)
{
    float max = grades[0];
    for (int i = 1; i < students; i++)
    {
        if (grades[i] > max)
        {
            max = grades[i];
        }
    }
    return max;
}

float average(float grades[], int students)
{
    float sum = 0;
    for (int i = 0; i < students; i++)
    {
        sum += grades[i];
    }
    return sum / students;
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

float median(float grades[], int students)
{
    float sorted[100];
    for (int i = 0; i < students; i++)
    {
        sorted[i] = grades[i];
    }

    sort(sorted, students);

    if (students % 2 == 0)
    {
        return (sorted[students / 2 - 1] + sorted[students / 2]) / 2.0;
    }
    else
    {
        return sorted[students / 2];
    }
}

int validateScore(float score, float maxPoints)
{
    if (score < 0)
    {
        printf("Error: Score cannot be negative\n");
        return 0;
    }
    if (score > maxPoints)
    {
        printf("Error: Score cannot exceed maximum points (%.2f)\n", maxPoints);
        return 0;
    }
    return 1;
}

int validatePositive(float value)
{
    if (value <= 0)
    {
        printf("Error: Value must be positive\n");
        return 0;
    }
    return 1;
}
