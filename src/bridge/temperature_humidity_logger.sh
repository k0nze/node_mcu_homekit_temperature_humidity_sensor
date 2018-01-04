#!/bin/bash

# reads the temperature or humidity from the sensor by connecting via curl to
# http://IP/path and reading the value.
# The read value will be stored into a CSV (logfile path) file with the current 
# date:
#
# "YYYY-MM-DD HH:MM:SS",VALUE
#
# The read value will also be stored in a simple text document (current value
# file path)

# Parameters:
# 1. IP
# 2. path
# 3. logfile path
# 4. current value file path

LOGFILE_PATH=${3}
CURRENT_VALUE_FILE=${4}

URL="http://${1}/${2}"

while true; do
	# retrieve data
	VALUE=$(curl ${URL} 2>/dev/null)

	# remove whitespace characters
	VALUE="$(echo -e "${VALUE}" | tr -d '[:space:]')"

	# check if value is nan
	if [ "${VALUE}" != "nan" ]; then
		# get the time
		DATE_TIME=$(date +"%Y-%m-%d %H:%M:%S")
		DATE_TIME="\"${DATE_TIME}\""
		echo "${DATE_TIME},${VALUE}" >> ${LOGFILE_PATH}
	
		# write value into current value file	
		if [ -n "${CURRENT_VALUE_FILE}" ]; then
			echo ${VALUE} > ${CURRENT_VALUE_FILE}
		fi
	fi	

	sleep 60s
done
