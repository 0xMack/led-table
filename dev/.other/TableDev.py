import RPi.GPIO as GPIO
import time
import math
from random import randint
#Example:   time.sleep(x)

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)
allPins = (3,5,7,11,13,15,8,10,12,24,22,18,16)
for y in allPins:  #Instantiate GPIO pins
    GPIO.setup(y,GPIO.OUT)
#-------------------Port Selection--------------------------
ser = 8
clk = 10
latchIn = 12
pwmC = 24
pwmR = 22
pwmG = 18
pwmB = 16
DefLoOutputs = (3,5,7,11,13,15)
#-------------------Port Selection-------------------------
#-----------------PWM Variables----------------
redValue = 256
greenValue = 256 #Colour values for pwm
blueValue = 256
#-----------------PWM Variables----------------
#------------------------Other Variables-----------------------
ledRow = 1
ledCol = 1
ledNum = 1
binRow = ''
binCol = ''
binCup = '101111'
binOut = ''
x = 1
i = 0
reps = 10000
#------------------------Other Variables-----------------------

def checkHue(i):
    redValue = randint(1,256)
    greenValue = randint(1,256)
    blueValue = randint(1,256)
    #print 'G:' + str(greenValue) + ' B:' + str(blueValue) + ' R:' + str(redValue)
    if(blueValue > 50):
        GPIO.output(pwmB,GPIO.HIGH)
    else:
        GPIO.output(pwmB,GPIO.LOW)
    if(greenValue > 50):
        GPIO.output(pwmG,GPIO.HIGH)
    else:
        GPIO.output(pwmG,GPIO.LOW)
    if(redValue > 50):
        GPIO.output(pwmR,GPIO.HIGH)
    else:
        GPIO.output(pwmR,GPIO.LOW)
        

#------------------------Shifts the Concatenated Binary---------------------
def shift(binOut):
    #print binOut
    for x in range(0,32): #Reads binary string
        if binOut[x] == '1':
            GPIO.output(ser,GPIO.HIGH) #Pulls high when 1
        else:
            GPIO.output(ser,GPIO.LOW) #Pulls low when zero
        GPIO.output(clk,GPIO.HIGH)#Shifts Register
        GPIO.output(clk,GPIO.LOW)#Shifts Register
    latch()

def latch():
    GPIO.output(latchIn,GPIO.HIGH)
    GPIO.output(latchIn,GPIO.LOW)

def setDefaultShift():
    GPIO.output(pwmC,GPIO.LOW)
    GPIO.output(pwmR,GPIO.HIGH)
    GPIO.output(pwmG,GPIO.HIGH)
    GPIO.output(pwmB,GPIO.HIGH)
    for y in DefLoOutputs:
        GPIO.output(y,GPIO.LOW)
    GPIO.output(ser,GPIO.LOW)
    for p in range(1,32):
        GPIO.output(clk,GPIO.HIGH)#Shifts Register
        GPIO.output(clk,GPIO.LOW)#Shifts Register
    latch()
    print 'Default shift initiated...'
#------------------------Shifts the Concatenated Binary---------------------

#---------------------Cups---------------------

            #Not written yet

#---------------------Cups---------------------

#---------------------Converts LED number to binary---------------------
def splitColRow(ledNum): 
    ledRow = int(math.floor(ledNum / 8))
    ledCol = int(ledNum % 8)
    return (ledRow,ledCol)
def convBinRow(ledRow):
    binRow = '{0:05b}'.format(ledRow)
    return binRow
def convBinCol(ledCol):
    binCol = '{0:03b}'.format(ledCol)
    return binCol
#---------------------Converts LED number to binary---------------------

#---------------------Concatenate Binary Strings---------------------
def concatBin(binCol,binRow):
    binOut = '00' + binCup + binRow + binCol + binRow + '000' + binRow + '000'
    return binOut
#---------------------Concatenate Binary Strings---------------------


def main(reps):
    i = 0
    reps = reps * 255
    for x in range(0,reps):
        if i == 256:
            i = 0
            #checkHue(i)
        else:
            i = i + 1
            time.sleep(0.01)
        ledNum = i
        ledRow,ledCol = splitColRow(ledNum)
        binRow = convBinRow(ledRow)
        binCol = convBinCol(ledCol)
        binOut = concatBin(binCol,binRow)
        shift(binOut)


def testing():
    fakebin = '00000000' + '00010' + '111' + '00000' + '000' + '00000' + '000'
    #            Cups     Red       Columns   Green             Blue
    shift(fakebin)
setDefaultShift()
#testing()
main(reps)

