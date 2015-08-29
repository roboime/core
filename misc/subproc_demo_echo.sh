#!/bin/bash
while IFS='' read -r line || [[ -n "$line" ]]; do
	line="$(echo -e "${line}" | tr -d '[[:space:]]')"
	case $line in
		"enough")
			>&2 echo "subexit"
			exit 0
			;;
		*)
			echo "sub$line"
			;;
	esac
done
