from machine import Pin, ADC
import utime
xAxis = ADC(Pin(27))
yAxis = ADC(Pin(26))

while True:
    xValue = xAxis.read_u16()
    yValue = yAxis.read_u16()
    print(str(xValue) +", " + str(yValue))
    utime.sleep(0.1)