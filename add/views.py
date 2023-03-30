from django.shortcuts import render
from rest_framework import generics
from rest_framework.views import APIView

from .models import *
from .serializers import *


class FromRandomTruthTableAPIList(generics.ListCreateAPIView):
    queryset = FromRandomTruthTable.objects.all()
    serializer_class = FromRandomTruthTableSerializer


class RandLevelAPIList(generics.ListCreateAPIView):
    queryset = RandLevel.objects.all()
    serializer_class = RandLevelSerializer


class NumOperationsAPIList(generics.ListCreateAPIView):
    queryset = NumOperations.objects.all()
    serializer_class = NumOperationsSerializer


class GeneticPlaybackAPIList(generics.ListCreateAPIView):
    queryset = GeneticPlayback.objects.all()
    serializer_class = GeneticPlaybackSerializer


class GeneticMutationAPIList(generics.ListCreateAPIView):
    queryset = GeneticMutation.objects.all()
    serializer_class = GeneticMutationSerializer


class GeneticSelectionAPIList(generics.ListCreateAPIView):
    queryset = GeneticSelection.objects.all()
    serializer_class = GeneticSelectionSerializer
