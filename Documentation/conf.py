# SPDX-License-Identifier: GPL-2.0-only
# Configuration file for the Sphinx documentation builder.

"""
The Test Linux documentation build configuration file.
"""

import os
import sphinx
import sys

doc_dir = os.path.dirname(os.path.abspath(__file__))

project = 'The Test Linux Documentation'
copyright = 'Copyright (C) 2022-2026 Rong Tao'
author = 'Rong Tao'
version = release = '0.0.148'

html_logo = "images/logo.svg"
# Theme: alabaster, sphinx_rtd_theme, sphinx_rtd_dark_mode
html_theme = "sphinx_rtd_theme"

if html_theme in ["sphinx_rtd_theme", "sphinx_rtd_dark_mode"]:
    try:
        import sphinx_rtd_theme
    except ImportError:
        html_theme = "alabaster"

if html_theme == "alabaster":
    html_theme_options = {
        "description": version,
        "page_width": "65em",
        "sidebar_width": "15em",
        "fixed_sidebar": "true",
        "font_size": "inherit",
        "font_family": "serif",
    }

html_static_path = ["sphinx-static"]
html_css_files = [
    "custom.css",
]

extensions = [
    'sphinxcontrib.mermaid',
    'sphinx.ext.graphviz',
]

# Display
sys.stderr.write("Using %s theme\n" % html_theme)
