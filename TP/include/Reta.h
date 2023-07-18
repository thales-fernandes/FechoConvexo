#ifndef RETA_
#define RETA_
#include <iostream>
#include "Ponto.h"
#include <math.h>

using namespace std;

class reta
{
private:
    Ponto comeco;
    Ponto final;

public:
    reta(Ponto com, Ponto fin) : comeco(com), final(fin) {}

    double Angulo() const
    {
        double ab = final.pegaX() - comeco.pegaX();
        double cd = final.pegaY() - comeco.pegaY();
        double retorno = atan2(cd, ab) * 180.0 / M_PI;
        if (retorno < 0)
            retorno = 360.0 + retorno;
        return retorno;
    }

    double Comprimento() const
    {
        double ab = final.pegaX() - comeco.pegaX();
        double cd = final.pegaY() - comeco.pegaY();
        double retorno = sqrt(pow(ab, 2) + pow(cd, 2));
        return retorno;
    }

    ~reta() {}
};

#endif
