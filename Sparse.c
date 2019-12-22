//Ahlden Brough
//ajbrough
//pa2

#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"

int main(int argc, char * argv[]){
	printf("Starts");
   int n = 0;
   int a = 0;
   int b = 0;
   int i;
   int j;
   double v;
   FILE *in, *out;
    // check command line for correct number of arguments
    if( argc != 3 ){
      printf("Usage: Sparse <input file> <output file>\n");
      exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
    }
    if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
    }

    fscanf(in, "%d %d %d", &n, &a, &b);
    printf("scans first line");
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    Matrix C, D, E, F, G, H, I, J;

    for(int z = 0; z < a; z++){
    	fscanf(in, "%d %d %lf", &i, &j, &v);
    	changeEntry(A, i, j, v);
    	printf("scans 1");
    }

    for(int z = 0; z < b; z++){
    	fscanf(in, "%d %d %lf", &i, &j, &v);
    	changeEntry(B, i, j, v);
    	printf("scans 2");
    }
    
    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");

    D = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, D);
    fprintf(out, "\n");

    E = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, E);
    fprintf(out, "\n");

    F = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, F);
    fprintf(out, "\n");

    G = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, G);
    fprintf(out, "\n");
 
    H = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, H);
    fprintf(out, "\n");

    I = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, I);
    fprintf(out, "\n");

    J = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, J);

    /* close files */
    fclose(in);
    fclose(out);

 	//free matrices
 	freeMatrix(&A);
 	freeMatrix(&B);
 	freeMatrix(&C);
 	freeMatrix(&D);
 	freeMatrix(&E);
 	freeMatrix(&F);
 	freeMatrix(&G);
 	freeMatrix(&H);
 	freeMatrix(&I);
 	freeMatrix(&J);

    return(0);
}