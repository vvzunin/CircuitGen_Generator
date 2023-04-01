from django.db import models


class AddParameter(models.Model):
    min_in = models.IntegerField(default=None, verbose_name='Минимальное количество входов')
    max_in = models.IntegerField(default=None, verbose_name='Максимальное количество входов')
    min_out = models.IntegerField(default=None, verbose_name='Минимальное количество выходов')
    max_out = models.IntegerField(default=None, verbose_name='Максимальное количество выходов')
    repeat_n = models.IntegerField(default=None, verbose_name='Количество повторений каждой комбинации')
    limit = models.BooleanField(default=None, verbose_name='Ограничение генерации')
    CNFF = models.BooleanField(default=None, verbose_name='CNFF')
    CNFT = models.BooleanField(default=None, verbose_name='CNFT')

    max_level = models.IntegerField(default=None, verbose_name='Максимальное количество уровней')
    max_elem = models.IntegerField(default=None, verbose_name='Максимальное количество элементов')

    limit = models.BooleanField(default=None, verbose_name='Ограничение генерации')
    CNFF = models.BooleanField(default=None, verbose_name='CNFF')
    CNFT = models.BooleanField(default=None, verbose_name='CNFT')

    empty_out = models.BooleanField(default=None, verbose_name='Оставлять пустые выходы')
    oper_type = models.CharField(default=None, max_length=100, db_index=True, verbose_name=' ')
    num = models.IntegerField(default=None, verbose_name=' ')

    population = models.IntegerField(default=None, verbose_name='Размер популяции')
    cycles = models.IntegerField(default=None, verbose_name='Количество циклов')
    u_out = models.IntegerField(default=None, verbose_name='Коэффициент выхода')
    chromosome_type = models.CharField(default=None, max_length=100, verbose_name='Тип хромосомы')

    selection_type_parent = models.CharField(default=None, max_length=100, verbose_name='Тип отбора родителей')
    tour_size = models.IntegerField(default=None, verbose_name='Размер турнира')
    playback_type = models.CharField(default=None, max_length=100, verbose_name='Тип воиспроизведения')
    ref_points = models.IntegerField(default=None, verbose_name='Reference points')
    mask_prob = models.IntegerField(default=None, verbose_name='maskProbability')
    rec_num = models.IntegerField(default=None, verbose_name='recombinationNumber')

    mut_type = models.CharField(default=None, max_length=100, verbose_name='Тип мутации')
    mut_chance = models.IntegerField(default=None, verbose_name='Вероятность мутации')
    swap_type = models.IntegerField(default=None, verbose_name='Тип обмена')
    ratio = models.IntegerField(default=None, verbose_name='Соотношение в таблице истинности')

    selection_type = models.CharField(default=None, max_length=100, verbose_name='Тип отбора')
    surv_num = models.IntegerField(default=None, verbose_name='Количество выживших')
