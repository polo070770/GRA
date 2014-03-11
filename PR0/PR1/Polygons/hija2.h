#ifndef HIJA2_H
#define HIJA2_H
#include "primera.h"

namespace miespacio{
    class Hija2 : public Primera
    {
    public:
        Hija2();
        int getNum();
        void setValues(int x, int y);
    };
}
#endif // HIJA2_H
