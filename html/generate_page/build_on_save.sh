#!/bin/sh

while file=$(inotifywait -r -q -e modify --format "%w%f" ../); do
  FILE=${file##*/}
  NAME=${FILE%.*}
  EXT=${FILE#*.}
  echo $FILE "modified"
  if [ "$EXT" = "php" ] || [ "$EXT" = "html.template" ] || [ "$EXT" = "imports.cfg" ]
  then
    echo "building index.html"
    php build.php > ../index.html  
  elif [ "$EXT" = "scss" ]
  then
    echo "building $NAME.css"
    sass "scss/"$FILE "../css/"$NAME".css"
  fi
  echo
done
