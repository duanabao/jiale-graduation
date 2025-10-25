你看到的警告表明，在你的系统上启用了输入输出内存管理单元（IOMMU），这可能会导致在使用 PCIe 点对点内存复制时出现问题，特别是在裸金属（非虚拟化）Linux 系统上。如果你是在裸金属系统上，建议禁用 IOMMU，以避免潜在的图像损坏和程序不稳定。

### 如何禁用 IOMMU（在裸金属系统上）：

#### 1. **BIOS 设置：**
   你可以通过 BIOS/UEFI 设置直接禁用 IOMMU。具体选项因主板不同而有所不同，但通常会称为：
   - **Intel 面向 I/O 的虚拟化技术（VT-d）**，适用于 Intel 处理器
   - **AMD I/O 虚拟化技术（AMD-Vi）**，适用于 AMD 处理器

   禁用方法：
   - 重启系统并进入 BIOS/UEFI 设置（通常在启动时按 `Del`、`F2`、`F10` 等键进入）。
   - 查找虚拟化设置，通常位于“高级”或“CPU 配置”部分。
   - 禁用 **VT-d**（适用于 Intel）或 **AMD-Vi**（适用于 AMD）。
   - 保存更改并退出 BIOS/UEFI。

#### 2. **内核参数：**
   如果你更倾向于通过内核参数禁用 IOMMU，可以在启动时通过编辑 GRUB 配置文件来完成。

   **通过 GRUB 禁用 IOMMU 的步骤：**
   - 编辑 GRUB 配置文件：
     ```bash
     sudo nano /etc/default/grub
     ```
   - 找到以 `GRUB_CMDLINE_LINUX_DEFAULT` 开头的行，并在选项中添加 `intel_iommu=off`（适用于 Intel CPU）或 `amd_iommu=off`（适用于 AMD CPU）：
     对于 Intel 系统：
     ```bash
     GRUB_CMDLINE_LINUX_DEFAULT="quiet splash intel_iommu=off"
     ```
     对于 AMD 系统：
     ```bash
     GRUB_CMDLINE_LINUX_DEFAULT="quiet splash amd_iommu=off"
     ```
   - 修改完成后，更新 GRUB：
     ```bash
     sudo update-grub
     ```
   - 重启系统，使更改生效。

#### 3. **虚拟机环境：**
   如果你正在使用带有 GPU 直通（vGPU）的虚拟机，**不应禁用** IOMMU，因为它对于虚拟化 GPU 设置是必需的。在这种情况下，你可以忽略警告，因为 IOMMU 对于虚拟化 GPU 的使用是必要的。

### 额外说明：
- **图像损坏和不稳定性**：如果在 IOMMU 启用的情况下运行 CUDA 应用程序或任何需要 GPU 的工作负载，可能会发生这些问题。禁用 IOMMU 应该能解决这些问题。
- **虚拟机**：如果你是在虚拟化环境中运行，并且使用了 GPU 直通（vGPU），则应该保持 IOMMU 启用，这样的警告不适用。

如果你在执行这些步骤时需要更多帮助，欢迎随时告知！