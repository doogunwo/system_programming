#!/bin/bash

# 행의 수를 지정합니다.
rows=4

for ((i=rows; i>=1; i--)); do
    for ((j=1; j<=i; j++)); do
        echo -n "*"
    done
    echo
done
