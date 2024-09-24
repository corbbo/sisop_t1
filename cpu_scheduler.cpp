#include "cpu_scheduler.h"
#include <map>
#include <utility>
#include <sstream>
#include <iomanip>
#define LOGIC processlist.it = processlist.begin(); processlist.it != processlist.end(); ++processlist.it

int tempo = 0;
std::map<int, std::string> lines;

void calculaTempo(ProcessList processlist); //calcula tempo de execução (soma de tempo de cpu dos processos)

int init() {

	ProcessList processlist;
	Process A(0, 'w', 3, 2, 5, 6, 1);
	processlist.add(A);
	Process B(1, 'w', 3, 3, 10, 6, 2);
	processlist.add(B);
	Process C(2, 'w', 3, 0, 0, 14, 3);
	processlist.add(C);
	Process D(3, 'w', 3, 0, 0, 10, 4);
	processlist.add(D);

	for (LOGIC){
		lines[processlist.it->pid] = std::to_string(processlist.it->pid) + ":\t";  }  

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
				if (processlist.it->counteres < 0) {
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

		for(LOGIC){
		lines[processlist.it->pid] += (processlist.it->estado) ;
		lines[processlist.it->pid] += " ";
		}

		processlist.it = processlist.begin();

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
	}
	print_result(processlist);
	return 1;
}

void calculaTempo(ProcessList processlist) //calcula tempo de execução (soma de tempo de cpu dos processos)
{
	for (LOGIC) {
		tempo = tempo + processlist.it->tempocpu;
	}
}
int print_result(ProcessList processlist) {
	for(auto const& x : lines) {
		std::cout << x.second << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Total CPU time:\t" << tempo << "ms"<< std::endl;
	std::stringstream ss;
	for(auto it : processlist.processos_teminados){
		std::cout << "Process " << it.pid << ":\t" << it.tempo_total_cpu << "ms" << "\t||\t" << std::setprecision(4) << double(it.tempo_total_cpu)/double(tempo) * 100 << "%" << std::endl;
	}
	return 0;
}
