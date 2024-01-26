from django.contrib import admin
from django.urls import path, include

from make_dataset import views
from make_dataset.views import *
# from backend.views import front
from .views import front
from add_parameter.views import *
from rest_framework import routers


router = routers.SimpleRouter()
router.register(r'add_parameter', AddParameterAPISet)
router.register(r'datasets', DatasetList)

urlpatterns = [
    path('', front, name="front"),
    path('add', front),
    path('admin/', admin.site.urls),
    path('api/', include(router.urls)),
    path('api/add_dataset', views.add_dataset),
    path('api/progress_of_datasets', views.progress_of_datasets),
    # path('api/add_parameter', AddParameterAPI.as_view()),
]
