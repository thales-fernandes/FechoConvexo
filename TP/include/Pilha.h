#ifndef PILHA_
#define PILHA_

#include <iostream>

using namespace std;

template <typename Tipo>
class Pilha
{
public:
    Pilha() { tamanho = 0; };
    int GetTamanho() { return tamanho; };
    bool Vazia() { return tamanho == 0; };
    virtual void Empilha(Tipo item) = 0;
    virtual Tipo Desempilha() = 0;
    virtual void Limpa() = 0;

protected:
    int tamanho;
};

template <typename Tipo>
class PilhaArranjo : public Pilha<Tipo>
{
public:
    PilhaArranjo() : Pilha<Tipo>()
    {
        topo = -1;
    };
    void Empilha(Tipo item)
    {
        if (this->tamanho == MAXTAM)
            throw "A pilha está cheia!";
        topo++;
        itens[topo] = item;
        this->tamanho++;
    };
    Tipo Desempilha()
    {
        Tipo aux;
        if (this->tamanho == 0)
            throw "A pilha está vazia!";
        aux = itens[topo];
        topo--;
        this->tamanho--;
        return aux;
        ;
    };
    void Limpa()
    {
        topo = -1;
        this->tamanho = 0;
    };
    Tipo topov()
    {
        return itens[topo];
    };
    Tipo Segundo()
    {
        Tipo aux = this->Desempilha();
        Tipo segundo = this->topov();
        this->Empilha(aux);
        return segundo;
    };

private:
    int topo;
    static const int MAXTAM = 20000;
    Tipo itens[MAXTAM];
};

#endif