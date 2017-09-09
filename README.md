# word-counter
A mini project in word/character counter of given source files programmed in C

usage: 
freq [-l length] [-w | -c] [--scaled] filename1 filename2 .. 

-w - word count
-c - character count
-l - number of words/characters should show in the graph from top results
     if not specified all the words/characters will be shown
--scaled - fullscreen
filname1 filename2.. - any number of given source files to count words/characters

example:
freq -10 -w --scaled engineer.hum
