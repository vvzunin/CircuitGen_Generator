from django.http import JsonResponse
from django.shortcuts import render
from django.http import HttpResponse
from add_parameter.views import *


def make_dataset(request):
    cpp_function(AddParameter.objects.all().values())
    return HttpResponse("Ok")


def cpp_function(data):
    # run cpp code here
    print(data)
    return HttpResponse("https://youtu.be/dQw4w9WgXcQ")
