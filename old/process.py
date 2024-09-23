# b -- blocked
# w -- waiting
# t -- terminated
# r -- running

from typing import Any


class Process:
    def __init__(self, name, priority, order, io_time, burst_time, cpu_time, state):
        self._name = name
        self._priority = priority
        self._order = order
        self._io_time = io_time
        self._io_remaining = io_time
        self._cpu_time = cpu_time
        self._state = state
        self._burst_remaining = burst_time
        self._burst_time = burst_time
        self._total_cpu_time = 0
        self._credits = priority
    
    def dec_burst(self):
        if self._burst_time == 0: 
            return
        self._burst_remaining -= 1
        if self._burst_remaining <= 0:
            self._state = 'b'
            self._burst_remaining = self._burst_time
            return
        self._credits -= 1
        if self._credits <= 0:
            self._credits = 0
            self._state = 'w'
            return
    
    def dec_io(self):
        if self._io_time == 0:
            return
        self._io_remaining -= 1
        if self._io_remaining <= 0:
            self._state = 'w'
            self._io_remaining = self._io_time
    
    def dec_cpu(self):
        self._cpu_time -= 1
        self._credits -= 1 if self._burst_time == 0 else 0
        if self._cpu_time <= 0:
            self._state = 't'
            return
        if self._credits <= 0:
            self._credits = 0
            self._state = 'w'
            return
            
    def schedule(self):
        if self._credits <= 0 or self._state == 'b' or self._state == 't':
            return False
        else:
            return True
    
    def inc_cpu_time(self):
        self._total_cpu_time += 1
    
    def get_name(self):
        return self._name
    
    