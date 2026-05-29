# Patches vendored m.css doxygen.py for Doxygen 1.9.x (Ubuntu LTS):
# - extract_metadata: skip XML without <compounddef> (e.g. Doxyfile.xml).
# - parse_xml: skip XML whose root is not <doxygen> (Doxyfile.xml uses <doxyfile>).
# - parse_desc_internal (anchor): tolerate anchor ids without current_definition_url_base prefix.
# - parse_desc_internal (sect/heading): Doxygen 1.9.x may emit empty title (i.text is None).
# - extract_metadata: compound title/compoundname .text may be None (html.escape).
# - parse_xml: compoundname .text may be None ('@' in ... check for unnamed namespace).
# - parse_xml: compound.name assignment (same as extract_metadata; used before prefix_wbr).
# - _search.py ResultMap.serialize: offset for URL must use "if e.url:" (not "if e.name and e.url"),
#   otherwise empty compound names break assert len(output) == offset.
function(mcss_patch_doxygen_py script_path)
  if(NOT EXISTS "${script_path}")
    return()
  endif()
  file(READ "${script_path}" _py)
  set(_changed FALSE)

  if(NOT _py MATCHES "No compounddef in")
    string(REPLACE
      "    compounddef: ET.Element = root.find('compounddef')\n\n    if compounddef.attrib['kind'] not in"
      "    compounddef: ET.Element = root.find('compounddef')\n\n    if compounddef is None:\n        logging.debug(\"No compounddef in {}, skipping\".format(os.path.basename(xml)))\n        return\n\n    if compounddef.attrib['kind'] not in"
      _py "${_py}")
    set(_changed TRUE)
  endif()

  if(NOT _py MATCHES "skip non-compound XML")
    string(REPLACE
      "    root = tree.getroot()\n    assert root.tag == 'doxygen'\n\n    compounddef: ET.Element = root[0]"
      "    root = tree.getroot()\n    if root.tag != 'doxygen':\n        logging.debug(\"{}: skip non-compound XML\".format(os.path.basename(xml)))\n        return None\n\n    compounddef: ET.Element = root[0]"
      _py "${_py}")
    set(_changed TRUE)
  endif()

  if(NOT _py MATCHES "emit anchors without full URL base")
    string(REPLACE
      "            else:\n                assert id.startswith(state.current_definition_url_base)\n                id = id[len(state.current_definition_url_base)+2:]"
      "            elif state.current_definition_url_base and id.startswith(state.current_definition_url_base):\n                id = id[len(state.current_definition_url_base)+2:]\n            # else: keep id as-is (Doxygen 1.9.x may emit anchors without full URL base)"
      _py "${_py}")
    set(_changed TRUE)
  endif()

  if(NOT _py MATCHES "title = html.escape\\(i.text or ''\\)")
    string(REPLACE
      "                title = html.escape(i.text)"
      "                title = html.escape(i.text or '')"
      _py "${_py}")
    set(_changed TRUE)
  endif()

  if(NOT _py MATCHES "h_tag_level, html.escape\\(i.text or ''\\)")
    string(REPLACE
      "                out.parsed += '<h{0}>{1}</h{0}>'.format(h_tag_level, html.escape(i.text))"
      "                out.parsed += '<h{0}>{1}</h{0}>'.format(h_tag_level, html.escape(i.text or ''))"
      _py "${_py}")
    set(_changed TRUE)
  endif()

  if(NOT _py MATCHES "compound.name = html.escape\\(\\(")
    string(REPLACE
      "    compound.name = html.escape(compounddef.find('title').text if compound.kind in ['page', 'group'] and compounddef.findtext('title') else compounddef.find('compoundname').text)"
      "    compound.name = html.escape((compounddef.find('title').text if compound.kind in ['page', 'group'] and compounddef.findtext('title') else compounddef.find('compoundname').text) or '')"
      _py "${_py}")
    set(_changed TRUE)
  endif()

  if(NOT _py MATCHES "'@' in \\(compounddef.find\\('compoundname'\\).text or ''\\)")
    string(REPLACE
      "        (compounddef.attrib['kind'] == 'namespace' and '@' in compounddef.find('compoundname').text)):"
      "        (compounddef.attrib['kind'] == 'namespace' and '@' in (compounddef.find('compoundname').text or ''))):"
      _py "${_py}")
    set(_changed TRUE)
  endif()

  if(NOT _py MATCHES "compound.name = \\(compounddef.find\\('title'\\).text if compound.kind in \\['page', 'group'\\] and compounddef.findtext\\('title'\\) else compounddef.find\\('compoundname'\\).text\\) or ''")
    string(REPLACE
      "    compound.name = compounddef.find('title').text if compound.kind in ['page', 'group'] and compounddef.findtext('title') else compounddef.find('compoundname').text"
      "    compound.name = (compounddef.find('title').text if compound.kind in ['page', 'group'] and compounddef.findtext('title') else compounddef.find('compoundname').text) or ''"
      _py "${_py}")
    set(_changed TRUE)
  endif()

  if(_changed)
    file(WRITE "${script_path}" "${_py}")
  endif()
endfunction()

function(mcss_patch_search_py script_path)
  if(NOT EXISTS "${script_path}")
    return()
  endif()
  file(READ "${script_path}" _py)
  string(FIND "${_py}" "if e.name and e.url:" _patch_idx)
  if(NOT _patch_idx EQUAL -1)
    string(REPLACE
[[            if e.name and e.url:
                 offset += len(e.url.encode('utf-8')) + 1]]
[[            if e.url:
                 offset += len(e.url.encode('utf-8')) + 1]]
      _py "${_py}")
    file(WRITE "${script_path}" "${_py}")
  endif()
endfunction()
