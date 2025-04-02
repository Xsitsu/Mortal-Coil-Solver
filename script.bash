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
    ./webhandler.py $USERNAME $PASSWORD GET $LEVEL
    ./cmake-build/bin/solver.exe "../../../board.dat" "../../../solution.dat"
    ./webhandler.py $USERNAME $PASSWORD POST
done
