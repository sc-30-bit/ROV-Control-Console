# ROV-Control-Console

![GUI Preview](figs/2a14c97303ae70b2d5635eec3b7f76e7.png)

## Demo Videos

<table width="100%">
  <tr>
    <td width="50%" align="center">
      <video src="https://github.com/user-attachments/assets/dbc5ccab-f5d6-47d4-9ec9-3d5ce958680d" width="100%" controls></video>
      <br />
      <b>Third-person View</b>
    </td>
    <td width="50%" align="center">
      <video src="https://github.com/user-attachments/assets/19950f9d-3234-482d-b3ec-de8ad022553d" width="100%" controls></video>
      <br />
      <b>First-person View</b>
    </td>
  </tr>
</table>

## Requirements

`Qt5`, `C++`, `GCC`, `QUC` (directly integrated into Qt Designer), `OpenCV 4.6.0+`, `CUDA 11.x`, `cuDNN`, `Eigen` (matrix library).

## GUI Stylesheet

You can use AI to generate a theme stylesheet and apply it with `setStylesheet`.

## TCP Communication with Lower Computer

If you already know how to build a basic Qt chat app, you can quickly understand the `tcpserver` class and extend it as needed.

## RTSP Video Transmission

The `rtsp` class receives two streams from OrangePi.  
Use [Mediamtx](https://github.com/bluenviron/mediamtx) on OrangePi for pushing streams.

## Image and Video Saving

The `saver` class lets you choose whether to save images and videos.

## Localization Map

The `localizationmap` class visualizes ROV position.  
The `KalmanFilter` class provides a smoothing idea for ROV trajectory.

<video src="https://github.com/user-attachments/assets/7522e47d-0ffb-4cef-993c-863e858d4147" width="100%" controls></video>

## Image Stitching

Please read OpenCV official sample first:  
[stitching_detailed](https://docs.opencv.org/4.6.0/d9/dd8/samples_2cpp_2stitching_detailed_8cpp-example.html)

Then check this project `stitcher` class.  
For further optimization, refer to [CS205-ImageStitching](https://github.com/ziqiguo/CS205-ImageStitching).

<table width="100%">
  <tr>
    <td align="center">
      <video src="https://github.com/user-attachments/assets/ef1f17b2-07ff-4b9c-b810-0e07d6ec99ad" width="100%" controls></video>
      <br />
      <b>Step 1: Stitching Process</b>
    </td>
  </tr>
  <tr>
    <td align="center">
      <img src="figs/58ade65cdb93bd15ab43af068c164260.png" width="100%" />
      <br />
      <b>Step 2: Stitched Result</b>
    </td>
  </tr>
</table>

## Real-time ROV 3D Position Display

Refer to the `_3d` class and update `3d.qml` as needed (`.obj` model path).  
Example ROV model: [Haiwei](https://www.alipan.com/s/f3p4jHjJv4x), extraction code: `50od`.

## License

[MIT](https://choosealicense.com/licenses/mit/)