
# GPIO serial:
# https://oscarliang.com/raspberry-pi-and-arduino-connected-serial-gpio/

# USB serial:
# https://www.sunfounder.com/blog/rpi-ard/

# setting up raspi serial:
# https://raspberrypi.stackexchange.com/questions/45570/how-do-i-make-serial-work-on-the-raspberry-pi3-pi3b-pizerow
# https://www.cube-controls.com/2015/11/02/disable-serial-port-terminal-output-on-raspbian/

# use "ls /dev/tty.*" to find port


import serial
import time

N = 4*512

file = open("output.txt","wb")

# setup the serial connection
ser = serial.Serial('/dev/ttyS0', 40000000)
ser.flushInput() #ser.reset_input_buffer()
print("serial connected")
ser.write('start'.encode('utf-8'))

count = 0
start = time.time()
lastReceive = start;

while ((lastReceive - start) < 1):
    if ser.inWaiting >= N: #(ser.in_waiting)
        response = ser.read(N) #N)
        count = count + 1
        lastReceive = time.time()
        print(count)
        print(time.time()-start)
  #      ser.write('g'.encode('utf-8'))
	file.write(response)

#    if (time.time() - lastReceive) > 1.0:

ser.close()
file.close()

print("done")
print(count)


# with n=1024, delay=1us
# read 6036 times in 10.3sec
# =   586kb/sec!


# need 334kb/sec for 4 mics

# need 172 packets per second (512*173 = 44100*2)


873/10
