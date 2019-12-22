//Ahlden Brough
//ajbrough
//pa2

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Matrix.h"
#include"List.h"

typedef struct EntryObj{
  int column;
  double value;
} EntryObj;

typedef EntryObj* Entry;

typedef struct MatrixObj{
  int size;
  int NNZ;
  List* rows;
}MatrixObj;

// newEntry()
// Returns reference to new Entry object. Initializes column and value fields.
// Private.
Entry newEntry(int column, double value){
  Entry E = malloc(sizeof(EntryObj));
  E->column = column;
  E->value = value;
  return E;
}

// freeEntry()
// Frees heap memory pointed to by *pE, sets *pE to NULL.
// Private.
void freeEntry(Entry* pE){
  if( pE!=NULL && *pE!=NULL ){
    free(*pE);
  	*pE = NULL;
	}
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state. Matrix newMatrix(int n)
Matrix newMatrix(int n){
  //printf("starts newMatrix\n");
  Matrix M;
  M = malloc(sizeof(MatrixObj)); // need to malloc space for the lists also
  M->NNZ = 0;
  M->size = n;
  M->rows = calloc(n, sizeof(List));
  for(int i = 0; i < n; i++){
    M->rows[i] = newList();
  }
  return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
  if(pM!=NULL && *pM!=NULL){
  	makeZero(*pM);
    //printf("----------gets past make zero---------\n");
    for(int row = 0; row < size(*pM); row++){
      //printf("pre if row = %d\n", row);
      if(length((*pM)->rows[row]) != 0){
        //printf("before print list");
        freeList(&(*pM)->rows[row]);
        //printf("frees list %d\n", row);
      }
    }
  	free((*pM)->rows);
    (*pM)->rows = NULL;
    (*pM)->size = 0;
    free(*pM);
  	*pM = NULL;
    //printf("----------completed---------\n");
  }
}

// Access functions

// size()
// Return the size of square Matrix M.
int size(Matrix M){
  if(M == NULL){
	printf("Matrix Error: calling size() on NULL Matrix reference\n");
	exit(EXIT_FAILURE);
  }
  return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
  if(M == NULL){
	printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
	exit(EXIT_FAILURE);
  }
  return M->NNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise. 
int equals(Matrix A, Matrix B){
  if( A==NULL || B==NULL ){
    printf("Matrix Error: calling equals() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if(A == B){
     //printf("edge 1\n");
     return 1;
  }
  if(A->NNZ != B->NNZ){
    //printf("edge 2\n");
    return 0;
  }
  if(size(A) != size(B)){
    //printf("edge 3\n");
    return 0;
  }
  for(int z = 0; z < size(A); z++){
    //printf("z = %d\n", z);
    if(length(A->rows[z]) == length(B->rows[z]) && (length(A->rows[z]) != 0) && (length(B->rows[z]) != 0) ){
      //printf("length was the same\n");
      moveFront(A->rows[z]);
      moveFront(B->rows[z]);
      while(index(A->rows[z]) > -1 && index(B->rows[z]) > -1 ){  
        Entry a = get(A->rows[z]);
        Entry b = get(B->rows[z]);
        if(a->column != b->column && a->value != b->value){
          //printf("index %0.1f !=  index %0.1f\n", (a->value), (b->value));
          return 0;
        }
        //printf("moves next\n");
        moveNext(A->rows[z]);
        moveNext(B->rows[z]);
      }
    }
    else if(length(A->rows[z]) == length(B->rows[z]) && (length(A->rows[z]) == 0)){
      continue;
    }
  }
  return 1;
}

// Manipulation procedures

// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M){
  for(int row = 0; row < size(M); row++){
    //printf("makeZero row = %d\n", row + 1);
    if(length(M->rows[row]) != 0){
      while(index(M->rows[row]) != -1){
        Entry E = (Entry)get(M->rows[row]);
        changeEntry(M, row, E->column, 0);
        //printf("deletes (%d, %d)\n", row + 1, col + 1);

      }
      clear(M->rows[row]);
    }
  }
  M->NNZ = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
	if(M == NULL){
	  printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
	  exit(EXIT_FAILURE);
	}
	if(i > size(M)){
	  printf("Matrix Error: invalid row\n");
	  exit(EXIT_FAILURE);
	}
	if(j > size(M)){
	  printf("Matrix Error: invalid column\n");
	  exit(EXIT_FAILURE);
	}

  //case 1: Mij == 0 and x == 0 inserting 0 and no entry exists (do nothing)
  //case 2: Mij != 0 and x == 0 inserting 0 and entry exists (delete entry)
  //case 3: Mij == 0 and x != 0 inserting non zero and entry does not exist (new entry)
  //case 4: Mij != 0 and x != 0 inserting non zero and entry exists (modify entry)
  //printf("starts changeEntry\n");
  Entry E = newEntry(j, x);
  int Mij = 0;
  if(length(M->rows[i-1]) == 0 && x != 0){
    append(M->rows[i-1], E);
    M->NNZ++;
    return;
  }
  //finding if entry exists and if so where
  if(length(M->rows[i-1]) > 0){
    moveFront(M->rows[i-1]);
  }
  while(index(M->rows[i-1]) > -1){
    Entry current = (Entry)get(M->rows[i-1]);
    if(current->column == j){
      Mij = 1;
      break;
    }
    moveNext(M->rows[i-1]);
  }
  //case 3
  if(Mij == 0 && x != 0){
    //printf("case 3\n");
    moveFront(M->rows[i-1]);
    Entry current = (Entry)get(M->rows[i-1]);
    while(1){
      if( (current->column < j) && (get(M->rows[i-1]) != back(M->rows[i-1])) ){
          moveNext(M->rows[i-1]);
          current = (Entry)get(M->rows[i-1]);
        }
      else if( (current->column < j) && (get(M->rows[i-1]) == back(M->rows[i-1])) ){
          append(M->rows[i-1], E);
          M->NNZ++;
          break;
        }
      else{
        insertBefore(M->rows[i-1], E);
        M->NNZ++;
        break;
      }
    }
    return;
  }
  //case 2
  else if(Mij != 0 && x == 0){
    //printf("case 2\n");
    Entry current = (Entry)get(M->rows[i-1]);
    //freeEntry(&current);
    delete(M->rows[i-1]);
    //current = NULL;
    M->NNZ--;
    return;
  }
  // case 4
  else if(Mij != 0 && x != 0){
    //printf("case 4\n");
    Entry current = (Entry)get(M->rows[i-1]);
    current->value = x;
    return;
  }
}

// Matrix Arithmetic operations

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){ // modify this please 
  //printf("starts copy\n");
  Matrix N = newMatrix(size(A));
  for(int q = 0; q < size(A); q++){
    if(length(A->rows[q]) != 0){
      moveFront(A->rows[q]);
    }
    while(index(A->rows[q]) > -1){  
      Entry E = get(A->rows[q]);
      Entry B = newEntry(E->column, E->value); 
      append(N->rows[q], B);
      N->NNZ++;
      if(NNZ(A) == NNZ(N)){ //if matrices have the same number of NNZ
        return N;
      }
      moveNext(A->rows[q]);
    }
  }
  return N;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose of A.
Matrix transpose(Matrix A){
  //printf("starts transpose\n");
  Matrix N = newMatrix(A->size);
  int old_column;
  for(int q = 0; q < size(A); q++){
    if(length(A->rows[q]) != 0){
      moveFront(A->rows[q]);
    }
    while(index(A->rows[q]) > -1){  
      Entry E = get(A->rows[q]);
      old_column = E->column;
      append(N->rows[old_column - 1], newEntry(q + 1, E->value));
      N->NNZ++;
      if(NNZ(A) == NNZ(N)){ //if matrices have the same number of NNZ
        return N;
      }
      moveNext(A->rows[q]);
    }
  }
  return N;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
  //printf("starts scalarMult\n");
  Matrix N = newMatrix(size(A));
  for(int q = 0; q < size(A); q++){
    if(length(A->rows[q]) > 0){
      moveFront(A->rows[q]);
    }
    while(index(A->rows[q]) > -1){
      Entry E = get(A->rows[q]);
      Entry new_E = newEntry(E->column, E->value);
      new_E->value = new_E->value * x;
      append(N->rows[q], new_E);
      N->NNZ++;
      if(NNZ(A) == NNZ(N)){ //if matrices have the same number of NNZ
        return N;
      }
      moveNext(A->rows[q]);
    }
  }
  return N;
}

List helpRow(List P, List Q, int add_or_sub, Matrix M){
  List N = newList();
  if(P==Q){
    return N;
  }
  if(length(P) > 0){
    moveFront(P);
  }
  if(length(Q) > 0){
    moveFront(Q);
  }
  while(index(P) > -1 && index(Q) > -1){
    //printf("first while loop\n");
    Entry current_P = (Entry)get(P);
    Entry current_Q = (Entry)get(Q);
    //printf("(%d, %0.1f), (%d, %0.1f)\n", current_P->column, current_P->value, current_Q->column, current_Q->value);
    
    if(current_P->column == current_Q->column){
      //printf("(%d, %0.1f), (%d, %0.1f)\n", current_P->column, current_P->value, current_Q->column, current_Q->value);
      if( (current_P->value + (add_or_sub * current_Q->value)) == 0){
        //printf("condtion where adds to zero\n");
        //printf("(%d, %0.1f) + %d * (%d, %0.1f)\n", current_P->column, current_P->value, add_or_sub, current_Q->column, current_Q->value);
        moveNext(P);
        //printf("moves next P\n");
        if(P != Q){
          moveNext(Q);
          //printf("moves next Q\n");
        }
        //printf("~~~~~~~~~~~~~~~~~~if statement over~~~~~~~~~~~~~~~~~~\n");
        continue;
      }
      append(N, newEntry(current_P->column, current_P->value + (add_or_sub * current_Q->value)));
      M->NNZ++;
      //printf("(%d, %0.1f) + %d * (%d, %0.1f)\n", current_P->column, current_P->value, add_or_sub, current_Q->column, current_Q->value);
      //printf("appends (%d, %0.1f)\n", current_P->column, current_P->value + (add_or_sub * current_Q->value));
      moveNext(P);
      moveNext(Q);
    }

    else if(current_P->column < current_Q->column){
      append(N, newEntry(current_P->column, current_P->value));
      M->NNZ++;
      //printf("(%d, %0.1f) + %d * (%d, %0.1f)\n", current_P->column, current_P->value, add_or_sub, current_Q->column, current_Q->value);
      //printf("appends (%d, %0.1f)\n", current_P->column, current_P->value);
      moveNext(P);
    }
    else if(current_P->column > current_Q->column){
      append(N, newEntry(current_Q->column, current_Q->value * add_or_sub));
      M->NNZ++;
      //printf("(%d, %0.1f) + %d * (%d, %0.1f)\n", current_P->column, current_P->value, add_or_sub, current_Q->column, current_Q->value);
      //printf("appends (%d, %0.1f)\n", current_Q->column, current_Q->value * add_or_sub);
      moveNext(Q);
    }
    //printf("-------------------------------------\n");
  }
  if(index(P) == -1 && index(Q) != -1){
    while(index(Q) > -1){
      //printf("second while loop\n");
      Entry current_Q = (Entry)get(Q);
      append(N, newEntry(current_Q->column, current_Q->value * add_or_sub));
      M->NNZ++;
      //printf("(%d, %0.1f)\n", current_Q->column, current_Q->value);
      //printf("appends (%d, %0.1f)\n", current_Q->column, current_Q->value * add_or_sub);
      moveNext(Q);
    }
  }
  else if(index(Q) == -1 && index(P) != -1){
    while(index(P) > -1){
      //printf("third while loop\n");
      Entry current_P = (Entry)get(P);
      append(N, newEntry(current_P->column, current_P->value));
      M->NNZ++;
      //printf("(%d, %0.1f)\n", current_P->column, current_P->value);
      //printf("appends (%d, %0.1f)\n", current_P->column, current_P->value);
      moveNext(P);
    }
  }
  return N;
}

// sum()
// Returns a reference to a new matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
  if(size(A) != size(B)){
    printf("Matrix Error: calling sum() on different size matrices\n");
      exit(EXIT_FAILURE);
  }
  if(A == B){
    return scalarMult(2.0, A);
  }
  Matrix N = newMatrix(size(A));
  for(int row = 0; row < size(A); row++){
    N->rows[row] = helpRow(A->rows[row], B->rows[row], 1, N);
  }
  return N;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
  if(size(A) != size(B)){
    printf("Matrix Error: calling diff() on different size matrices\n");
      exit(EXIT_FAILURE);
  }
  Matrix N = newMatrix(size(A));
  for(int row = 0; row < size(A); row++){
    //printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
    //printf("row %d\n", row + 1);
    //printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
    N->rows[row] = helpRow(A->rows[row], B->rows[row], -1, N);
  }
  return N;
}


double vectorDot(List P, List Q){
  //printf("starts vectorDot\n");
  if(length(P) > 0){
    moveFront(P);
  }
  if(length(Q) > 0){
    moveFront(Q);
  }
  double sum = 0;
  while(index(P) > -1 && index(Q) > -1){
    //printf("enters while\n");
    Entry current_P = (Entry)get(P);
    Entry current_Q = (Entry)get(Q);
    if(current_P->column == current_Q->column){
      //printf("first if\n");
      sum = sum + (current_P->value * current_Q->value);
      moveNext(P);
      moveNext(Q);
    }
    else if(current_P->column < current_Q->column){
      //printf("second if\n");
      moveNext(P);
    }
    else if(current_P->column > current_Q->column){
      //printf("third if\n");
      moveNext(Q);
    }
  }
  //printf("exits vectorDot\n");
  return sum;
}


// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
  if(size(A) != size(B)){
    printf("Matrix Error: calling product() on different size matrices\n");
      exit(EXIT_FAILURE);
  }
  Matrix transposed = transpose(B);
  Matrix N = newMatrix(size(A));
  for(int row = 0; row < size(A); row++){
    if(length(A->rows[row]) != 0){
      for(int col = 0; col < size(A); col++){
        changeEntry(N, row + 1, col + 1, vectorDot(A->rows[row], transposed->rows[col]));
      }
    } 
  }
  freeMatrix(&transposed);
  transposed = NULL;
  return N;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows 
// are not printed. Each non-zero is represented as one line consisting 
// of the row number, followed by a colon, a space, then a space separated 
// list of pairs "(col, val)" giving the column numbers and non-zero values 
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
  //printf("starts printMatrix\n");
  for(int p = 0; p < size(M); p++){
  	if(length(M->rows[p]) == 0){
  	  //printf("length of row was 0\n");
      continue;
  	}
  	moveFront(M->rows[p]);
  	fprintf(out, "%d: ", p + 1);
  	while(index(M->rows[p]) > -1){
      Entry print = (Entry)get(M->rows[p]);
  	  if(index(M->rows[p]) == length(M->rows[p]) - 1){
  		  fprintf(out, "(%d, %0.1f)\n", print->column, print->value);
  		  break;
  	  }
  	  fprintf(out, "(%d, %0.1f) ", print->column, print->value);
      moveNext(M->rows[p]);
  	}
  }
}
