#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "routing.h"
#include <winsock2.h>

#define M 9  //Rows
#define N 150  //characters


void init(){
    // limit is M as there are M rows in txt file
    for (int i = 0; i < M; i++) { 
        // Initialize head of each LL with NULL. 
        head[i] = NULL; 
    }
    return ; 
}



void insertInArray(FILE* fp, char buf[M][N], char net[M][N],char mask[M][N], char gateway[M][N], char port[M][N]) { 
  
    char line[200]; 
    int c, i = 0, j, k = 0, m = 0; 

    // entire row from the routing table is stored in buf array
    // printf("beforewhile\n");
    while (fgets(line, sizeof(line), fp) != NULL) { 
        j = 0; 
        for (int l = 0; l < strlen(line); l++) { 
            buf[i][j] = line[l]; 
            j++; 
        } 
        i++; 
    } 
    // printf("afterwhile\n");

    // In the routing txt file ....the first column is of network IP address ->Subnet Mass -> Gateway’s IP Address -> Interface Name....and total rows are M	
    for (i = 0; i < M; i++) { 
        k = 0; 
        // Network ip
        for (j = 0; buf[i][j] != ','; j++) { 
            net[i][k] = buf[i][j]; 
            k++; 
        } 
        m = j + 2; 
        k = 0; 
	//Subnet Mask
        for (j = m; buf[i][j] != ','; j++) { 
            mask[i][k] = buf[i][j]; 
            k++; 
        } 
        m = j + 2; 
        k = 0; 
	//Gateway ip
        for (j = m; buf[i][j] != ','; j++) { 
            gateway[i][k] = buf[i][j]; 
            k++; 
        } 
        m = j + 2; 
        k = 0; 
	//Interface name
        for (j = m; buf[i][j] != '\0'; j++) { 
            port[i][k] = buf[i][j]; 
            k++; 
        } 
    }
    // printf("afterfor\n"); 
}



  
// Routing table is formed.....in which every head will have all four columns linked by LL
void createTable( char buf[M][N], char net[M][N], char mask[M][N], char gateway[M][N], char port[M][N]){ 

    char *temp1, *temp2, *temp3, *temp4; 
    struct node* nn; 

    for (int i = 0; i < M; i++) { 
        for (int j = 0; j < 4; j++) { 
  
            // If head is null then first create new node and store network id into it. 
            if (head[i] == NULL) { 
  
                nn = (struct node*)malloc(sizeof(struct node)); 
                nn->data = net[i]; 
                nn->next = NULL; 
                head[i] = nn; 
            } 
  
            // If head is not null and value of j is 1 then create new node which is pointed by head and it will contain subnet mask 
            else if (j == 1) { 
  
                nn->next = (struct node*)malloc(sizeof(struct node)); 
                nn = nn->next; 
                nn->data = mask[i]; 
                nn->next = NULL; 
            } 
  
	    // gateway ip 
            else if (j == 2) { 
  
                nn->next = (struct node*)malloc(sizeof(struct node)); 
                nn= nn->next; 
                nn->data = gateway[i]; 
                nn->next = NULL;
            } 
  
	    //Port	 
            else if (j == 3) { 
                nn->next = (struct node*)malloc(sizeof(struct node)); 
                nn = nn->next; 
                nn->data = port[i]; 
                nn->next = NULL;
            } 
        } 
    } 

    //Bubble sort
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M-i; j++) {
  
            // Longest prefix has been compared by using inet_addr() system call which gives decimal value of an ip address.
            if (inet_addr(head[i]->next->data) < inet_addr(head[j]->next->data)) { 
                struct node* temp = head[i];
                head[i] = head[j];
                head[j] = temp;
            }
        }
    }
    return;
}




//returns index of array having the maximum value
int Max_Value(int ar[]){
	int max =0;
	int j=0;
	for(int i=0; i<M;i++){
		if(max<ar[i]){
			max = ar[i];
			j=i;
		}
	}
	return j;
}

//Matching of result with Network address and Finding Longest Prefix match
void Routing(FILE* fp1, FILE* fp2){
  
    char str[100];
    struct in_addr addr;
    unsigned int val;
    fprintf(fp2, "%c", ' ');
    int count;
    int prefix[M] = {0};
    
    while (fgets(str, sizeof(str), fp1)) {
  
        for (int i = 0; i < M; i++) {
            val = inet_addr(str) & inet_addr(head[i]->next->data);
            addr.s_addr = val;
            char* str1 = inet_ntoa(addr);
            char* str2 = head[i]->data;

            count = 0;
            // count is maintained to find longest prefix match
            for (int i = 0; str1[i] != '\0'; i++) {
  
                if (str1[i] == str2[i]) {
                    count++;
                }
            }
            prefix[i] = count;
            
        }
        //int value of LFM head ptr is returned
        int max = Max_Value(prefix);

		struct node* ptr = head[max]->next;
		struct node* temp = ptr->next; // to get gateway IP address
		while (temp != NULL) {
			// printf("hell6\n");
            //storing into file
			fprintf(fp2, "%s ", temp->data);
			temp = temp->next;
		}
    }
    return;
}