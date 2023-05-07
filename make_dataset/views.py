import pathlib
import random
import subprocess

from django.http import JsonResponse
from django.http import HttpResponse
from add_parameter.views import *
import json
import os

from rest_framework import viewsets
from .models import Dataset
from .serializers import DatasetSerializer

from pathlib import Path
import glob

# from data.SynologyDrive.synology_drive_api.drive import SynologyDrive
from synology_drive_api.drive import SynologyDrive


class DatasetList(viewsets.ModelViewSet):
    queryset = Dataset.objects.all()
    serializer_class = DatasetSerializer


def add_dataset(request):
    # добавление пустого датасета в бд датасетов

    list_of_parameters = list(AddParameter.objects.all().values())
    list_of_id_of_parameters = []

    for obj in list_of_parameters:
        yandex_link_to_parameter = "empty link"
        obj["yandex_link_of_parameter"] = yandex_link_to_parameter
        list_of_id_of_parameters.append(obj)

    dataset_id = Dataset.objects.create(parameters_of_generation=list_of_id_of_parameters).id

    # получить параметры генерации

    dataset_id = str(dataset_id)
    parameters_of_generation = list(AddParameter.objects.all().values())
    for obj in parameters_of_generation:
        obj['id'] = str(obj['id'])
        obj['swap_type'] = int(obj['swap_type'])

    # запуск генератора

    cpp_function(parameters_of_generation, dataset_id)

    # запус Yosys

    # make_image_from_verilog(dataset_id)
    # make_image_from_verilog(7)

    # загрузка на яндекс диск
    # upload_to_synology()

    # изменение ссылки на яндекс диск на актуальную
    # ??????????

    # удалить json
    # удалить v

    return HttpResponse("Ok")


def cpp_function(parameters_of_generation, dataset_id):
    # print(parameters_of_generation)
    for obj in parameters_of_generation:
        obj['dataset_id'] = dataset_id
    with open(f'temp_for_json/data_{dataset_id}.json', 'w', encoding='utf-8') as f:
        json.dump(parameters_of_generation, f, ensure_ascii=False, indent=4)
    subprocess.Popen(f"./Generator/source/build/prog --json_path=./temp_for_json/data_{dataset_id}.json", shell=True)


def make_image_from_verilog(dataset_id):
    path = 'export PATH="/Users/kudr.max/PycharmProjects/1290_project/source/data/Yosys/bin:$PATH"'
    base_folder_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    directory = f"./dataset/{dataset_id}/"
    for verilog_path in glob.iglob(f'{directory}/**/**/*.v', recursive=True):
        image_path = pathlib.Path(verilog_path).parent
        full_name = os.path.basename(verilog_path)
        file_name = os.path.splitext(full_name)
        image_path = './' + str(image_path) + '/' + file_name[0]
        yo = "yosys -p'read_verilog " + verilog_path + "; show -format png -prefix " + image_path + "'"
        os.system(path + ";" + yo)


def progress_of_datasets(request):
    datasets = list(Dataset.objects.all().values())
    progress_list = {}
    for obj in datasets:
        ready = ready_verilogs(obj["id"])
        in_total = in_total_function(obj)
        progress_dict = {
            "ready": ready,
            "in_total": in_total
        }
        progress_list[obj["id"]] = progress_dict
    return JsonResponse(progress_list)


def ready_verilogs(dataset_id):
    directory = Path(f"./dataset/{dataset_id}/")
    num = len(list(directory.rglob("*.v")))
    return num


def in_total_function(obj):
    list_of_param = obj["parameters_of_generation"]
    in_total = 0
    for param in list_of_param:
        id_of_parameter = param["id_of_parameter"]
        data_param = AddParameter.objects.values().get(id=id_of_parameter)
        in_total += (data_param["max_in"] - data_param["min_in"] + 1) * (data_param["max_out"] - data_param["min_out"] + 1) * data_param["repeat_n"]
        if data_param["CNFF"] is True or data_param["CNFT"] is True:
            in_total *= 2
    return in_total
