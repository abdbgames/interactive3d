#ifndef frog_h
#define frog_h

#include "object.h"

struct FrogBase : public kg::Object
{
	FrogBase();
	virtual void start();
	virtual void update();
};

struct FrogBody : public kg::Object
{
	FrogBody();
	virtual void start();
	virtual void update();
};

struct FrogOuterLeg : public kg::Object
{
	FrogOuterLeg();
	virtual void start();
	virtual void update();
};

struct FrogMiddleLeg : public kg::Object
{
	FrogMiddleLeg();
	virtual void start();
	virtual void update();
};

struct FrogInnerLeg : public kg::Object
{
	FrogInnerLeg();
	virtual void start();
	virtual void update();
};

struct FrogOuterArm : public kg::Object
{
	FrogOuterArm();
	virtual void start();
	virtual void update();
};

struct FrogMiddleArm : public kg::Object
{
	FrogMiddleArm();
	virtual void start();
	virtual void update();
};

struct FrogInnerArm : public kg::Object
{
	FrogInnerArm();
	virtual void start();
	virtual void update();
};

struct FrogHead : public kg::Object
{
	FrogHead();
	virtual void start();
	virtual void update();
};

struct FrogMouth : public kg::Object
{
	FrogMouth();
	virtual void start();
	virtual void update();
};

struct FrogEye : public kg::Object
{
	FrogEye();
	virtual void start();
	virtual void update();
};

struct FrogPupil : public kg::Object
{
	FrogPupil();
	virtual void start();
	virtual void update();
};

struct FrogFinger : public kg::Object
{
	FrogFinger();
	virtual void start();
	virtual void update();
};

#endif /* frog_h */

