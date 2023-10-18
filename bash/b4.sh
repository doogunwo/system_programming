#!/bin/bash

echo "3개의 숫자를 입력하세요:"

# 사용자로부터 숫자를 입력받음
read num1
read num2
read num3

# 초기화
max=$num1
min=$num1

# 최댓값과 최솟값 계산
if [ $num2 -gt $max ]; then
    max=$num2
fi

if [ $num2 -lt $min ]; then
    min=$num2
fi

if [ $num3 -gt $max ]; then
    max=$num3
fi

if [ $num3 -lt $min ]; then
    min=$num3
fi

echo "가장 큰 수: $max"
echo "가장 작은 수: $min"
