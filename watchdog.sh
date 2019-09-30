#!/bin/sh

if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ]
then
    >&2 echo "Usage: ./watchdog.sh PID PERIOD_SEC WATCHDOG_FILE_NAME"
    exit 1
fi

PID=$1
PRD=$2
FILE=$3

while ps -p $PID > /dev/null
do
    touch $FILE
    sleep $PRD

    if [ -f "$FILE" ]
    then
        echo $(date +"%d.%m.%Y %H:%M:%S\t***** WATCHDOG forced terminate process $PID") 
        kill $PID 2> /dev/null
        unlink $FILE 2> /dev/null
        exit 2
    fi
done

exit 0