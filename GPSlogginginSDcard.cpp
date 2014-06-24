#include "mbed.h"
#include "GPS.h"
#include "SDFileSystem.h"

SDFileSystem sd(p11, p12, p13, p19, "sd"); // the pinout on the mbed Cool Components workshop board

Serial pc(USBTX, USBRX);
GPS gps(NC, p14);
Timer t;
int main() 
{
    t.start();
    mkdir("sd/mydir",0777);
    FILE *fp = fopen("/sd/mydir/sdgps.txt", "w");// fopen function writes sice W is written and returns the FILE pointer object. 
    if(fp == NULL) 
    {error("Could not open file for write\n");}
    fprintf(fp, "Lat \t \t Long \t speed \t course \t Time \n" );
    fclose(fp);
    while(1)
     {        
        if(gps.sample())
        
         {  
         FILE *fp = fopen("/sd/mydir/sdgps.txt", "a");        
         fprintf(fp, "\n %f \t %f \t %f \t %f \t %f \n", gps.lon, gps.lat, gps.speedgnd, gps.course, t.read());           
         pc.printf(" %f \t %f \t %f \t %f \t %f \n", gps.lon, gps.lat, gps.speedgnd, gps.course, t.read());
         fclose(fp); 
        } 
        
        else
        {
        pc.printf("No Lock");
        }
     }
    
}
