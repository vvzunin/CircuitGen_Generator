from django.db import models


class AddParameter(models.Model):
    min_in = models.IntegerField(null=False, default=1, verbose_name='Минимальное количество входов')
    max_in = models.IntegerField(null=False, default=1, verbose_name='Максимальное количество входов')
    min_out = models.IntegerField(null=False, default=1, verbose_name='Минимальное количество выходов')
    max_out = models.IntegerField(null=False, default=1, verbose_name='Максимальное количество выходов')
    repeat_n = models.IntegerField(null=False, default=1, verbose_name='Количество повторений каждой комбинации')

    class Meta:
        abstract = True


class FromRandomTruthTable(AddParameter):
    limit = models.BooleanField(null=False, default=False, verbose_name='Ограничение генерации')
    CNFF = models.BooleanField(null=False, default=False, verbose_name='CNFF')
    CNFT = models.BooleanField(null=False, default=False, verbose_name='CNFT')


class RandLevel(AddParameter):
    max_level = models.IntegerField(null=False, default=1, verbose_name='Максимальное количество уровней')
    max_elem = models.IntegerField(null=False, default=1, verbose_name='Максимальное количество элементов')


class NumOperations(AddParameter):
    empty_out = models.BooleanField(null=False, default=False, verbose_name='Оставлять пустые выходы')
    oper_type = models.CharField(max_length=100, db_index=True, verbose_name=' ')
    num = models.IntegerField(null=False, default=1, verbose_name=' ')


class Genetic(AddParameter):
    population = models.IntegerField(null=False, default=1, verbose_name='Размер популяции')
    cycles = models.IntegerField(null=False, default=1, verbose_name='Количество циклов')
    u_out = models.IntegerField(null=False, default=1, verbose_name='Коэффициент выхода')
    chromosome_type = models.CharField(max_length=100, verbose_name='Тип хромосомы')

    class Meta:
        abstract = True


class GeneticPlayback(Genetic):
    selection_type = models.CharField(max_length=100, verbose_name='Тип отбора родителей')
    tour_size = models.IntegerField(null=False, default=1, verbose_name='Размер турнира')
    playback_type = models.CharField(max_length=100, verbose_name='Тип воиспроизведения')
    ref_points = models.IntegerField(null=False, default=1, verbose_name='Reference points')
    mask_prob = models.IntegerField(null=False, default=1, verbose_name='maskProbability')
    rec_num = models.IntegerField(null=False, default=1, verbose_name='recombinationNumber')


class GeneticMutation(Genetic):
    mut_type = models.CharField(max_length=100, verbose_name='Тип мутации')
    mut_chance = models.IntegerField(null=False, default=1, verbose_name='Вероятность мутации')
    swap_type = models.IntegerField(null=False, default=1, verbose_name='Тип обмена')
    ratio = models.IntegerField(null=False, default=1, verbose_name='Соотношение в таблице истинности')


class GeneticSelection(Genetic):
    selection_type = models.CharField(max_length=100, verbose_name='Тип отбора')
    surv_num = models.IntegerField(null=False, default=1, verbose_name='Количество выживших')
