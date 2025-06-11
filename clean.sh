#!/bin/bash

# Remove all object (*.o) and executable files recursively

find . -type f \( -name "*.o" -o -perm -111 \) -delete