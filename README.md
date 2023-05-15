**1290 Разработка единой системы хранения и обработки датасета цифровых схем**

<font size="5">**Content**:</font>
<a name="content_rus"></a> 
- [Сборка и запуск компонентов](#build_rus)
    - [Backend + frontend](#backend_frontend_rus)
        - [Установка](#install_rus)
        - [Запуск](#run_rus)
    - [Генератор](#generator_rus)
        - [Установка](#generator_build_rus)
        - [Запуск одного json фалйа с информацией](#generator_run_one_json_rus)

# Сборка и запуск компонентов
<a name="build_rus"></a> 
## Backend + frontend
<a name="backend_frontend_rus"></a> 
### Установка
<a name="install_rus"></a> 
```
pip install djangorestframework
pip install django-cors-headers

python manage.py makemigrations
python manage.py migrate
cd frontend
npm i
npm run build
cd ..
```

[&#8593; Contents](#content_rus)

### Запуск
<a name="run_rus"></a> 
```
python manage.py runserver
```

[&#8593; Contents](#content_rus)

## Generator
<a name="generator_rus"></a> 
### Build
<a name="generator_build_rus"></a> 
```
./run.sh
```

[&#8593; Contents](#content_rus)

### Запуск одного json фалйа с информацией
<a name="generator_run_one_json_rus"></a> 
```
<path_to_compiled_prog> --json_path <path_to_json>
```

[&#8593; Contents](#content_rus)

# Планы на будущее
## Написать полностью свою архитектуру нейронное сети с нуля
## Реализовать больше методов оценки надёжности
## Исправить сомнительные участки в коде, которые были помечены в ходе работы
## Написать больше тестов на тетестируемые функции
## Написать программу визуализации схем, которая будет заметно быстрее работать, чем yosys
## Сделать кросс-платформенность

