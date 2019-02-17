import fileinput
import time
import serial

ser = serial.Serial('/dev/ttyUSB0', 9600)

#adb logcat -s 'TARGETTING' | python /home/ray/sharedfolder/logcatPiper.py
value = ''

print('Running logcatPiper.py')
'''
for line in fileinput.input():
    #print(line)
    try:
        value = line.split(' ')[-1].rstrip("\n")
    except:
        print('Invalid format')
        continue

    print('Writing ' + value + 'a to arduino!')
    ser.write(value + 'a')
    ser.flush()
'''

#Testing
for i in range(-400, 500, 100):
    val = str(i) + 'a'
    print('sending' + val)
    ser.write(val)
    ser.flush()
    time.sleep(1)
