from django.shortcuts import render
from django.http import HttpResponse


def make_dataset_function(request):
    # some magic happens here
    return HttpResponse("Dataset was generated")
