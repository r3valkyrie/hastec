## hastec - a small hastebin client written in C

This is a small thing I wrote while learning C.

### Requirements
Most GNU/Linux systems should come with these libraries already.

* make
* libcurl
* libjson-c

### Installation
```
git clone https://github.com/r3valkyrie/hastec.git       # clone the repo.
cd hastec                                                # cd into the repo.
make                                                     # compile the program.
sudo make install                                        # install the program.
```

### Usage
```
./haste                                                  # Standalone accepts input until an EOF is sent (CTRL-D on GNU/Linux).
cat file.txt | haste                                     # Accepts input piped from stdout.
```

### Configuration
The only configuration option is a `#define` in haste.c that specifies the base URL of the hastebin the program will try to upload to.
