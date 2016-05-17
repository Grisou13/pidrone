import thread,os,signal,sys,subprocess

from .helpers import callprocess,genSsid,genPassword
hostapd_conf = '/../misc/etc/hostapd/hostapd.conf'
tmp_conf= '/tmp/hostapd.conf'
def startHostapd():
	global ssid
	global wifi_password
    global hostapd_conf
    global tmp_conf
	# Read in the file
	filedata = None
	with open(hostapd_conf, 'r') as file :
		filedata = file.read()

	# Replace the target string
	filedata = filedata.replace('wpa_passphrase=PASSWORD', 'wpa_passphrase='+wifi_password)
	filedata = filedata.replace( 'ssid=WIFI','ssid='+ssid)
	# Write the file out again
	with open(tmp_conf, 'w') as file:
		file.write(filedata)
	return callprocess('/etc/hostapd/hostapd '+os.path.abspath(tmp_conf))

def stopHostapd():
    global hostapd_conf
    # Read in the file

	return callprocess('/etc/init.d/hostapd stop')

if __name__ == '__main__':
    try:
        startHostapd()
    except KeyboardInterrupt as e:
        stopHostapd()
