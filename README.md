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

<video src="https://github.com/user-attachments/assets/43791a6b-ef61-429b-9d66-44579fb8a69b" width="100%" controls></video>

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

## Face Pig Mask Script (Python)

Use this helper script to overlay a pig icon on a fixed ROI in every frame.

1. Install dependency:

```bash
pip install opencv-python numpy
```

2. Run:

```bash
python tools/face_pig_mask.py --input figs/Image90.mp4 --icon GIGIBoy.webp --output output_face_mask.mp4 --select-roi
```

Optional params:
- `--roi x,y,w,h` use fixed ROI instead of interactive selection
- `--roi-preview path` save first frame when ROI GUI is unavailable (default `roi_preview.jpg`)

If ROI window cannot open (OpenCV GUI not available), script falls back to matplotlib ROI selection.
If that also fails, it saves first frame to `roi_preview.jpg` and asks you to rerun with `--roi x,y,w,h`.
