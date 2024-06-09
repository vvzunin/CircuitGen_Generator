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
OUTPUT=$(realpath ../../buildGenerator.sh)
# We can use `str3 = “$str1$str2″`

removeTimeFromLog(){
    local log=$1
    strlen=${#log}
    counter=0
    needed_pos=-1
    for (( i=0; i<strlen; i++ ))
    do
        char=${log:i:1}
        if [[ "$char" == ' ' ]]; then
            ((counter++)) 
        fi 
        if [[ $counter -eq 2 ]]; then
            needed_pos=$i
            break 
        fi 
    done 
    ((needed_pos++))
    return $needed_pos
}
pt="a b c123"
removeTimeFromLog "$pt"
$needed_length=$?
echo ${needed_pos}
strlen=${#pt}
needed_length=$((strlen - needed_pos))
echo ${pt:needed_pos:needed_length}

# for dir in ./correct_logs/*/
# do
#     for file in $dir*
#     do
#         value=$(<$file)
#         echo $value 
#     done 
# done 