#!/bin/bash

USERNAME=""
PASSWORD=""
LEVEL=""

while getopts "u:p:" OPT; do
    case "${OPT}" in
        u)
            USERNAME=${OPTARG}
            ;;
        p)
            PASSWORD=${OPTARG}
            ;;
        l)
            LEVEL=${OPTARG}
            ;;
    esac
done

while true; do
    ./cmake-build/bin/solver.exe $USERNAME $PASSWORD
done
