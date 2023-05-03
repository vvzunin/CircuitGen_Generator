### Backend + frontend

pip install djangorestframework
pip install django-cors-headers

python manage.py makemigrations
python manage.py migrate

cd frontend
npm i
npm run build
cd ..

python manage.py runserver