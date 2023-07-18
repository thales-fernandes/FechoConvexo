#include <iostream>
#include <string>
#include <sstream>
#include "Fecho.h"
#include "MarchaJarvis.h"
#include "Pilha.h"
#include "Graham_Merge.h"
#include "Graham_Insertion.h"
#include <chrono>
#include <iomanip>
#include <cstdint>
#include <fstream>
#include "Graham_Linear.h"
#include "Ponto.h"
#include "Reta.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[])
{
    // abre o arquivo
    string nomeArquivo = argv[1];
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open())
    {   // Erro de leitura de arquivo
        cout << "O arquivo especificado para leitura não existe." << endl;
        return 0;
    }
    string entrada, x, y;
    // As estruturas Fecho que armazenam o fecho convexo resultante são criadas
    Fecho<Ponto> Merge_saida;
    Fecho<Ponto> Jarvis_saida;
    Fecho<Ponto> Insertion_saida;
    Fecho<Ponto> Linear_saida;
    Ponto aux;
    double x1, y1;
    Fecho<Ponto> Jarvis_entrada;
    // Lê o arquivo de entrada e armazena os pontos
    while (getline(arquivo, entrada))
    {
        stringstream ss(entrada);
        ss >> x >> y;
        x1 = stod(x);
        y1 = stod(y);
        Ponto p(x1, y1);
        Jarvis_entrada.push_back(p);
    }
    arquivo.close();
    int count = Jarvis_entrada.size();
    if (count < 3)
    {   //Erro de quantidade de pontos na entrada
        cout << "Não é possível fazer um fecho convexo com menos de 3 pontos." << endl;
        return 0;
    }
    Ponto *Merge_entrada = new Ponto[count];
    Ponto *Insertion_entrada = new Ponto[count];
    Ponto *Linear_entrada = new Ponto[count];
    for (int c = 0; c < count; c++)
    {
        Merge_entrada[c].atribuiX(Jarvis_entrada[c].pegaX());
        Merge_entrada[c].atribuiY(Jarvis_entrada[c].pegaY());
        Linear_entrada[c].atribuiX(Jarvis_entrada[c].pegaX());
        Linear_entrada[c].atribuiY(Jarvis_entrada[c].pegaY());
        Insertion_entrada[c].atribuiX(Jarvis_entrada[c].pegaX());
        Insertion_entrada[c].atribuiY(Jarvis_entrada[c].pegaY());
    }
    auto t_jarvis = chrono::high_resolution_clock::now();
    Jarvis_saida = MarchaJarvis(Jarvis_entrada);
    auto t_jarvisf = chrono::high_resolution_clock::now();
    if (Jarvis_saida.size() < 3)
    {   // Erro de pontos colineares
        cout << "Não há pelo menos 3 pontos não colineares na entrada para realizar o fecho convexo." << endl;
        return 0;
    }
    cout << "FECHO CONVEXO:" << endl;
    for (int i = 0; i < Jarvis_saida.size(); i++)
    {
        std::cout << Jarvis_saida[i].pegaX() << " " << Jarvis_saida[i].pegaY() << endl;
    }
    auto t_merge = chrono::high_resolution_clock::now();
    Graham_Merge(Merge_entrada, count, Merge_saida);
    auto t_mergef = chrono::high_resolution_clock::now();
    // Se quiser imprimir a saída do Graham_Merge, retire os comentários a seguir
    /*for(int i = 0; i < Merge_saida.size(); i++){
        cout << Merge_saida[i].pegaX() << " " << Merge_saida[i].pegaY() << endl;
    }*/
    auto t_insertion = chrono::high_resolution_clock::now();
    Graham_Insertion(Insertion_entrada, count, Insertion_saida);
    auto t_insertionf = chrono::high_resolution_clock::now();
    // Se quiser imprimir a saída do Graham_Insertion, retire os comentários a seguir
    /*for(int l = 0; l < Insertion_saida.size(); l++){
        cout << Insertion_saida[l].pegaX() << " " << Insertion_saida[l].pegaY() << endl;
    }*/
    auto t_linear = chrono::high_resolution_clock::now();
    Graham_Linear(Linear_entrada, count, Linear_saida);
    auto t_linearf = chrono::high_resolution_clock::now();
    // Se quiser imprimir a saída do Graham_Linear, retire os comentários a seguir
    /*for(int l = 0; l < Linear_saida.size(); l++){
        cout << Linear_saida[l].pegaX() << " " << Linear_saida[l].pegaY() << endl;
    }*/
    cout << endl;
    cout << "GRAHAM+MERGESORT: " << fixed << setprecision(3) << chrono::duration<double>(t_mergef - t_merge).count() << "s" << endl;
    cout << "GRAHAM+INSERTIONSORT: " << fixed << setprecision(3) << chrono::duration<double>(t_insertionf - t_insertion).count() << "s" << endl;
    cout << "GRAHAM+LINEAR: " << fixed << setprecision(3) << chrono::duration<double>(t_linearf - t_linear).count() << "s" << endl;
    cout << "JARVIS: " << fixed << setprecision(3) << chrono::duration<double>(t_jarvisf - t_jarvis).count() << "s" << endl;
    delete[] Merge_entrada;
    delete[] Insertion_entrada;
    delete[] Linear_entrada;
    return 0;
}