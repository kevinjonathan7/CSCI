#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define SIZE 24
#define nRows 8
#define nCols 3

// QUESTION 1

// Function prints all elements of a one-dimensional array
void print_array(int array[], int length) {
    // Loop goes through each element and prints its index and value
    for (int i = 0; i < length; i++)
        printf("array[%d] = %d\n", i, array[i]);
}

// Function prints all elements of a two-dimensional matrix
void print_matrix(int mat[][nCols], int rows) {
    // Outer loop goes through each row
    for (int i = 0; i < rows; i++) {
        // Inner loop goes through each column of the current row
        for (int j = 0; j < nCols; j++)
            printf("mat[%d][%d] = %d\n", i, j, mat[i][j]);
        puts("");
    }
}

// Function fills an array with sequential integers starting from zero
void set_array(int arr[], int length) {
    // Loop assigns each index position the same number as its index
    for (int i = 0; i < length; i++)
        arr[i] = i;
}

// Function removes an element at a specific position and shifts remaining items left
void rem_align(int arr[], int length, int pos) {
    if (pos < 0 || pos >= length) {
        printf("Invalid position\n");
        return;
    }
    // Loop shifts all elements after the removed one to the left
    for (int i = pos; i < length - 1; i++)
        arr[i] = arr[i + 1];
    arr[length - 1] = 0; // Last element cleared after shift
}

// Function inserts a value at a specific position and shifts other elements right
void insert_align(int arr[], int length, int pos, int value) {
    if (pos < 0 || pos >= length) {
        printf("Invalid position\n");
        return;
    }
    // Loop shifts elements to right to make space for the new value
    for (int i = length - 1; i > pos; i--)
        arr[i] = arr[i - 1];
    arr[pos] = value;
}

// Function converts one-dimensional to two-dimensional matrix
void reshape(int arr[], int length, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Error: array length mismatch\n");
        return;
    }
    int k = 0;
    // Outer loop goes through rows, inner loop goes through columns
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            arr2d[i][j] = arr[k++];
}

// Function prints the transpose of  matrix 
void print_trans_matrix(int arr2d[nRows][nCols]) {
    // Outer loop iterates over columns, inner loop over rows
    for (int j = 0; j < nCols; j++) {
        for (int i = 0; i < nRows; i++)
            printf("%d ", arr2d[i][j]);
        printf("\n");
    }
}

// Function checks if  one-dimensional array contains any duplicate values
bool found_duplicate(int arr[], int length) {
    // Outer loop checks each element
    for (int i = 0; i < length - 1; i++)
        // Inner loop compares current element with every subsequent one
        for (int j = i + 1; j < length; j++)
            if (arr[i] == arr[j])
                return true;
    return false;
}

// Function creates a reversed copy of an array
void flip_array(int arr[], int length, int flipped[]) {
    // Loop assigns elements from end of original array to start of new one
    for (int i = 0; i < length; i++)
        flipped[i] = arr[length - 1 - i];
}

//QUESTION 2

#define numOfSubjects 5
#define numOfStudents 3

// Structure represents student record with name, ID, marks, and grade
typedef struct {
    char FirstName[50];
    char LastName[50];
    int StudentID;
    float SubjectMarks[numOfSubjects];
    float AggregateMarks;
    char Grade[20];
} Student;

// Function reads an integer input with validation
int read_int(const char *prompt) {
    int x;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &x) == 1 && x >= 0) return x;
        printf("Invalid input. Try again.\n");
        while (getchar() != '\n');
    }
}

// Function determines grade based on average marks
void compute_grade(Student *s) {
    if (s->AggregateMarks == -1) {
        strcpy(s->Grade, "undefined");
        return;
    }
    float mark = s->AggregateMarks;
    if (mark >= 85) strcpy(s->Grade, "HD");
    else if (mark >= 75) strcpy(s->Grade, "D");
    else if (mark >= 65) strcpy(s->Grade, "C");
    else if (mark >= 50) strcpy(s->Grade, "P");
    else strcpy(s->Grade, "F");
}

// Function adds or updates a student record in the list
void enrol(Student list[], int n) {
    int id = read_int("Enter student ID: ");
    int index = -1;

    // Loop checks if the student ID already exists
    for (int i = 0; i < n; i++)
        if (list[i].StudentID == id)
            index = i;

    // If no existing record found, search for an empty slot
    if (index == -1) {
        printf("New student record.\n");
        for (int i = 0; i < n; i++) {
            if (list[i].StudentID == 0) {
                index = i;
                list[i].StudentID = id;
                break;
            }
        }
    }

    if (index == -1) {
        printf("No space left.\n");
        return;
    }

    // Collect basic details for the student
    printf("Enter FirstName: ");
    scanf("%s", list[index].FirstName);
    printf("Enter LastName: ");
    scanf("%s", list[index].LastName);

    int allEntered = 1;
    float total = 0;

    // Loop allows entry of marks for each subject
    for (int i = 0; i < numOfSubjects; i++) {
        char choice;
        printf("Enter mark for Subject %d? (y/n): ", i + 1);
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            printf("Enter mark: ");
            scanf("%f", &list[index].SubjectMarks[i]);
            total += list[index].SubjectMarks[i];
        } else {
            list[index].SubjectMarks[i] = -1;
            allEntered = 0;
        }
    }

    // Compute average only if all marks were entered
    if (allEntered)
        list[index].AggregateMarks = total / numOfSubjects;
    else
        list[index].AggregateMarks = -1;

    compute_grade(&list[index]);
}

// Function searches for a student by ID or last name, with option to update record
void searchUpdate(Student list[], int n) {
    char mode;
    printf("Search by (I)D or (L)astName? ");
    scanf(" %c", &mode);

    int found = -1;

    // Search mode by ID
    if (mode == 'I' || mode == 'i') {
        int id = read_int("Enter ID: ");
        for (int i = 0; i < n; i++)
            if (list[i].StudentID == id)
                found = i;
    } 
    // Search mode by last name
    else {
        char lname[50];
        printf("Enter LastName: ");
        scanf("%s", lname);
        for (int i = 0; i < n; i++)
            if (strcasecmp(list[i].LastName, lname) == 0)
                found = i;
    }

    if (found == -1) {
        printf("Student not found.\n");
        return;
    }

    Student *s = &list[found];
    printf("Record found:\n");
    printf("%s %s, ID: %d, Aggregate: %.2f, Grade: %s\n",
           s->FirstName, s->LastName, s->StudentID, s->AggregateMarks, s->Grade);

    char update;
    printf("Update record? (y/n): ");
    scanf(" %c", &update);

    // If update requested, allow new details and marks
    if (update == 'y' || update == 'Y') {
        printf("Enter new FirstName: ");
        scanf("%s", s->FirstName);
        printf("Enter new LastName: ");
        scanf("%s", s->LastName);
        s->StudentID = read_int("Enter new ID: ");

        float total = 0;
        // Loop collects new marks for all subjects
        for (int i = 0; i < numOfSubjects; i++) {
            printf("New mark for Subject %d: ", i + 1);
            scanf("%f", &s->SubjectMarks[i]);
            total += s->SubjectMarks[i];
        }

        s->AggregateMarks = total / numOfSubjects;
        compute_grade(s);
    }
}

// Function finds students with the highest aggregate marks
void topStudents(Student list[], int n) {
    float highest = -1;
    // Loop for finding maximum aggregate mark
    for (int i = 0; i < n; i++)
        if (list[i].AggregateMarks > highest)
            highest = list[i].AggregateMarks;

    printf("Top Students (Aggregate %.2f):\n", highest);

    // Loop prints students matching top aggregate value
    for (int i = 0; i < n; i++)
        if (list[i].AggregateMarks == highest)
            printf("%s %s (ID: %d, Grade: %s)\n",
                   list[i].FirstName, list[i].LastName, list[i].StudentID, list[i].Grade);
}

// Main program loop
int main() {
    //Question 1: Arrays
    printf("=== Question 1: Array Processing Tests ===\n");

    int arr[SIZE];
    int arr2d[nRows][nCols];
    int flipped[SIZE];

    // 1. set_array
    set_array(arr, SIZE);
    printf("\nArray after set_array:\n");
    print_array(arr, SIZE);

    // 2. rem_align
    printf("\nRemoving element at index 2:\n");
    rem_align(arr, SIZE, 2);
    print_array(arr, SIZE);

    // 3. insert_align
    printf("\nInserting 99 at index 3:\n");
    insert_align(arr, SIZE, 3, 99);
    print_array(arr, SIZE);

    // 4. reshape
    printf("\nReshaping array to 2D matrix:\n");
    if (SIZE == nRows * nCols)
        reshape(arr, SIZE, arr2d);
    print_matrix(arr2d, nRows);

    // 5. print_trans_matrix
    printf("\nTranspose of matrix:\n");
    print_trans_matrix(arr2d);

    // 6. found_duplicate
    printf("\nChecking for duplicates in array:\n");
    if (found_duplicate(arr, SIZE))
        printf("Duplicates found.\n");
    else
        printf("No duplicates found.\n");

    // 7. flip_array
    flip_array(arr, SIZE, flipped);
    printf("\nFlipped array:\n");
    print_array(flipped, SIZE);

    //Question 2: Student Records
    printf("\n=== Question 2: Student Records Menu ===\n");

    Student list[numOfStudents] = {0};
    int choice;
    do {
        printf("\nMain Menu\n1. Enrol\n2. Search/Update\n3. Top Students\n4. Exit\n");
        choice = read_int("Enter choice: ");

        switch (choice) {
            case 1: enrol(list, numOfStudents); break;
            case 2: searchUpdate(list, numOfStudents); break;
            case 3: topStudents(list, numOfStudents); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice\n");
        }
    } while (choice != 4);

    return 0;
}
