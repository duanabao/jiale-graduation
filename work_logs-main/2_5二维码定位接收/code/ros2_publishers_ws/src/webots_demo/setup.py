import os
from glob import glob
from setuptools import find_packages, setup

package_name = 'webots_demo'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/' + package_name, ['package.xml']),
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='ros',
    maintainer_email='ros@todo.todo',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'epuck_scan = webots_demo.epuck_scan:main',
            'random_walk = webots_demo.random_walk:main',
            'camera_xyz = webots_demo.camera_xyz:main',
            'camera_xyz2 = webots_demo.camera_xyz2:main',
            'identify_qr_code = webots_demo.identify_qr_code:main',
            'epuck_control_node = webots_demo.epuck_control_node:main',
        ],
    },
)
