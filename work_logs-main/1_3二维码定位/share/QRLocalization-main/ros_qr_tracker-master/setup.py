#!/usr/bin/env python
import os

from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

# 获取当前目录的绝对路径
CURRENT_DIR = os.path.abspath(os.path.dirname(__file__))

def get_reqs(*fns):
    """
    从给定的文件中读取依赖包名称并返回一个列表。
    :param fns: 文件名列表
    :return: 依赖包名称列表
    """
    lst = []
    for fn in fns:
        # 逐行读取文件内容
        for package in open(os.path.join(CURRENT_DIR, fn)).readlines():
            package = package.strip()  # 去除前后空白
            if not package:  # 如果为空行则跳过
                continue
            lst.append(package.strip())  # 添加到列表中
    return lst

# 生成初始的分发设置
d = generate_distutils_setup()
print('d0:', d)

# 生成最终的分发设置
d = generate_distutils_setup(
    #version='0.1.0',  # 版本号（可选）
    packages=['ros_qr_tracker'],  # 包名称
    package_dir={'': 'src'},  # 包目录
    # scripts=['bin/myscript'],  # 脚本（可选）
    install_requires=get_reqs('pip-requirements.txt'),  # 安装依赖
    #install_requires=['Pillow', 'libzbar-cffi', 'Numpy', 'qrcode'],  # 其他依赖（可选）
)

# 执行安装
setup(**d)
