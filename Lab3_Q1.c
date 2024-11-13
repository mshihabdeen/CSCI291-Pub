#include<stdio.h> 
#include <stdbool.h> 
#define SIZE 24
#define nRows 8
#define nCols 3
// PROTOTYPES
void print_array(int array[]);
void print_matrix(int mat[][nCols], int rows);
bool isValid(const int arr[], int pos);
void remove_element(int arr[], int pos);


int main()
{
int arr[SIZE];
int arr2d[nRows][nCols];
print_matrix(arr2d,nRows);
//Call to different functions
}

void print_array(int array[]){
   int length = sizeof(array)/sizeof(array[0]);

   for(int i=0;i<length; i++)
      printf("array[%d]= %d\n", i, array[i]);
}

void print_matrix(int mat[][nCols], int rows){
   for(int i=0;i<rows; i++){
    for(int j=0;j<nCols; j++)
         printf("mat[%d][%d]= %d\n", i,j, mat[i][j]);
    puts("");     
   }     
}

bool isValid(const int arr[],int pos){
   int length = sizeof(arr)/sizeof(arr[0]);

   if (pos < (length-1) && pos > 0){
      return true;
   }
   else{
      return false;
   }
}

void remove_element(int arr[], int pos){
   int length = sizeof(arr)/sizeof(arr[0]);
   bool valid = isValid(arr,pos);
   int arrCopy[length];


   if (valid == true){
      for (int i=pos;i<(length-1);i++){
         arr[pos] = arrCopy[pos-1];
      }
   }

}