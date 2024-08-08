# brainfuck-interpreter
This is a very simple and minimal [brainfuck](https://en.wikipedia.org/wiki/Brainfuck#Language_design) interpreter, it does not check whether the syntax is actually correct.

## Compiling
To compile the interpreter you can run:
```bash
g++ ./src/interpreter.cpp -o brainfuck
```

## Usage
After having compiled the interpreter, simply supply the file containing the brainfuck code as the only command argument:
```bash
./brainfuck ./test/hellow_world.bf
```
