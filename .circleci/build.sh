ARPATH=/opt/arduino
LIBRARIES=""

for lib in `ls third_party_packages`
do
  LIBRARIES=$LIBRARIES" -libraries "$lib
done

for sketch in `find ./src/ -name '*.ino'`
do
  echo $ARPATH/arduino-builder -hardware $ARPATH/hardware -tools $ARPATH/hardware/tools/avr -tools $ARPATH/tools-builder -libraries $ARPATH/libraries $LIBRARIES -fqbn arduino:avr:uno $sketch
done
