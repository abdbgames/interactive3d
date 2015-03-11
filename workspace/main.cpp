#include "stdafx.h"
#include "glutBegin.h"
#include "tute1.h"

void quit() { exit(EXIT_SUCCESS); }

int main(int argc, char **argv)
{
	kg::keyboardControl::setKeyPressed(KGkey_esc, "quit", quit);

	init(&argc, argv, new Tute1("Tutorial 1"));

	return EXIT_SUCCESS;
}
