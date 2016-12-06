#ifndef _MEMORYSAVER_
#define _MEMORYSAVER_

//Uncomment the following definition when you use them
#define OV2640_CAM
//#define MT9D111_CAM

#if defined OV2640_CAM
	#include "ov2640_regs.h"
#endif

#if defined MT9D111_CAM	
	#include "mt9d111_regs.h"
#endif

#endif	//_MEMORYSAVER_
