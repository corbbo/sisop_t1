#include "cpu_scheduler.h"

#define LOGIC processlist.it = processlist.begin(); processlist.it != processlist.end(); ++processlist.it

int tempo = 0;

void calculaTempo(ProcessList processlist); //calcula tempo de execução (soma de tempo de cpu dos processos)

int init() {

    ProcessList processlist;
    Process A("A", 'w', 3, 2, 5, 6, 1);
    processlist.add(A);
    Process B("B", 'w', 3, 3, 10, 6, 2);
    processlist.add(B);
    Process C("C", 'w', 3, 0, 0, 14, 3);
    processlist.add(C);
    Process D("D", 'w', 3, 0, 0, 10, 4);
    processlist.add(D);

    //calcula tempo de execução (soma de tempo de cpu dos processos)
    calculaTempo(processlist);
    //ordena os processos
    processlist.sort(0);

    //onde o escalonamento acontece
    for (int i = 0; i < tempo; i++) {

        int counter = 0;
        for (LOGIC) {
            //se o estado é bloqueio decrementa o contador de tempo de bloqueio
            if (processlist.it->estado == 'b') {
                processlist.it->counteres--;
                if (processlist.it->counteres == 0) {
                    processlist.it->estado = 'w';
                    processlist.it->counteres = processlist.it->tempoes;
                    processlist.it->temposurto = processlist.it->surto;
                }
            }

            if (processlist.it->creditos != 0) {
                if (processlist.it->estado != 'b') {
                    counter++;
                }
            }
        }

        //se o counter é zero usa formula
        if (counter == 0) {
            for (LOGIC) {
                processlist.it->creditos = processlist.it->creditos/2 + processlist.it->prioridade;
            }
            processlist.sort(1);
        }

        //it = inicio
        processlist.it = processlist.begin();
        if (processlist.it->estado == 'b') {
            processlist.add(*processlist.it);
            processlist.pop_front();
            processlist.it = processlist.begin();
        }
        
        if (processlist.it->estado == 'w') {
            processlist.it->estado = 'r';
        }

        if (processlist.it->estado == 'r') {
            processlist.it->temposurto--;
            processlist.it->creditos--;
            processlist.it->tempocpu--;
            if (processlist.it->tempocpu == 0) {
                processlist.erase(processlist.it);
                processlist.sort(1);
            } else if (processlist.it->temposurto == 0) {
                processlist.it->estado = 'b';
                processlist.add(*processlist.it);
                processlist.pop_front();
            } else if (processlist.it->creditos == 0) {
                processlist.it->estado = 'w';
                processlist.add(*processlist.it);
                processlist.pop_front();
                processlist.sort(1); 
            }   
        }   
        print_result(i, processlist);
    }
    return 1;
}

void calculaTempo(ProcessList processlist) //calcula tempo de execução (soma de tempo de cpu dos processos)
{
    for (LOGIC) {
        tempo = tempo + processlist.it->tempocpu;
    }
}
int print_result(int i, ProcessList processlist) {
            std::cout << "Tempo: " << i + 1 << std::endl;
        for (LOGIC) {
            std::cout << "PID = " << processlist.it->pid << " " << "Estado = " << processlist.it->estado << " " << "Creditos = " << processlist.it->creditos << " " << "Surto = " << processlist.it->temposurto << " " << "Tempo E/S = " << processlist.it->counteres << " " << "Tempo CPU = " << processlist.it->tempocpu << " " << "Ordem = " << processlist.it->ordem << " " << "Prioridade = " << processlist.it->prioridade << std::endl;
        }
    return 0;
}