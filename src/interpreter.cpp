#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>

void help() {
	std::cout << "Use $ bf filename.bf to interpret a file\n";
}

std::string::iterator prev_matching_bracket(std::string::iterator it) {
	// bracket depth relative to current bracket
	int depth = 0;
	while(true) {
		it--;
		char c = *it;
		// entering brackets inside matching bracket pair, thus adding 1 to depth
		if(c == ']') depth++;
		// correct dpeth and opening bracket -> matching opening bracket
		if(c == '[' && depth == 0) return it;
		// incorrect depth and opening bracket -> brackets inside the bracket pair we're looking for
		else if(c == '[' && depth != 0) depth--;
	}
}

std::string::iterator next_matching_bracket(std::string::iterator it) {
	// bracket depth relative to current bracket
	int depth = 0;
	while(true) {
		it++;
		char c = *it;
		// entering brackets inside matching bracket pair, thus adding 1 to depth
		if(c == '[') depth++;
		// correct dpeth and opening bracket -> matching opening bracket
		if(c == ']' && depth == 0) return it;
		// incorrect depth and opening bracket -> brackets inside the bracket pair we're looking for
		else if(c == ']' && depth != 0) depth--;
	}
}

int interpret(char* filepath) {
	// allocate array and clear it
	char arr[30000];
	memset(&arr[0], 0, sizeof(arr));
	// current cell that is being read from/written to
	int cell = 0;

	// open file
	std::cout << "Opening file " << filepath << "\n";
	std::ifstream stream(filepath);
	
	// check for successful open
	if(!stream.is_open()) {
		std::cout << "error: file could not be opened (does it exist)\n";
		return -1;
	}

	// read entire file and save in memory
	std::stringstream buffer;
	buffer << stream.rdbuf();
	std::string code = buffer.str();
	stream.close();

	for (std::string::iterator it = code.begin(); it != code.end();) {
		char c = *it;
		switch(c) {
			case '>':
				cell++;
				break;
			case '<':
				cell--;
				break;
			case '+':
				arr[cell]++;
				break;
			case '-':
				arr[cell]--;
				break;
			case '.':
				putc(arr[cell], stdout);
				break;
			case ',':
				arr[cell] = getc(stdin);
				break;
			case '[':
				// go to command after matching ']'
				if(arr[cell] == 0) {
					it = next_matching_bracket(it);
				}
				break;
			case ']':
				// go back to matching '['
				if(arr[cell] != 0) {
					it = prev_matching_bracket(it);
				}
				break;
		}
		it++;
	}

	return 0;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		help();
		return -1;
	}
	return interpret(argv[1]);
}
