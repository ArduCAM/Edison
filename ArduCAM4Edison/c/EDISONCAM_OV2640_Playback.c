/*
 ============================================================================
 Name        : EDISONCAM_OV2640_Playback.c
 Author      : Lee
 Version     : V1.0
 Copyright   : ArduCAM demo (C)2015 Lee
 Description :
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "EDISONCAM.h"

#define BOOL int
#define TRUE 1
#define FALSE 0
#define BMPIMAGEOFFSET 66

const char bmp_header[BMPIMAGEOFFSET] PROGMEM =
{
  0x42, 0x4D, 0x36, 0x58, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x28, 0x00,
  0x00, 0x00, 0x40, 0x01, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x03, 0x00,
  0x00, 0x00, 0x00, 0x58, 0x02, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x1F, 0x00,
  0x00, 0x00
};

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
  	printf("SPI interface Error!\n");
  	while(1);
  }
  InitCAM();
}

int main()
{
  setup();
  unsigned long previous_time = 0;
  static int k = 0;
  uint8_t temp;
  struct timeval tv;
  struct timezone tz;
  write_reg(ARDUCHIP_MODE, 0x00);		 	//Switch to CAM
  while(1)
  {
    sleep(3);
    gettimeofday (&tv , &tz);  
	  memset(filePath,0,28);
	  strcat(filePath,"/home/");
	  getnowtime();
	  strcat(filePath,nowtime);
	  strcat(filePath,".bmp");
	  //Open the new file
	  fp = fopen(filePath,"w+");
	  if (fp == NULL)
	   {
		   printf("open file failed\n");
		   return 0;
	   }				//Generate file name
    write_reg(ARDUCHIP_MODE, 0x00);    	//Switch to MCU, freeze the screen
    GrabImage(filePath);  
  }
}
int GrabImage(char* str)
{
  char VH,VL;
  uint8_t temp;
  uint8_t buf[256];
  static int k = 0;
  int i,j = 0;
  int nmemb = 1;
  printf("GrabImage.\n");

  //Open the new file
  fp = fopen(str,"w+");
  if (fp == NULL)
  {
	  printf("open file failed\n");
	  return 0;
  }
  //Switch to FIFO Mode
  write_reg(ARDUCHIP_TIM, MODE_MASK);
  //Flush the FIFO
  flush_fifo();
  //Start capture
  capture();
  printf("Start Capture\n");

  //Polling the capture done flag
  while(!(read_reg(ARDUCHIP_TRIG) & CAP_DONE_MASK));
  printf("Capture Done!\n");
  printf("Saving the picture!\n");
  k = 0;
  //Write the BMP header
  for( i = 0; i < BMPIMAGEOFFSET; i++)
  {
    char ch = pgm_read_byte(&bmp_header[i]);
    buf[k++] = ch;
  }
  fwrite(buf,k,nmemb,fp);
  //Read first dummy byte
  //read_fifo();

  k = 0;
  //Read 320x240x2 byte from FIFO
  //Save as RGB565 bmp format
  for(i = 0; i < 240; i++)
    for(j = 0; j < 320; j++)
  {
      VH = read_fifo();
      VL = read_fifo();
      buf[k++] = VL;
      buf[k++] = VH;
      //Write image data to bufer if not full
      if(k >= 256)
      {
        //Write 256 bytes image data to file from buffer
        fwrite(buf,256,nmemb,fp);
        k = 0;
      }
  }
  //Close the file
  fclose(fp);
  printf("Picture save OK.\n");
  //Clear the capture done flag
  clear_fifo_flag();

  //Switch to LCD Mode
  write_reg(ARDUCHIP_TIM, 0);
  return 1;
}