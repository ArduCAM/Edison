/*
 ============================================================================
 Name        : EDISONCAM_OV2640_DigitalCamera.c
 Author      : Lee
 Version     : V1.0
 Copyright   : ArduCAM demo (C)2015 Lee
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "EDISONCAM.h"

#define BOOL int
#define TRUE 1
#define FALSE 0
#define OV2640_CHIPID_HIGH 	0x0A
#define OV2640_CHIPID_LOW 	0x0B

void setup()
{
  uint8_t vid,pid;
  uint8_t temp;

  ArduCAM(OV2640);
  printf("ArduCAM Start!\n");

  //Check if the ArduCAM SPI bus is OK
  write_reg(ARDUCHIP_TEST1, 0x55);
  temp = read_reg(ARDUCHIP_TEST1);
  if(temp != 0x55)
  {
  	printf("SPI interface Error! temp Not 0x55\n");
    printf("temp: " + temp);
    printf("\n");
  	while(1);
  }

  //Check if the camera module type is OV2640
  rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
  printf("vid is : %x",vid);
  rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);
  printf("   pid is : %x\n",pid);
  if((vid != 0x26) || (pid != 0x42))
  	printf("Can't find OV2640 module!\n");
  else
  	printf("OV2640 detected\n");

  //Change to BMP capture mode and initialize the OV2640 module
  set_format(JPEG);
  InitCAM();
  OV2640_set_JPEG_size(OV2640_640x480);
  sleep(1);
}

int main(void)
{
	int nmemb = 1;
	setup();
	while(1)
	{
	    
		uint8_t buf[256];
		static int i = 0;
		static int k = 0;
		static int n = 0;
		uint8_t temp,temp_last;
		uint8_t start_capture = 0;
		
    sleep(3);
		start_capture = 1;
		if(start_capture)
		{
			//Flush the FIFO
			flush_fifo();
			//Clear the capture done flag
			clear_fifo_flag();
			//Start capture
			capture();
			printf("Start Capture\n");
		}

	while (!(read_reg(ARDUCHIP_TRIG) & CAP_DONE_MASK));
			printf("Capture Done!\n");
			
			//Construct a file name
			memset(filePath,0,20);
			strcat(filePath,"/home/");
			getnowtime();
			printf("Saving the picture!\n");
			strcat(filePath,nowtime);
			strcat(filePath,".jpg");
			//Open the new file
			fp = fopen(filePath,"w+");
			if (fp == NULL)
			{
				printf("open file failed");
				return 0;

			}
			i = 0;
			temp = read_fifo();
			//Write first image data to buffer
			buf[i++] = temp;
			//Read JPEG data from FIFO
			while( (temp != 0xD9) | (temp_last != 0xFF) )
			{
				temp_last = temp;
				temp = read_fifo();
				//Write image data to buffer if not full
				if(i < 256)
					buf[i++] = temp;
				else
				{
					//Write 256 uint8_ts image data to file
					fwrite(buf,256,nmemb,fp);
					i = 0;
					buf[i++] = temp;
				}
			}
			//Write the remain uint8_ts in the buffer
			if(i > 0)
				fwrite(buf,i,nmemb,fp);
			    

			//Close the file
			fclose(fp);
			printf("Picture save OK !\n");
			//Clear the capture done flag
			clear_fifo_flag();
			//Clear the start capture flag
			start_capture = 0;

	}
}
