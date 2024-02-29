#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6


void print_number(int n){
  static int counter;
  counter++;
  if(counter == COLUMNS){
    printf("%10d", n);
    printf("\n");
    counter = 0;    // reset the counter
  }else{
    printf("%10d", n);
  }
}

void print_sieves(int number){
    char* prime_arr = (char*) malloc((number-1) * (sizeof(char))) ; //allocating number-2 bytes memory. #numbers fr. 2 to number

    for(int i = 0; i < number-1; i++){   //starting from 2 to number
        prime_arr[i] = 1;           // setting 1 to all these places (instead of boolean true)
    }

    for(int j = 2; j <= number; j++){ 
        if(prime_arr[j-2]){  
            print_number(j); 
            for(int k = j*j; k <= number; k+=j){  // 2p,3p,4p... < number
                prime_arr[k-2] = 0;             // setting them to 0 (boolean false/not prime)
                }          
        }
    }
    free(prime_arr);        //releasing memory(after using malloc)
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}