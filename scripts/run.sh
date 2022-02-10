#!/usr/bin/env sh

#clean build
if [ -e "Timer" ]; then
   rm -rf *;
fi;
APP_DIR="../source/app"
cmake $APP_DIR

#cmake successful?
if [ $? -eq 0 ]; then
    # compile using make
    make

    #make successful
    if [ $? -eq 0 ]; then
	echo "TIMER APP BUILT SUCCESSFULLY";

	echo "Running Test [ 1 ]"
	./Timer 
    fi;

    
fi;

