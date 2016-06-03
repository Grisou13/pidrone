import thread,os,signal,sys,subprocess

MJPEG_SERVER_PID = None

def startStreaming():
	global MJPEG_SERVER_PID
	DETACHED_PROCESS = 0x00000008

	MJPEG_SERVER_PID = subprocess.Popen(["/etc/mjpegstreamer/mjpegstreamer",],
	                       creationflags=DETACHED_PROCESS).pid
def stopStreaming():
	global MJPEG_SERVER_PID
	os.kill(MJPEG_SERVER_PID, signal.SIGTERM)

if __name__ == '__main__':
    try:
        startStreaming()
    except KeyboardInterrupt as e:
        stopStreaming()
