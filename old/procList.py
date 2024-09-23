from process import Process

class ProcessList:
    def __init__(self):
        self._processes = []
        
    def add_process(self, name, priority, order, io_time, burst_time, cpu_time, state):
        self._processes.append(Process(name, priority, order, io_time, burst_time, cpu_time, state))
    
    def sort_procs(self, key):
        if key == 0:
            self._processes.sort(key=lambda x: (x._priority, x._order))
        else:
            self._processes.sort(key=lambda x: (x._credits, x._order))
    
    def schedule(self):
        # schedule the process with the highest priority, and increment and decrement appropriate counters as we go through the list
        proc = None
        for p in self._processes:
            print(p._name, p._credits, p._state)
            if p._state == 't':
                continue
            if p.schedule():
                proc = p
                break
        if proc is not None:
            return proc
        # if no process is scheduled, reset credits
        for p in self._processes:
            p._credits = p._credits/2 + p._priority
        for p in self._processes:
            if p._state == 't':
                continue
            if p.schedule():
                return p
        # if no process is scheduled, return None, indicating that the all processes are terminated
        return None           
    
    def tick(self):
        for p in self._processes:
            if p._state == 'r':
                p.dec_burst()
                p.dec_cpu()
                p.inc_cpu_time()
            elif p._state == 'b':
                p.dec_io()
    
    def get_total_cpu_time(self):
        return sum([p._total_cpu_time for p in self._processes])