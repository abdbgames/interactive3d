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
use in Interactive3D

I had already written it, so it wasn't a
waste of time in my opinion ;) */

#include "stdafx.h"
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

	std::vector<KG_KeyType> keyboardControl::keyTrack;
	std::map<KG_KeyType, bool> keyboardControl::keyTrackP;
	std::map<KG_KeyType, bool> keyboardControl::keyTrackR;

	std::vector<KG_KeyType>::iterator keyboardControl::findElement(std::vector<KG_KeyType> &v, const KG_KeyType &key)
	{
		std::vector<KG_KeyType>::iterator i;

		for (i = v.begin(); i < v.end(); ++i)
		{
			if (*i == key)
				return i;
		}

		return i;
	}
	
	void keyboardControl::keyboardCallback(KG_KeyType key, int x, int y)
	{
		// Check if the key is in the held keys list:
		if (findElement(keyTrack, key) == keyTrack.end())
		{
			// It wasn't we tell the controller it was pressed for the first time:
			keyPress(key);

			// And add it to the list:
			keyTrack.push_back(key);

			// Add/set this as true in the single key press list:
			keyTrackP[key] = true;
		}
		else
		{
			// This means it is being pressed a consecutive time:
			std::map<KG_KeyType, bool>::iterator i = keyTrackP.find(key);

			// If it wasn't in our list don't worry about it:
			if (i == keyTrackP.end())
				return;
			// If it was and flagged as true, it's not ready to remove:
			else if (i->second)
				return;
			// And finally, we can remove it:
			else
				keyTrackP.erase(i);
		}
	}

	void keyboardControl::keyboardUpCallback(KG_KeyType key, int x, int y)
	{
		// We tell the controller this key was released here:
		keyRelease(key);

		// Find and remove it from our list:
		std::vector<KG_KeyType>::iterator i = findElement(keyTrack, key);

		// Remove element if element exists:
		if (i != keyTrack.end())
			keyTrack.erase(i);

		// Add/set this as true for our key release list:
		keyTrackR[key] = true;
	}

	void keyboardControl::keyBufferBegin()
	{
		// Run all pressed functions:
		for (unsigned int i = 0; i < keyTrack.size(); ++i)
			keyPressed(keyTrack[i]);

		// Remove remaining elements flagged as false in the key press list:
		for (std::map<KG_KeyType, bool>::iterator i = keyTrackP.begin(); i != keyTrackP.end(); )
		{
			// If it's true ignore it:
			if (i->second)
				++i;
			// Otherwise erase it:
			else
				keyTrackP.erase(i++);
		}

		// Same for our key release list:
		for (std::map<KG_KeyType, bool>::iterator i = keyTrackR.begin(); i != keyTrackR.end();)
		{
			// If it's true ignore it:
			if (i->second)
				++i;
			// Otherwise erase it:
			else
				keyTrackR.erase(i++);
		}
	}

	void keyboardControl::keyBufferEnd()
	{
		// We ran an update so set our key press list elements to false:
		for (std::map<KG_KeyType, bool>::iterator i = keyTrackP.begin(); i != keyTrackP.end(); ++i)
			i->second = false;

		// Same for our key release list:
		for (std::map<KG_KeyType, bool>::iterator i = keyTrackR.begin(); i != keyTrackR.end(); ++i)
			i->second = false;
	}

	bool keyboardControl::removeFunctionInNameList(voidNameMap &vnm, const std::string &fName)
	{
		// check if the fName exists:
		voidNameMap::iterator it = vnm.find(fName);

		// If it doesn't exist, we can't remove it:
		if (it == vnm.end())
		{
			std::printf("%s doesn't exist!\n", fName.c_str());
			return false;
		}

		// remove the function from the list based on iterator:
		vnm.erase(it);

		return true;
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

		// Our iterator value will have changed:
		it = vkm.find(key);
		
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
			std::printf("%c is not on the function list!\n", key);
			return;
		}

		// Remove the function:
		if (!removeFunctionInNameList(it->second, fName))
			std::printf("Above error created for %c key.\n", key);
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
		// CLEAR ALL:
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

	bool keyboardControl::onKeyPress(const KG_KeyType &key)
	{
		return (keyTrackP.find(key) != keyTrackP.end());
	}

	bool keyboardControl::onKeyPressed(const KG_KeyType &key)
	{
		return (findElement(keyTrack, key) != keyTrack.end());
	}

	bool keyboardControl::onKeyRelease(const KG_KeyType &key)
	{
		return (keyTrackR.find(key) != keyTrackR.end());
	}
}
