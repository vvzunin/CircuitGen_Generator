from django.db import models


def contact_default():
    return {"email": "to1@example.com"}


class Dataset(models.Model):
    parameters_of_generation = models.JSONField("ContactInfo", default=contact_default)
    parameters_of_generation = models.JSONField("ContactInfo", default=contact_default)
