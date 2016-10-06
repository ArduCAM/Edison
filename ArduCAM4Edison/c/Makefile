all : OV2640_DigitalCamera

objects = DefaultFonts_SPI.o BBBCAM.o

OV2640_Playback : $(objects) BBBCAM_OV2640_Playback.o
	gcc -o OV2640_Playback $(objects) BBBCAM_OV2640_Playback.o

OV2640_DigitalCamera : $(objects) BBBCAM_OV2640_DigitalCamera.o 
	gcc -o OV2640_DigitalCamera $(objects) BBBCAM_OV2640_DigitalCamera.o

DefaultFonts_SPI.o : DefaultFonts_SPI.c
	gcc -c DefaultFonts_SPI.c
BBBCAM.o : BBBCAM.c
	gcc -c BBBCAM.c
BBBCAM_OV2640_Playback.o : BBBCAM_OV2640_Playback.c
	gcc -c BBBCAM_OV2640_Playback.c
	
BBBCAM_OV2640_DigitalCamera.o : BBBCAM_OV2640_DigitalCamera.c
	gcc -c BBBCAM_OV2640_DigitalCamera.c
	
clean : 
	rm  OV2640_DigitalCamera
	rm *.o