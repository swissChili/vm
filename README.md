# vm

This project contains a simple stack-based virtual machine. the instruction set
is available [on the wiki](https://github.com/swissChili/vm/wiki/Instructions).


## building

```sh
$ meson build
$ ninja -C build
# build/vm is the compiled binary
```

## design

This virtual machine is designed with the following ideas in mind:

- complete unicode support
- stack-based
  - untyped stack, everything on the stack is a 32 bit integer, which can be a
    pointer to the heap, or just a value
- local heap
  - variables can be addressed by absolute values, greatly simplifying compiler
    design
  - heap can inherit from another heap, each function has it's own heap, each
    inheriting from the "root" heap.
- functional
  - functions work like the JVM's `.class`es. 
  - modules are made up of 1 or more functions
  - dependencies are sub modules

### convenience > file size

I've made the decision several times during the design of this software to
prioritize the convenience of the developer over everything else. By developer
I mean both myself working on the virtual machine, and any person who might use
it as a compiler target, write assembly for it, or really anything pertaining
to its use. For this reason I've chosen to use 32 bit integers as the basis for
*everything* in this vm. Strings are encoded in utf-32, pointers are 32 bit,
the heap is a vector of 32 bit ints, even the bytecode encodes every instruction
as a 32 bit integer. The detriments of this are pretty obvious, drastically
increased file size, possible increase in memory consumption (although it can't
be as bad as the JVM... can it?)

## types

### strings

Strings are encoded in utf32. They are stored on the stack like so:

```
    End of string     Top of stack
          v                v
[ ...  0xFFFF  o  l  l  e  H ]
```

And on the heap:

```
Start of string    End of string
       v                v
[ ...  H  e  l  l  o  0xFFFF  ... ]
```

### complex types

Complex types (structs, unions, etc) should be constructed in a manner similar
to lambda calculus. The exact nature of these is really dependent on the compiler.
For instance, here is a way a C struct could be compiled to a lambda calculus
(and vm) function:

```c
struct foo
{
    int a;
    int b;
    char c;
}
```

```hs
-- foo :: Int -> Int -> Int -> Bool -> Bool -> Bool -> Int
λ a . λ b . λ c .
    λ a1 . λ b1 . λ c1 .
        a1 a (b1 b (c1 c 0))
```

Assuming of course that the `Bool` type mentioned is the typical lambda calc
boolean implementation of

```hs
-- true = 
λ a . λ b . a
-- false =
λ a . λ b . b
```

Creating a type `foo` then would involve calling the function with the first
three arguments, the items to store in it, and accessing those values
by passing three more booleans to it.

## usage

- `-D`, `--debug`: show debug output, prints stack, registers, and operation at
  each iteration
- `-r`, `--run`: text assembly file to execute
- `-e`, `--execute`: compiled bitcode to execute

## example

```sh
$ cat test.s
PSH 123
POP EAX
LDR EAX
$ vm -Dr test.s
Running test.s with debug mode 1
____________________________
PSH 123
lt: 0 gt: 0 eq: 0
EAX: 0 EBX: 0 ECX: 0 EDX: 0
[ 123 ]
____________________________
POP 0
lt: 0 gt: 0 eq: 0
EAX: 123 EBX: 0 ECX: 0 EDX: 0
[ ]
____________________________
LDR 0
lt: 0 gt: 0 eq: 0
EAX: 123 EBX: 0 ECX: 0 EDX: 0
[ 123 ]
Returned 123
```

## known issues

- parser uses scanf and is really finicky. It will not accept leading or
  trailing whitespace.
- `DUP` instruction does not parse for some bizarre reason.

## roadmap

- parse using a less horrible method (maybe bison or yacc?)
- add a heap

## license

![GPL-3.0 License](https://www.gnu.org/graphics/gplv3-127x51.png)

Copyright (C) 2019  swissChili

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

