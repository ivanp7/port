#!/bin/sh

sed "s/^unsigned char /static unsigned char /;
    s/^unsigned int \(.*\) = \([0-9]*\);$/#define \1 \2/"

