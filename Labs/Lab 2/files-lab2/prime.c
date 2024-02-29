/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n){

  int flag = 1;
  int m = n/2;
  if(n == 0 || n == 1){
    flag = 0;
  }

  for(int i = 2; i <= m; i++){
    if( n % i == 0){
      flag = 0;
    }
  }
  return flag;
}

int main(void){
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
