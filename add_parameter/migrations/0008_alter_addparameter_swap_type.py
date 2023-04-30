# Generated by Django 4.1.7 on 2023-04-30 08:07

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('add_parameter', '0007_rename_empty_out_addparameter_leave_empty_out_and_more'),
    ]

    operations = [
        migrations.AlterField(
            model_name='addparameter',
            name='swap_type',
            field=models.CharField(choices=[(0, 'Cell Above'), (1, 'Cell Right'), (2, 'Four Cells'), (3, 'String Above')], max_length=12, verbose_name='Тип обмена'),
        ),
    ]
