#!/usr/bin/python3
import os,signal,sys,subprocess
import uuid
def genSsid():
	return "pidrone-"+str(uuid.uuid4().fields[-1])[:4]
def genPassword():
	return str(uuid.uuid4().fields[-1])[:12]
def callprocess(proc):
	p = subprocess.Popen(proc, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
	output = ""
	for line in p.stdout.readlines():
		output+=line+"\n"
	for line in p.stderr.readlines():
		output+=line+"\n"
	retval = p.wait()
	logging.debug("output of %s start",proc)
	loggin.debug(output)
	logging.debug("return value")
	loggin.debug(retval)
	return retval == 0
# http://stackoverflow.com/questions/2536197/convert-args-to-flat-list
def flatten(ls):
  if isinstance(ls, list):
     return [fa for a in ls for fa in flatten(a)]
  else:
     return [ls]
