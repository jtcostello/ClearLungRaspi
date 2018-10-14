


# GPIO serial:
# https://oscarliang.com/raspberry-pi-and-arduino-connected-serial-gpio/

# USB serial:
# https://www.sunfounder.com/blog/rpi-ard/

# setting up raspi serial:
# https://raspberrypi.stackexchange.com/questions/45570/how-do-i-make-serial-work-on-the-raspberry-pi3-pi3b-pizerow
# https://www.cube-controls.com/2015/11/02/disable-serial-port-terminal-output-on-raspbian/

import serial

# setup the output file
file = open("output.txt","w") 

# setup the serial connection
ser = serial.Serial('/dev/serial0', 9600, timeout=1)
ser.flushInput()
ser.write("begin record")


while True:
	if ser.inWaitin() > 0
	response = ser.read(512)
	print response
	file.write(response)


# for i in range(100)
# 	# read 512 bytes
# 	response = ser.read(512) 
# 	print response
# 	file.write(response)

# close file
file.close() 










