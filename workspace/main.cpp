#include "stdafx.h"
#include "glutBegin.h"
#include "tute3.h"
#include "tute2.h"
#include "tute1.h"

// Exit function:
void quit() { exit(EXIT_SUCCESS); }

int main(int argc, char **argv)
{
	// Set up exit keystrokes:
	kg::keyboardControl::setKeyRelease(KGkey_esc, "quit", quit);
	kg::keyboardControl::setKeyRelease(KGkey_q, "q", quit);

	// Check if we wish to target a specific tute class:
	std::string test = (argc > 1) ? argv[2] : "";

	// Initialise Engine based on first detected input:
	if (test == "")
		init(&argc, argv, new Tute3("No input given, running default!"));
	else if (test == "tute1")
		init(&argc, argv, new Tute1("Tutorial 1"));
	else if (test == "tute2")
		init(&argc, argv, new Tute2("Tutorial 2"));
	else if (test == "tute3")
		init(&argc, argv, new Tute1("Tutorial 3"));

	// Quit:
	return EXIT_SUCCESS;
}
