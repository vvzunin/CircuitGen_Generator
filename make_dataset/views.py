import random

from django.http import JsonResponse
from django.shortcuts import render
from django.http import HttpResponse
from add_parameter.views import *


def make_dataset(request):
    data = AddParameter.objects.all().values()
    dataset_id = "%032x" % random.getrandbits(128)
    cpp_function(data, dataset_id)
    return HttpResponse("Ok")


def cpp_function(data, dataset_id):
    # run cpp code here
    # print(dataset_id)
    # print(data)
    return HttpResponse("https://youtu.be/dQw4w9WgXcQ")
