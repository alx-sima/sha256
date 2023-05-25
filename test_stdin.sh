#!/bin/env bash
# Copyright (C) 2023 Alexandru Sima (312CA) #
#
# Script de test pentru executabil.
#
# Testeaza daca output-ul executabilului este cel al 
# executabilului original pentru siruri aleatoare de bytes.
#
# Argumente:
#   $1 - calea catre executabilul de testat
#   $2 - calea catre executabilul original
#   $3 - numarul de teste (optional, default 100) 

if test $# -lt 2; then
    echo "Usage: $0 <my_exec> <original_exec> [tests_no]"
    exit 1
fi

[[ -n $3 ]] && tests_no=$3 || tests_no=100

for i in $(seq 1 $tests_no); do
    teststr=$(< /dev/urandom | tr -d '\0' | head -c $i)

    output=$(echo -n "$teststr" | $1)
    expected=$(echo -n "$teststr" | $2)

    if test "$output" != "$expected"; then
        echo "Test $i failed"
        echo "Expected: $expected"
        echo "Got: $output"
        exit 1
    else
        echo "Test $i passed"
    fi
done
