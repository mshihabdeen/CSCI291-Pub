#include <stdio.h>

char ch,chars[100];
float value,values[100];
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
    
    fseek(rfp,0,SEEK_SET);
    
   while(!feof(rfp)){
        //fscanf(rfp,"%f ", &value);
        fscanf(rfp,"%c ", &ch);
        
        int char_ascii = ch;
        
        if(char_ascii>57){
            chars[total_corrupt] = ch;
            total_corrupt++;
        }
       /* if (&value != NULL){
            values[total_valid] = value;
            total_valid++;
        }*/
    
   }

        
    if(ferror(rfp))
    printf(" HARDWARE FAILURE \n");

    if(ferror(wfp))
    printf(" HARDWARE FAILURE \n");

    if(feof(rfp)){
        
        printf("\nThe number of chars in the file %d\n", total_corrupt);
        
        for (int i=0;i<total_valid;i++){
            printf("%f\n",values[i]);
        }
        
        return 0;
        
    }
    else{
    printf("EOF was not reached\n");
    return -1;
    }
    
    

    fclose(rfp);
    fclose(wfp);

    getchar();
    return 0;
}
