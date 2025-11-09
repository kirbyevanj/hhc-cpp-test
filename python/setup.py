#!/usr/bin/env python3
"""
Setup script for HHC Python bindings.
"""

from pybind11.setup_helpers import Pybind11Extension, build_ext
from setuptools import setup, find_packages
import os

# Get the directory containing this setup.py
this_dir = os.path.dirname(os.path.abspath(__file__))
root_dir = os.path.dirname(this_dir)

# Define the extension module
ext_modules = [
    Pybind11Extension(
        "hhc",
        ["hhc_python.cpp"],
        include_dirs=[os.path.join(root_dir, "hhc-cpp")],
        cxx_std=23,
        language="c++",
    ),
]

# Read README for long description
readme_path = os.path.join(root_dir, "README.md")
if os.path.exists(readme_path):
    with open(readme_path, "r", encoding="utf-8") as f:
        long_description = f.read()
else:
    long_description = "HHC (High-performance Hash Codec) Python bindings"

setup(
    name="hhc",
    version="1.0.0",
    author="HHC Authors",
    description="Python bindings for HHC (High-performance Hash Codec)",
    long_description=long_description,
    long_description_content_type="text/markdown",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    python_requires=">=3.6",
    install_requires=["pybind11>=2.6.0"],
    classifiers=[
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
        "Programming Language :: C++",
        "Topic :: Software Development :: Libraries",
    ],
    zip_safe=False,
)
