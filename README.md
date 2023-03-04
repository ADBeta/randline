﻿# codelines

codelines counts the number of lines, and how many are code in singlefiles, multiple
files and directories, ignoring comments, blank or empty space.

It defaults to C/C++ styling but this can be changed via CLI options. 
The file input can be a list of files, a directory, or a single file. See --help 
for more information.

This program uses [TeFiEd](https://github.com/ADBeta/TeFiEd) for text handling,
and [CLIah](https://github.com/ADBeta/CLIah) for the Command line handling.

----
## Dependencies
This project only uses the std libraries and custom libs, so there are no external 
dependencies. 

## Compilation
#### Linux

## Usage

----
## TO-DO
* language handler header
* directory flags
* sometimes program miscalculates total and overflows itself.

## Changelog (Reminder for self)
* 0.0 - Initial setup
* 0.4 - basic functional model
* 0.6 - changed entire methodolgy. Stronger usage of TeFiEd
* 0.7 - Upgraded TeFiEd with replace
* 1.0 - Finished the main line counting and modification routines.
* 1.5 - First multi-file version finished

## Licence
<b> 2023 ADBeta </b>  
This software is under the GPL (GPL3.0), please see LICENCE for information
