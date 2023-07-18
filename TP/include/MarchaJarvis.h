#ifndef JARVIS_
#define JARVIS_

#include <iostream>
#include <string>
#include <math.h>
#include "Fecho.h"
#include "Ponto.h"
#include "Reta.h"

using namespace std;

int Auxiliar(const Fecho<Ponto> &f, int atual)
{
  int proximo = (atual + 1) % f.size();
  for (int i = 0; i < f.size(); i++)
  {
    if (i != atual)
    {
      double trajetoria = (f[i].pegaX() - f[atual].pegaX()) * (f[proximo].pegaY() - f[atual].pegaY()) - (f[i].pegaY() - f[atual].pegaY()) * (f[proximo].pegaX() - f[atual].pegaX());
      if (trajetoria > 0 || (trajetoria == 0 && (f[i].pegaX() - f[atual].pegaX()) * (f[i].pegaX() - f[atual].pegaX()) + (f[i].pegaY() - f[atual].pegaY()) * (f[i].pegaY() - f[atual].pegaY()) >
                                                    (f[proximo].pegaX() - f[atual].pegaX()) * (f[proximo].pegaX() - f[atual].pegaX()) + (f[proximo].pegaY() - f[atual].pegaY()) * (f[proximo].pegaY() - f[atual].pegaY())))
      {
        proximo = i;
      }
    }
  }
  return proximo;
}

Fecho<Ponto> MarchaJarvis(const Fecho<Ponto> &Jarvis_entrada)
{
  Fecho<Ponto> Resposta;
  int tamanho = Jarvis_entrada.size();
  int atual, proximo;
  int menor_y = Jarvis_entrada[0].pegaY();
  int inicial = 0;
  for (int i = 1; i < tamanho; i++)
  {
    int y = Jarvis_entrada[i].pegaY();

    // Escolhe o ponto mais baixo ou o mais à esquerda em caso de empate
    if ((y < menor_y) || (menor_y == y && (Jarvis_entrada[i].pegaX() < Jarvis_entrada[inicial].pegaX())))
    {
      menor_y = Jarvis_entrada[i].pegaY();
      inicial = i;
    }
  }
  // p0 será o ponto inicial
  Ponto p0 = Jarvis_entrada[inicial];
  // Acha o fecho convexo pelo algoritmo Marcha de Jarvis
  atual = inicial;
  int m = 0;
  while (m != 1)
  {
    Resposta.push_back(Jarvis_entrada[atual]);
    proximo = Auxiliar(Jarvis_entrada, atual);
    atual = proximo;
    if (atual == inicial)
      m++;
  }
  return Resposta;
}

#endif
