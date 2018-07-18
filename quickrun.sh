#!/bin/bash
# Your device may be mounted in a different location. Inspect yourself before you wreck yourself!
yotta build
if [ $? -eq 0 ]; then
    cp build/bbc-microbit-classic-gcc/source/microbit-shooter-combined.hex /media/$USER/MICROBIT1
else
    echo "BUILD FAILED"
fi
