#include "adcDevice.h"

int fd;
int cmd = 0x84;

int init(int addr){
    wiringPiSetup();
    
    fd = wiringPiI2CSetup(addr);   
    if (fd < 0){		
	printf("Error address : 0x%x \n",addr);
	return 0;
    } 
    else{	
        if(wiringPiI2CWrite(fd,0) < 0){
            printf("No device found in address 0x%x \n",addr);
            return 0;
        }
        else{
            printf("Device found in address 0x%x \n",addr);
            return 1;
        }
    }
}

int analogRead(int chn){
    wiringPiI2CWrite(fd, cmd|(((chn<<2 | chn>>1)&0x07)<<4));
    return wiringPiI2CRead(fd);
}
