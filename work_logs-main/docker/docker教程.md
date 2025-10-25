这是一个从 **零开始使用 Docker 容器** 的基本教程，适用于你要运行如 Gazebo 这类仿真任务的情况：

---

## 🐳 一、Docker 安装（宿主机）

### Ubuntu 下安装 Docker：

```bash
sudo apt update
sudo apt install -y docker.io
sudo systemctl enable docker
sudo systemctl start docker
```

### （可选）将当前用户加入 `docker` 组，避免每次用 `sudo`：

```bash
sudo usermod -aG docker $USER
newgrp docker
```

---

## 📦 二、下载镜像或构建镜像

### 1. 从 Docker Hub 拉取镜像（例如 ros-noetic + Gazebo）：

```bash
docker pull osrf/ros:noetic-desktop-full
```

### 2. 自定义构建（如果你有 Dockerfile）：

```bash
docker build -t my_gazebo_image .
```

---

## 🚀 三、运行容器

最基础运行：

```bash
docker run -it osrf/ros:noetic-desktop-full
```

### 常见增强配置（建议记住）：

```bash
docker run -it \
  --name gazebo_container \
  --gpus all \                       # 使用 GPU
  -e DISPLAY=$DISPLAY \             # 图形界面
  -v /tmp/.X11-unix:/tmp/.X11-unix \  # X11 socket 共享
  -v ~/your_ws:/root/your_ws \        # 映射工作目录
  --network host \                  # 使用宿主网络（适合 ROS）
  osrf/ros:noetic-desktop-full
```

先运行这个确保 X11 通信没问题：

```bash
xhost +local:docker
```

---

## 🛠 四、常见容器操作命令

| 操作      | 命令                                 |
| ------- | ---------------------------------- |
| 查看容器列表  | `docker ps -a`                     |
| 启动已停止容器 | `docker start <container>`         |
| 进入容器    | `docker exec -it <container> bash` |
| 停止容器    | `docker stop <container>`          |
| 删除容器    | `docker rm <container>`            |
| 查看日志    | `docker logs <container>`          |

---

## 🧹 五、退出容器（推荐方式）

* **不要用 `Ctrl+Z`**，那只是挂起。
* 用：

  ```bash
  exit
  ```
* 如果你用了 `docker run -it`，这会自动停止并退出容器。

---

如果你已经有镜像但不确定是否带 Gazebo、ROS、GPU 驱动等，可以贴出镜像名，我帮你检查内容和运行方式。也可以参考一个完整的[Gazebo容器使用案例](f)。
