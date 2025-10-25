from setuptools import find_packages
from setuptools import setup

setup(
    name='isas_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('isas_msgs', 'isas_msgs.*')),
)
