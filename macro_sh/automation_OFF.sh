#!/bin/bash
# Turn Automation OFF

LOCKFILE=/var/lock/automation_is_on.lock 

# Pressing fader off button on board should not clear logs unless
# automation is actually running
if [ -f ${LOCKFILE} ] 
then
	/usr/local/bin/rmlsend LL\ 1\ Blank\!
	/usr/local/bin/rmlsend LL\ 2\ Blank\!
	/usr/local/bin/rmlsend LL\ 3\ Blank\!
	rm -f lockfile
fi

# Turn automation off (i.e. call this script) on GPI from board
# This cart is the startup cart, so these are called then
# Registering GPI multiple times does NOT cause multiple executions
if [ `hostname` = "ADELE" ]
then
	/usr/local/bin/rmlsend GI\ 1\ I\ 15\ 1\ 999997\!
fi

if [ `hostname` = "COULTON" ]
then
	/usr/local/bin/rmlsend GI\ 3\ I\ 20\ 1\ 999997\!
fi
