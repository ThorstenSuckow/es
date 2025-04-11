#! /bin/bash
echo "Usage: ProcLift.sh [n] "
echo "       n = Interval in seconds, defaults to 5"

default="5"
arg1=${1}
interval=$((0 + arg1))

if [ ${interval} -le 0 ]
    then interval=${default}
fi



while true
  do
    memtotal=$(egrep -o  "^MemTotal(.*)kB$" /proc/meminfo | egrep -o "[[:digit:]]{0,}")
    memfree=$(egrep -o  "^MemFree(.*)kB$" /proc/meminfo | egrep -o "[[:digit:]]{0,}")
    printf  "\r $((memtotal - memfree))"
    sleep ${interval}
  done
