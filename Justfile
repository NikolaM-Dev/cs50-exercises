# List all avalible recipes
default:
    just --list

# Make <cs50.h> avalible
init:
    #!/usr/bin/env bash
    cd ../libcs50
    sudo make install

# Compile the `main.c` into `main` and add the `<cs50.h> lib`
build:
    gcc main.c -lcs50 -o main

# Build and run the `main` binary
run: build
    ./main

# Hot reaload listening for change in `*.c` files
hot_reload:
    ls *.c | entr -r sh -c 'clear; gcc -lcs50 -o main *.c && ./main'
