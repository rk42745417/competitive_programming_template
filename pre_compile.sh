#!/usr/bin/env bash
version=$(g++ --version | head -n 1 | awk '{print $(NF-1)}')
g++ -std=gnu++23 -Wall -Wextra -Wconversion -Wshadow -Wfatal-errors -fsanitize=undefined -fsanitize=address -g -DEMT \
    -o Header/stdc++.h.gch \
    "/usr/include/c++/${version}/x86_64-pc-linux-gnu/bits/stdc++.h"
