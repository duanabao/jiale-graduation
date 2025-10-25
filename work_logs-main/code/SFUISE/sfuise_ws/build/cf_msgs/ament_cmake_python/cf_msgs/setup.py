from setuptools import find_packages
from setuptools import setup

setup(
    name='cf_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('cf_msgs', 'cf_msgs.*')),
)
