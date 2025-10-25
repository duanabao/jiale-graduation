以下是你日常使用 Anaconda（或 Miniconda）时最常用的 **conda 命令清单**，分类清晰，直接可用：

---

## 🧱 环境管理相关

| 功能                | 命令                                     |
| ----------------- | -------------------------------------- |
| 创建新环境（指定Python版本） | `conda create -n env_name python=3.8`  |
| 激活环境              | `conda activate env_name`              |
| 退出当前环境            | `conda deactivate`                     |
| 删除环境              | `conda remove -n env_name --all`       |
| 查看已有环境            | `conda env list` 或 `conda info --envs` |

---

## 📦 安装与卸载包

| 功能                 | 命令                                 |
| ------------------ | ---------------------------------- |
| 安装包（如 numpy）       | `conda install numpy`              |
| 从特定源安装（如 PyTorch）  | `conda install pytorch -c pytorch` |
| 使用 pip 安装非 conda 包 | `pip install some_package`         |
| 卸载包                | `conda remove package_name`        |
| 更新包                | `conda update package_name`        |

---

## 📂 导出与导入环境

| 功能              | 命令                                    |
| --------------- | ------------------------------------- |
| 导出当前环境到文件       | `conda env export > environment.yml`  |
| 从 `.yml` 文件创建环境 | `conda env create -f environment.yml` |
| 更新环境（已有环境基础上）   | `conda env update -f environment.yml` |

---

## 🔍 查看信息

| 功能          | 命令                                                 |
| ----------- | -------------------------------------------------- |
| 查看当前激活环境中的包 | `conda list`                                       |
| 搜索可用的包      | `conda search package_name`                        |
| 查看环境路径      | `which python`（Linux/Mac）或 `where python`（Windows） |

---

## 🚑 常见问题解决命令

| 问题            | 命令                   |
| ------------- | -------------------- |
| 清除缓存（空间太大时）   | `conda clean -a`     |
| 修复环境损坏        | `conda update --all` |
| 检查 Conda 本身更新 | `conda update conda` |

---

## 🛠 示例（实际使用）

```bash
# 创建名为 headpose 的 Python3.6 环境
conda create -n headpose python=3.6

# 激活环境
conda activate headpose

# 安装 PyTorch
conda install pytorch torchvision cudatoolkit=10.1 -c pytorch

# 导出环境
conda env export > environment.yml
```

---

如果你需要我根据某个项目自动生成一个环境 `.yml` 文件，也可以发给我 `conda list` 的结果，我可以帮你提炼关键依赖。
