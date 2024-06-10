#!/bin/bash
file="../CMakeLists.txt" # path to CMakeLists.txt for tests
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
# We can use `str3 = “$str1$str2″`

removeTimeFromLog(){
    local log="2024-06-10 00:29:38,762 INFO minInputs: 50; maxInputs: 50; minOutputs: 50; maxOutputs: 50; eachIteration: 1; generationParameters:"
    local ch=" "
    strlen=${#log}
    counter=0
    needed_pos=-1
    for (( i=0; i<strlen; i++ ))
    do
        char=${log:i:1}
        
        if [[ "$char" == "$ch" ]]; then
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

findFirstPosOfCharacter(){
    local s=$1
    local ch=$2
    strlen=${#s}
    for ((i=0; i<strlen; i++))
    do
        char=${s:i:1}
        if [[ "$char" == "$ch" ]]; then
            return $i 
        fi 
    done 
}

findLastPosOfCharacter(){
    local s=$1
    local ch=$2
    strlen=${#s}
    for ((i=strlen-1; i>=0; i--))
    do
        char=${s:i:1}
        if [[ "$char" == "$ch" ]]; then
            return $i 
        fi 
    done 
}



for dir in ./correct_logs/*/
do
    findLastPosOfCharacter $dir "/"
    name_of_json_file=$dir
    pos_of_slash=$?
    strlen=${#name_of_json_file}
    needed_length=$((strlen-1))
    name_of_json_file=${name_of_json_file:0:needed_length}
    dir=$name_of_json_file
    strlen=${#name_of_json_file}
    findLastPosOfCharacter $name_of_json_file "/"
    pos_of_slash=$?
    ((pos_of_slash++))
    strlen=${#name_of_json_file}
    needed_length=$((strlen-pos_of_slash))
    name_of_json_file=${name_of_json_file:pos_of_slash:needed_length}
 

    /bin/bash $OUTPUT $name_of_json_file.json
    log_for_database="`cat $dir/log_for_database_generator_parameters.log`"
    log_for_generation="`cat $dir/log_for_generation_parameters.log`"

    
    # Search include directory

    cur=$OUTPUT 
    
    findLastPosOfCharacter $cur '/'
    pos=$?
    needed_length=$pos
    cur=${OUTPUT:0:needed_length}
    
    examined_log_for_database=""
    examined_log_for_generation=""

    path="$cur/include/path/to"
    for dir2 in $path/*/
    do
        examined_log_for_database="`cat $dir2/log_for_database_generator_parameters.log`"
        examined_log_for_generation="`cat $dir2/log_for_generation_parameters.log`"
    done 




    strlen=${#examined_log_for_database}
    counter=0
    needed_pos=-1
    for (( i=0; i<strlen; i++ ))
    do
        char=${examined_log_for_database:i:1}
        if [[ "$char" == " " ]]; then
            ((counter++)) 
        fi 
        if [[ $counter -eq 2 ]]; then
            needed_pos=$i
            break 
        fi 
    done 
    ((needed_pos++))
    strlen=${#examined_log_for_database}
    needed_length=$((strlen - needed_pos))
    #examined_log_for_database2=${examined_log_for_database, needed_pos, needed_length2}
    examined_log_for_database=${examined_log_for_database:needed_pos:needed_length}
    




    strlen=${#examined_log_for_generation}
    counter=0
    needed_pos=-1
    for (( i=0; i<strlen; i++ ))
    do
        char=${examined_log_for_generation:i:1}
        if [[ "$char" == " " ]]; then
            ((counter++)) 
        fi 
        if [[ $counter -eq 2 ]]; then
            needed_pos=$i
            break 
        fi 
    done 
    ((needed_pos++))
    strlen=${#examined_log_for_generation}
    needed_length=$((strlen - needed_pos))
    #examined_log_for_database2=${examined_log_for_database, needed_pos, needed_length2}
    examined_log_for_generation=${examined_log_for_generation:needed_pos:needed_length}


    
    strlen=${#log_for_database}
    counter=0
    needed_pos=-1
    for (( i=0; i<strlen; i++ ))
    do
        char=${log_for_database:i:1}
        if [[ "$char" == " " ]]; then
            ((counter++)) 
        fi 
        if [[ $counter -eq 2 ]]; then
            needed_pos=$i
            break 
        fi 
    done 
    ((needed_pos++))
    strlen=${#log_for_database}
    needed_length=$((strlen - needed_pos))
    #examined_log_for_database2=${examined_log_for_database, needed_pos, needed_length2}
    log_for_database=${log_for_database:needed_pos:needed_length}
    




    strlen=${#log_for_generation}
    counter=0
    needed_pos=-1
    for (( i=0; i<strlen; i++ ))
    do
        char=${log_for_generation:i:1}
        if [[ "$char" == " " ]]; then
            ((counter++)) 
        fi 
        if [[ $counter -eq 2 ]]; then
            needed_pos=$i
            break 
        fi 
    done 
    ((needed_pos++))
    strlen=${#log_for_generation}
    needed_length=$((strlen - needed_pos))
    #examined_log_for_database2=${examined_log_for_database, needed_pos, needed_length2}
    log_for_generation=${log_for_generation:needed_pos:needed_length}

    if [[ "$log_for_generation" != "$examined_log_for_generation" ]]; then
        echo "The json that program generated differ from standard. Please fix all bugs."
        echo $log_for_generation
        echo $examined_log_for_generation
    fi 

    if [[ "$log_for_generation" != "$examined_log_for_generation" ]]; then
        echo "The json that program generated differ from standard. Please fix all bugs."
        echo $log_for_generation
        echo $examined_log_for_generation
    fi 

    # pos=$?
    # strlen=${#examined_log_for_database}
    # needed_length=$((strlen - pos))
    # examined_log_for_database2=${examined_log_for_database:pos:needed_length}
    # echo $pos
    # $char=${examined_log_for_database,10,1}
    # if [[ $char==" " ]]; then
    #     echo "It worked out. It means the problem in send parameters"
    # fi






    # removeTimeFromLog $examined_log_for_generation 
    # pos=$?
    # strlen=${#examined_log_for_generation}
    # needed_length=$((strlen - pos))
    # examined_log_for_generation=${examined_log_for_generation:pos:needed_length}
    # # if [[ "$log_for_database" != "$examined_log_for_database" ]]; then
    # #         echo "Something went terrible wrong"
    # # fi 
    
    # echo "Log_for_database"
    # echo $log_for_database
    # echo "examined_log_for_database"
    # echo $examined_log_for_database2







    # for file in $dir*
    # do
    #     pt=$(<$file)
    #     removeTimeFromLog "$pt"
    #     needed_length=$?
    #     strlen=${#pt}
    #     needed_length=$((strlen - needed_pos))
    # done 
done 