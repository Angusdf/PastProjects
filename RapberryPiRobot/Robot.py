#!/usr/bin/python
#needed to use compass
import smbus
import time
import math
import matplotlib.pyplot as plt
import RPi.GPIO as gpio
import numpy as np
import cv2
#globals 
bus = smbus.SMBus(1)
address = 0x1e
scale = 0.92
xarray, yarray=[], []
xarray1, yarray1=[], []

def init():
  """Init the motor pins.

  Pins 17, 22, 23, 24 are used to control the motors.

  Args: 
      None

  Returns: 
        None

  """

  gpio.setmode(gpio.BCM)
  gpio.setup(17, gpio.OUT)
  gpio.setup(22, gpio.OUT)
  gpio.setup(23, gpio.OUT)
  gpio.setup(24, gpio.OUT)
 

def forward(rs,ls, sec):
  """Drive the motors depending on speed.

  Args: 
     rs: Right side speed
     ls: left side speed
     sec: tiem interval

  Returns: 
        None

  """

  init()
  print("forward")
  w=gpio.PWM(17,100)
  w.start(0)
  q=gpio.PWM(24,100)
  q.start(0)

  gpio.output(17,True)
  gpio.output(22,False)
  gpio.output(23,False)
  gpio.output(24,True)
  w.ChangeDutyCycle(rs)
  q.ChangeDutyCycle(ls)
 
  time.sleep(sec)
  gpio.cleanup()
  w.stop()

def calibrate():
  """ Callibrate the compass

     The robot will spin in a circle while
     reading in data points.
 
  Args: 
      None

  Returns: 
        xoff: x offset.
 
        yoff: y offset.

  """

  init()
  w=gpio.PWM(17,100)
  w.start(0)
  q=gpio.PWM(24,100)
  q.start(0)

  gpio.output(17,True)
  gpio.output(22,False)
  gpio.output(23,True)
  gpio.output(24,True)
  w.ChangeDutyCycle(75)
  q.ChangeDutyCycle(75)
 
  xoff, yoff = offset() 
  gpio.cleanup()
  w.stop()
  return xoff,yoff

def offset():
    """Find the  offset of the compass to determine true dirction.

    Args: 
      None

    Returns: 
        x_offset: x offset.
 
        y_offset: y offset.


    """

    # Set to 8 samples @ 15Hz
    write_byte(0, 0b01110000)
    # 1.3 gain LSb / Gauss 1090 (default)
    write_byte(1, 0b00100000) 
    # Continuous sampling
    write_byte(2, 0b00000000) 

    minx, maxx = 0, 0
    miny. maxy = 0, 0
    print("callibrate")
    for i in range(0,60):
       x_out = read_word_2c(3)
       y_out = read_word_2c(7)
       z_out = read_word_2c(5)
       xarray.append(x_out)
       yarray.append(y_out)
    
       if x_out < minx:
          minx=x_out
    
       if y_out < miny:
          miny=y_out
    
       if x_out > maxx:
          maxx=x_out
    
       if y_out > maxy:
          maxy=y_out  
    
       time.sleep(0.1)

    x_offset =(maxx + minx) / 2
    y_offset = (maxy + miny) / 2
    print("done")

    return x_offset,y_offset

def read_byte(adr):
  """Read in the byte from compass

  Args: 
      adr: address where compass info is stored

  Returns: 
        byte: information wanted from compass

  """

  return bus.read_byte_data(address, adr)

def read_word(adr):
  """Read in info from compass

  Args: 
      adr: address where compass info is stored 

  Returns: 
        val: value found from compass

  """

  high = bus.read_byte_data(address, adr)
  low = bus.read_byte_data(address, adr+1)
  val = (high << 8) + low
  return val

def read_word_2c(adr):
  """read from comapss and determine if reasonable

  Args: 
      adr: address where info is stored

  Returns: 
        val: reading from compass

  """

  val = read_word(adr)
  if (val >= 0x8000):
      return -((65535 - val) + 1)
  else:
      return val

def write_byte(adr, value):
  """Wrte bytes

  Args: 
      adr: Address writing to
      value: value being wrote 

  Returns: 
        None

  """

  bus.write_byte_data(address, adr, value)

video_capture = cv2.VideoCapture(-1)
#set size
video_capture.set(3, 480)
video_capture.set(4, 680)

while(True):
    #x_out = (read_word_2c(3) - x) * scale
    #y_out = (read_word_2c(7) - y) * scale
    #z_out = (read_word_2c(5)) * scale
    #bearing  = math.atan2(y_out, x_out)
    #if (bearing < 0):
    #    bearing += 2 * math.pi
    #print ("Bearing: ", math.degrees(bearing))

    # Capture the frames
    ret, frame = video_capture.read()
    
    # Crop the image
    img = frame[0:480, 0:680]
    # Convert to grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # Gaussian blur
    blur = cv2.GaussianBlur(gray,(5,5),0)
    
    # Color thresholding
    ret,thresh1 = cv2.threshold(blur,130,255,cv2.THRESH_TOZERO)

    # Find the contours of the frame
    contours,hierarchy = cv2.findContours(thresh1.copy(), 1, cv2.CHAIN_APPROX_NONE)

    # Find the biggest contour (if detected)
    if len(contours) > 0:
        c = max(contours, key=cv2.contourArea)
        M = cv2.moments(c)

        cx = int(M['m10']/M['m00'])
        cy = int(M['m01']/M['m00'])

        cv2.line(img,(cx,0),(cx,720),(255,0,0),1)
        cv2.line(img,(0,cy),(1280,cy),(255,0,0),1)

        cv2.drawContours(img, contours, -1, (0,255,0), 1)
        print (cx)
        if cx >= 300:
            print ("Turn Right!")
            forward(25,20,.1)
        if (cx > 200 and cx < 300):
            print ("On Track!")
            forward(50,50,.5)
        if cx <= 200:
            print ("Turn left")
            forward(20,80,.1)
#
    else:
        print ("I don't see the line")


    #Display the resulting frame
    cv2.imshow('Orginal',img)
    cv2.imshow('thresh1',thresh1)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


