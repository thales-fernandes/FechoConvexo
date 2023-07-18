#ifndef LINEAR_
#define LINEAR_
#include <iostream>
#include <math.h>
#include "Fecho.h"
#include "Pilha.h"
#include "Ponto.h"
#include "Reta.h"
#include "Graham_Merge.h"

using namespace std;

void Troca_Radix(Ponto &p1, Ponto &p2)
{
  Ponto temp = p1;
  p1 = p2;
  p2 = temp;
}

int getMenorY(Ponto *pontos, int tamanho)
{
  // retorna o ponto com menor coordenada y em um fecho
  Ponto p(pontos[0]);
  int s = 0;
  for (int i = 1; i < tamanho; i++)
  {
    if (p.pegaY() > pontos[i].pegaY())
    {
      p.atribuiX(pontos[i].pegaX());
      p.atribuiY(pontos[i].pegaY());
      s = i;
    }
  }
  return s;
}

int Orienta_Radix(Ponto p, Ponto q, Ponto r)
{
  // checa o sentido tomado pelo segmento de reta entre dois pontos
  // quando se adiciona outro Ponto
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

bool Compara_Radix(Ponto p0, Ponto p1, Ponto p2)
{
  // gera retas em relação a um p0 e as compara termos de angulo
  reta r1(p0, p1), r2(p0, p2);
  if (r2.Angulo() > r1.Angulo())
    return true;
  else
    return false;
}

void radixSort(Ponto *pontos, int tamanho, Ponto p0)
{
  if (tamanho > 10)
  { // Se a entrada do programa tem mais que 10 pontos é possível fazer o radix já que é usado 10 buckets
    int i;
    Ponto *b = new Ponto[tamanho];
    Ponto maior = pontos[0];
    int parametro = 1;
    for (i = 0; i < tamanho; i++)
    {
      b[i] = Ponto(0, 0);
      if (Compara_Radix(p0, maior, pontos[i]))
      {
        maior = pontos[i];
      }
    }
    while (int(100000 * reta(p0, maior).Angulo() / parametro) > 0)
    {
      int *bucket = new int[10]();
      for (i = 0; i < tamanho; i++)
      {
        bucket[int(100000 * reta(p0, pontos[i]).Angulo() / parametro) % 10]++;
      }
      for (i = 1; i < 10; i++)
      {
        bucket[i] += bucket[i - 1];
      }
      for (i = tamanho - 1; i >= 0; i--)
      {
        b[--bucket[int(100000 * reta(p0, pontos[i]).Angulo() / parametro) % 10]] = pontos[i];
      }
      for (i = 0; i < tamanho; i++)
      {
        pontos[i] = b[i];
      }
      parametro *= 10;
    }
    delete[] b;
  }
  else
  {                           // Se a entrada do programa não tiver mais que 10 pontos, iremos fazer um bucketSort com o mergeSort com apenas um bucket, já que a entrada é pequena para ser dividida em 10 buckets
    const int numBuckets = 1; // Apenas 1 bucket
    Ponto *bucket = new Ponto[tamanho];
    for (int i = 0; i < tamanho; i++)
    {
      bucket[i].atribuiX(pontos[i].pegaX());
      bucket[i].atribuiY(pontos[i].pegaY());
    }
    mergeSort(bucket, p0, 0, tamanho - 1);

    for (int i = 0; i < tamanho; i++)
    {
      pontos[i].atribuiX(bucket[i].pegaX());
      pontos[i].atribuiY(bucket[i].pegaY());
    }
    delete[] bucket;
  }
}

void Graham_Linear(Ponto *pontos, int tamanho, Fecho<Ponto> &r_)
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
  Troca_Radix(pontos[0], pontos[inicial]);
  // ordena os pontos pelo método linear
  radixSort(pontos, tamanho, p0);
  // Acha o fecho convexo pela pilha do Scan de Graham
  PilhaArranjo<Ponto> pilha;
  pilha.Empilha(pontos[0]);
  pilha.Empilha(pontos[1]);
  for (int m = 2; m < tamanho; m++)
  {
    while (pilha.GetTamanho() > 1 && Orienta_Radix(pilha.topov(), pontos[m], pilha.Segundo()) != 2)
    {
      pilha.Desempilha();
    }
    pilha.Empilha(pontos[m]);
  }
  // joga os pontos do fecho convexo dentro da estrutura Fecho Resposta
  while (pilha.GetTamanho() > 0)
  {
    r_.push_back(pilha.Desempilha());
  }
}
#endif
