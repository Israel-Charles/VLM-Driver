from setuptools import find_packages, setup

package_name = 'baseline_cv'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='samaviajaffery',
    maintainer_email='samaviajaffery@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'baseline_node = baseline_cv.baseline_node:main',
            'fake_camera_pub= baseline_cv.fake_camera_pub:main',
        ],
    },
)
