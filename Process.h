#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <iostream>
#include <string>

class Process {
	public:
	// std::string pid;
	int pid;
	char estado;
	int creditos;
	int surto;
	int temposurto;
	int tempoes;
	int counteres;
	int tempocpu;
	int ordem;
	int prioridade;
	Process(std::string n, char e, int c, int s, int ts, int tcpu, int o);
	Process(int n, char e, int c, int s, int ts, int tcpu, int o);
	void print();
};
	std::ostream& operator<<(std::ostream& os, const Process& p);

#endif // PROCESS_HPP
