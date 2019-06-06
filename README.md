# vm

this project contains a simple stack-based virtual machine. the instruction set is available
[on the wiki](https://github.com/swissChili/vm/wiki/Instructions).


## building

```sh
$ meson build
$ cd build
$ ninja
$ ./vm
```


## flags

- `-D`, `--debug`: show debug output, prints stack, registers, and operation at each iteration
- `-r`, `--run`: text assembly file to execute

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
