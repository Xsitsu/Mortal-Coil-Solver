#!/bin/bash

USERNAME=""
PASSWORD=""

while getopts "u:p:" OPT; do
    case "${OPT}" in
        u)
            USERNAME=${OPTARG}
            ;;
        p)
            PASSWORD=${OPTARG}
            ;;
    esac
done

while true; do
    ./http.py $USERNAME $PASSWORD GET
    ./solver.exe
    ./http.py $USERNAME $PASSWORD POST
done
