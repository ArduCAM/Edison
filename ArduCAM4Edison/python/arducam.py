#!usr/bin/env python

import mraa as m
import time

spi = m.Spi(0)
spi.mode(m.SPI_MODE0)

rxbuff = bytearray(4)

rxbuff[0] = 0x00
rxbuff[1] = 0x55
rxbuff[2] = 0x3C
rxbuff[3] = 0x55

#def Test():
    #for i in range(6):
        #Page(i)
        #Column(0)
        #for j in range(128):
            #spi.write(0x00)

#Test()


rxbuff = spi.writeByte(0x00)
print (rxbuff)