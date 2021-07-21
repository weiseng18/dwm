#! /bin/bash
string=$(brightnessctl | awk 'c&&!--c;/Current/')

brightness=$(python3 - $string << EOF
import sys
bri=sys.argv[4] # [56%]
strip=bri[1:-2]
print(strip)
EOF
)

if [ $brightness -gt 66 ]; then
    icon="\xef\x97\x9f"
elif [ $brightness -gt 33 ]; then
    icon="\xef\x97\x9e"
else
    icon="\xef\x97\x9d"
fi

echo -e "$brightness%" $icon
