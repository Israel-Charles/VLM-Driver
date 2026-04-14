from setuptools import find_packages
from setuptools import setup

setup(
    name='vlm_driver_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('vlm_driver_msgs', 'vlm_driver_msgs.*')),
)
