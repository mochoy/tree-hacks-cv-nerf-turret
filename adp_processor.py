import subprocess as sp
import os

coords = {
    'x' : 0,
    'y' : 0
}

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
except:
    print('No connected devices')

sp.check_output([cmds.adb, cmds.pull, '-a', cmds.phone_path, cmds.rpi_path]) #pull openCV
sp.check_output([cmds.sudo, cmds.chmod, '-R', '0777', cmds.rpi_path]) #allow read & write

with open(cmds.rpi_path + '/NerfVision/example.txt', 'r') as datafile:
    data = datafile.read()

#Process data and split into x and y
processed_data = data.split('\n')
coords['x'] = processed_data[0].split(' ')[-1]
coords['y'] = processed_data[1].split(' ')[-1]

#TODO: Send data to Arduino