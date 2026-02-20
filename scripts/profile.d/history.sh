#!/bin/bash

USER=$( whoami )
USER_IP=$( who -u am i 2>/dev/null|egrep -o "([0-9]{1,3}\.){3}[0-9]{1,3}" )
if [ "$USER_IP" = "" ]; then
    USER_IP=$( hostname )
fi
if [ ! -d /var/log/history ]; then
    mkdir /var/log/history/
    chmod 777 /var/log/history
fi
if [ ! -d /var/log/history/$USER ]; then
    mkdir /var/log/history/$USER
    chmod 300 /var/log/history/$USER
    chown $USER:$USER /var/log/history/$USER
fi

export HISTSIZE=10240
export HISTTIMEFORMAT="%F %T "

DT=`date +"%Y%m%d_%H:%M:%S"`
export HISTFILE="/var/log/history/$USER/${USER}@${USER_IP}_$DT"
export PROMPT_COMMAND='{ echo " ##### $(who am i |awk "{print \$1\" \"\$2\" \"\$5}")  #### $(history 1 | { read x cmd; echo "$cmd"; })"; } >> $HISTFILE'
chmod 600 /var/log/history/$USER/*history* 2>/dev/null
