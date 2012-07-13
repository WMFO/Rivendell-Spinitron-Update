Rivendell - Spintron Udpate
========

WMFO - Tufts Freeform Radio  
ops@wmfo.org  
For coprights and licensing, see TERMS and COPYING.  

This is a Rivendell Loadable Module made to report the current playing song
metadata to Spinitron. It was made for Rivendell 1.5.  It sends Now&Next PAD
data via UDP packets to the destination(s) specified in the configuration file
pointed to by the plugin argument.

Compile with the included Makefile to produce rlm_spinitron.rlm.
Install at RDAdmin->ManageHosts->select the host->Edit->RDAirplay
  ->EditNow&NextData and specify the path to the file. Restart RDAirplay.

Please note: when the on-air signal is on, the module posts to the current
playlist of the active Spinitron user; when it is off, it posts to the account
provided in the parameters. This was made to support automated playback when no
'live' Spinitron user is logged in. It effectively logs all automated playlists
under a 'fake' automated user. This user should be set up in Spinitron just
like a regular user. We use a Macro cart on the Rivendell cart screen to turn
Automation 'on' or 'off' and switch between the active DJ and the automation
user.

Changelog
---------
###05/12/11
Initial version. - Ben Yu and Eric Berg

###07/12/12
Move credentials to new file, prepare documentation, Makefile.
As few modifications as possible.- Max Goldstein
