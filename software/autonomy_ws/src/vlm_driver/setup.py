from setuptools import find_packages, setup
from glob import glob
import os

package_name = 'vlm_driver'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Israel Charles',
    maintainer_email='israelcharlesic10@gmail.com',
    description='VLM driving controller',
    license='MIT',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'download_models = vlm_driver.download_models:main',
            'vlm_driver_node = vlm_driver.vlm_driver_node:main',
        ],
    },
)
