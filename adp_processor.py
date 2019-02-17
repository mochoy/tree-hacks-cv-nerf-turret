import subprocess as sp
import os
import serial

#TODO PATHTOARDUINO from RPI
ser = serial.Serial(PATHTOARDUINO, 9600)
data = ''
prevCmd = 0

class cmds:
    adb = 'adb'
    chmod = 'chmod'
    devices = 'devices'
    shell = 'shell'
    sudo = 'sudo'
    pull = 'pull'
    phone_path = '/storage/sdcard0/NerfVision'
    rpi_path = '/home/ray/sharedfolder'

sp.check_output([cmds.adb, 'start-server'])

#Check if there is a device connected and save the name
try:
    out = sp.check_output([cmds.adb, cmds.devices])
    device = out.split('\n')[1] #Devices
    if 'unauthorized' in out.split('\t')[1]: #device status
        print('WARNING: DEVICE UNAUTHORIZED')
    print('Found device:\n' + device)
except:lo
    print('No connected devices')
    raise

while(true) {
    sp.check_output([cmds.adb, cmds.pull, '-a', cmds.phone_path, cmds.rpi_path]) #pull openCV
    sp.check_output([cmds.sudo, cmds.chmod, '-R', '0777', cmds.rpi_path]) #allow read & write

    with open(cmds.rpi_path + '/NerfVision/data.txt', 'r') as datafile:
        data = datafile.read()

    #Process data
    processed_data = data.split('\n')
    try:
        newestCmd = processed_data[-1]
    except Exception:
        pass

    #Check if latest command is different from previously sent command
    if newestCmd != prevCmd:
        print('New command: ' + newestCmd)
        ser.write(newestCmd.encode)
        ser.flush()
}

#facialrecogapp