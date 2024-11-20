#include<stdio.h> 
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 24
#define nRows 8
#define nCols 3

// PROTOTYPES
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);

bool isValid(const int arr[], int pos, int length);
void remove_element(int arr[],int length, int pos);
void insert_element(int arr[],int length, int pos, int value);
void reshape(const int arr[], int length, int arr2d[nRows][nCols]);
void trans_matrix(int inputMat[nRows][nCols], int outputMat[nCols][nRows]);
bool found_duplicate(int arr[],int length);

// Variables
int arr[SIZE];
int arr2d[nRows][nCols];
int mat_transp[nCols][nRows];
int test[] = {0,1,2,3,4,5,6,7,7,8};

int main() {
    // Check for duplicates in the test array
    bool truth = found_duplicate(test, 10);
    printf("%d\n", truth);
}

// Function to print an array
void print_array(int array[], int length) {
    for (int i = 0; i < length; i++)
        printf("array[%d]= %d\n", i, array[i]);
}

// Function to print a matrix
void print_matrix(int mat[][nCols], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < nCols; j++)
            printf("mat[%d][%d]= %d\n", i, j, mat[i][j]);
        puts("");     
    }     
}

// Function to check if a position is valid
bool isValid(const int arr[], int pos, int length) {
    if (pos < (length - 1) && pos > 0) {
        return true;
    } else {
        return false;
    }
}

// Function to remove an element from an array
void remove_element(int arr[], int length, int pos) {
    bool valid = isValid(arr, pos, length);
    if (valid == true) {
        for (int i = pos; i > 1; i--) {
            arr[i] = arr[i - 1];
        }
    } else {
        printf("Pos is Invalid");
    }
}

// Function to insert an element into an array
void insert_element(int arr[], int length, int pos, int value) {
    bool valid = isValid(arr, pos, length);
    if (valid == true) {
        for (int i = 1; i < pos + 1; i++) {
            arr[i - 1] = arr[i];
        }
        arr[pos] = value;
    } else {
        printf("Pos is Invalid");
    }
}

// Function to reshape a 1D array into a 2D array
void reshape(const int arr[], int length, int arr2d[nRows][nCols]) {
    if (length == (nRows * nCols)) {
        int count = 0;
        for (int i = 0; i < nCols; i++) {
            for (int j = 0; j < nRows; j++) {
                arr2d[j][i] = arr[count];
                count++;
            }
        }
    } else {
        printf("1D array length does not match number of elements in 2D array");
        exit(-1);
    }
}

// Function to transpose a matrix
void trans_matrix(int inputMat[nRows][nCols], int outputMat[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            inputMat[i][j] = outputMat[j][i];            
        }
    }
}

// Function to check for duplicates in an array
bool found_duplicate(int arr[], int length) {
    bool duplicate = false;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            if (arr[i] == arr[j] && i != j) {
                duplicate = true;
                break;
            }
        }
    }
    return duplicate;
}
