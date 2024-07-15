模块一：Python 模型训练及导出

模块⼆：Mapper 知存工具链 mapper 的输入及产物示例

模块三：Project 板端工程示例

模块四：Tools 串口工具及模型转换工具


1、实验环境的搭建

方法一：Linux环境下通过Docker部署Mapper软件环境

1）安装Docker

–更新软件包列表并安装Docker:

 sudo apt update
 
 sudo apt install docker.io
 
 启动Docker服务并设置自动启动:
 
 sudo systemctl start docker
 
 sudo systemctl enable docker
 
2）下载和部署Docker镜像

–拉取Mapper软件的Docker镜像：

 docker pull witin/toolchain:v001.000.024
 
 如果在WSL中使用Docker，确保WSL版本和Docker Desktop协同工作。
 
3）管理Docker镜像和容器

–加载镜像文件（如果有）并检查镜像列表:

 docker load -i 镜像文件.tar
 
 docker images
 
–启动和连接到Docker容器:

 docker start [容器名]

 docker attach [容器名]

4）文件传输

–从本地到容器:

 docker cp [本地文件路径] [容器ID]:[容器内路径]
 
–从容器到本地:

 docker cp [容器ID]:[容器内文件路径] [本地目标路径]
 
方法二：Windows环境下通过Docker Desktop部署Mapper软件环境

1）安装Docker Desktop for Windows

–从Docker官方网站下载适合Windows 10的版本并安装。

2）配置和使用Docker Desktop

–启用WSL并安装Linux发行版。

–通过软连接修改Docker安装路径。

–搜索并获取witin_toolchain的特定版本（如034版本）。

2、机器学习算法的开发实践

1）模型训练和导出

–训练模型并生成网络权重文件（bestModel.pth）。

–转换模型格式到ONNX (bestModel.onnx).

2）模型转换至芯片格式

–将ONNX文件导入至mapper工具链，并生成芯片格式文件。

3）烧写NPU权重

–连接系统和设置跳线帽。

–使用WitinProgramTool执行权重烧写命令。

4）板端工程验证及测试

–使用Witmem Studio设置工程，编译并下载至硬件。

–使用串口调试工具查看输出和准确率。


Module One: Python Model Training and Export

Module Two: Mapper Knowledge Storage Tool Chain - Mapper's Input and Product Examples

Module Three: Project Board Engineering Example

Module Four: Tools - Serial Port Tools and Model Conversion Tools

1. Experimental Environment Setup

Method One: Deploying Mapper Software Environment in Linux Environment via Docker

1) Install Docker

- Update the software package list and install Docker:

  sudo apt update
  
  sudo apt install docker.io

  Start the Docker service and set it to automatically start:

  sudo systemctl start docker
  
  sudo systemctl enable docker
 

2) Download and Deploy Docker Images

- Pull the Docker image of the Mapper software:

  docker pull witin/toolchain:v001.000.024

  If using Docker in WSL, ensure that the WSL version and Docker Desktop work in coordination.

3) Manage Docker Images and Containers

- Load the image file (if any) and check the list of images:

  docker load -i image_file.tar
  
  docker images

- Start and connect to the Docker container:

  docker start [container_name]
  
  docker attach [container_name]
  

4) File Transfer

- From local to container:

  docker cp [local_file_path] [container_id]:[container_path]

- From container to local:

  docker cp [container_id]:[container_path] [local_target_path]


Method Two: Deploying Mapper Software Environment in Windows Environment via Docker Desktop

1) Install Docker Desktop for Windows

- Download the version suitable for Windows 10 from the Docker official website and install it.

2) Configure and Use Docker Desktop

- Enable WSL and install a Linux distribution.

- Modify the Docker installation path through a soft link.

- Search for and obtain a specific version of the witin_toolchain (e.g., version 034).

2. Machine Learning Algorithm Development Practice

1) Model Training and Export

- Train the model and generate a network weight file (bestModel.pth).

- Convert the model format to ONNX (bestModel.onnx).

2) Model Conversion to Chip Format

- Import the ONNX file into the mapper tool chain and generate a chip format file.

3) Burn NPU Weights

- Connect the system and set the jumper cap.

- Use the WitinProgramTool to execute the weight burning command.

4) Board-side Engineering Verification and Testing

- Use Witmem Studio to set up the project, compile, and download it to the hardware.

- Use the serial port debugging tool to view the output and accuracy.


