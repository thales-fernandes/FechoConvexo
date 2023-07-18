#ifndef MERGE_
#define MERGE_

#include <iostream>
#include <math.h>
#include "Fecho.h"
#include "Pilha.h"
#include "Ponto.h"
#include "Reta.h"

using namespace std;

int Orienta_Merge(const Ponto &p, const Ponto &q, const Ponto &r)
{
    // Checa o sentido tomado pelo segmento de reta entre dois pontos quando se adiciona outro ponto
    double valor = (q.pegaY() - p.pegaY()) * (r.pegaX() - q.pegaX()) - (q.pegaX() - p.pegaX()) * (r.pegaY() - q.pegaY());
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

bool Compara_Merge(const Ponto &p0, const Ponto &p1, const Ponto &p2)
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

void merge(Ponto Merge_entrada[], const Ponto &p0, int esq, int mid, int dir)
{
    int i, j, k;
    int n1 = mid - esq + 1;
    int n2 = dir - mid;
    Ponto L[n1];
    Ponto R[n2];
    for (i = 0; i < n1; i++)
        L[i] = Merge_entrada[esq + i];
    for (j = 0; j < n2; j++)
        R[j] = Merge_entrada[mid + 1 + j];
    i = 0;
    j = 0;
    k = esq;
    while (i < n1 && j < n2)
    {
        if (Compara_Merge(p0, L[i], R[j]))
        {
            Merge_entrada[k] = L[i];
            i++;
        }
        else
        {
            Merge_entrada[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        Merge_entrada[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        Merge_entrada[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Ponto Merge_entrada[], const Ponto &p0, int esq, int dir)
{
    if (esq < dir)
    {
        int mid = esq + (dir - esq) / 2;
        mergeSort(Merge_entrada, p0, esq, mid);
        mergeSort(Merge_entrada, p0, mid + 1, dir);
        merge(Merge_entrada, p0, esq, mid, dir);
    }
}

void Graham_Merge(const Ponto Merge_entrada[], int tamanho, Fecho<Ponto> &Resposta)
{
    int menor_y = Merge_entrada[0].pegaY();
    int inicial = 0;
    for (int i = 1; i < tamanho; i++)
    {
        int y = Merge_entrada[i].pegaY();

        // Escolhe o ponto mais baixo ou o mais à esquerda em caso de empate
        if ((y < menor_y) || (menor_y == y && (Merge_entrada[i].pegaX() < Merge_entrada[inicial].pegaX())))
        {
            menor_y = Merge_entrada[i].pegaY();
            inicial = i;
        }
    }
    // p0 será o ponto inicial
    Ponto p0 = Merge_entrada[inicial];
    Ponto sortedPoints[tamanho];
    for (int i = 0; i < tamanho; i++)
    {
        sortedPoints[i] = Merge_entrada[i];
    }
    // ordena pelo mergeSort
    mergeSort(sortedPoints, p0, 0, tamanho - 1);
    // Acha o fecho convexo pela pilha do Scan de Graham
    PilhaArranjo<Ponto> pilha;
    pilha.Empilha(sortedPoints[0]);
    pilha.Empilha(sortedPoints[1]);
    for (int m = 2; m < tamanho; m++)
    {
        while (pilha.GetTamanho() > 1 && Orienta_Merge(pilha.topov(), sortedPoints[m], pilha.Segundo()) != 2)
        {
            pilha.Desempilha();
        }
        pilha.Empilha(sortedPoints[m]);
    }
    // joga os pontos do fecho convexo dentro da estrutura Fecho Resposta
    while (!pilha.Vazia())
    {
        Resposta.push_back(pilha.Desempilha());
    }
}

#endif
