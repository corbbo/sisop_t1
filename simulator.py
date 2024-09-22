from procList import ProcessList

def simulate():
    pl = ProcessList()
    # add_process(name, priority, order, io_time, burst_time, cpu_time, state, credits)
    pl.add_process('A', 3, 1, 5, 2, 6, 'w', 3)
    pl.add_process('B', 3, 2, 10, 3, 6, 'w', 3)
    pl.add_process('C', 3, 3, 0, 0, 14, 'w', 3)
    pl.add_process('D', 3, 4, 0, 0, 10, 'w', 3)
    pl.sort_procs()
    lines = [] * len(pl._processes)
    print(len(pl._processes))
    print(len(lines))
    for i in range(len(pl._processes)):
        lines.append(f'P{i+1}    ')
    while True:
        p = pl.schedule()
        if p is None:
            break
        else:
            p._state = 'r'
        for i in range(len(pl._processes)):
            lines[i] += f'    {pl._processes[i]._state}'
    for l in lines:
        print(l)
    print(f'Total CPU time: {pl.get_total_cpu_time()}')
    print(f'Total CPU time per process: {pl.get_total_cpu_time()/len(pl._processes)}')
    
simulate()