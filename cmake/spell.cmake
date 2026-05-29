cmake_minimum_required(VERSION 3.14)

macro(default name)
  if(NOT DEFINED "${name}")
    set("${name}" "${ARGN}")
  endif()
endmacro()

default(SPELL_COMMAND codespell)
default(FIX NO)

# -P scripts do not define PROJECT_SOURCE_DIR; this file lives in <root>/cmake/.
get_filename_component(_spell_project_root "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

set(flag "")
if(FIX)
  set(flag -w)
endif()

execute_process(
  COMMAND "${SPELL_COMMAND}" ${flag}
  WORKING_DIRECTORY "${_spell_project_root}"
  RESULT_VARIABLE result
)

if(result MATCHES "No such file or directory")
  message(FATAL_ERROR "Spell checker '${SPELL_COMMAND}' is not found. Install it or override SPELL_COMMAND.")
elseif(result EQUAL "65")
  message(FATAL_ERROR "Run again with FIX=YES to fix these errors.")
elseif(result EQUAL "64")
  message(FATAL_ERROR "Spell checker printed the usage info. Bad arguments?")
elseif(NOT result EQUAL "0")
  message(FATAL_ERROR "Spell checker returned with ${result}")
endif()
