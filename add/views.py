from django.shortcuts import render
from rest_framework import generics, viewsets
from rest_framework.response import Response
from rest_framework.views import APIView

from .models import *
from .serializers import *


# class AddParameterAPISet(viewsets.ModelViewSet):
#     # queryset = AddParameter.objects.all()
#     # serializer_class = AddParameterSerializer
#     pass


class AddParameterAPISet(APIView):
    def get(self, request):
        return Response({
            'FromRandomTruthTable': list(FromRandomTruthTable.objects.all().values()),
            'RandLevel': list(RandLevel.objects.all().values()),
            'NumOperations': list(NumOperations.objects.all().values()),
            'GeneticPlayback': list(GeneticPlayback.objects.all().values()),
            'GeneticSelection': list(GeneticSelection.objects.all().values()),
            'GeneticMutation': list(GeneticMutation.objects.all().values()),
        })



class FromRandomTruthTableAPISet(viewsets.ModelViewSet):
    queryset = FromRandomTruthTable.objects.all()
    serializer_class = FromRandomTruthTableSerializer


class RandLevelViewAPISet(viewsets.ModelViewSet):
    queryset = RandLevel.objects.all()
    serializer_class = RandLevelSerializer


class NumOperationsViewAPISet(viewsets.ModelViewSet):
    queryset = NumOperations.objects.all()
    serializer_class = NumOperationsSerializer


class GeneticPlaybackViewAPISet(viewsets.ModelViewSet):
    queryset = GeneticPlayback.objects.all()
    serializer_class = GeneticPlaybackSerializer


class GeneticMutationViewAPISet(viewsets.ModelViewSet):
    queryset = GeneticMutation.objects.all()
    serializer_class = GeneticMutationSerializer


class GeneticSelectionViewAPISet(viewsets.ModelViewSet):
    queryset = GeneticSelection.objects.all()
    serializer_class = GeneticSelectionSerializer
