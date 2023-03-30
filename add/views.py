from django.shortcuts import render
from rest_framework import generics
from rest_framework.views import APIView

from .models import FromRandomTruthTable
from .serializers import FromRandomTruthTableSerializer


class FromRandomTruthTableAPIview(generics.ListCreateAPIView):
    queryset = FromRandomTruthTable.objects.all()
    serializer_class = FromRandomTruthTableSerializer
