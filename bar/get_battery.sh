#! /bin/bash
overallInfo=$(upower -i /org/freedesktop/UPower/devices/battery_BAT0)

batteryInfo=$(echo "$overallInfo" | grep -E "power supply")
percentageInfo=$(echo "$overallInfo" | grep -E percentage)
stateInfo=$(echo "$overallInfo" | grep -E state)

battery=$(python3 - $batteryInfo << EOF
import sys
print(sys.argv[-1])
EOF
)

# obtains the percentage (number)
percentage=$(python3 - $percentageInfo << EOF
import sys
print(sys.argv[-1][:-1])
EOF
)

state=$(python3 - $stateInfo << EOF
import sys
print(sys.argv[-1])
EOF
)

if [ $battery == "no" ]; then
    true
elif [ $state == "charging" ]; then
    if [ $percentage -gt 90 ]; then
        icon="\xef\x96\x8a"
    elif [ $percentage -gt 80 ]; then
        icon="\xef\x96\x89"
    elif [ $percentage -gt 60 ]; then
        icon="\xef\x96\x88"
    elif [ $percentage -gt 40 ]; then
        icon="\xef\x96\x87"
    elif [ $percentage -gt 30 ]; then
        icon="\xef\x96\x86"
    else
        icon="\xef\x96\x85"
    fi
    echo -e "$percentage%" $icon
elif [ $state == "discharging" ]; then
    if [ $percentage -gt 90 ]; then
        icon="\xef\x96\x81"
    elif [ $percentage -gt 80 ]; then
        icon="\xef\x96\x80"
    elif [ $percentage -gt 70 ]; then
        icon="\xef\x95\xbf"
    elif [ $percentage -gt 60 ]; then
        icon="\xef\x95\xbe"
    elif [ $percentage -gt 50 ]; then
        icon="\xef\x95\xbd"
    elif [ $percentage -gt 40 ]; then
        icon="\xef\x95\xbc"
    elif [ $percentage -gt 30 ]; then
        icon="\xef\x95\xbb"
    elif [ $percentage -gt 20 ]; then
        icon="\xef\x95\xba"
    else
        icon="\xef\x96\xb9"
    fi
    echo -e "$percentage%" $icon
fi
