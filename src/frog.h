#ifndef frog_h
#define frog_h

#include "object.h"

struct FrogFinger : public kg::Object
{
	FrogFinger();
	virtual void start();
	virtual void update();
};

struct FrogOuterLeg : public kg::Object
{
	FrogOuterLeg();
	virtual void start();
	virtual void update();

	FrogFinger *m_fLeft, *m_fMid, *m_fRight;
};

struct FrogMiddleLeg : public kg::Object
{
	FrogMiddleLeg();
	virtual void start();
	virtual void update();

	FrogOuterLeg *m_child;
};

struct FrogInnerLeg : public kg::Object
{
	FrogInnerLeg();
	virtual void start();
	virtual void update();

	FrogMiddleLeg *m_child;
};

struct FrogOuterArm : public kg::Object
{
	FrogOuterArm();
	virtual void start();
	virtual void update();

	FrogFinger *m_fLeft, *m_fMid, *m_fRight;
};

struct FrogMiddleArm : public kg::Object
{
	FrogMiddleArm();
	virtual void start();
	virtual void update();

	FrogOuterArm *m_child;
};

struct FrogInnerArm : public kg::Object
{
	FrogInnerArm();
	virtual void start();
	virtual void update();

	FrogMiddleArm *m_child;
};

struct FrogMouth : public kg::Object
{
	FrogMouth();
	virtual void start();
	virtual void update();
};

struct FrogPupil : public kg::Object
{
	FrogPupil();
	virtual void start();
	virtual void update();
};

struct FrogEye : public kg::Object
{
	FrogEye();
	virtual void start();
	virtual void update();

	FrogPupil *m_pupil;
};

struct FrogHead : public kg::Object
{
	FrogHead();
	virtual void start();
	virtual void update();

	FrogEye *m_eyeLeft, *m_eyeRight;
	FrogMouth *m_mouthLower, *m_mouthUpper;
};

struct FrogBody : public kg::Object
{
	FrogBody();
	virtual void start();
	virtual void update();

	FrogHead *m_head;
	FrogInnerLeg *m_legLeft, *m_legRight;
	FrogInnerArm *m_armLeft, *m_armRight;
};

struct FrogBase : public kg::Object
{
	FrogBase();
	virtual void start();
	virtual void update();

	FrogBody *m_body;
};

#endif /* frog_h */
