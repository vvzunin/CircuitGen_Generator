import pathlib
import random
import subprocess

from django.http import JsonResponse
from django.http import HttpResponse
from add_parameter.views import *
import json

from rest_framework import viewsets

from .models import Dataset
from .serializers import DatasetSerializer

from pathlib import Path
import glob

import io
import os

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
        obj['swap_type'] = int(obj['swap_type'])

    # запуск генератора
    # cpp_function(parameters_of_generation, dataset_id)

    # запус Yosys
    make_image_from_verilog(9999)

    # загрузка на яндекс диск
    # upload_to_synology(dataset_id)

    # изменение ссылки на synology на актуальную
    # ДОПИСАТЬ

    # удалить локальную папку с датасетом
    # ДОПИСАТЬ

    print("add_dataset is finished")
    return HttpResponse("Ok")


def cpp_function(parameters_of_generation, dataset_id):
    # print(parameters_of_generation)
    for obj in parameters_of_generation:
        obj['dataset_id'] = dataset_id
    with open(f'temp_for_json/data_{dataset_id}.json', 'w', encoding='utf-8') as f:
        json.dump(parameters_of_generation, f, ensure_ascii=False, indent=4)
    subprocess.Popen(f"./Generator/source/build/prog --json_path=./temp_for_json/data_{dataset_id}.json",
                     shell=True).wait()


def make_image_from_verilog(dataset_id):
    dataset_id = int(dataset_id)
    path = 'export PATH="/Users/kudr.max/PycharmProjects/1290_project/source/data/Yosys/bin:$PATH"'
    base_folder_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    directory = f"./dataset/{dataset_id}/"
    print(directory)
    for verilog_path in glob.iglob(f'{directory}/**/**/*.v', recursive=True):
        print("yosys")
        image_path = pathlib.Path(verilog_path).parent
        full_name = os.path.basename(verilog_path)
        file_name = os.path.splitext(full_name)
        image_path = './' + str(image_path) + '/' + file_name[0]
        yo = "yosys -p'read_verilog " + verilog_path + "; clean; show -format png -prefix " + image_path + "'"
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
        in_total += (data_param["max_in"] - data_param["min_in"] + 1) * (
                    data_param["max_out"] - data_param["min_out"] + 1) * data_param["repeat_n"]
        if data_param["CNFF"] is True or data_param["CNFT"] is True:
            in_total *= 2
    return in_total


def upload_to_synology(dataset_id):
    NAS_USER = 'project1290'
    NAS_PASS = '~.*{*$7]NJ1[pS`\\'
    NAS_IP = 'vvzunin.me'
    NAS_PORT = 10003
    dsm_version = '7'

    with SynologyDrive(NAS_USER, NAS_PASS, NAS_IP, NAS_PORT, dsm_version=dsm_version) as synd:
        dataset_id = str(dataset_id)
        dataset_dir = './dataset/' + dataset_id
        for param in os.listdir(dataset_dir):
            param_dir = '/'.join([dataset_dir, param])
            for circuit in os.listdir(param_dir):
                extension_lst = ['.v', '.json', '.png']
                for extension in extension_lst:
                    verilog_path = '/'.join([param_dir, circuit, circuit]) + extension
                    with open(verilog_path, 'rb') as file:
                        bfile = io.BytesIO(file.read())
                        bfile.name = '/'.join([dataset_id, param, circuit, circuit]) + extension
                        synd.upload_file(bfile, dest_folder_path='/team-folders/circuits/')