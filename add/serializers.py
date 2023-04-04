from rest_framework import serializers
from .models import *


class AddParameterSerializer(serializers.ModelSerializer):
    class Meta:
        model = AddParameter
        fields = "__all__"
        # extra_kwargs = {field.name:{'required': False, 'allow_null': True} for field in AddParameter._meta.get_fields()}
