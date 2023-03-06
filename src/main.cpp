/*******************************************************************************
* This file is part of randline, which will pick a random line from a file
* and print it to the terminal
*
* This project is under the GPL 3.0 Licence. Please see LICENCE for more info
* (c) 2023 ADBeta
*
* 04 March 23
* v1.0.2
*******************************************************************************/

#include <ctime> 
#include <iostream>

#include "TeFiEd.hpp"
#include "CLIah.hpp"

namespace message {
std::string shortHelp = "randline: invalid input. Try \"randline --help\" for \
more information.\n";
	
std::string longHelp = "Usage: randline [input file] [options]\n\n\
By default randline selects a single random line in a ASCII file and prints\n\
it to the command line.\n\n\
Options:\n\
-h, --help\t\tShow this help message\n\
-s, --seed\t\tSet the random seed\n\
-l, --lines\t\tChange how many lines get printed\n"; 

} //namespace message


int main(int argc, char *argv[]) {
	/*** Define CLIah Arguments ***********************************************/
	//CLIah::Config::verbose = true; //Set verbosity when match is found
	CLIah::Config::stringsEnabled = true; //Set arbitrary strings allowed
	
	CLIah::addNewArg(
		"Help",                 //Reference
		"--help",               //Primary match string
		CLIah::ArgType::flag,   //Argument type
		"-h"                    //Alias match string
    );
	
	//Change/Specify random seed
	CLIah::addNewArg(
		"Seed",
		"--seed",
		CLIah::ArgType::subcommand,
		"-s"
    );
    
    //how many lines to print
    CLIah::addNewArg(
		"LineCount",
		"--lines",
		CLIah::ArgType::subcommand,
		"-l"
    );
    
    //Should any lines be excluded
    CLIah::addNewArg(
		"ExcludeLines",
		"--exclude",
		CLIah::ArgType::subcommand,
		"-e"
    );
    
	/*** User Argument handling ***********************************************/
	//Get CLIah to scan the CLI Args
	CLIah::analyseArgs(argc, argv);

	if(CLIah::isDetected("Help")) {
		std::cout << message::longHelp;
	}

	//Random Seed Generation
	if(CLIah::isDetected("Seed")) {
		//Convert the seed string to an unsigned int and use it to seed
		unsigned int seedInt = std::stoi(CLIah::getSubstring("Seed"));
		srand(seedInt);
	} else {
		//Generate random seed based on the time (Unix)
		srand((unsigned int)time(0)); 
	}

	//Line number exclusions
	//if( CLIah::isDetected("


	/*** File handling ********************************************************/
	//Create TeFiEd object using -ONLY- the first CLIah string
	if(CLIah::stringVector.size() == 0) {
		std::cout << message::shortHelp;
		return 1;
	}
	
	//Create a TeFiEd object for the input file
	TeFiEd inFile( CLIah::stringVector.at(0).string );
	//Read the input file into RAM. Exit if fail
	if(inFile.read() != 0) return 1;
	
	/*** Line & output handling ***********************************************/
	//Generate a random number from 1 to the line count of file.
	//Check if it has been excluded 
	size_t randLineNum = (rand() % inFile.lines()) + 1;
	
	//Print output lines (multiple if selected)
	size_t linesToPrint = 1;
	
	//If CLI has specified how many lines to print, limit to 1 minimum
	if(CLIah::isDetected("LineCount")) {
		linesToPrint = std::stoi(CLIah::getSubstring("LineCount"));
		
		if(linesToPrint < 1) linesToPrint = 1;
	}
	
	for(size_t printLine = 0; printLine < linesToPrint; ++printLine) {
		size_t currentLine = printLine + randLineNum;
		
		//If the currentLine overruns the file lines, exit
		if(currentLine > inFile.lines()) return 0;
		
		//Print the current line
		std::cout << currentLine << " | " << inFile.getLine(currentLine) 
		          << std::endl;
	}
	
	return 0;
}
