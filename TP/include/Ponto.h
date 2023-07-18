#ifndef PONTO_
#define PONTO_
#include <iostream>

using namespace std;

class Ponto
{
private:
    double x;
    double y;

public:
    Ponto()
    {
        x = 0;
        y = 0;
    }

    Ponto(double varX, double varY) : x(varX), y(varY) {}

    double pegaX() const
    {
        return x;
    }

    double pegaY() const
    {
        return y;
    }

    void atribuiX(double varX)
    {
        x = varX;
    }

    void atribuiY(double varY)
    {
        y = varY;
    }

    ~Ponto() {}
};

#endif
