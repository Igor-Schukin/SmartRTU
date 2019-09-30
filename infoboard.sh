#!/bin/sh

status=1
wdfile="./infoboard.watchdog"

echo >> ./infoboard.log
echo $( date +"%d.%m.%Y %H:%M:%S\t***** INFOBOARD bash script started" ) >> ./infoboard.log

while [ $status -ne 0 ]
do
    ./infoboard >> ./infoboard.log & pid=$! 
    echo $pid > ./infoboard.pid

    ./watchdog.sh $pid 900 $wdfile >> ./infoboard.log & wpid=$!
    echo $( date +"%d.%m.%Y %H:%M:%S\t***** WATCHDOG bash script started" ) >> ./infoboard.log

    wait $pid
    status=$?

    kill $wpid 2> /dev/null
    unlink $wdfile 2> /dev/null
    unlink ./infoboard.pid 2> /dev/null
    
    if [ "$1" != "daemon" ]
    then
        break
    fi

    if [ $status -ne 0 ]
    then
        sleep 5
        echo $( date +"%d.%m.%Y %H:%M:%S\t***** INFOBOARD is restarted from bash script" ) >> ./infoboard.log
    fi
done

echo $(date +"%d.%m.%Y %H:%M:%S\t***** INFOBOARD bash script finished") >> ./infoboard.log
