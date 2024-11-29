#include <stdio.h>
#include <ctype.h>

char ch, chars[100];
float value, values[100];
int total_corrupt = 0, total_valid = 0;
FILE *rfp;
FILE *wfp;

int main() {
    rfp = fopen("data.txt", "r");//open files
    wfp = fopen("output.txt", "w");

    if (rfp == NULL) {
        // LINK Not created
        printf("Read text file stream was not created\n");
        return -1;
    } else {
        printf("Read text file stream created\n");
    }

    if (wfp == NULL) {
        // LINK Not created
        printf("Write text file stream was not created\n");
        return -1;
    } else {
        printf("Write text file stream created\n");
    }

    while (fscanf(rfp, "%c", &ch) == 1) {
        if (isalpha(ch)) {
            chars[total_corrupt] = ch; //append to char array
            total_corrupt++; //increment corrupt char count
        } else if (isdigit(ch) || ch == '-' || ch == '.') {
            ungetc(ch, rfp); // Put the character back to read the float
            if (fscanf(rfp, "%f", &value) == 1) {
                values[total_valid] = value; //append to valid float array
                total_valid++;
            }
        }
    }
      //print invalid chars
    printf("\nThe number of chars in the file: %d\n", total_corrupt);
    for (int i = 0; i < total_corrupt; i++) {
        printf("%c\n", chars[i]);
    }
      //print valid floats
    printf("\nThe number of valid floats in the file: %d\n", total_valid);
    for (int i = 0; i < total_valid; i++) {
        printf("%f\n", values[i]);
        fprintf(wfp, "%.1f ",values[i]); // write to text file
    }
    
    //error handling
    if (ferror(rfp)) {
        printf("HARDWARE FAILURE\n");
    }

    if (ferror(wfp)) {
        printf("HARDWARE FAILURE\n");
    }
      // close files
    fclose(rfp);
    fclose(wfp);
      // exit
    return 0;
}
