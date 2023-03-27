from django.shortcuts import render
from rest_framework import viewsets
from .serializer import *

class TruthTableViewSet(viewsets.ModelViewSet):
    queryset = TruthTable.objects.all()
    serializer_class = TruthTableSerializer

class RandLevelViewSet(viewsets.ModelViewSet):
    queryset = RandLevel.objects.all()
    serializer_class = RandLevelSerializer

class NumOperationsViewSet(viewsets.ModelViewSet):
    queryset = NumOperations.objects.all()
    serializer_class = NumOperationsSerializer

class GeneticPlaybackViewSet(viewsets.ModelViewSet):
    queryset = GeneticPlayback.objects.all()
    serializer_class = GeneticPlaybackSerializer

class GeneticMutationViewSet(viewsets.ModelViewSet):
    queryset = GeneticMutation.objects.all()
    serializer_class = GeneticMutationSerializer

class GeneticSelectionViewSet(viewsets.ModelViewSet):
    queryset = GeneticSelection.objects.all()
    serializer_class = GeneticSelectionSerializer

def main(request):
    return render(request, 'backend/index.html')
