# Copyright (c) 2022-2025, The Isaac Lab Project Developers.
# All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause

"""该脚本演示如何在Isaac Sim中创建一个简单的场景。

.. code-block:: bash

    # 使用方法
    ./isaaclab.sh -p source/standalone/tutorials/00_sim/create_empty.py

"""

"""首先启动Isaac Sim模拟器。"""


import argparse

from omni.isaac.lab.app import AppLauncher

# 创建参数解析器
parser = argparse.ArgumentParser(description="创建空场景的教程。")
# 添加AppLauncher命令行参数
AppLauncher.add_app_launcher_args(parser)
# 解析参数
args_cli = parser.parse_args()
# 启动Omniverse应用程序
app_launcher = AppLauncher(args_cli)
simulation_app = app_launcher.app

"""接下来的所有内容。"""

from omni.isaac.lab.sim import SimulationCfg, SimulationContext


def main():
    """主函数。"""

    # 初始化仿真上下文，物理特性和渲染时间步长设置为 0.01 秒
    sim_cfg = SimulationCfg(dt=0.01)
    sim = SimulationContext(sim_cfg)
    # 设置主摄像机
    sim.set_camera_view([2.5, 2.5, 2.5], [0.0, 0.0, 0.0])

    # 播放模拟器
    sim.reset()
    # 现在我们准备好了！
    print("[INFO]: 设置完成...")

    # 模拟物理
    while simulation_app.is_running():
        # 执行一步
        sim.step()


if __name__ == "__main__":
    # 运行主函数
    main()
    # 关闭模拟应用程序
    simulation_app.close()
