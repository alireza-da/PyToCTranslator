# Python To C Translator
A Translator for converting python to a C script.

# Installation
Ubuntu
We included a makefile which compiles the c files and generates the Test.out file
The Test.out binary file could be executed using GCC, use your ubuntu terminal/bash in order to run the following commands If you encounter any errors, Try to restart from the first command of section “Compilation of Binary and Executable file”. 

# Ubuntu
Preinstallation:

  `` $ sudo apt install flex bison ``

Compilation of Binary and Executable file:

+ to delete the old Test.out : 

  `` $ make clean `` 

+ generate Test.out :

  `` $ make ``

+ execute Test.out with input python file test5.txt: 

  `` $ ./Test.out < test5.txt ``

+ finally you can test C file with the command :

  `` $ gcc output.c ``


# Windows
You can simply install Ubuntu WSL from the Microsoft store and run the above commands or you can download and install flex and bison and run them on cmd. However, the project wasn’t tested in this environment.



