#include <stdio.h>

char ch;
float value,values[1000];
int total_corrupt = 0,total_valid = 0;
FILE *rfp;
FILE *wfp;


int main(){
      

  rfp=fopen("data.txt","r");
  wfp=fopen("output.txt","w");
  
   if(rfp==NULL){
      // LINK Not created
      printf("Read text file stream was not created\n");
      return -1;
    }
    else{printf("Read text file stream created\n");}


    if(wfp==NULL){
      // LINK Not created
      printf("write text file stream was not created\n");
      return -1;
    }
    else{printf("write text file stream created\n");}


    /*while(fscanf(rfp,"%c", &ch)==1){
       total_corrupt++;
   }*/

   while(fscanf(rfp,"%f", &value)==1){
        values[total_valid] = value;
        total_valid++;
   }

        
    if(ferror(rfp))
    printf(" HARDWARE FAILURE \n");

    if(ferror(wfp))
    printf(" HARDWARE FAILURE \n");

    if(feof(rfp)){
        
        printf("\n the number of chars in the file %d", total_corrupt);
        
        for (int i=0;i<total_valid;i++){
            printf("%f\n",values[i]);
        }
        
    }
    else{
    printf("EOF was not reached\n");}
    
    

    fclose(rfp);
    fclose(wfp);

    getchar();
    return 0;
