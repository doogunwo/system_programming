#!/bin/bash

# 텍스트 파일 경로
file="test.txt"

# 파일을 한 줄씩 읽어서 검색
while IFS= read -r line; do
    # 문장에서 "korea"를 검색하고 결과를 출력
    if [[ $line == *korea* ]]; then
        echo "문장 내에서 'korea'를 발견했습니다: $line"
    fi
done < "$file"