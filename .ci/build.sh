#!/bin/bash
set -eux
pio lib --global install "arduino-libraries/Servo"
platformio run