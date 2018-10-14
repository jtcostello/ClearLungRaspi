


# GPIO serial:
# https://oscarliang.com/raspberry-pi-and-arduino-connected-serial-gpio/

# USB serial:
# https://www.sunfounder.com/blog/rpi-ard/

# setting up raspi serial:
# https://raspberrypi.stackexchange.com/questions/45570/how-do-i-make-serial-work-on-the-raspberry-pi3-pi3b-pizerow
# https://www.cube-controls.com/2015/11/02/disable-serial-port-terminal-output-on-raspbian/

import serial
import time

# setup the output file
file = open("output.txt","w") 

# setup the serial connection
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.flushInput()
#ser.write("begin record")
print("serial connected")

N = 512

start = time.time()
count = 0
while count<1000:
#	print(ser.in_waiting)
	if ser.in_waiting > 1:
#		print(ser.in_waiting)
		response = ser.read(N)
		print response
		file.write(response)
		count += 1

# output execution time
end = time.time()
print(end-start)

# close file
file.close() 










