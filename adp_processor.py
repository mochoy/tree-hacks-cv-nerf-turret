import subprocess as sp
import os
#import serial #NO MODULE NAMED SERIAL

#TODO PATHTOARDUINO from RPI
#ser = serial.Serial(PATHTOARDUINO, 9600)
newVal = ''

class cmds:
    adb = 'adb'
    devices = 'devices'
    logcat = 'logcat'
    tag = 'TARGETTING'

sp.check_output([cmds.adb, 'start-server'])

#Check if there is a device connected and save the name
try:
    out = sp.check_output([cmds.adb, cmds.devices])
    device = out.split('\n')[1] #Devices
    if 'unauthorized' in out.split('\t')[1]: #device status
        print('WARNING: DEVICE UNAUTHORIZED')
    print('Found device:\n' + device)
except:
    print('No connected devices')
    raise

#Check for targeting tag; BROKEN, while is sending too many commands
while(True)
    #Log from adb only outputs with tags labelled TARGETTING
    print('Reached here')
    #print sp.check_output([cmds.adb, cmds.logcat, '-s', 'TARGETTING '])
    commands = [cmds.adb, cmds.logcat, '-s']
    output = sp.Popen(commands, stdin=sp.PIPE)
    output.stdin.write(cmds.tag, shell=False)
    output.close()
    print output.communicate()
    try:
        newVal = output.split(' ')[-1]
    except:
        print('Invalid format for targetting')
        pass
    print('Sending to arduino: ' + newVal)
    #ser.write(newVal.encode)
    #ser.flush()