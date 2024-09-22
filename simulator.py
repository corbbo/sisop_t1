from procList import ProcessList

def simulate():
    pl = ProcessList()
    # add_process(name, priority, order, io_time, burst_time, cpu_time, state, credits)
    pl.add_process('A', 3, 1, 5, 2, 6, 'w')
    pl.add_process('B', 3, 2, 10, 3, 6, 'w')
    pl.add_process('C', 3, 3, 0, 0, 14, 'w')
    pl.add_process('D', 3, 4, 0, 0, 10, 'w')
    pl.sort_procs(0)
    lines = [] * len(pl._processes)
    for i in range(len(pl._processes)):
        lines.append(f'P{i+1}    ')
    while True:
        pl.tick()
        p = pl.schedule()
        if p is None:
            for i in range(len(pl._processes)):
                lines[i] += f'    t'
            break
        else:
            p._state = 'r'
            pl.sort_procs(1)
        for i in range(len(pl._processes)):
            lines[i] += f'    {pl._processes[i]._state}' if pl._processes[i]._state != 't' else ''
    for l in lines:
        print(l)
    print(f'Total CPU time: {pl.get_total_cpu_time()}')
    print('Total CPU usage per process:')
    total_cpu_time = pl.get_total_cpu_time()
    for p in pl._processes:
        print(f'P{pl._processes.index(p)+1}: {p._total_cpu_time/total_cpu_time:.2f}')
    
simulate()