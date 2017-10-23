#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <inttypes.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

/*
 * Function:	create_files
 * --------------------------
 * Use:		Takes a path and create "amount" of files on that path
 *			
 * Params:	path - path where to create file
 *		amount - number of files to create
 *
 * returns:	nothing
 */
void create_files(char path[],int amount);

/*
 * Function:	add_to_file
 * --------------------------
 * Use:		Adds a char to given file, at the moment
 *		its hardcoded to "a" for testing
 * 
 * Params:	fp - file for writing to
 *
 * returns:	nothing
 */
void add_to_file(FILE *fp);

/*
 * Function:	calculate_time
 * --------------------------
 * Use:		Create a timecheck at the current time
 *			
 * Params:	nothing
 *		
 * returns:	Current time in milliseconds
 */
double calculate_time();

/*
 * Function:	remove_files
 * --------------------------
 * Use:		Takes a path and remove "amount" of files on that path
 *			
 * Params:	path - path where to remove file
 *		amount - number of files to remove
 *		
 * returns:	nothing
 */
void remove_files(char path[],int amount);

/*
 * Function:	read_files
 * --------------------------
 * Use:		Take a path and read "amount" of files on that path
 *	
 * Params:	path - path where to read
 *		amount - number of files to read
 *
 * returns:	nothing
 */
void read_files(char path[],int amount);

/*
 * Function:	test1
 * --------------------------
 * Use:		test1 does 3 things before stopping:
 * 			Create 30 files with same size on same directory
 *			Read 30 files with same size on same directory
 *			Delete 30 files with same size on same directory
 *	
 * Params:	argum - argument for threads (what they should do)
 *
 * returns:	nothing
 */
void *test1(void *argum);

/*
 * Function:	test2
 * --------------------------
 * Use:		test2 does 3 things before stopping:
 *			Create 30 files with same size in 10 different directories(3 in each)
 *			Read 30 files with same size in 10 different directories(3 in each)
 *			Delete 30 files with same size in 10 different directories(3 in each)
 *	
 * Params:	argument for threads (what they should do)
 *
 * returns:	nothing
 */
void *test2(void *argum);

/*
 * Function:	test3
 * --------------------------
 * Use:		Checking how many files can be creating druing "testtime"
 *		Later removing all files.	
 *		
 * Params:	testtime - how long (in seconds) to create files in same directory
 *
 * returns:	nothing
 */
void *test3(int testtime);

/*
 * Function:	file_exists
 * --------------------------
 * Use:		Check if file exist
 *		if exist return true
 *		else return false
 *	
 * Params:	path - path for file
 *	
 * returns:	true or false
 */
bool file_exists(char path[]);
