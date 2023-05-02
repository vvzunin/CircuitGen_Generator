from django.db import models
import json


def parameters_of_generation_default():
    return {
        "parameter_id": 0,
        "data": {
            "yandex_link_to_parameter": "some_link",
            "data_of_parameter": {
                "min_in": 0,
                "max_in": 0
            }
        }
    }


class Dataset(models.Model):
    parameters_of_generation = models.JSONField()
