//Ahlden Brough
//ajbrough
//pa2

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main(){
  printf("starts matrix client main()");
  int n=3;
  Matrix M = newMatrix(n);
  changeEntry(M, 1, 1, 1);
  printMatrix(stdout, M);
  changeEntry(M, 1, 2, 2);
  printMatrix(stdout, M);
  changeEntry(M, 1, 3, 3);
  printMatrix(stdout, M);
  changeEntry(M, 2, 1, 4);
  printMatrix(stdout, M);
  changeEntry(M, 2, 2, 5);
  printMatrix(stdout, M);
  changeEntry(M, 2, 3, 6);
  printMatrix(stdout, M);
  changeEntry(M, 3, 1, 7);
  printMatrix(stdout, M);
  changeEntry(M, 3, 2, 8);
  printMatrix(stdout, M);
  changeEntry(M, 3, 3, 9);
  printMatrix(stdout, M);
  changeEntry(M, 2, 2, 0);
  printMatrix(stdout, M);
  changeEntry(M, 3, 2, 69);
  printMatrix(stdout, M);
  Matrix N = copy(M);
  printMatrix(stdout, N);
  M = transpose(M);
  printMatrix(stdout, M);
  scalarMult(2.0, N);
  printMatrix(stdout, N);
  if(equals(M, N)){
    printf("true\n");
  }
  else{
    printf("false\n");
  }
  Matrix O = copy(M);
  if(equals(M, O)){
    printf("true\n");
  }
  else{
    printf("false\n");
  }
  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);
  changeEntry(A, 1, 1, 1);
  changeEntry(A, 1, 2, 2);
  changeEntry(A, 1, 3, 3);
  //changeEntry(A, 2, 1, 1);
  changeEntry(A, 2, 2, 1);
  //changeEntry(A, 2, 3, 1);
  //changeEntry(A, 3, 1, 1);
  //changeEntry(A, 3, 2, 1);
  //changeEntry(A, 3, 3, 1);
  changeEntry(B, 1, 1, 2);
  changeEntry(B, 1, 2, 4);
  //changeEntry(B, 1, 3, 1);
  changeEntry(B, 2, 1, 1);
  changeEntry(B, 2, 2, 1);
  changeEntry(B, 2, 3, 1);
  changeEntry(B, 3, 1, 3);
  changeEntry(B, 3, 2, 6);
  changeEntry(B, 3, 3, 8);
  Matrix A_B = sum(A, B);
  printMatrix(stdout, A_B);
  Matrix C = newMatrix(n);
  Matrix D = newMatrix(n);
  changeEntry(C, 1, 1, 1);
  changeEntry(C, 1, 2, 1);
  changeEntry(C, 1, 3, 1);
  // changeEntry(C, 2, 1, 1);
  // changeEntry(C, 2, 2, 1);
   changeEntry(C, 2, 3, 1);
  // changeEntry(C, 3, 1, 1);
   changeEntry(C, 3, 2, 1);
  // changeEntry(C, 3, 3, 1);
  changeEntry(D, 1, 1, 1);
  changeEntry(D, 1, 2, 1);
  changeEntry(D, 1, 3, 1);
  changeEntry(D, 2, 1, 1);
  changeEntry(D, 2, 2, 1);
  changeEntry(D, 2, 3, 1);
  changeEntry(D, 3, 1, 1);
  changeEntry(D, 3, 2, 1);
  changeEntry(D, 3, 3, 1);
  Matrix C_D = diff(C, D);
  printMatrix(stdout, C_D);
  Matrix AxB = product(A, B);
  printMatrix(stdout, AxB);
  Matrix AxB_copy = copy(AxB);
  printMatrix(stdout, AxB_copy);
  printf("AxB->NNZ = %d\n", NNZ(AxB));
  printf("AxB_copy->NNZ = %d\n", NNZ(AxB_copy));
  if(equals(AxB, AxB_copy)){
    printf("true\n");
  }
  else{
    printf("false\n");
  }
  if(equals(AxB, C_D)){
    printf("true\n");
  }
  else{
    printf("false\n");
  }
  if(equals(AxB, AxB)){
    printf("true\n");
  }
  else{
    printf("false\n");
  }
  makeZero(AxB);
  printMatrix(stdout, AxB);
  return EXIT_SUCCESS;
}