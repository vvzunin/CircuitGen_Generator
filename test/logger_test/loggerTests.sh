#!/bin/bash
file="../CMakeLists.txt"
path_to_current_logger_files=""
while IFS= read -r line
do
    if [[ $line =~ "ADD_DEFINITIONS( -D_PATH_TO_LOGGING=" ]]
    then
        l_double_quote=-1
        r_double_quote=-1
        strlen=${#line}
        for (( i=strlen-1; i>=0; i-- ))
        do
            char=${line:i:1}
            if [[ "$char" == '"' ]]; then
                r_double_quote=$i
                break
            fi 
        done  
        for (( i=0; i<strlen; i++ ))
        do
            char=${line:i:1}
            if [[ "$char" == '"' ]]; then
                l_double_quote=$i
                break
            fi
        done
        path_to_current_logger_files=${line:l_double_quote+1:r_double_quote-l_double_quote-2}
        break
    fi 
done < "$file"
OUTPUT=$(realpath ../../run.sh)
/bin/bash $OUTPUT
