import sys
from bf_memory import InterpreterMemory
from bf_instructions import INTERPRETER_INSTR


class InterpreterInstance(object):

    NO_CODE_ERROR = 1
    MEMORY_ERROR = 2
    SYNTAX_ERROR = 3

    def __init__(self):
        self.code = None
        self.memory = InterpreterMemory()
        self.pointer = 0
        self.max_pointer = 0
        self.terminated = False
        self.instructions = INTERPRETER_INSTR
        self.pos_in_file = 0
        self.loop_stack = []
        self.input = []

    def load_code(self, name):
        try:
            with open(name, "r") as f:
                self.code = f.read()
        except IOError:
            print "Could not open file!"
        self.pos_in_file = 0
        self.loop_stack = []
        self.terminated = False

    def crash(self, error_code):
        self.terminated = True
        print "Program crashed!"
        if error_code == self.NO_CODE_ERROR:
            print "No code loaded!"
        elif error_code == self.MEMORY_ERROR:
            print "Memory error!"
        elif error_code == self.SYNTAX_ERROR:
            print "Syntax error!"
        print "pointer:", self.pointer
        print "position in code:", self.pos_in_file
        print "loop stack:", self.loop_stack

    def terminate(self):
        self.terminated = True

    def run_single_step(self):
        if self.code is None:
            self.crash(self.NO_CODE_ERROR)
            return
        if self.pos_in_file >= len(self.code):
            self.terminate()
            return
        command = self.code[self.pos_in_file]
        if command in self.instructions:
            instruction = self.instructions[command]
            instruction(self)
        if self.pointer > self.max_pointer:
            self.max_pointer = self.pointer
        # print "pointer:", self.pointer
        # print "command:", command
        # print "value:", self.memory.fetch_byte(self.pointer)
        # print "position in code:", self.pos_in_file
        # print "loop stack:", self.loop_stack
        # print "memory:", " ".join(str(self.memory.fetch_byte(i)) for i in xrange(self.max_pointer + 1))
        # print "-------------"
        self.pos_in_file += 1

    def run(self):
        while not self.terminated:
            self.run_single_step()

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print "usage: bf.py <filename>"
        sys.exit(1)
    inter = InterpreterInstance()
    inter.load_code(sys.argv[1])
    inter.run()
