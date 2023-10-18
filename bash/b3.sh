#!/bin/bash

echo "피보나치 수열을 계산합니다."

# 피보나치 수열의 첫 두 항은 0과 1입니다.
fibonacci=(0 1)

# 피보나치 수열을 계산할 항의 개수를 지정합니다.
n=10

# n번째 피보나치 수열까지 계산합니다.
for ((i=2; i<n; i++)); do
    # 현재 항을 계산하여 배열에 추가합니다.
    let next_fibonacci=${fibonacci[i-1]}+${fibonacci[i-2]}
    fibonacci+=($next_fibonacci)
done

# 계산된 피보나치 수열을 출력합니다.
echo "피보나치 수열 (첫 $n 항): ${fibonacci[*]}"
