/*
 * main.c
 *
 *  Created on: Jan 11, 2014
 *      Author: aeon29
 */

/*
 * arguments in command line
 */
#include "tp.h"

int main(int argc, char *argv[]){
	if(argc != 3) {
		printf("Usage : <tsParser> <filename> <table>");
		return 1;
	}
	int table = atoi(argv[2]);
	if(table>15 || table <0){
		printf("Enter valid table number");
		return 1;
	}
	setTS(argv[1]);
	verbosePacket(table);

	//exit
	exit(0);
}


