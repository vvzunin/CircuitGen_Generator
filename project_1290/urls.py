from django.contrib import admin
from django.urls import path, include
from rest_framework import routers
from backend.views import *

router = routers.SimpleRouter()
router.register(r'table', TruthTableViewSet)
router.register(r'rand', RandLevelViewSet)
router.register(r'num', NumOperationsViewSet)
router.register(r'gen_play', GeneticPlaybackViewSet)
router.register(r'gen_mut', GeneticMutationViewSet)
router.register(r'gen_sel', GeneticSelectionViewSet)

urlpatterns = [
    path('admin/', admin.site.urls),
    path('', main, name='main'),
    path('', include(router.urls))
]
