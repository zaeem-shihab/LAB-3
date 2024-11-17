
#include <stdio.h>
#include <stdbool.h>

// Function prototypes
bool isValid(const int arr[], int length, int pos);                                                   // Validates the position in an array
void remove_element(int arr[], int length, int pos);                                                  // Removes an element from an array
void insert_element(int arr[], int length, int pos, int value);                                       // Inserts an element into the array
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]);             // Reshapes the array
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]);   // Transposes the matrix
bool found_duplicate(const int arr[], int length);                                                    // Checks for duplicates within an array
void printArray(const int arr[], int length);                                                         // Prints a 1D array
void print2DArray(int nRows, int nCols, const int arr2d[nRows][nCols]);                               // Prints a 2D array

// ---------------------- Function Definitions ---------------------- //

// Checks if a position is valid within the array range
bool isValid(const int arr[], int length, int pos) {
    return (pos >= 0 && pos < length);  // Valid position is within the range [0, length-1]
}

// Removes an element at a specific position and shifts the elements within the array
void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {
        printf("[ERROR] Invalid position: %d. Operation failed.\n", pos);
        return;
    }

    for (int i = pos; i > 0; i--) {
        arr[i] = arr[i - 1];
    }

    printf("[SYS] Element at index %d has been successfully removed.\n", pos);
}

// Inserts an element at a specific position and shifts the elements within the array
void insert_element(int arr[], int length, int pos, int value) {
    if (!isValid(arr, length, pos)) {
        printf("[ERROR] Insertion at index %d is out of bounds. Operation halted.\n", pos);
        return;
    }

    for (int i = 0; i < pos; i++) {
        arr[i] = arr[i + 1];
    }
    arr[pos] = value;

    printf("[SYS] The Value -> %d has been successfully inserted at index %d.\n", value, pos);
}

// Here we reshape a 1D array into a 2D array with specific dimensions
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("[ERROR] Dimensions %dx%d are incompatible with array length.\n", nRows, nCols);
        return;
    }

    int idx = 0;
    for (int col = 0; col < nCols; col++) {
        for (int row = 0; row < nRows; row++) {
            arr2d[row][col] = arr[idx++];
        }
    }

    printf("[SYS] Array successfully restructured to %dx%d format.\n", nRows, nCols);
}

// Transposes a matrix as needed
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat_transp[j][i] = mat[i][j];
        }
    }

    printf("[SYS] Matrix transposition complete.\n");
}

// Checks for duplicate values within the array
bool found_duplicate(const int arr[], int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;    // True if duplicates are identified
            }
        }
    }
    return false;    // false if no duplicates are found
}

// Prints a 1D array
void printArray(const int arr[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Prints a 2D array
void print2DArray(int nRows, int nCols, const int arr2d[nRows][nCols]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            printf("%d ", arr2d[i][j]);
        }
        printf("\n");
    }
}

// --------------------------- Main Program --------------------------- //

int main() {
    // Array setup and initialization
    int arr[] = {10, 20, 30, 40, 50};
    int length = sizeof(arr) / sizeof(arr[0]);

    // Displays the original array to the user
    printf(">> Initial Array Configuration:\n");
    printArray(arr, length);

    // Tests remove_element from the array
    printf("\n>> Executing remove_element at 2nd Index:\n");
    remove_element(arr, length, 2);
    printArray(arr, length);

    printf("\n>> Attempting remove_element at 10th Index:\n");
    remove_element(arr, length, 10);

    // Resets the array for element insertion test
    int arr2[] = {10, 20, 30, 40, 50};
    printf("\n>> Executing insert_element at 2nd Index with Value -> 80:\n");
    insert_element(arr2, length, 2, 80);
    printArray(arr2, length);

    // Attempting invalid element insertion within the array
    printf("\n>> Attempting insert_element at 10th Index:\n");
    insert_element(arr2, length, 10, 80);

    // Reshaping the array test
    int arr3[] = {1, 2, 3, 4, 5, 6};
    int arr2d[3][2];
    printf("\n>> Executing 3x2 Restructure Format to Array:\n");
    reshape(arr3, 6, 3, 2, arr2d);
    print2DArray(3, 2, arr2d);

    printf("\n>> Attempting Incompatible 2x2 Restructure:\n");
    reshape(arr3, 6, 2, 2, arr2d);

    // Transposing the array test
    int mat[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int mat_transp[3][2];
    printf("\n>> Original Matrix Structure:\n");
    print2DArray(2, 3, mat);

    printf("\n>> Executing Matrix Transposition:\n");
    trans_matrix(2, 3, mat, mat_transp);
    print2DArray(3, 2, mat_transp);

    // Tests the array for duplicate elements
    int arr4[] = {10, 20, 30, 20, 50};
    printf("\n>> Analyzing for Duplicate Elements within the Array:\n");
    printArray(arr4, 5);
    if (found_duplicate(arr4, 5)) {
        printf("[SYS] Duplicate Elements Identified within the Array.\n");
    } else {
        printf("[SYS] No Duplicate Elements Present in the Array.\n");
    }

    return 0;
}