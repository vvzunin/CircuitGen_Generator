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
    #print(dataset_id)
    #print(data)

    data = list(data)[0]

    data['request_id'] = dataset_id

    with open(f'data_{dataset_id}.json', 'w', encoding='utf-8') as f:
        json.dump(data, f, ensure_ascii=False, indent=4)

    subprocess.Popen(f"./Generator/source/build/prog --json_path=./data_{dataset_id}.json", shell=True)
    return HttpResponse("https://youtu.be/dQw4w9WgXcQ")


def make_image_from_verilog(request):
    # scheme_images_path = '/Users/kudr.max/PycharmProjects/1290_project/source/scheme_images'
    # os.system('pwd')
    # os.system('cd ' + scheme_images_path)
    # os.system('pwd')
    # os.system('yosys')

    # os.system('source /Users/kudr.max/PycharmProjects/1290_project/oss-cad-suite/environment')
    # os.system('read_verilog /Users/kudr.max/oss-cad-suite/my_verilogs/CNFT.v')
    # os.system('yosys')
    # os.system('show -format png -prefix /Users/kudr.max/oss-cad-suite/my_verilogs/name')

    # os.system('read_verilog /Users/kudr.max/oss-cad-suite/my_verilogs/CNFT.v')
    # os.system('show')
    # os.system('dot -Tpng yosys_show.dot -o name.png')
    # os.system('dot -Tpng ' + dot_path + ' -o image.png')
    path = 'export PATH="/Users/kudr.max/PycharmProjects/1290_project/oss-cad-suite/bin:$PATH"'
    yo = "yosys -p 'read_verilog /Users/kudr.max/PycharmProjects/1290_project/source/CNFT.v; show -format png -prefix /Users/kudr.max/PycharmProjects/1290_project/source/name'"
    os.system(path + ";" + yo)
    return HttpResponse('sheme_image')
