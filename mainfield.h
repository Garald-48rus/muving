#ifndef MAINFIELD_H
#define MAINFIELD_H

#include "field.h"

class mainField: public field
{
public:
    mainField();

private:
    virtual void init_cells() override;
};

#endif // MAINFIELD_H
