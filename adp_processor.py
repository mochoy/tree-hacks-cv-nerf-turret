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
    tag = 'TARGETTING\n'

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

#Log from adb only outputs with tags labelled TARGETTING
print('Reached here')
#print sp.check_output([cmds.adb, cmds.logcat, '-s', 'TARGETTING '])

#print output.communicate()
'''
def execute(cmds):
    output = sp.Popen(commands, stdin=sp.PIPE)
    output.stdin.write(cmds.tag, shell=False)
    
    for stdout_line in iter(output.stdout.readline, ""):
        yield stdout_line
    output.close()
    output.communicate()
    output.wait()
'''
'''
commands = [cmds.adb, cmds.logcat, '-s']
for path in execute(commands):
    print path
'''

def execute(cmd):
    popen = sp.Popen(cmd, stdout=sp.PIPE, universal_newlines=True)
    popen.communicate(input=cmds.tag)
    for stdout_line in iter(popen.stdout.readline, ""):
        yield stdout_line 
    #popen.stdin.write(cmds.tag, shell=False)
    popen.stdout.close()
    return_code = popen.wait()
    if return_code:
        raise subprocess.CalledProcessError(return_code, cmd)

# Example
for path in execute([cmds.adb, cmds.logcat, '-s', cmds.tag]):
    print path
'''
try:
    newVal = output.split(' ')[-1]
except:
    print('Invalid format for targetting')
    pass
print('Sending to arduino: ' + newVal)
#ser.write(newVal.encode)
#ser.flush()
'''