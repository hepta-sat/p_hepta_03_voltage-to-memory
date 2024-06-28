#include "mbed.h"
#include "HEPTA_CDH.h"
#include "HEPTA_EPS.h"

RawSerial pc(USBTX,USBRX,9600);
HEPTA_CDH cdh(p5, p6, p7, p8, "sd");
HEPTA_EPS eps(p16,p26);
Timer sattime;
 
int main(){
    sattime.start();
    float bt;
    char str[100];
    mkdir("/sd/mydir", 0777);

    FILE *fp = fopen("/sd/mydir/test.txt","w");
    if(fp == NULL) {error("Could not open file for write\r\n");}
    pc.printf("Hello world!\r\n");
    for(int i = 0; i < 10; i++) {
        eps.vol(&bt);
        fprintf(fp, "Time = %.2f [s] Vol = %.2f [V]\r\n", sattime.read(),bt);
        wait(0.1);  
    }
    fclose(fp);

    fp = fopen("/sd/mydir/test.txt","r");
    for(int j = 0; j < 10; j++) {
        fgets(str,100,fp);
        pc.puts(str);
    }
    fclose(fp);
    pc.printf("Goodbye!!\r\n");
}
