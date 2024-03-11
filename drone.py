from servo import Servo
import time

motor=Servo(pin=22)
motor.move(180)
time.sleep(seconds=5)
motor.move(0) 
time.sleep(seconds=2)
motor.move(10) 
