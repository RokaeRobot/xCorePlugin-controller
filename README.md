# 控制器插件

控制器插件是珞石机器人提供给客户用于二次开发的软件产品，插件直接运行在控制器，客户可以对机器人进行更深入的一系列控制和操作。

### 接口使用

见 *examples*

[开发指导](http://sw.rokae.com:8989/docs/Plugin/controller)

### 编译安装

```bash
mkdir build
cd build
#根据需要选择对应的工具链文件
cmake -DCMAKE_TOOLCHAIN_FILE=../rokae_x86_64.cmake  ..
make -j4
```

# License

> Copyright (C) 2025 ROKAE (Beijing) Technology Co., LTD. 


