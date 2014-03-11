#ifndef PRIMERA_H
#define PRIMERA_H


namespace miespacio {
    class Primera {
    protected:
        int *x, *y;
    public:
        Primera();
        Primera(int x, int y);
        ~Primera();
        void setValues(int x, int y);
        virtual int getNum() = 0; // se ha de igualar a 0, Un metodo abstracto hace que toda la clase sea abstracta
    };
}

#endif // PRIMERA_H
