#!/bin/bash

echo "구구단을 계산합니다."

for i in {2..9}; do
    echo "[$i 단]"
    for j in {1..9}; do
        result=$((i * j))
        echo "$i x $j = $result"
    done
    echo ""
done