
#include <stdio.h>

#define MAX 100

/* Function Declarations */
void enterRecord(void);
void displayRecord(void);
void editRecord(void);
void displayTopper(void);
void searchStudent(void);
void deleteStudent(void);
void calculateResult(int i);
int findStudent(int roll);

/* Global Variables */
char name[MAX][50];
int rollNo[MAX];

float physics[MAX], maths[MAX], computer[MAX];
float civil[MAX], mechanical[MAX];
float total[MAX], percentage[MAX];
char grade[MAX];

int recordEntered = 0;

/* Main Function */
int main(void)
{
    int choice;

    while (1)
    {
        printf("\n============================================\n");
        printf("       STUDENT ACADEMIC RECORD SYSTEM\n");
        printf("============================================\n");
        printf("1. Enter / Add Student Record\n");
        printf("2. Display All Student Records\n");
        printf("3. Edit Student Details\n");
        printf("4. Display Topper Student\n");
        printf("5. Search Student Record\n");
        printf("6. Delete Student Record\n");
        printf("7. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input! Please enter a number.\n");

            while (getchar() != '\n')
            {
            }

            continue;
        }

        switch (choice)
        {
            case 1:
                enterRecord();
                break;

            case 2:
                displayRecord();
                break;

            case 3:
                editRecord();
                break;

            case 4:
                displayTopper();
                break;

            case 5:
                searchStudent();
                break;

            case 6:
                deleteStudent();
                break;

            case 7:
                printf("\nThank you for using this system!\n");
                return 0;

            default:
                printf("\nInvalid choice! Enter 1 to 7.\n");
        }
    }

    return 0;
}

/* Calculate Total, Percentage and Grade */
void calculateResult(int i)
{
    total[i] = physics[i] + maths[i] + computer[i]
             + civil[i] + mechanical[i];

    percentage[i] = total[i] / 5.0f;

    if (percentage[i] >= 85)
        grade[i] = 'A';
    else if (percentage[i] >= 70)
        grade[i] = 'B';
    else if (percentage[i] >= 55)
        grade[i] = 'C';
    else if (percentage[i] >= 40)
        grade[i] = 'D';
    else
        grade[i] = 'F';
}

/* Find Student Using Roll Number */
int findStudent(int roll)
{
    int i;

    for (i = 0; i < recordEntered; i++)
    {
        if (rollNo[i] == roll)
            return i;
    }

    return -1;
}

/* Enter Multiple Student Records */
void enterRecord(void)
{
    int number, j, i;
    int roll;
    float p, m, c, cv, mech;

    printf("\nHow many students' details do you want to add? ");

    if (scanf("%d", &number) != 1)
    {
        printf("\nInvalid input!\n");

        while (getchar() != '\n')
        {
        }

        return;
    }

    if (number <= 0)
    {
        printf("\nPlease enter a number greater than zero.\n");
        return;
    }

    if (number > MAX - recordEntered)
    {
        printf("\nYou can add only %d more students.\n",
               MAX - recordEntered);
        return;
    }

    for (j = 0; j < number; j++)
    {
        i = recordEntered;

        printf("\n============================================\n");
        printf("          ENTER STUDENT %d DETAILS\n", j + 1);
        printf("============================================\n");

        printf("Enter student name: ");
        scanf(" %49[^\n]", name[i]);

        printf("Enter roll number: ");

        if (scanf("%d", &roll) != 1)
        {
            printf("\nInvalid roll number. Please start again.\n");

            while (getchar() != '\n')
            {
            }

            j--;
            continue;
        }

        if (findStudent(roll) != -1)
        {
            printf("\nThis roll number already exists!\n");
            printf("Please enter the details again.\n");
            j--;
            continue;
        }

        printf("\nEnter marks of 5 subjects (0-100):\n");

        printf("Physics: ");
        if (scanf("%f", &p) != 1)
            goto invalid_input;

        printf("Maths: ");
        if (scanf("%f", &m) != 1)
            goto invalid_input;

        printf("Computer: ");
        if (scanf("%f", &c) != 1)
            goto invalid_input;

        printf("Civil: ");
        if (scanf("%f", &cv) != 1)
            goto invalid_input;

        printf("Mechanical: ");
        if (scanf("%f", &mech) != 1)
            goto invalid_input;

        if (p < 0 || p > 100 ||
            m < 0 || m > 100 ||
            c < 0 || c > 100 ||
            cv < 0 || cv > 100 ||
            mech < 0 || mech > 100)
        {
            printf("\nMarks must be between 0 and 100.\n");
            printf("Please enter this student's details again.\n");
            j--;
            continue;
        }

        rollNo[i] = roll;
        physics[i] = p;
        maths[i] = m;
        computer[i] = c;
        civil[i] = cv;
        mechanical[i] = mech;

        calculateResult(i);
        recordEntered++;

        printf("\nStudent %d record added successfully!\n", j + 1);
        continue;

        invalid_input:
        printf("\nInvalid marks input! Please enter numbers only.\n");

        while (getchar() != '\n')
        {
        }

        j--;
    }

    printf("\nAll requested student records have been entered!\n");
}

/* Display All Student Records */
void displayRecord(void)
{
    int i;

    if (recordEntered == 0)
    {
        printf("\nNo student record found!\n");
        printf("Please enter student details first.\n");
        return;
    }

    printf("\n========== ALL STUDENT RECORDS ==========\n");

    for (i = 0; i < recordEntered; i++)
    {
        printf("\nStudent Number: %d\n", i + 1);
        printf("--------------------------------------------\n");

        printf("Name        : %s\n", name[i]);
        printf("Roll Number : %d\n", rollNo[i]);
        printf("Physics     : %.2f\n", physics[i]);
        printf("Maths       : %.2f\n", maths[i]);
        printf("Computer    : %.2f\n", computer[i]);
        printf("Civil       : %.2f\n", civil[i]);
        printf("Mechanical  : %.2f\n", mechanical[i]);

        printf("--------------------------------------------\n");

        printf("Total Marks : %.2f / 500\n", total[i]);
        printf("Percentage  : %.2f%%\n", percentage[i]);
        printf("Grade       : %c\n", grade[i]);

        if (percentage[i] >= 40)
            printf("Result      : PASS\n");
        else
            printf("Result      : FAIL\n");
    }

    printf("\n============================================\n");
}

/* Edit Student Details */
void editRecord(void)
{
    int roll, i;
    char newName[50];
    float p, m, c, cv, mech;

    if (recordEntered == 0)
    {
        printf("\nNo student record found!\n");
        return;
    }

    printf("\nEnter roll number of student to edit: ");

    if (scanf("%d", &roll) != 1)
    {
        printf("\nInvalid roll number!\n");

        while (getchar() != '\n')
        {
        }

        return;
    }

    i = findStudent(roll);

    if (i == -1)
    {
        printf("\nStudent not found!\n");
        return;
    }

    printf("Enter new student name: ");
    scanf(" %49[^\n]", newName);

    printf("Enter new Physics marks: ");
    if (scanf("%f", &p) != 1)
        goto edit_invalid;

    printf("Enter new Maths marks: ");
    if (scanf("%f", &m) != 1)
        goto edit_invalid;

    printf("Enter new Computer marks: ");
    if (scanf("%f", &c) != 1)
        goto edit_invalid;

    printf("Enter new Civil marks: ");
    if (scanf("%f", &cv) != 1)
        goto edit_invalid;

    printf("Enter new Mechanical marks: ");
    if (scanf("%f", &mech) != 1)
        goto edit_invalid;

    if (p < 0 || p > 100 ||
        m < 0 || m > 100 ||
        c < 0 || c > 100 ||
        cv < 0 || cv > 100 ||
        mech < 0 || mech > 100)
    {
        printf("\nMarks must be between 0 and 100.\n");
        printf("Record was not changed.\n");
        return;
    }

    {
        int k = 0;

        while (newName[k] != '\0')
        {
            name[i][k] = newName[k];
            k++;
        }

        name[i][k] = '\0';
    }

    physics[i] = p;
    maths[i] = m;
    computer[i] = c;
    civil[i] = cv;
    mechanical[i] = mech;

    calculateResult(i);

    printf("\nStudent details updated successfully!\n");
    return;

    edit_invalid:
    printf("\nInvalid input! Record was not changed.\n");

    while (getchar() != '\n')
    {
    }
}

/* Display Topper Student */
void displayTopper(void)
{
    int i;
    float highest;

    if (recordEntered == 0)
    {
        printf("\nNo student record found!\n");
        printf("Please enter student details first.\n");
        return;
    }

    highest = percentage[0];

    for (i = 1; i < recordEntered; i++)
    {
        if (percentage[i] > highest)
            highest = percentage[i];
    }

    printf("\n========== TOPPER STUDENT(S) ==========\n");

    for (i = 0; i < recordEntered; i++)
    {
        if (percentage[i] == highest)
        {
            printf("\nName        : %s\n", name[i]);
            printf("Roll Number : %d\n", rollNo[i]);
            printf("Total Marks : %.2f / 500\n", total[i]);
            printf("Percentage  : %.2f%%\n", percentage[i]);
            printf("Grade       : %c\n", grade[i]);
            printf("--------------------------------------------\n");
        }
    }
}

/* Search Student Record */
void searchStudent(void)
{
    int roll, i;

    if (recordEntered == 0)
    {
        printf("\nNo student record found!\n");
        printf("Please add student details first.\n");
        return;
    }

    printf("\nEnter roll number to search: ");

    if (scanf("%d", &roll) != 1)
    {
        printf("\nInvalid roll number! Please enter numbers only.\n");

        while (getchar() != '\n')
        {
        }

        return;
    }

    i = findStudent(roll);

    if (i == -1)
    {
        printf("\nStudent with roll number %d was not found.\n", roll);
        return;
    }

    printf("\n========== STUDENT RECORD FOUND ==========\n");
    printf("Name        : %s\n", name[i]);
    printf("Roll Number : %d\n", rollNo[i]);
    printf("Physics     : %.2f\n", physics[i]);
    printf("Maths       : %.2f\n", maths[i]);
    printf("Computer    : %.2f\n", computer[i]);
    printf("Civil       : %.2f\n", civil[i]);
    printf("Mechanical  : %.2f\n", mechanical[i]);
    printf("--------------------------------------------\n");
    printf("Total Marks : %.2f / 500\n", total[i]);
    printf("Percentage  : %.2f%%\n", percentage[i]);
    printf("Grade       : %c\n", grade[i]);

    if (percentage[i] >= 40)
        printf("Result      : PASS\n");
    else
        printf("Result      : FAIL\n");

    printf("============================================\n");
}

/* Delete Student Record */
void deleteStudent(void)
{
    int roll, i, j, confirm;

    if (recordEntered == 0)
    {
        printf("\nNo student record found!\n");
        printf("Please add student details first.\n");
        return;
    }

    printf("\nEnter roll number of student to delete: ");

    if (scanf("%d", &roll) != 1)
    {
        printf("\nInvalid roll number! Please enter numbers only.\n");

        while (getchar() != '\n')
        {
        }

        return;
    }

    i = findStudent(roll);

    if (i == -1)
    {
        printf("\nStudent with roll number %d was not found.\n", roll);
        return;
    }

    printf("\nStudent record to be deleted:\n");
    printf("Name        : %s\n", name[i]);
    printf("Roll Number : %d\n", rollNo[i]);

    printf("Are you sure you want to delete this record? (1 = Yes, 0 = No): ");

    if (scanf("%d", &confirm) != 1)
    {
        printf("\nInvalid input! Record was not deleted.\n");

        while (getchar() != '\n')
        {
        }

        return;
    }

    if (confirm != 1)
    {
        printf("\nDelete cancelled. Record was not changed.\n");
        return;
    }

    /* Shift remaining records one position to the left */
    for (j = i; j < recordEntered - 1; j++)
    {
        rollNo[j] = rollNo[j + 1];

        {
            int k = 0;

            while (name[j + 1][k] != '\0')
            {
                name[j][k] = name[j + 1][k];
                k++;
            }

            name[j][k] = '\0';
        }

        physics[j] = physics[j + 1];
        maths[j] = maths[j + 1];
        computer[j] = computer[j + 1];
        civil[j] = civil[j + 1];
        mechanical[j] = mechanical[j + 1];
        total[j] = total[j + 1];
        percentage[j] = percentage[j + 1];
        grade[j] = grade[j + 1];
    }

    recordEntered--;

    printf("\nStudent record deleted successfully!\n");
}

