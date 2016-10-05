all :  ov2640_capture ov2640_4cams_capture ov5642_capture ov5642_4cams_capture

objects = arducam.o arducam_arch_edison.o


ov2640_capture : $(objects) arducam_ov2640_capture.o 
	gcc -o ov2640_capture $(objects) arducam_ov2640_capture.o -lmraa -Wall
ov2640_4cams_capture : $(objects) arducam_ov2640_4cams_capture.o 
	gcc -o ov2640_4cams_capture $(objects) arducam_ov2640_4cams_capture.o -lmraa -Wall
ov5642_capture : $(objects) arducam_ov5642_capture.o 
	gcc -o ov5642_capture $(objects) arducam_ov5642_capture.o -lmraa -Wall
ov5642_4cams_capture : $(objects) arducam_ov5642_4cams_capture.o 
	gcc -o ov5642_4cams_capture $(objects) arducam_ov5642_4cams_capture.o -lmraa -Wall
	
arducam.o : arducam.c
	gcc -c arducam.c -lmraa -Wall
arducam_arch_edison.o : arducam_arch_edison.c
	gcc -c arducam_arch_edison.c -lmraa -Wall


arducam_ov2640_capture.o : arducam_ov2640_capture.c
	gcc -c arducam_ov2640_capture.c -lmraa -Wall
arducam_ov2640_4cams_capture.o : arducam_ov2640_4cams_capture.c
	gcc -c arducam_ov2640_4cams_capture.c -lmraa -Wall
arducam_ov5642_capture.o : arducam_ov5642_capture.c
	gcc -c arducam_ov5642_capture.c -lmraa -Wall
arducam_ov5642_4cams_capture.o : arducam_ov5642_4cams_capture.c
	gcc -c arducam_ov5642_4cams_capture.c -lmraa -Wall

clean : 
	rm -f  ov2640_capture ov2640_4cams_capture ov5642_capture ov5642_4cams_capture $(objects) *.o
