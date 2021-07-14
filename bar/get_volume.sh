#! /bin/bash
string=$(amixer -c 1 | awk 'c&&!--c;/Master/{c=4}')

volume=$(python3 - $string << EOF
import sys
vol=sys.argv[4] # [56%]
strip=vol[1:-2]
print(strip)
EOF
)

if [ $volume -gt 60 ]; then
    icon="\xef\xa9\xbd"
elif [ $volume -gt 40 ]; then
    icon="\xef\xa9\xbf"
elif [ $volume -gt 0 ]; then
    icon="\xef\xa9\xbe"
else
    icon="\xef\xaa\x80"
fi

echo -e "$volume%" $icon
