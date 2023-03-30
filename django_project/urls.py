from django.contrib import admin
from django.urls import path, include

# from backend.views import front
from .views import front
from add.views import *
from rest_framework import routers


router = routers.SimpleRouter()
router.register(r'table', FromRandomTruthTableAPISet)
router.register(r'rand', RandLevelViewAPISet)
router.register(r'num', NumOperationsViewAPISet)
router.register(r'gen_play', GeneticPlaybackViewAPISet)
router.register(r'gen_mut', GeneticMutationViewAPISet)
router.register(r'gen_sel', GeneticSelectionViewAPISet)

urlpatterns = [
    path('', front, name="front"),
    path('admin/', admin.site.urls),
    path('api/', include(router.urls)),
    # path('api/fromrandomtruthtablelist', FromRandomTruthTableAPISet.as_view()),
    # path('api/randlevellist', RandLevelAPIList.as_view()),
    # path('api/numoperationslist', NumOperationsAPIList.as_view()),
    # path('api/geneticplaybacklist', GeneticPlaybackAPIList.as_view()),
    # path('api/geneticmutationlist', GeneticMutationAPIList.as_view()),
    # path('api/geneticselectionlist', GeneticSelectionAPIList.as_view()),
    # path('api/addparameterlist', AddParameterAPISet.as_view()),
]
