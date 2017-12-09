class InterpreterMemory(object):
    MAX_MEMORY_SIZE = 128*1024

    def __init__(self):
        self._mem = bytearray(1024)

    def fetch_byte(self, address):
        if address < 0 or address >= self.MAX_MEMORY_SIZE:
            return None
        if address >= len(self._mem):
            self._mem.append(0 for _ in xrange(address - len(self._mem) + 1))
        return self._mem[address]

    def store_byte(self, address, value):
        if address < 0 or address >= self.MAX_MEMORY_SIZE:
            return None
        if address >= len(self._mem):
            self._mem.append(0 for _ in xrange(address - len(self._mem) + 1))
        self._mem[address] = value % 0xFF
        return 0
