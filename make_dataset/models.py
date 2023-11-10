from django.db import models
import json

# def parameters_of_generation_default():
#     pass


class Dataset(models.Model):
    ready = models.BooleanField(default=0, verbose_name='ready')
    parameters_of_generation = models.JSONField()
