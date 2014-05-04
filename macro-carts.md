#Macro CARTS
Automation is controlled using these two Macro CARTS. Of note with regards to
the Spinitron logger is the on-air flag, which has been appropriated to be the
automation is off flag. This affects the pm used by the logger.

##Automation ON
````
001  PM 2!
002  TA 0!
003  RN /usr/bin/playlist.sh!
````

This sets the mode to automatic (instead of manual or liveassist),
sets the on-air flag to 0,
and executes a shell script copied in this repo.

The script loads the failsafe log, and if today's log exists, overwrites it
with that. It calculates the correct item to play based on the time.  These
logs are generated by a [separate script](https://github.com/WMFO/Automation-Scheduler).

##Automation OFF
````
001  TA 1!
002  LL 1 BLANK!
003  LL 2 BLANK!
004  LL 3 BLANK!
````

This sets the on-air flag to 1, and removes all logs.

Logs are global to a Rivendell install, so failsafe and blank logs need to be
made once per station, not once per computer.