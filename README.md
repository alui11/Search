Search
===================

A partial re-implementation of 'find' (called search). Recursively searches a directory and prints items based on specified search options. Created for a class project. The goal of this project was to practice system calls dealing with files, directories, and processes in C.

Members
-------

- Alison Lui (alui@nd.edu)
- Ivy Wang (jwang28@nd.edu)

Responses
---------

1. Parsing command line arguments:
First we automatically set argv[1] as the path name, but then checked to see if it was actually a flag by checking its first character, and if it was we checked it against the flag names and otherwise started checking for flags at argv[2]. To check for flags we iterated through argv by increasing an index variable as long as the index was less than argc and argv of the index was greater than one and started with a dash. We compared each argument against every flag using streq, and when a match was found we altered a settings variable which was instantiated earlier.
For-executable, -readable, and -writable, we or'd settings.access with X\_OK, R\_OK, and W\_OK, respectivley to add those access writes. For type we casted the following argument to an int and set settings.type equal to it For empty we simply set settings.empty to true, and for name and path we set settings.name and settings.path equal to the following argument in argv. For perm we converted the following argument to an int one character at a time by subtracting '0' and then manually converted the octal to decmial with math. For newer we used get\_mtime from utilities.c to find the time of the specified file and stored that in settings.newer. For uid and gid we just used atoi to convert the string to an int. For print we just set settings.print to true. For exec we created a string of size BUFSIZ and kept going through argv adding arguments to the new string until an argument of ";" was found. The number of arguments were counted while doing this. For help and the default case, usage was called using argv[0] as the program name.

2. Walking the directory tree:
In search if the file was a directory, we instantiated a dirent sructure and used opendir() to open the directory. After checking to make sure the opendir() was succesful, we walked the directory by using readdir() (storing the result in the dirent struct) in a while loop and continuing until readdir returned NULL. For each item in the directory we checked if it was "." or ".." and excluded those files by using continue. We then created a new string to store the path, and used sprintf to write to it so could append the name of the file to root, the current path. Then we recursively called search on the path. This way all directories would be recursively walked.

3. Determining whether or not to print the path:
We put a print statement to print the path inside an if statement in execute, which executed under the condition (settings->print || !settings->exec\_argc). This way, it would first check if the print flag was specified, and it would always print if this was the case, but if it was not the case, it would check exec\_argc, which would be zero if -exec was not specified. So the print statement would execute if print and exec were both not specified. This way, if exec was specified without print, it would not print, but otherwise it would always print.


See the file output.txt for the output we are looking at as we answer the last two questions.

Differences between number and type of system calls between search and find:
We have noticed that search uses fewer types of system calls in general, and a big difference is that is uses many calls to lstat, but find does not use lstat at all. Both search and find use clone and wait the exact same number of times. Find also does more open and close than search, and more write and read, and it seems mostly more in general except for lstat. A lot of the system calls are the same between them, but find uses more kinds.

Surprises:
We were somewhat surprised that there were always more opens than closes in each trace. Also, we were surprised that there were a lot more system calls than we explicitly wrote and learned about. We are not sure if we are supposed to be surprised by this.


Contributions
-------------

We pair-programmed the entire assignment.
