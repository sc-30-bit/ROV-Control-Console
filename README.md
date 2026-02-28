# ROV Control Console

![界面预览](figs/2a14c97303ae70b2d5635eec3b7f76e7.png)

## 演示视频

| 第三人称视角 | 第一人称视角 |
| --- | --- |
| [点击观看](https://github.com/user-attachments/assets/dbc5ccab-f5d6-47d4-9ec9-3d5ce958680d) | [点击观看](https://github.com/user-attachments/assets/19950f9d-3234-482d-b3ec-de8ad022553d) |

| 机动演示 |
| --- |
| [点击观看](https://github.com/user-attachments/assets/43791a6b-ef61-429b-9d66-44579fb8a69b) |

## 环境要求

`Qt5`、`C++`、`GCC`、`QUC`（可直接集成到 Qt Designer）、`OpenCV 4.6.0+`、`CUDA 11.x`、`cuDNN`、`Eigen`（矩阵运算库）。

## 功能说明

### GUI 样式

可通过 AI 生成主题样式表，然后使用 `setStylesheet` 快速应用到界面。

### 与下位机的 TCP 通信

如果你熟悉 Qt 聊天程序的基本写法，就能很快理解 `tcpserver` 类并按需扩展。

### RTSP 视频传输

`rtsp` 类用于接收 OrangePi 推流的双路视频。  
OrangePi 端可使用 [Mediamtx](https://github.com/bluenviron/mediamtx) 推流。

### 图像与视频保存

`saver` 类支持按需启用或关闭图像/视频保存。

### 定位地图显示

`localizationmap` 类用于可视化 ROV 位置。  
`KalmanFilter` 类提供了轨迹平滑思路（当前版本未在比赛中启用）。

## 图像拼接

建议先阅读 OpenCV 官方 `stitching_detailed` 示例，再理解本项目的 `stitcher` 类：  
[stitching_detailed](https://docs.opencv.org/4.6.0/d9/dd8/samples_2cpp_2stitching_detailed_8cpp-example.html)  
进阶参考：[CS205-ImageStitching](https://github.com/ziqiguo/CS205-ImageStitching)

| 步骤1：拼接过程 |
| --- |
| [点击观看](https://github.com/user-attachments/assets/ef1f17b2-07ff-4b9c-b810-0e07d6ec99ad) |

| 步骤2：拼接结果 |
| --- |
| ![拼接结果](figs/58ade65cdb93bd15ab43af068c164260.png) |

## 实时 ROV 三维姿态显示

参考 `_3d` 类，并按需修改 `3d.qml`（`.obj` 模型路径）。  
示例模型下载：[海卫](https://www.alipan.com/s/f3p4jHjJv4x)（提取码：`50od`）。

## License

[MIT](https://choosealicense.com/licenses/mit/)
