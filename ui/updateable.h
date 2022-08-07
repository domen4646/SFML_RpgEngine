#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include "drawablebase.h"

class Updateable : public DrawableBase
{
public:
    virtual bool acceptsInput() override;
    virtual void update(YIELD_SINK &sink) = 0;
};

#endif // UPDATEABLE_H
