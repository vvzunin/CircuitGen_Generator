import random
import subprocess

from django.core import serializers
from django.http import JsonResponse
from django.shortcuts import render
from django.http import HttpResponse
from add_parameter.views import *
import json
import os


def make_dataset(request):
    data = AddParameter.objects.all().values()
    dataset_id = "%032x" % random.getrandbits(128)
    cpp_function(data, dataset_id)
    return HttpResponse("Ok")


def cpp_function(data, dataset_id):
    # run cpp code here
    # print(dataset_id)
    # print(data)

    data = list(data)[0]

    data['request_id'] = dataset_id

    with open(f'data_{dataset_id}.json', 'w', encoding='utf-8') as f:
        json.dump(data, f, ensure_ascii=False, indent=4)

    subprocess.Popen(f"./Generator/source/build/prog --json_path=./data_{dataset_id}.json", shell=True)
    return HttpResponse("https://youtu.be/dQw4w9WgXcQ")


def make_image_from_verilog(request):
    path = 'export PATH="/Users/kudr.max/PycharmProjects/1290_project/oss-cad-suite/bin:$PATH"'
    base_folder_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    verilog_name = "CNFT.v"
    verilog_path = base_folder_path + "/scheme_images/" + verilog_name

    image_id = "image_" + "%032x" % random.getrandbits(128)
    image_path = base_folder_path + "/scheme_images/" + image_id
    image_path_dot_png = image_path + ".png"

    yo = "yosys -p'read_verilog " + verilog_path + "; show -format png -prefix " + image_path + "'"
    os.system(path + ";" + yo)
    return JsonResponse({"image_path": image_path_dot_png})
