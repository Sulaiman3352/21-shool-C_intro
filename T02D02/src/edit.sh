#!/bin/sh

for file; do
  test "${file%.txt}" = "${file}" && continue
  sed -i 's/"\([^"]*\)"/\1/g' "$file"
done

file_path=$(readlink -f "$file")
file_size=$(ls -l "$file_path" | awk '{print $5}')
file_date=$(date +%F -r "$file_path")
file_time=$(ls -l "$file_path" | awk '{print $8}')
file_hash=$(sha256sum "$file_path" | awk '{print $1}')

echo "$file_path $file_size $file_date $file_time $file_hash" >> files.log
