#! /bin/bash

# after DURATION seconds, a running sirene will be switched off
DURATION=60

# wait for WAIT seconds in between time measurements
WAIT=60

# compute the seconds that have already passed once
# we branch into end of shift. if WAIT-OVERFLOW is less than
# zero, we might have encountered leap seconds,
# which will not be considered in further delta calculations
OVERFLOW=0

# remove previous processes
echo "Suche nach laufender Sirenensteuerung..."
prevproc=$(ps hS -o pid -C Sirene.sh)
for i in $prevproc
    do
        if [ ${i} -ne $$ ]
            then
                echo "Killing previous Sirene.sh ${i}"
                kill ${i}
        fi
    done


echo "Sirenensteuerung läuft (${$})."

while true
    do

        time=$(date "+%H:%M")

        case "${time}" in
            "06:00" | "14:00" | "14:02")
                OVERFLOW=$(date "+%-S")

                if [ ${OVERFLOW} -gt 0 ]
                    then
                        echo "$(date "+%H:%M:%S") : ${OVERFLOW} Sekunden werden für"
                        echo "           den nächsten Tick abgezogen."
                fi

                ./Sirene_Ein.sh
                echo "$(date '+%H:%M:%S') Sirene eingeschaltet."
                sleep ${DURATION}
                ./Sirene_Aus.sh
                echo "$(date '+%H:%M:%S') Sirene ausgeschaltet."
            ;;
        esac

        if [ $((WAIT - OVERFLOW)) -lt 0 ]
            then
                sleep 0
            else
                sleep $((WAIT - OVERFLOW))
            fi
        OVERFLOW=0
    done