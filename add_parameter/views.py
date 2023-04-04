from django.shortcuts import render
from rest_framework import generics, viewsets, status
from rest_framework.response import Response
from rest_framework.views import APIView

from .models import *
from .serializers import *


class AddParameterAPISet(viewsets.ModelViewSet):
    queryset = AddParameter.objects.all()
    serializer_class = AddParameterSerializer

