[![forthebadge](https://forthebadge.com/images/badges/60-percent-of-the-time-works-every-time.svg)](https://forthebadge.com)
## hastec - a small hastebin client written in C

This is a small thing I wrote while learning C. It's a program that takes input from stdin and uploads it to my Hastebin. Does not support 32-bit architectures.

### Requirements

* make
* pkg-config
* gcc
* libcurl (openssl)
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
cat file.txt | haste                                     # Input stream.
```

### Configuration
The only configuration option is a `#define` in haste.c that specifies the base URL of the hastebin the program will try to upload to.
