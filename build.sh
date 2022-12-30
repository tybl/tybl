#!/bin/bash
cmake -S deps/ -B build_deps
cmake --build build_deps
cmake -S . -B build_tybl -DCMAKE_PREFIX_PATH=deps
cmake --build build_tybl
