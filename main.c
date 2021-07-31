#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "routing.c"
#define M 9
#define N 150

int main(){ 
  
    FILE *fin, *fout, *fp; //fin -> input....fout -> output.....fp->routing table file

    char buf[M][N] = { { 0 } }; 
    char net[M][N] = { { 0 } }; 
    char mask[M][N] = { { 0 } }; 
    char gateway[M][N] = { { 0 } }; 
    char port[M][N] = { { 0 } }; 
  
  
    fin = fopen("input.txt", "r"); 
    fout = fopen("output.txt", "w"); 
    fp = fopen("routing.txt", "r"); 

  
    // If any of the file is not present then it will give an error. 
    if (fp == NULL || fin == NULL || fout == NULL) {  
        printf("Error"); 
        return 0; 
    } 

    //Initialization of node pointer Head
    init();
    printf("\nDATA INITIALIZED SUCCESSFULLY\n");

    // File to buf array and then to other arrays
    insertInArray(fp, buf, net, mask, gateway, port); 
    printf("\nDATA INSERTED INTO ARRAYS SUCCESSFULLY\n");

    //Links arrays to each other by nodes
    createTable(buf, net, mask, gateway, port) ;
    printf("\nTABLE CREATED SUCCESSFULLY\n");

    //Finds the gateway and port address and stores into "output.txt"
    Routing(fin, fout);
    printf("\nDESTINATION ADDRESS FOUND SUCCESSFULLY !!!\n");


    fclose(fin); 
    fclose(fp); 
    fclose(fout); 
  
    return 0; 
} 


//gcc main.c -lwsock32


/*
128.75.43.0, 255.255.255.0, 192.13.2.55, Eth0
128.75.43.0, 255.255.255.128, 192.13.2.55, Eth1
192.12.17.5, 255.255.255.255, 192.13.2.55, Eth3
200.200.16.0, 255.255.248.0, 192.13.2.55, eth4
200.200.200.0, 255.255.248.0, 192.13.2.55, eth4
0.0.0.0, 0.0.0.0, 12.23.44.1, eth9
20.128.0.0, 255.128.0.0, 12.1.1.1, eth1
20.0.0.0, 255.0.0.0, 12.1.1.1, eth2
20.0.0.0, 255.128.0.0, 12.1.1.1, eth3

input
192.12.17.10   =   192.13.2.55 Eth3
128.75.43.16   =   192.13.2.55 Eth1
201.2.2.2 	   =   12.23.44.1 eth9
20.129.0.1     =   12.1.1.1 eth1

*/







/*
inet_addr
The inet_addr function interprets the character string specified by the cp parameter. This string represents a numeric Internet address expressed in the Internet standard ".'' notation. The value returned is a number suitable for use as an Internet address
*/

/*
inet_ntoa
The function inet_ntoa() converts a network address in a struct in_addr to a dots-and-numbers format string. 
*/
