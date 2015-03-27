#include "stdafx.h"
#include "glutBegin.h"
#include "tute3.h"
#include "tute2.h"
#include "tute1.h"
#include "ass1.h"

// Exit function:
void quit() { exit(EXIT_SUCCESS); }

// Functions to start program:
typedef void(*StartF)(int*, char**, const char*);
void t1(int *argc, char **argv, const char *in) {
	init(argc, argv, new Tute1(in)); }
void t2(int *argc, char **argv, const char *in) {
	init(argc, argv, new Tute2(in)); }
void t3(int *argc, char **argv, const char *in) {
	init(argc, argv, new Tute3(in)); }
void a1(int *argc, char **argv, const char *in) {
	init(argc, argv, new Ass1(in)); }

/* To see the code for any tute or assignment, just go to it's
 * respective .cpp file.
 * For instance: ass1.cpp for Assignment 1. */

int main(int argc, char **argv)
{
	// Set up exit keystrokes:
	kg::keyboardControl::setKeyRelease(KGkey_esc, "quit", quit);
	kg::keyboardControl::setKeyRelease(KGkey_q, "q", quit);

	/* I wrote this input controller because I was bored and curious.
	 * it also speeds up switching between different versions of
	 * the program, so it was worth it... */

	// Map to lookup which program to start based on input:
	std::map<std::string, StartF> start;

	// Input options:
	start["tute1"] = t1;
	start["tutorial1"] = t1;
	start["Tute1"] = t1;
	start["Tutorial1"] = t1;
	start["tute2"] = t2;
	start["tutorial2"] = t2;
	start["Tute2"] = t2;
	start["Tutorial2"] = t2;
	start["tute3"] = t3;
	start["tutorial3"] = t3;
	start["Tute3"] = t3;
	start["Tutorial3"] = t3;
	start["ass1"] = a1;
	start["assignment1"] = a1;
	start["Ass1"] = a1;
	start["Assignment1"] = a1;

	// Initialise Engine based on first detected input:
	std::map<std::string, StartF>::iterator s =
		start.find(std::string(argv[argc - 1]));
	if (s != start.end())
		// An option in our options map was found, so run that:
		s->second(&argc, argv, s->first.c_str());
	else
		// No option was found so run the default:
		a1(&argc, argv, "No input given, running default");

	// Quit:
	return EXIT_SUCCESS;
}
