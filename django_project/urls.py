from django.contrib import admin
from django.urls import path, include

# from backend.views import front
from .views import front
from add_parameter.views import *
from rest_framework import routers


router = routers.SimpleRouter()
router.register(r'add_parameter', AddParameterAPISet)

urlpatterns = [
    path('', front, name="front"),
    path('admin/', admin.site.urls),
    path('api/', include(router.urls)),
    # path('api/add_parameter', AddParameterAPI.as_view()),
]
