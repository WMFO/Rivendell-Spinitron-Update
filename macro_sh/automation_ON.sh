#!/bin/bash
# Turn Automation ON

LOCKFILE=/var/lock/automation_is_on.lock

hour=`date +%H`
min=`date +%M`
item=`echo  "$hour * 33 + ( $min * 33 / 60 ) / 1" | bc`

/usr/local/bin/rmlsend LL\ 1\ Failsafe\!
/usr/local/bin/rmlsend LL\ 1\ `date +%Y_%m_%d`\ $item\!

touch $LOCKFILE
