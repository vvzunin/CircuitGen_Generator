import random
import subprocess

from django.core import serializers
from django.http import JsonResponse
from django.shortcuts import render
from django.http import HttpResponse
from add_parameter.views import *
import json


def make_dataset(request):
    data = AddParameter.objects.all().values()
    dataset_id = "%032x" % random.getrandbits(128)
    cpp_function(data, dataset_id)
    return HttpResponse("Ok")


def cpp_function(data, dataset_id):
    # run cpp code here
    print(dataset_id)
    print(data)

    data = list(data)[0]

    data['request_id'] = dataset_id

    with open(f'data_{dataset_id}.json', 'w', encoding='utf-8') as f:
        json.dump(data, f, ensure_ascii=False, indent=4)

    subprocess.Popen(f"./Generator/source/build/prog --json_path=./data_{dataset_id}.json", shell=True)
    return HttpResponse("https://youtu.be/dQw4w9WgXcQ")
