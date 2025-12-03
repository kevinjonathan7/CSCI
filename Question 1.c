#include <stdio.h>

// Iterative Version
void rearrange_iterative(int *A, int n) {
    int B[n];
    int *odd = B;          // pointer for next odd
    int *even = B + n - 1; // pointer for next even

    for (int i = 0; i < n; i++) {
        if (A[i] % 2 != 0) {
            *odd = A[i];
            odd++;
        } else {
            *even = A[i];
            even--;
        }
    }

    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }
}

// Recursive Version
void rearrange_recursive_helper(int *A, int *B, int index, int odd, int even, int n) {
    if (index == n)
        return;

    if (A[index] % 2 != 0) {
        B[odd] = A[index];
        rearrange_recursive_helper(A, B, index + 1, odd + 1, even, n);
    } else {
        B[even] = A[index];
        rearrange_recursive_helper(A, B, index + 1, odd, even - 1, n);
    }
}

void rearrange_recursive(int *A, int n) {
    int B[n];
    rearrange_recursive_helper(A, B, 0, 0, n - 1, n);

    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }
}

// Main
int main() {
    int n;

    printf("Enter array size: ");
    scanf("%d", &n);

    int A[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    int method;
    printf("\n1. Iterative\n2. Recursive\nChoose: ");
    scanf("%d", &method);

    if (method == 1)
        rearrange_iterative(A, n);
    else
        rearrange_recursive(A, n);

    printf("\nRearranged array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}
