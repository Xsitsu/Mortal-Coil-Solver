#!/bin/sh

script_dir="$(dirname -- "$(readlink -f -- "$0")")"
build_dir="$script_dir"/cmake-build

cmake -B "$build_dir" -S "$script_dir"

cmake --build "$build_dir" --target solver
