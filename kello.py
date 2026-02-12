from machine import Pin, SPI
import max7219
import time
from font import FONT

# 8 modules = 64x8
spi = SPI(1, baudrate=1000000, polarity=1, phase=0,  sck=Pin(4),
    mosi=Pin(2),)
cs = Pin(5, Pin.OUT)

display = max7219.Matrix8x8(spi, cs, 8)
display.brightness(0)
display.fill(0)
display.show()


def build_buffer(text):
    buffer = []
    for char in text:
        if char in FONT:
            glyph = FONT[char]
            width = glyph[0]
            cols = glyph[1:]
            buffer.extend(cols)
            buffer.append(0x00)  # spacing
        else:
            buffer.extend([0x00] * 4)
    return buffer

def scroll(text, delay=0.02):
    buf = build_buffer(text)
    while len(buf) < 64: buf=[0]+buf
    width = len(buf)
    for i in range(width - 64 + 1):
        display.fill(0)
        for x in range(64):
            col = buf[i + x]
            for y in range(8):
                if col & (1 << y):
                    display.pixel(x, y, 1)
        display.show()
        time.sleep(delay)


scroll("VALMIS   ")        
#while True:
#    print("testi")

