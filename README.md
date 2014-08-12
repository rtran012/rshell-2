 shell is a program that takes the user's input from the keyboard and lets the user control the operating system. The shell is a text only user interface for Linux and other Unix like operating systems. It is the most fundamental way for a user to interact with the computer. The shell executes the commands and display the output on the screen.

In this program called "rshell", it reproduces the terminal in Linux. When "rshell" is compiled and ran, it will act as another terminal. Basically a terminal within a terminal. It has a command prompt with the currently logged in user and the hostname of the machine followed by a "$". From there the user types in a command, such as ls, clear, etc., then hit the enter/return key to execute the command. The command that had been executed will show up on the screen. Once the user is done, the user needs to type "exit" to exit the program.

There are a few bugs in this program. 
Typing in "ls -lR /" makes the program go crazy.
Using the directional arrows do no work when using the program.
When typing in the command, there HAS to be only a SINGLE space between the command and the argument list. 
If there are more than one space between the command and the argument list, it will say "No such file or directory". 
If the user enters multiple spaces after the argument list, it will also indicate "No such file or directory". 
If the user enters unrecognized commands, it will prints out "execvp failed". Because the command is not listed.
If the user enters "cd",  (change directory), it will also print out "execvp failed".
The command "dirs" will not work, it prints out "execvp failed".
The command "hash" will not work either.
The command "jobs" does not work.
The command "shopt" does not work.
The -R does not work either.
Look in the tests file

Other than these bugs, the rshell works like the regular terminal. 
Commands such as: ls (-a, -l, -la, -al, -l -a, -a -l), vim, cat, rm, mkdir, rmdir, time, touch, top, exit, pwd, script, etc. will all work.
