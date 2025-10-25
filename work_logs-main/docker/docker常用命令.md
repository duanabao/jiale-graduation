Docker 是一个用于打包、分发和运行应用程序的容器化平台。下面是一些**常用的 Docker 命令**，按功能分类，方便查阅。

---

### 🔧 容器管理

| 操作            | 命令示例                                  |
| ------------- | ------------------------------------- |
| 查看正在运行的容器     | `docker ps`                           |
| 查看所有容器（包括已停止） | `docker ps -a`                        |
| 启动容器          | `docker start <container_id>`         |
| 停止容器          | `docker stop <container_id>`          |
| 删除容器          | `docker rm <container_id>`            |
| 进入容器交互终端      | `docker exec -it <container_id> bash` |
| 从容器启动新交互      | `docker run -it ubuntu bash`          |
| 后台运行容器        | `docker run -d <image_name>`          |

---

### 📦 镜像管理

| 操作     | 命令示例                                   |
| ------ | -------------------------------------- |
| 查看所有镜像 | `docker images`                        |
| 搜索镜像   | `docker search <image_name>`           |
| 拉取镜像   | `docker pull <image_name>`             |
| 删除镜像   | `docker rmi <image_name>`              |
| 构建镜像   | `docker build -t <name:tag> .`         |
| 给镜像打标签 | `docker tag <image_id> <new_name:tag>` |

---

### 📁 数据卷和挂载

| 操作         | 命令示例                                 |
| ---------- | ------------------------------------ |
| 创建 volume  | `docker volume create mydata`        |
| 查看 volumes | `docker volume ls`                   |
| 使用 volume  | `docker run -v mydata:/data <image>` |
| 目录挂载       | `docker run -v $(pwd):/app <image>`  |

---

### 📚 其他实用命令

| 功能          | 命令示例                               |
| ----------- | ---------------------------------- |
| 查看日志        | `docker logs <container_id>`       |
| 容器资源使用      | `docker stats`                     |
| 查看容器详细信息    | `docker inspect <container_id>`    |
| 清理无用镜像/容器   | `docker system prune`              |
| 导出镜像为 tar 包 | `docker save -o myimg.tar <image>` |
| 导入镜像        | `docker load -i myimg.tar`         |

---

需要的话我可以提供 [Dockerfile 示例](f)、[容器网络配置方法](f)，或者 [常见错误排查](f)。
