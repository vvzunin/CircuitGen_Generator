from rest_framework import serializers
from .models import *

class TruthTableSerializer(serializers.ModelSerializer):
    class Meta:
        model = TruthTable
        fields = "__all__"

class RandLevelSerializer(serializers.ModelSerializer):
    class Meta:
        model = RandLevel
        fields = "__all__"

class NumOperationsSerializer(serializers.ModelSerializer):
    class Meta:
        model = NumOperations
        fields = "__all__"

class GeneticPlaybackSerializer(serializers.ModelSerializer):
    class Meta:
        model = GeneticPlayback
        fields = "__all__"

class GeneticMutationSerializer(serializers.ModelSerializer):
    class Meta:
        model = GeneticMutation
        fields = "__all__"

class GeneticSelectionSerializer(serializers.ModelSerializer):
    class Meta:
        model = GeneticSelection
        fields = "__all__"