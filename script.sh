#!/bin/bash

FILENAME="test.txt"
FILEPATH="/Users/danilmacin/hse/iot/coursach/MIEM_coursach/$FILENAME"
TOKEN=""

# Простая функция для парсинга свойств из JSON
function parseJson()
{
    local output
    regex="(\"$1\":[\"]?)([^\",\}]+)([\"]?)"
    [[ $2 =~ $regex ]] && output=${BASH_REMATCH[2]}
    echo $output
}

# Функция для отправки файла
function sendFile
{
    echo "Start sending a file: $1"

    # Получаем URL для загрузки файла
    sendUrlResponse=`curl -s -H "Authorization: OAuth $TOKEN" "https://cloud-api.yandex.net/v1/disk/resources/upload/?path=app:/$FILENAME&overwrite=true"`
    echo "After send url"
    sendUrl=$(parseJson 'href' $sendUrlResponse)
    echo "After send url2"
    echo "Url"
    echo $sendUrl
    # Отправляем файл
    sendFileResponse=`curl -s -T $FILEPATH -H "Authorization: OAuth $TOKEN" $sendUrl`
    echo "Completing a file upload: $1"
}

sendFile $FILEPATH
