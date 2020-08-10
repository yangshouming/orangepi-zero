import spidev
import time
spi = spidev.SpiDev()
spi.open(1, 0)
spi.max_speed_hz = 3200000
spi.mode = 0b1
spi.xfer([0x00, ])
data = [
    0x00,
    0x88, 0x88, 0x88, 0x88,  # R:0
    0xcc, 0xcc, 0xcc, 0xcc,  # G:255
    0x88, 0x88, 0x88, 0x88,  # B:0
]
spi.xfer(data)
