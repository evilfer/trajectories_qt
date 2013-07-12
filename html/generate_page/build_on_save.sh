#!/bin/sh

while file=$(inotifywait -r -e modify --format "%w%f" ../); do
  FILE=${file##*/}
  NAME=${FILE%.*}
  EXT=${FILE#*.}
  echo $FILE
  echo $EXT
  if [ $EXT = "php" ] || [ $EXT = "html.template" ] || [ $EXT = "imports.cfg" ]
  then
    php build.php > ../index.html  
  elif [ $EXT = "scss" ]
  then
    sass "scss/"$FILE "../css/"$NAME".css"
  fi
done
