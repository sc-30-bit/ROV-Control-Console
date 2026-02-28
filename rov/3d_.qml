import QtQuick 2.0
import QtQuick 2.1 as QQ2
import QtQuick.Scene3D 2.0
import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import QtQuick.Controls 2.0


Item
{
    width: 610;
    height:520;

    property var v1 : 0;
    property var v2 : 0;
    property var v3 : 180;
    Row
    {
        spacing:4;
        z:1.5;

       Slider
       {
           id:slider1;
           z:1.5;
           from:-180;
           to:180;
           value:v1;
           stepSize: 1;
           orientation: "Horizontal"

           onValueChanged:
           {
               cubeTransform.selectid=1;
               cubeTransform.rollAngle=slider1.value;
           }
       }

       Slider
       {
           id:slider2;
           z:1.5;
           from:-180;
           to:180;
           value:v2;
           stepSize: 1;
           orientation: "Horizontal"

           onValueChanged:
           {
               cubeTransform.selectid=2;
               cubeTransform.pitchAngle=slider2.value;
           }
       }

       Slider
       {
           id:slider3;
           z:1.5;
           from:0;
           to:360;
           value:v3;
           stepSize: 1;
           orientation: "Horizontal"

           onValueChanged:
           {
               cubeTransform.selectid=3;
               cubeTransform.angle=slider3.value;
           }
       }
    }

    Scene3D
    {
        id:rootScene;
        anchors.fill:parent;
        Entity
        {
            Camera
            {
                id: camera
                projectionType: CameraLens.PerspectiveProjection
                fieldOfView: 10
                aspectRatio: 16/9
                nearPlane: 0.1
                farPlane: 1000.0
                position: Qt.vector3d(0.0, 0.0, 30.0)
                viewCenter: Qt.vector3d(0.0, 0.5, 0.0)
                upVector: Qt.vector3d(0.0, 0.0, 0.0)
            }

            FirstPersonCameraController { camera: camera }

            OrbitCameraController
            {
                camera: camera
            }

            components:
            [
                RenderSettings
                {
                    activeFrameGraph: ForwardRenderer
                    {
                        clearColor: Qt.rgba(0,0,0,0);
                        camera: camera;
                    }

                },
                // Event Source will be set by the Qt3DQuickWindow
                InputSettings { }
            ]

            PhongAlphaMaterial
            {
                id:material
            }

            Mesh
            {
                id:cube;
                source: "/home/stephen/下载/dam1.obj";
            }


            Transform
            {
                id: cubeTransform

                property real rollAngle: 0
                property real pitchAngle: 0
                property real altitude: 0
                property real angle: 0
                property real scaleFactor: 0
                property real selectid: 0

                translation: Qt.vector3d(0,0,0);

                //rotation: fromEulerAngles( angle, rollAngle, pitchAngle )

                matrix:
                {
                    var m = Qt.matrix4x4();
                    m.translate(Qt.vector3d(0,0,altitude));

                    /*要实现绕物体自身坐标系旋转的关键*/

                    /*要实现绕物体自身坐标系旋转的关键*/

                    if(1==selectid)
                    {
                        m.rotate(angle, Qt.vector3d(0, 1, 0));
                        m.rotate(pitchAngle, Qt.vector3d(-1, 0, 0));
                        m.rotate(rollAngle, Qt.vector3d(0, 0, 1));
                        m.scale(1.0);
                    }
                    else if(2==selectid)
                    {
                        m.rotate(angle, Qt.vector3d(0, 1, 0));
                        m.rotate(pitchAngle, Qt.vector3d(-1, 0, 0));
                        m.rotate(rollAngle, Qt.vector3d(0, 0, 1));
                        m.scale(1.0);
                    }

                    else if(3==selectid)
                    {
                        m.rotate(angle, Qt.vector3d(0, 1, 0));
                        m.rotate(pitchAngle, Qt.vector3d(-1, 0, 0));
                        m.rotate(rollAngle, Qt.vector3d(0, 0, 1));
                        m.scale(1.0);
                    }
                    return m;
                }
            }
            Entity
            {
                id:entity_cube;
                components: [cube,material,cubeTransform]
            }
        }
    }
}
