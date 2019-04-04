Rivendell - Spintron Update
===========================

WMFO - Tufts Freeform Radio  
ops@wmfo.org  
For copyrights and licensing, see TERMS and COPYING.  

This is a Rivendell Loadable Module made to report the current playing song
metadata to Spinitron. It was orginally made for Rivendell 1.5 and has been
updated to work with Rivendell 2.

Before use, revert to the latest known good version. These are numbered using `git tag`.  
Add your Spinitron credentials to `credentials-dummy.h` and rename it `credentials.h`.  
You may also need to change the symlink `rlm.h` to point to the correct location in your install.  
If you don't want to log the cart number in the notes field, change LOG_CART_NUM to `0`.  
Compile using `make all` to produce rlm_spinitron.rlm.  
Optionally, install the file to another directory with `make install`.  
Runtime configurtaion is done at RDAdmin->ManageHosts->select the host->Edit->
RDAirplay->EditNow&NextData and specify the path to the file. Restart RDAirplay.

Rivendell 2.5.3 introduced native Spinitron integration, which may be viable
for some stations. However, it's based on the "Operating Mode" tri-state toggle
of "Automatic", "LiveAssist", and "Manual". We at WMFO consider this model
to be broken, and have hacked the source so that the only "Playback Modes"
are "Continuous" and "Single" (details available on request). We use a
Macro cart (see separate file for details) on the Rivendell sound panel to
turn Automation 'on' or 'off'. This involves loading the log of songs to
play (a rather inconvenient operation to do and undo when asking Rivendell
to play songs continuously!), and switchng between the active DJ and the
automation user.

When the on-air signal is on, the module posts to the current playlist of the
active Spinitron user; when it is off, it posts to the account provided in the
parameters. This was made to support automated playback when no 'live'
Spinitron user is logged in. It effectively logs all automated playlists under
a 'fake' automated user. This user should be set up in Spinitron just like a
regular user. You need to ask [Tom at Spinitron](mailto:tom@spinitron.com) to
enable automation access. It is a security measure. When you ask for access,
Spinitron configures an access control that allows only those machines that you
nominate to log spins into your Spinitron database.


Changelog
---------
###05/12/11
Initial version. - Benjamin Yu and Eric Berg

###07/12/12
Move credentials to new file, prepare documentation, Makefile.
As few modifications as possible. - Max Goldstein

###07/15/12
Refactor code, particularly for safe string functions. - Max Goldstein

###07/29/12
Fix bug where sepcial characters such as `&` would not be escaped properly.
Makefile now keeps a backup during install and replaces it on uninstall. - Max Goldstein

###08/12/12
Fix bug where script would never log as DJ with open playlist. curl now
times out instead of freezing RDAirplay. - Max Goldstein

###9/25/12
Restrict access to files containing credentials automatically in the Makefile. - Max Goldstein

###10/13/12
Add logging cart number to notes field. - Max Goldstein

###10/15/12
Add tag for known-good commit. Update README. - Max Goldstein

###11/21/12
New known-good commit. Optionally logs cart numbers, curl times out. - Max Goldstein

###10/15/13
Update the README. No code changes. - Max Goldstein

###5/3/14
Update documentation about the shell script to turn automation on. - Max Goldstein

###5/6/14
Add `macro_sh`, a collection of shell scripts called by our Rivendell macros. - Max Goldstein

###5/15/14
Set up automation off from board fader off. - Max Goldstein

###4/3/2019
Updated to use the Spinitron V2 API.
