#!/bin/sh

while file=$(inotifywait -r -e modify --format "%w%f" ./); do
  EXT=${file##*.}
  if [ $EXT = "php" ] || [ $EXT = "template" ]
  then
    php build.php > index.html  
  fi
done
