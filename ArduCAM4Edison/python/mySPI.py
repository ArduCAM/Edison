import mraa
import pprint
class mySPI(object):
    def __init__(self, cs):
        self.spi = mraa.Spi(0)
        self.cs = mraa.Gpio(23) if cs == 0 else mraa.Gpio(9)
        self.cs.dir(mraa.DIR_OUT)
        self.cs.write(1)
        #self.spi.frequency(2000000) # 2 MHz
        self.spi.mode(mraa.SPI_MODE0)
        self._WRITE_MAX = 20
        # first write a dummy byte
        self.spi.writeByte(0)

    def setFrequency(self, freq):
        self.spi.frequency(freq)

    # 1 byte Data
    def writeByte(self, data):
        # dummy byte
        self.spi.writeByte(0)
        self.cs.write(0)
        miso = self.spi.writeByte(data)
        self.cs.write(1)
        return miso

    # byte array
    def write(self, data):
        data = bytearray(data)
        self.spi.writeByte(0)
        self.cs.write(0)
        miso = []
        for i in range(0, len(data), self._WRITE_MAX):
            miso_sub = self.spi.write(data[i:min(i+self._WRITE_MAX, len(data))])
            miso += miso_sub
        self.cs.write(1)
        return list(miso)

pp = pprint.PrettyPrinter(indent=4)
rxbuff = bytearray(4)

rxbuff[0] = 0xFF
rxbuff[1] = 0x00
rxbuff[2] = 0x3C
rxbuff[3] = 0x55
pp.pprint( mySPI(1).writeByte(0x42) )
pp.pprint( mySPI(1).write(rxbuff) )