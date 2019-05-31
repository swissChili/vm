# vm

this project contains a simple stack-oriented virtual machine implemented in c. it contains
few instructions but can be used to write mildly interesting programs. `main.c` contains an
example of a factorial program. it does not currently work.


## building

```sh
$ meson build
$ cd build
$ ninja
$ ./vm
```
