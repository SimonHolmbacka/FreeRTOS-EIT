#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <string.h>
#include <FreeRTOS.h>
#include "queue.h"
#include "rsa.h"
#include "Canny/canny.h"

#define START 0
#define COUNT 600
#define SIZE 64642


int chunksize;
long int p, q, n, t, flag, j, i;
char * msg;

long int * en;
long int * m;
long int * temp;
long int * e;
long int *d;
char * msg; 

int prime(long int); 
void ce(); 
long int cd(long int); 
void encrypt(); 
void decrypt(); 
int counter = 0;

void encryptmain(cannyMessage * can) {
	//printf("MAIN: Chunksize %d\n", chunksize);
    p = 199;
    q = 191;
	
	for (i = 0; can->value[i] == 0 || can->value[i] == 255; i++) {
		counter++;
	}
	ebuf = (char *)malloc(sizeof(char *) * counter);
	//printf("Counter %d\n", counter);

	m = (long int *)malloc(sizeof(long int) * counter);
	temp = (long int *)malloc(sizeof(long int) * counter);
	en = (long int *)malloc(sizeof(long int) * counter);
	e = (long int *)malloc(sizeof(long int) * counter);
	d = (long int *)malloc(sizeof(long int) * counter);
	msg = (char *)malloc(sizeof(char) * counter);

	//msg = (char *)malloc(sizeof(char) * counter);
	//printf("\nHere is the canny message\n");
	for (i = START; i < COUNT; i++) {
		//printf("%c ", (char)can->value[i]+'0');
		msg[i] = (char)can->value[i]+'0';
	}
    for(i=0;msg[i]!=NULL;i++) 
        m[i]=msg[i]; 
    n=p*q; 
    t=(p-1)*(q-1); 
    ce(); 

    encrypt();
	free(m);
	free(temp);
	free(en);
	free(e);
	free(d);
	free(msg);
#if 0
	printf("\nHere is the encrypted message after return as char\n");
	for (i = START; i < COUNT; i++) {
		printf("%c ", en[i]);
	}
#endif
    //decrypt(); 
} 
    
int prime(long int pr) { 
    int i; 
    j=sqrt(pr); 
    for(i=2;i<=j;i++) { 
        if(pr%i==0) 
        return 0; 
    } 
    return 1; 
} 
void ce() { 
    int k; 
    k=0; 
    for(i=2;i<t;i++) { 
        if(t%i==0) 
            continue; 
        flag=prime(i); 
    if(flag==1&&i!=p&&i!=q){ 
        e[k]=i; 
        flag=cd(e[k]); 
        if(flag>0) 
        { 
            d[k]=flag; 
            k++; 
        } 
        if(k==99) 
            break; 
        } 
    } 
} 
long int cd(long int x) { 
    long int k=1; 
    while(1) { 
        k=k+t; 
        if(k%x==0) 
            return(k/x); 
    } 
} 
void encrypt() { 
    long int pt,ct,key=e[0],k,len; 
    i=0; 
    //len=strlen(msg); 
	len = SIZE;
	printf("Len %d\n", len);
    while(i!=len) { 
        pt=m[i]; 
        pt=pt-96; 
        k=1; 
        for(j=0;j<key;j++)  { 
            k=k*pt; 
            k=k%n; 
        } 
        temp[i]=k; 
        ct=k+96; 
        en[i]=ct; 
        i++; 
    } 
    en[i]=-1; 

#if 0
    printf("\nTHE ENCRYPTED MESSAGE IS\n"); 
    for(i=0;en[i]!=-1;i++) 
        printf("%c",en[i]); 
#endif

	
	for (i = 0; i < counter; i++)
		ebuf[i] = en[i];
		
} 
#if 0
void decrypt() { 
    long int pt,ct,key=d[0],k; 
    i=0; 
    while(en[i]!=-1) { 
        ct=temp[i]; 
        k=1; 
        for(j=0;j<key;j++)  { 
            k=k*ct; 
            k=k%n; 
        } 
        pt=k+96; 
        m[i]=pt; 
        i++; 
    } 
    m[i]=-1; 
    printf("\nTHE DECRYPTED MESSAGE IS\n"); 
    for(i=0;m[i]!=-1;i++) 
        printf("%c",m[i]); 
}
#endif