from django.urls import path, include
from . import views

urlpatterns = [
    # path('', include('backend.urls')),
    path('', views.front, name="front"),
]