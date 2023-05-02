import random
import subprocess

from django.core import serializers
from django.http import JsonResponse
from django.shortcuts import render
from django.http import HttpResponse
from add_parameter.views import *
import json
import os

from rest_framework import viewsets
from .models import Dataset
from .serializers import DatasetSerializer


class DatasetList(viewsets.ModelViewSet):
    queryset = Dataset.objects.all()
    serializer_class = DatasetSerializer


def add_dataset(request):

    # добавление пустого датасета в бд датасетов

    list_of_parameters = list(AddParameter.objects.all().values())
    list_of_id_of_parameters = []

    for obj in list_of_parameters:
        yandex_link_to_parameter = "empty link"
        my_dict = {
            "id_of_parameter": obj['id'],
            "yandex_link_of_parameter": yandex_link_to_parameter
        }
        list_of_id_of_parameters.append(my_dict)

    Dataset.objects.create(parameters_of_generation=list_of_id_of_parameters)

    # # получить параметры генерации
    # data = AddParameter.objects.all().values()
    # dataset_id = "%032x" % random.getrandbits(128)
    #
    # # запуск генератора
    # cpp_function(data, dataset_id)

    # загрузка на яндекс диск

    # изменение ссылки на яндекс диск на актуальную

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
    path = 'export PATH="/Users/kudr.max/PycharmProjects/1290_project/source/Yosys/bin:$PATH"'
    base_folder_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    verilog_name = "CNFT.v"
    verilog_path = base_folder_path + "/scheme_images/" + verilog_name

    image_id = "image_" + "%032x" % random.getrandbits(128)
    image_path = base_folder_path + "/scheme_images/" + image_id
    image_path_dot_png = image_path + ".png"

    yo = "yosys -p'read_verilog " + verilog_path + "; show -format png -prefix " + image_path + "'"
    os.system(path + ";" + yo)
    return JsonResponse({"image_path": image_path_dot_png})
