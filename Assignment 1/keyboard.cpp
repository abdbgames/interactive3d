/*
___________________________________

KG Engine Keyboard library
___________________________________

Written by Alastair Bilby
Edited by:

___________________________________

Description:

This library handles user input.
It allows the user to effectivly
attach as many function calls they
want to any keyboard or mouse input
with a name, so that it can be
easily accessed for deletion if
needed. It will not handle any
strings on an update, or to call
a key press (as this would slow
things down significantly!)
___________________________________

Knoob Group 2013,
All rights reserved.
___________________________________
*/

/* Please note this file has been modified for
use in Interactive3D */

#include "keyboard.h"

namespace kg
{
	voidKeyMap keyboardControl::functionList;
	voidKeyMap keyboardControl::functionRList;
	voidKeyMap keyboardControl::functionPList;
	voidNameMap keyboardControl::mouseL;
	voidNameMap keyboardControl::mouseR;
	voidNameMap keyboardControl::mouseM;
	voidNameMap keyboardControl::RmouseL;
	voidNameMap keyboardControl::RmouseR;
	voidNameMap keyboardControl::RmouseM;
	voidNameMap keyboardControl::PmouseL;
	voidNameMap keyboardControl::PmouseR;
	voidNameMap keyboardControl::PmouseM;
	std::map<KG_KeyType, bool> keyboardControl::keyTrack;

	void keyboardControl::keyboardCallback(KG_KeyType key, int x, int y)
	{
		// It is garunteed we need to run "pressed" on this callback:
		keyPressed(key);

		// If our key is already flagged as being pressed last update:
		if (keyTrack.find(key) != keyTrack.end())
			keyTrack[key] = true;
	}

	void keyboardControl::keyBufferEnd()
	{
		/* makes sure we are ready to scoop up key inputs before the next update function is called */

		// To call at the end of an update:
		for (std::map<KG_KeyType, bool>::iterator it = keyTrack.begin(); it != keyTrack.end(); ++it)
			it->second = false;
	}

	void keyboardControl::keyBufferBegin()
	{
		/* looks over what happened before we called update and works respectivly */

		// To call at the start of an update:
		for (std::map<KG_KeyType, bool>::iterator it = keyTrack.begin(); it != keyTrack.end(); ++it)
		{
			if (!it->second)
			{
				// This key was not pressed this update so was thus released:
				keyRelease(it->first);
				// Free the key from the list so next time we see it, it counts as a press:
				keyTrack.erase(it);
			}
		}
	}

	bool keyboardControl::removeFunctionInNameList(voidNameMap &vnm, const const std::string &fName)
	{
		// check if the fName exists:
		voidNameMap::iterator it = vnm.find(fName);

		// If it doesn't exist, we can't remove it:
		if (it == vnm.end())
		{
			printf("%s doesn't exist!\n");
			return false;
		}

		// remove the function from the list based on iterator:
		vnm.erase(it);
	}

	void keyboardControl::runAllFunctionsForName(voidNameMap &vnm)
	{
		// iterate through all functions, run them all if not NULL:
		for (voidNameMap::iterator it = vnm.begin(); it != vnm.end(); ++it)
			if (it->second)
				it->second();
	}

	void keyboardControl::addFunctionToKeyList(voidKeyMap &vkm, const KG_KeyType &key, const std::string &fName, VoidF function)
	{
		// Search for if our key already exists:
		voidKeyMap::iterator it = vkm.find(key);

		// We need to make it if it doesn't exist:
		if (it == vkm.end())
			// This will push to the back so we can keep the it value:
			vkm[key] = voidNameMap();
		
		// Now we add the key, if it already exists it will overwrite so be careful:
		it->second[fName] = function;
	}

	void keyboardControl::removeFunctionInKeyList(voidKeyMap &vkm, const KG_KeyType &key, const std::string &fName)
	{
		// Search for if our key already exists:
		voidKeyMap::iterator it = vkm.find(key);

		// We can't do anything if it doesn't:
		if (it == vkm.end())
		{
			printf("%c is not on the function list!\n", key);
			return;
		}

		// Remove the function:
		if (!removeFunctionInNameList(it->second, fName))
			printf("Above error created for %c key.\n", key);
	}

	void keyboardControl::runAllFunctionsForKey(voidKeyMap &vkm, const KG_KeyType &key)
	{
		// Search for if our key already exists:
		voidKeyMap::iterator it = vkm.find(key);

		// Disregard if key not found:
		if (it == vkm.end())
			return;

		// Run all functions attached to that key:
		runAllFunctionsForName(it->second);
	}
	
	void keyboardControl::setKeyPress(const KG_KeyType &key, const std::string &fName, VoidF function)
	{
		addFunctionToKeyList(functionPList, key, fName, function);
	}

	void keyboardControl::breakKeyPress(const KG_KeyType &key, const std::string &fName)
	{
		removeFunctionInKeyList(functionPList, key, fName);
	}

	void keyboardControl::setKeyPressed(const KG_KeyType &key, const std::string &fName, VoidF function)
	{
		addFunctionToKeyList(functionList, key, fName,  function);
	}

	void keyboardControl::breakKeyPressed(const KG_KeyType &key, const std::string &fName)
	{
		removeFunctionInKeyList(functionList, key, fName);
	}

	void keyboardControl::keyPress(const KG_KeyType &key)
	{
		runAllFunctionsForKey(functionPList, key);
	}

	void keyboardControl::keyPressed(const KG_KeyType &key)
	{
		runAllFunctionsForKey(functionList, key);
	}

	void keyboardControl::setKeyRelease(const KG_KeyType &key, const std::string &fName, VoidF function)
	{
		addFunctionToKeyList(functionRList, key, fName, function);
	}

	void keyboardControl::breakKeyRelease(const KG_KeyType &key, const std::string &fName)
	{
		removeFunctionInKeyList(functionRList, key, fName);
	}

	void keyboardControl::keyRelease(const KG_KeyType &key)
	{
		runAllFunctionsForKey(functionRList, key);
	}

	void keyboardControl::clearKeyFunctions()
	{
		// Clear the lists:
		functionRList.clear();
		functionPList.clear();
		functionList.clear();
	}

	void keyboardControl::clearMouseFunctions()
	{
		// Set all to NULL:
		mouseL.clear();
		mouseR.clear();
		mouseM.clear();
		RmouseL.clear();
		RmouseR.clear();
		RmouseM.clear();
		PmouseL.clear();
		PmouseR.clear();
		PmouseM.clear();
	}

	void keyboardControl::setMousePressL(const std::string &fName, VoidF function)
	{
		// Set the function for the name, this will overwrite so be careful:
		mouseL[fName] = function;
	}

	void keyboardControl::setMousePressR(const std::string &fName, VoidF function)
	{
		// Set the function for the name, this will overwrite so be careful:
		mouseR[fName] = function;
	}

	void keyboardControl::setMousePressM(const std::string &fName, VoidF function)
	{
		// Set the function for the name, this will overwrite so be careful:
		mouseM[fName] = function;
	}

	void keyboardControl::setMouseReleaseL(const std::string &fName, VoidF function)
	{
		// Set the function for the name, this will overwrite so be careful:
		RmouseL[fName] = function;
	}

	void keyboardControl::setMouseReleaseR(const std::string &fName, VoidF function)
	{
		// Set the function for the name, this will overwrite so be careful:
		RmouseR[fName] = function;
	}

	void keyboardControl::setMouseReleaseM(const std::string &fName, VoidF function)
	{
		// Set the function for the name, this will overwrite so be careful:
		RmouseM[fName] = function;
	}

	void keyboardControl::setMousePressedL(const std::string &fName, VoidF function)
	{
		// Set the function for the name, this will overwrite so be careful:
		PmouseL[fName] = function;
	}

	void keyboardControl::setMousePressedR(const std::string &fName, VoidF function)
	{
		// Set the function for the name, this will overwrite so be careful:
		PmouseR[fName] = function;
	}

	void keyboardControl::setMousePressedM(const std::string &fName, VoidF function)
	{
		// Set the function for the name, this will overwrite so be careful:
		PmouseM[fName] = function;
	}

	void keyboardControl::breakMousePressL(const std::string &fName)
	{
		// Remove function at name:
		removeFunctionInNameList(mouseL, fName);
	}

	void keyboardControl::breakMousePressR(const std::string &fName)
	{
		// Remove function at name:
		removeFunctionInNameList(mouseR, fName);
	}

	void keyboardControl::breakMousePressM(const std::string &fName)
	{
		// Remove function at name:
		removeFunctionInNameList(mouseM, fName);
	}

	void keyboardControl::breakMouseReleaseL(const std::string &fName)
	{
		// Remove function at name:
		removeFunctionInNameList(RmouseL, fName);
	}

	void keyboardControl::breakMouseReleaseR(const std::string &fName)
	{
		// Remove function at name:
		removeFunctionInNameList(RmouseR, fName);
	}

	void keyboardControl::breakMouseReleaseM(const std::string &fName)
	{
		// Remove function at name:
		removeFunctionInNameList(RmouseM, fName);
	}

	void keyboardControl::breakMousePressedL(const std::string &fName)
	{
		// Remove function at name:
		removeFunctionInNameList(PmouseL, fName);
	}

	void keyboardControl::breakMousePressedR(const std::string &fName)
	{
		// Remove function at name:
		removeFunctionInNameList(PmouseR, fName);
	}

	void keyboardControl::breakMousePressedM(const std::string &fName)
	{
		// Remove function at name:
		removeFunctionInNameList(PmouseM, fName);
	}

	void keyboardControl::mouseLPress()
	{
		runAllFunctionsForName(mouseL);
	}

	void keyboardControl::mouseRPress()
	{
		runAllFunctionsForName(mouseR);
	}

	void keyboardControl::mouseMPress()
	{
		runAllFunctionsForName(mouseM);
	}

	void keyboardControl::mouseLRelease()
	{
		runAllFunctionsForName(RmouseL);
	}

	void keyboardControl::mouseRRelease()
	{
		runAllFunctionsForName(RmouseR);
	}

	void keyboardControl::mouseMRelease()
	{
		runAllFunctionsForName(RmouseM);
	}

	void keyboardControl::mouseLPressed()
	{
		runAllFunctionsForName(PmouseL);
	}

	void keyboardControl::mouseRPressed()
	{
		runAllFunctionsForName(PmouseR);
	}

	void keyboardControl::mouseMPressed()
	{
		runAllFunctionsForName(PmouseM);
	}
}