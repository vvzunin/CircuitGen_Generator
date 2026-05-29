#!/usr/bin/env bash
# Shared by scripts/ci/docs.sh and scripts/dev/build-docs.sh.
# Runs cmake/docs-ci.cmake once per DOXYGEN_LANG_VARIANTS and moves outputs to
# DOCGEN_OUTPUT_BASE/{html,xml,latex,pdf}/<abbr>/.
#
# Required environment:
#   DOCGEN_ROOT                      — absolute repository root
#   DOCGEN_CMAKE_PROJECT_BINARY_DIR — value for -DPROJECT_BINARY_DIR (e.g. .../build or .../build/dev)
#   DOCGEN_OUTPUT_BASE               — e.g. .../build/docs — results in .../html/en, .../html/ru, ...
#   DOCGEN_STAGING_BASE              — parent of per-variant temp trees (e.g. .../build/docs-tmp → .../docs-tmp/en)
#
# Optional (see cmake/docs-ci.cmake):
#   DOXYGEN_LANG_VARIANTS — default: en=english;ru=russian
#   DOXYGEN_CLANG_ASSISTED_PARSING, DOXYGEN_CLANG_OPTIONS, DOXYGEN_CLANG_DATABASE_PATH
#   DOXYGEN_SKIP_DOT_GRAPHS, DOXYGEN_SKIP_REFMAN_PDF
set -euo pipefail

: "${DOCGEN_ROOT:?DOCGEN_ROOT must be set to the repository root}"
: "${DOCGEN_CMAKE_PROJECT_BINARY_DIR:?}"
: "${DOCGEN_OUTPUT_BASE:?}"
: "${DOCGEN_STAGING_BASE:?}"

DOXYGEN_LANG_VARIANTS="${DOXYGEN_LANG_VARIANTS:-}"
if [[ -z "${DOXYGEN_LANG_VARIANTS}" ]]; then
  DOXYGEN_LANG_VARIANTS="en=english;ru=russian"
fi

CLANG_PARSE="${DOXYGEN_CLANG_ASSISTED_PARSING:-YES}"
CLANG_OPTS="${DOXYGEN_CLANG_OPTIONS:--std=c++17}"
CLANG_DB="${DOXYGEN_CLANG_DATABASE_PATH:-}"
SKIP_DOT="${DOXYGEN_SKIP_DOT_GRAPHS:-OFF}"
SKIP_PDF="${DOXYGEN_SKIP_REFMAN_PDF:-OFF}"

CMAKE_DOCS_CI="${DOCGEN_ROOT}/cmake/docs-ci.cmake"
if [[ ! -f "${CMAKE_DOCS_CI}" ]]; then
  echo "ERROR: missing ${CMAKE_DOCS_CI}"
  exit 1
fi

mkdir -p "${DOCGEN_STAGING_BASE}" "${DOCGEN_OUTPUT_BASE}"

IFS=';' read -r -a lang_variants <<< "${DOXYGEN_LANG_VARIANTS}"
for variant in "${lang_variants[@]}"; do
  if [[ -z "${variant}" ]]; then
    continue
  fi
  if [[ "${variant}" != *=* ]]; then
    echo "Invalid DOXYGEN_LANG_VARIANTS entry: ${variant}"
    echo "Expected format: abbr=section1 section2;abbr2=sectionX"
    exit 1
  fi

  lang_abbr="${variant%%=*}"
  lang_sections="${variant#*=}"
  if [[ -z "${lang_abbr}" || -z "${lang_sections}" ]]; then
    echo "Invalid DOXYGEN_LANG_VARIANTS entry: ${variant}"
    echo "Language abbreviation and sections must be non-empty."
    exit 1
  fi

  output_dir="${DOCGEN_STAGING_BASE}/${lang_abbr}"
  echo "Generating docs for ${lang_abbr} with sections: ${lang_sections}"
  cmake \
    "-DPROJECT_SOURCE_DIR=${DOCGEN_ROOT}" \
    "-DPROJECT_BINARY_DIR=${DOCGEN_CMAKE_PROJECT_BINARY_DIR}" \
    "-DDOXYGEN_OUTPUT_DIRECTORY=${output_dir}" \
    "-DDOXYGEN_CLANG_ASSISTED_PARSING=${CLANG_PARSE}" \
    "-DDOXYGEN_CLANG_OPTIONS=${CLANG_OPTS}" \
    "-DDOXYGEN_CLANG_DATABASE_PATH=${CLANG_DB}" \
    "-DDOXYGEN_ENABLED_SECTIONS=${lang_sections}" \
    "-DDOXYGEN_SKIP_DOT_GRAPHS=${SKIP_DOT}" \
    "-DDOXYGEN_SKIP_REFMAN_PDF=${SKIP_PDF}" \
    -P "${CMAKE_DOCS_CI}"

  for doc_type in html xml latex pdf; do
    src_dir="${output_dir}/${doc_type}"
    dst_dir="${DOCGEN_OUTPUT_BASE}/${doc_type}/${lang_abbr}"
    if [[ -d "${src_dir}" ]]; then
      rm -rf "${dst_dir}"
      mkdir -p "${DOCGEN_OUTPUT_BASE}/${doc_type}"
      mv "${src_dir}" "${dst_dir}"
    fi
  done
done
