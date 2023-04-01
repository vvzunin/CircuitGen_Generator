from rest_framework import serializers
from .models import *


class AddParameterSerializer(serializers.ModelSerializer):
    class Meta:
        model = AddParameter
        fields = "__all__"
