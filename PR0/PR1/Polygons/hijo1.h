#ifndef HIJO1_H
#define HIJO1_H
#include "primera.h"
namespace miespacio{
    class Hijo1 : public Primera // : protected Primera -> como minimo puclic a protected // : private Primera public i protected a private
    {
    public:
        Hijo1();
        int getNum();
        void setValues(int x, int y);
    };
}
#endif // HIJO1_H
