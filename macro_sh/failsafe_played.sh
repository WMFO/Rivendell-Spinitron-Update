#!/bin/bash

echo "The Rivendell failsafe log has been played. This means the automation scheduler is not working." | mail -s "Failsafe log played" ops-alerts@googlegroups.com
