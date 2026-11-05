#!/bin/sh

file="$1"

if [ $# -ne 1 ]; then
    echo "Error: Please provide a log file path" >&2
    exit 1
fi

if [ ! -s "$file" ]; then
    echo "The file is empty."
    exit 1
fi

total_number_of_records=$(cat "$file" | wc -l)
unique_files=$(sort -u "$file" | wc -l)
hash=$(
  awk -F ' - ' '{
    name = $1
    hash = $4
    if (name in prev && prev[name] != hash) count++
    prev[name] = hash
  } END {print count+0}' "$file"
)

echo "$total_number_of_records $unique_files $hash"
