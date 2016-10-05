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

rxbuff = spi.write(rxbuff)
print (rxbuff)
