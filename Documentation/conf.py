# SPDX-License-Identifier: GPL-2.0-only
# Configuration file for the Sphinx documentation builder.

"""
The Test Linux documentation build configuration file.
"""

import os
import sphinx

doc_dir = os.path.dirname(os.path.abspath(__file__))

project = 'The Test Linux Documentation'
copyright = 'Copyright (C) 2022-2026 Rong Tao'
author = 'Rong Tao'
release = '0.0.1'

html_logo = "images/logo.svg"

extensions = []
