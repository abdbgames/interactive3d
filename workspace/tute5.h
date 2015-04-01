#ifndef tute5_h
#define tute5_h

#include "tute.h"
#include "vectors.h"

class Tute5 : public Tute
{
public:
    Tute5(const char *name) : Tute(name) {}

    virtual void init();
    virtual void draw();
    virtual void update();
    virtual void end();

private:
    void drawAxis(const Vector3 &pos, const float &size);
};

#endif /* tute3_h */
