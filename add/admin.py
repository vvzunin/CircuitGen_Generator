from django.contrib import admin

from .models import FromRandomTruthTable
from .models import RandLevel
from .models import NumOperations
from .models import GeneticPlayback
from .models import GeneticSelection
from .models import GeneticMutation

admin.site.register(FromRandomTruthTable)
admin.site.register(RandLevel)
admin.site.register(NumOperations)
admin.site.register(GeneticPlayback)
admin.site.register(GeneticSelection)
admin.site.register(GeneticMutation)
