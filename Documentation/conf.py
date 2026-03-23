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
version = release = '0.0.9'

html_logo = "images/logo.svg"
html_theme = "alabaster"

html_theme_options = {
    "description": version,
    "page_width": "65em",
    "sidebar_width": "15em",
    "fixed_sidebar": "true",
    "font_size": "inherit",
    "font_family": "serif",
}

extensions = []

sys.stderr.write("Using %s theme\n" % html_theme)
