#include "Processlist.h"
#include <iostream>
#include <algorithm>


ProcessList::ProcessList() {
	processos = {};
	it = processos.begin();
}

void ProcessList::add(Process p) {
	processos.push_back(p);
	_size++;
}

void ProcessList::sort(int n) {
	switch (n){
		case 0:
			processos.sort([](const Process &a, const Process &b) { if (a.creditos == b.creditos) {return a.ordem < b.ordem;} else { return a.creditos > b.creditos; }}); 
			break;
		case 1:
            processos.sort([](const Process &a, const Process &b) {return a.creditos > b.creditos; }); 
			break;
	}
}

void ProcessList::print() {
	int i = 0;
	for (const auto &process : processos) {
		std::cout << i+1 << ": " << process << std::endl;
		i++;
	}
}

Process ProcessList::top() {
	if (!processos.empty()) {
		return processos.front();
	}
	throw std::runtime_error("Process list is empty");
}

std::list<Process>::iterator ProcessList::begin(){
	return processos.begin();
}
std::list<Process>::iterator ProcessList::end(){
	return processos.end();
}

Process ProcessList::pop_front(){
	if (!processos.empty()) {
		Process p = processos.front();
		processos.pop_front();
		_size--;
		return p;
	}
	throw std::runtime_error("Process list is empty");
}

Process ProcessList::erase(std::list<Process>::iterator p_it){
	Process p = *p_it;
	processos_teminados.push_back(p);
	processos.erase(p_it);
	_size--;
	return p;
}

int ProcessList::size(){
	return processos.size();
}