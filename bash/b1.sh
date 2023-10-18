#!/bin/bash

echo "일반 파일 목록:"
for file in *; do
    if [ -f "$file" ]; then
        echo "$file"
    fi
done
