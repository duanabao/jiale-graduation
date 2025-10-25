### 使用 SSH 代替 HTTPS 来访问 GitHub

首先，确保你已经在 GitHub 上配置了 SSH 密钥。如果你还没有配置 SSH 密钥，请按照以下步骤进行：

#### 1.1. 生成 SSH 密钥对
打开终端，输入以下命令来生成 SSH 密钥对。如果你已经有一个 SSH 密钥，可以跳过这一步。

```bash
ssh-keygen -t rsa -b 4096 -C "2725542843@qq.com"
```

- 这里的 `2725542843@qq.com` 替换为你的 GitHub 注册邮箱。
- 系统会提示你选择保存位置，通常可以直接按 Enter 使用默认路径 `~/.ssh/id_rsa`。
- 然后，它会要求你输入密码（这个密码可以为空，也可以设置一个密码进行加密）。(我使用的是空)

#### 1.2. 添加 SSH 密钥到 SSH agent
在生成 SSH 密钥之后，你需要将密钥添加到 SSH agent 中：

```bash
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_rsa
```

#### 1.3. 将公钥添加到 GitHub
接下来，你需要将公钥添加到 GitHub 账户。首先，复制你的公钥内容：

```bash
cat ~/.ssh/id_rsa.pub
```

然后，将输出的公钥内容复制到剪贴板。

- 登录到 [GitHub](https://github.com)。
- 进入 **Settings** > **SSH and GPG keys**。

- 点击 **New SSH key**，将复制的公钥粘贴到 **Key** 字段中，并为这个密钥命名（例如：`My Laptop`）。

#### 1.4. 测试 SSH 连接
完成以上步骤后，测试 SSH 是否配置成功：

```bash
ssh -T git@github.com
```

如果设置正确，你应该会看到类似以下的信息：

```
Hi <your-username>! You've successfully authenticated, but GitHub does not provide shell access.
```

### 2. 将远程仓库 URL 更改为 SSH

现在你已经设置了 SSH 密钥，可以将 GitHub 仓库的远程 URL 修改为 SSH 地址。执行以下命令：

```bash
git remote set-url origin git@github.com:FWWheat/work_logs.git
```

### 3. 拉取远程仓库的更改

修改远程仓库的 URL 后，可以再次尝试拉取远程仓库的内容：

```bash
git pull origin main --rebase
```

由于现在使用的是 SSH 协议，Git 会通过 SSH 进行连接，而不是通过 HTTPS，因此可以避免 HTTPS 相关的 TLS 问题。

### 4. 推送更改（如果需要）

如果你本地的更改需要推送到远程仓库，可以使用以下命令：

```bash
git push origin main
```

