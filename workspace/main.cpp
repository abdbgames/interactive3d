#include "stdafx.h"
#include "glutBegin.h"
#include "tute2.h"
#include "tute1.h"

void quit() { exit(EXIT_SUCCESS); }

int main(int argc, char **argv)
{
	kg::keyboardControl::setKeyPressed(KGkey_esc, "quit", quit);

	init(&argc, argv, new Tute2("Tute2"));

	return EXIT_SUCCESS;
}
