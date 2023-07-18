#ifndef INSERTION_
#define INSERTION_

#include <iostream>
#include <math.h>
#include "Fecho.h"
#include "Pilha.h"
#include "Ponto.h"
#include "Reta.h"

using namespace std;

void Troca_Insertion(Ponto &p1, Ponto &p2)
{
    Ponto temp = p1;
    p1 = p2;
    p2 = temp;
}

int Orienta_Insertion(const Ponto &pilha, const Ponto &q, const Ponto &r)
{
    // Checa o sentido tomado pelo segmento de reta entre dois pontos
    // quando se adiciona outro Ponto
    double valor = (q.pegaY() - pilha.pegaY()) * (r.pegaX() - q.pegaX()) - (q.pegaX() - pilha.pegaX()) * (r.pegaY() - q.pegaY());
    if (valor == 0)
    {
        return 0; // Pontos colineares
    }
    else if (valor > 0)
    {
        return 1; // Sentido horário (clockwise)
    }
    else
    {
        return 2; // Sentido anti-horário (counterclockwise)
    }
}

bool Compara_Insertion(const Ponto &p0, const Ponto &p1, const Ponto &p2)
{
    // Gera retas em relação a um p0 e as compara em termos de ângulo
    reta reta1(p0, p1);
    reta reta2(p0, p2);

    double angulo1 = reta1.Angulo();
    double angulo2 = reta2.Angulo();

    if (angulo1 != angulo2)
        return angulo1 < angulo2;

    double distancia1 = sqrt(pow(p1.pegaX() - p0.pegaX(), 2) + pow(p1.pegaY() - p0.pegaY(), 2));
    double distancia2 = sqrt(pow(p2.pegaX() - p0.pegaX(), 2) + pow(p2.pegaY() - p0.pegaY(), 2));

    return distancia1 < distancia2;
}

void insertionSort(Ponto *pontos, int tamanho, const Ponto &p0)
{
    int i, j;
    for (i = 0; i < tamanho; i++)
    {
        j = i;
        while ((j > 0) && (Compara_Insertion(p0, pontos[j], pontos[j - 1])))
        {
            Troca_Insertion(pontos[j], pontos[j - 1]);
            j--;
        }
    }
}

void Graham_Insertion(Ponto *pontos, int tamanho, Fecho<Ponto> &Resposta)
{
    int menor_y = pontos[0].pegaY();
    int inicial = 0;
    for (int i = 1; i < tamanho; i++)
    {
        int y = pontos[i].pegaY();

        // Escolhe o ponto mais baixo ou o mais à esquerda em caso de empate
        if ((y < menor_y) || (menor_y == y && (pontos[i].pegaX() < pontos[inicial].pegaX())))
        {
            menor_y = pontos[i].pegaY();
            inicial = i;
        }
    }
    // p0 será o ponto inicial
    Ponto p0 = pontos[inicial];
    // ordena pelo insertionSort
    insertionSort(pontos, tamanho, p0);
    // Acha o fecho convexo pela pilha do Scan de Graham
    PilhaArranjo<Ponto> pilha;
    pilha.Empilha(pontos[0]);
    pilha.Empilha(pontos[1]);
    for (int m = 2; m < tamanho; m++)
    {
        while (pilha.GetTamanho() > 1 && Orienta_Insertion(pilha.topov(), pontos[m], pilha.Segundo()) != 2)
        {
            pilha.Desempilha();
        }
        pilha.Empilha(pontos[m]);
    }
    // joga os pontos do fecho convexo dentro da estrutura Fecho Resposta
    while (!pilha.Vazia())
    {
        Resposta.push_back(pilha.Desempilha());
    }
}

#endif