#!/bin/sh

while file=$(inotifywait -r -q -e modify --format "%w%f" ../); do
  FILE=${file##*/}
  NAME=${FILE%.*}
  EXT=${FILE##*.}
  echo $FILE "modified"
  if [ "$EXT" = "php" ] || [ "$EXT" = "template" ] || [ "$EXT" = "cfg" ]
  then
    echo "building index.html"
    php build.php > ../index.html  
  elif [ "$EXT" = "scss" ]
  then
    echo "building t-style.css"
    sass "scss/"t-style.scss ../css/t-style.css
  fi
  echo
done
