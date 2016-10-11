all : OV2640_DigitalCamera OV2640_Playback

objects = DefaultFonts_SPI.o EDISONCAM.o

OV2640_Playback : $(objects) EDISONCAM_OV2640_Playback.o
	gcc -o OV2640_Playback $(objects) EDISONCAM_OV2640_Playback.o

OV2640_DigitalCamera : $(objects) EDISONCAM_OV2640_DigitalCamera.o 
	gcc -o OV2640_DigitalCamera $(objects) EDISONCAM_OV2640_DigitalCamera.o

DefaultFonts_SPI.o : DefaultFonts_SPI.c
	gcc -c DefaultFonts_SPI.c
EDISONCAM.o : EDISONCAM.c
	gcc -c EDISONCAM.c
EDISONCAM_OV2640_Playback.o : EDISONCAM_OV2640_Playback.c
	gcc -c EDISONCAM_OV2640_Playback.c
	
EDISONCAM_OV2640_DigitalCamera.o : EDISONCAM_OV2640_DigitalCamera.c
	gcc -c EDISONCAM_OV2640_DigitalCamera.c
	
clean : 
	rm  OV2640_DigitalCamera OV2640_Playback
	rm *.o