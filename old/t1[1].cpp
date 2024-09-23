#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>
#include <list>
#include <unordered_map>
#include <queue>
#include "Process.h"
#include "Processlist.h"

using namespace std;


int main () {
    list<Process> processos; //mapa que armazena processos
    Process A("A", 'w', 3, 2, 5, 6, 1);
    Process B("B", 'w', 3, 3, 10, 6, 2);
    Process C("C", 'w', 3, 0, 0, 14, 3);
    Process D("D", 'w', 3, 0, 0, 10, 4);
    
    processos.push_back(A);
    processos.push_back(B);
    processos.push_back(C);
    processos.push_back(D);

    list<Process>::iterator it;

    //calcula tempo de execução (soma de tempo de cpu dos processos)
    int tempo = 0;
    for (it = processos.begin(); it != processos.end(); ++it){
        tempo = tempo + it->tempocpu;
    }

    processos.sort([](const Process &a, const Process &b) { if (a.creditos == b.creditos) {return a.ordem < b.ordem;} else { return a.creditos > b.creditos; }}); 

    //onde o escalonamento acontece
    for (int i = 0; i < tempo; i++) {

        int counter = 0;
        for (it = processos.begin(); it != processos.end(); ++it) {
            //se o estado é bloqueio decrementa o contador de tempo de bloqueio
            if (it->estado == 'b') {
                it->counteres--;
                if (it->counteres == 0) {
                    it->estado = 'w';
                    it->counteres = it->tempoes;
                    it->temposurto = it->surto;
                }
            }

            if (it->creditos != 0) {
                if (it->estado != 'b') {
                    counter++;
                }
            }
        }

        //se o counter é zero usa formula
        if (counter == 0) {
            for (it = processos.begin(); it != processos.end(); ++it) {
                it->creditos = it->creditos/2 + it->prioridade;
            }
            processos.sort([](const Process &a, const Process &b) {return a.creditos > b.creditos; }); 
        }

        //it = inicio
        it = processos.begin();
        if (it->estado == 'b') {
            processos.push_back(*it);
            processos.pop_front();
            it = processos.begin();
        }
        
        if (it->estado == 'w') {
            it->estado = 'r';
        }

        if (it->estado == 'r') {
            it->temposurto--;
            it->creditos--;
            it->tempocpu--;
            if (it->tempocpu == 0) {
                processos.erase(it);
                processos.sort([](const Process &a, const Process &b) {return a.creditos > b.creditos; });
            } else if (it->temposurto == 0) {
                it->estado = 'b';
                processos.push_back(*it);
                processos.pop_front();
            } else if (it->creditos == 0) {
                it->estado = 'w';
                processos.push_back(*it);
                processos.pop_front();
                processos.sort([](const Process &a, const Process &b) {return a.creditos > b.creditos; }); 
            }   
        }

        cout << "Tempo: " << i + 1 << endl;
        for (it = processos.begin(); it != processos.end(); ++it) {
            cout << "PID = " << it->pid << " " << "Estado = " << it->estado << " " << "Creditos = " << it->creditos << " " << "Surto = " << it->temposurto << " " << "Tempo E/S = " << it->counteres << " " << "Tempo CPU = " << it->tempocpu << " " << "Ordem = " << it->ordem << " " << "Prioridade = " << it->prioridade << endl;
        }
    }
}
