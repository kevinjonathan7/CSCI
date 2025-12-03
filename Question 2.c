#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidName(char *name) {
    if (strlen(name) == 0) return 0;

    // Loop to check each character
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isprint(name[i]) || isdigit(name[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char filepath[200]; // Array to store the user-input file path
    printf("Enter the full path to the students file: ");
    fgets(filepath, sizeof(filepath), stdin);

    // Remove newline if present
    filepath[strcspn(filepath, "\n")] = 0;

    FILE *file; // Pointer to the file
    file = fopen(filepath, "r");
    if (file == NULL) {
        perror("File open error");
        return 1;
    }

    char line[100]; // Array to store each line from the file
    char name[50];  // Array to store the name
    int mark;
    int validCount = 0, corruptedCount = 0;
    int totalMarks = 0;

    // Loop to read each line
    while (fgets(line, sizeof(line), file) != NULL) {
        // Parse line using sscanf
        if (sscanf(line, "%49s %d", name, &mark) != 2 || !isValidName(name)) {
            corruptedCount++;
            continue; // Skip corrupted record
        }

        // Display valid record
        printf("Name: %s, Mark: %d\n", name, mark);
        validCount++;
        totalMarks += mark;
    }

    fclose(file); // Close the file

    printf("Total valid records: %d\n", validCount);
    printf("Total corrupted records: %d\n", corruptedCount);

    if (validCount > 0) {
        printf("Average mark: %.2f\n", (float)totalMarks / validCount);
    }

    return 0;
}
