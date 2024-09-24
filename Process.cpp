#include <string>
#include "Process.h"

Process::Process(int n, char e, int c, int s, int ts, int tcpu, int o){
	pid = n;
	estado = e;
	creditos = c;
	surto = s;
	temposurto = s;
	tempoes = ts;
	counteres = ts;
	tempocpu = tcpu;
	ordem = o;
	prioridade = c;
	tempo_total_cpu = tcpu;
}
	std::ostream& operator<<(std::ostream& os, const Process& p){
		os << "PID = " << p.pid << " " << "Estado = " << p.estado << " " << "Creditos = " << p.creditos << " " << "Surto = " << p.temposurto << " " << "Tempo E/S = " << p.counteres << " " << "Tempo CPU = " << p.tempocpu << " " << "Ordem = " << p.ordem << " " << "Prioridade = " << p.prioridade << std::endl;
		return os;
	}

