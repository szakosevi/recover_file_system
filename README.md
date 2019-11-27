Recover file system

Read the data from file line by line and check the first character. Is the first char is not enough to identify the line, need to check the followings characters.

I defined different states:
  LIST,       ls -l 
  CHANGE_DIR, cd./dirname
  NEXT_LINE,  total X
  UP,         cd ..
  DATA_DIR,   directory
  DATA_FILE,  file
  IDLE        start

It the code reach one state after will be execure the defined function.
LIST -> noticed that if is a list
CHANGE_DIR -> change the current directory to it
UP -> go back one directory
DATA_DIR -> this is a directory and add a new directory to actual directory
DATA_FILE -> this is a file and add a new file to actual directory
IDLE -> initialisation state

Print the (close to) JSON form with stream.

