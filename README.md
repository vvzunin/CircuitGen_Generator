# Сборка и запуск компонент
## Backend + frontend
### Установка
pip install djangorestframework

pip install django-cors-headers


python manage.py makemigrations

python manage.py migrate

cd frontend

npm i

npm run build

cd ..
### Запуск
python manage.py runserver


## Generator
### Build
./run.sh

### Запуск одного json фалйа с информацией
<path_to_compiled_prog> --json_path <path_to_json>

# Планы на будущее
## Написать полностью свою архитектуру нейронное сети с нуля
## Реализовать больше методов оценки надёжности
## Исправить сомнительные участки в коде, которые были помечены в ходе работы
## Написать больше тестов на тетестируемые функции
## Написать программу визуализации схем, которая будет заметно быстрее работать, чем yosys
## Сделать кросс-платформенность

