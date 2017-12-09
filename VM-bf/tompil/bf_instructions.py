import os
import sys

def increment_pointer(interpreter):
    interpreter.pointer += 1


def decrement_pointer(interpreter):
    interpreter.pointer -= 1


def increment_value(interpreter):
    val = interpreter.memory.fetch_byte(interpreter.pointer)
    if val is not None:
        val += 1
        interpreter.memory.store_byte(interpreter.pointer, val)
    else:
        interpreter.crash(interpreter.MEMORY_ERROR)


def decrement_value(interpreter):
    val = interpreter.memory.fetch_byte(interpreter.pointer)
    if val is not None:
        val -= 1
        interpreter.memory.store_byte(interpreter.pointer, val)
    else:
        interpreter.crash(interpreter.MEMORY_ERROR)


def print_value(interpreter):
    val = interpreter.memory.fetch_byte(interpreter.pointer)
    if val is not None:
        if val == 10:
            sys.stdout.write(os.linesep)
        else:
            sys.stdout.write(chr(val))
    else:
        interpreter.crash(interpreter.MEMORY_ERROR)


def read_value(interpreter):
    if len(interpreter.input) == 0:
        try:
            console_input = raw_input()
            for char in console_input:
                interpreter.input.append(ord(char))
            interpreter.input.append(10)
        except EOFError:
            interpreter.input.append(0)
    val = interpreter.input[0]
    interpreter.memory.store_byte(interpreter.pointer, val)
    interpreter.input.remove(interpreter.input[0])


def loop_begin(interpreter):
    if interpreter.memory.fetch_byte(interpreter.pointer) == 0:
        loop_stack_len = len(interpreter.loop_stack)
        interpreter.loop_stack.append(interpreter.pos_in_file)
        while len(interpreter.loop_stack) != loop_stack_len:
            interpreter.pos_in_file += 1
            if interpreter.pos_in_file >= len(interpreter.code):
                interpreter.crash(interpreter.SYNTAX_ERROR)
                return
            command = interpreter.code[interpreter.pos_in_file]
            if command == '[':
                interpreter.loop_stack.append(interpreter.pos_in_file)
            elif command == ']':
                interpreter.loop_stack.pop()
    else:
        interpreter.loop_stack.append(interpreter.pos_in_file)


def loop_end(interpreter):
    if interpreter.memory.fetch_byte(interpreter.pointer) == 0:
        interpreter.loop_stack.pop()
    else:
        interpreter.pos_in_file = interpreter.loop_stack[len(interpreter.loop_stack) - 1]

INTERPRETER_INSTR = {
    '>': increment_pointer,
    '<': decrement_pointer,
    '+': increment_value,
    '-': decrement_value,
    '.': print_value,
    ',': read_value,
    '[': loop_begin,
    ']': loop_end
}
