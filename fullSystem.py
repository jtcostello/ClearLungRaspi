
from subprocess import call
import RPi.GPIO as GPIO
import time
import serial



# Variables
recordTimeSec = 1
N = 512

startButtonPin = 27
upButtonPin = 28
downButtonPin = 29

#/////////////////////////////////// FUNCTIONS ///////////////////////////////////////

# function to read state of button
def readButton(pin):
	return GPIO.input(pin)

# function to display text on lcd
def lcdprint(l1, l2, l3, l4):
	call(["./newLcdCode/cmdlineLCD","a"," "," "," "])


# function to delay "t" milliseconds
def delay(t):
	time.sleep(t/1000)



# function updates lcd/record time before start
def waitForStart():
	updateWaitingScreen();
	# while the start button hasn't been pressed
	while not readButton(startButtonPin):
		if readButton(upButtonPin):
			# increase the record time
			recordTimeSec += 1
			print(recordTimeSec)
			updateWaitingScreen()
			delay(200);
		elif readButton(downButtonPin):
			# decrease record time
			if recordTimeSec > 1:
				recordTimeSec -= 1
			print(recordTimeSec)
			updateWaitingScreen()
			delay(200)

def updateWaitingScreen():
	lcdprint("Record for", str(recordTimeSec), "Press start", " ")



# function converts the byte data input to list of numbers
def formatDataIn(data):
	outdata = 0
	for i in range(0,length(data),2):
		lower = data[i]
		upper = data[i+1]
		value = (upper << 8) | lower
		if value > 10000:
			# subtract 2^15
			value -= 32768 #65536 
		outdata.append(value)


def makeGraph(fname):
	cmd1 = "gnuplot -e 'set terminal png; plot "
	cmd2 = " with lines' > \"graph.png\""
	# make the graph using gnuplot
	call(cmd1 + fname + cmd2)
	# open the image (install with: sudo apt-get -y install fbi)
	call("fbi -a graph.png")







#/////////////////////////////////// ON BOOT ///////////////////////////////////////
# setup pins
GPIO.setmode(GPIO.BCM)
GPIO.setup(startButtonPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(upButtonPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(downButtonPin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

# show title text
lcdprint(" ","Clear Lung Project")
delay(2000);

# open output files for each mic
mic1 = open("mic1.txt","w") 
mic2 = open("mic2.txt","w") 

# setup the serial connection
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.flushInput()
print("serial connected")

# display option to select recording time and wait for start button press 
waitForStart()



#/////////////////////////////////// ON START ///////////////////////////////////////
print("Recording now")
lcdprint("Recording now"," "," "," ")


# calculate total number of bytes for the recording time
numMics = 2
totalBytes = 44100 * recordTimeSec * 2 * numMics

# request the total num bytes from teensy in increments of (128)
# separate data into the files, write to files
mic1Counter = 0
mic2Counter = 0
bytesRead = 0

while bytesRead < totalBytes:
	if ser.in_waiting > 1:
		data = formatDataIn(ser.read(N))
		mic1.write(data)
		print(data)
		count += N



# close files
mic1.close()
mic2.close()




#/////////////////////////////////// ON FINISH ///////////////////////////////////////
lcdprint("Finished Recording"," "," "," ")

# // show graph of 1 sec of recording
makeGraph("mic1.txt")

# // show graph of fft
# runFFT(nearestPow2(valueCounter), "mic2.txt", "fft.txt");
# makeGraph("fft.txt");

print("all done")















