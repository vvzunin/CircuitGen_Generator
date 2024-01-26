from django.db import models
from rest_framework import serializers


class AddParameter(models.Model):
    type_of_generation = models.CharField(default='From Random Truth Table', max_length=23, choices=(
        ("From Random Truth Table", "From Random Truth Table"),
        ("Rand Level", "Rand Level"),
        ("Num Operation", "Num Operation"),
        ("Genetic reproduction", "Genetic reproduction"),
        ("Genetic mutation", "Genetic mutation"),
        ("Genetic selection", "Genetic selection"),
    ), verbose_name='Метод генерации')

    min_in = models.IntegerField(default=1, verbose_name='Минимальное количество входов')
    max_in = models.IntegerField(default=1, verbose_name='Максимальное количество входов')
    min_out = models.IntegerField(default=1, verbose_name='Минимальное количество выходов')
    max_out = models.IntegerField(default=1, verbose_name='Максимальное количество выходов')
    repeat_n = models.IntegerField(default=1, verbose_name='Количество повторений каждой комбинации')
    seed = models.IntegerField(default=-1, verbose_name='Сид генерации')
    CNFF = models.BooleanField(default=0, verbose_name='CNFF')
    CNFT = models.BooleanField(default=0, verbose_name='CNFT')

    max_level = models.IntegerField(default=1, verbose_name='Максимальное количество уровней')
    max_elem = models.IntegerField(default=0, verbose_name='Максимальное количество элементов')

    leave_empty_out = models.BooleanField(default=0, verbose_name='Оставлять пустые выходы')
    num_and = models.IntegerField(default=0)
    num_nand = models.IntegerField(default=0)
    num_or = models.IntegerField(default=0)
    num_not = models.IntegerField(default=0)
    num_nor = models.IntegerField(default=0)
    num_buf = models.IntegerField(default=0)
    num_xor = models.IntegerField(default=0)
    num_xnor = models.IntegerField(default=0)

    population_size = models.IntegerField(default=0, verbose_name='Размер популяции')
    cycles = models.IntegerField(default=0, verbose_name='Количество циклов')
    out_ratio = models.FloatField(default=0, verbose_name='Коэффициент выхода')
    chromosome_type = models.CharField(max_length=11, choices=(
        ("Truth Table", "Truth Table"),
        ("Other", "Other"),
    ), verbose_name='Тип хромосомы')

    selection_type_parent = models.CharField(max_length=10, choices=(
        ("Panmixia", "Panmixia"),
        ("Inbriding", "Inbriding"),
        ("Otbriding", "Otbriding"),
        ("Tournament", "Tournament"),
        ("Roulette", "Roulette"),
    ), verbose_name='Тип отбора родителей')
    tour_size = models.IntegerField(default=0, verbose_name='Размер турнира')
    playback_type = models.CharField(max_length=28, choices=(
        ("CrossingEachExitInTurnMany", "CrossingEachExitInTurnMany"),
        ("CrossingUniform", "CrossingUniform"),
        ("CrossingTriadic", "CrossingTriadic"),
        ("CrossingReducedReplace", "CrossingReducedReplace"),
        ("CrossingSnuffling", "CrossingSnuffling"),
    ), verbose_name='Тип воиспроизведения')
    ref_points = models.IntegerField(default=0, verbose_name='Reference points')
    mask_prob = models.FloatField(default=0, verbose_name='maskProbability')
    rec_num = models.IntegerField(default=0, verbose_name='recombinationNumber')

    mut_type = models.CharField(max_length=12, choices=(
        ("Binary", "Binary"),
        ("Density", "Density"),
        ("AccessionDel", "AccessionDel"),
        ("IncertDel", "IncertDel"),
        ("Exchange", "Exchange"),
        ("Delete", "Delete"),
    ), verbose_name='Тип мутации')
    mut_chance = models.FloatField(default=0, verbose_name='Вероятность мутации')
    swap_type = models.CharField(max_length=12, choices=(
        (0, "Cell Above"),
        (1, "Cell Right"),
        (2, "Four Cells"),
        (3, "String Above"),
    ), verbose_name='Тип обмена')
    ratio_in_table = models.FloatField(default=0, verbose_name='Соотношение в таблице истинности')

    selection_type = models.CharField(max_length=6, choices=(
        ("Base", "Base"),
        ("Other", "Other"),
    ), verbose_name='Тип отбора')
    surv_num = models.IntegerField(default=0, verbose_name='Количество выживших')
