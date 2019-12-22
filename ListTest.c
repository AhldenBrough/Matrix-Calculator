//Ahlden Brough
//ajbrough
//pa2

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
	List A = newList();
	List B = newList();
	int i;

   	for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   	}

   	printf("length(A) = %d\n", length(A));
   	printf("length(B) = %d\n", length(B));
   	printf("front(A) = %d\n", front(A));
   	printf("front(B) = %d\n", front(B));
   	moveFront(A);
   	moveFront(B);
   	moveNext(A);
   	moveNext(B);
   	printf("get(A) = %d\n", get(A));
   	printf("get(B) = %d\n", get(B));
   	moveBack(A);
   	moveBack(B);
   	printf("get(A) = %d\n", get(A));
   	printf("get(B) = %d\n", get(B));
   	insertBefore(A, 100);
   	insertAfter(B, 100);
   	deleteFront(A);
   	deleteFront(B);
   	deleteBack(A);
   	deleteBack(A);
   	printf("length(A) = %d\n", length(A));
   	printf("length(B) = %d\n", length(B));\
   	printf("front(A) = %d\n", front(A));
   	printf("front(B) = %d\n", front(B));
   	printf("back(A) = %d\n", back(A));
   	printf("back(B) = %d\n", back(B));

	return(0);
}