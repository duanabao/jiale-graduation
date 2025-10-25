from setuptools import find_packages
from setuptools import setup

setup(
    name='sfuise_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('sfuise_msgs', 'sfuise_msgs.*')),
)
