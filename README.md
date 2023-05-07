# Backend + frontend

pip install djangorestframework
pip install django-cors-headers

python manage.py makemigrations
python manage.py migrate

cd frontend
npm i
npm run build
cd ..

python manage.py runserver


# Generator
// TODO: Сделать .sh скрипты
## Build
cd Generator/source
mkdir build
cd build

cmake ..
make

## Run
mkdir dataset
cd dataset
mkdir FromRandomTruthTable Genetic FromRandomRandLvl FromNumOperations // TODO: поправить названия папок
<path_to_compiled_prog> --json_path <path_to_json>
