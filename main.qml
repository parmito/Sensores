import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts 2.15
import Charts 1.0

Item {
    width: 800; height: 1280

    Rectangle
    {
        id: idAccelerometerBox
        color: "yellow"
        x:0
        y:0
        width: Screen.width/4
        height: 75;

        Text
        {
            id: idTxtAxisX
            text: qsTr("X:")
            font.pixelSize: 14
            font.bold: true
            objectName: "txtAccelX"
            x:0
            y:0

            TextInput
            {
                id: idTxtInputAxisX
                cursorVisible: false
                text: "0"
                font.pixelSize: 14
                x:idTxtAxisX.width   /*idTxtAxisX.x + 100*/
                y:0                  /*idTxtAxisX.y*/
                objectName: "txtInputAccelX"

                signal qmlReceiveAccelX(string textIn)
                onQmlReceiveAccelX:
                {
                    console.log("onQmlReceiveAccelX:"+textIn)
                    text = textIn
                }
            }
        }
        Text
        {
            id:idTxtAxisY
            x:0
            y:idTxtAxisX.height
            text: qsTr("Y:")
            font.pixelSize: 14
            font.bold: true
            objectName: "txtAccelY"

            TextInput
            {
                id:idTxtInputAxisY
                x: idTxtAxisY.width
                y: 0
                text: "0"
                font.pixelSize: 14
                cursorVisible: false
                objectName: "txtInputAccelY"

                signal qmlReceiveAccelY(string textIn)
                onQmlReceiveAccelY:
                {
                    console.log("onQmlReceiveAccelY:"+textIn)
                    text = textIn
                }
            }
        }

        Text
        {
            id: idTxtAxisZ
            x: 0
            y: idTxtAxisX.height+idTxtAxisY.height
            text: qsTr("Z:")
            font.pixelSize: 14
            font.bold: true
            objectName: "txtAccelZ"

            TextInput
            {
                id: idTxtInputAxisZ
                x: idTxtAxisZ.width
                y: 0
                text: "0"
                font.pixelSize: 14
                cursorVisible: false
                objectName: "txtInputAccelZ"

                signal qmlReceiveAccelZ(string textIn)
                onQmlReceiveAccelZ:
                {
                    console.log("onQmlReceiveAccelZ:"+textIn)
                    text = textIn
                }
            }
        }

        /*ChartView {
            id: line
            x: 0
            y: 150
            width: 800
            height: 200
            objectName: "LineSeries"

            signal qmlReceiveLineSeries(real X,real Y)
            onQmlReceiveLineSeries:
            {
                console.log("onQmlReceiveLineSeries:"+x+","+y)
                new XYPoint(x = X, y = Y)
            }

            LineSeries {
                name: "LineSeries"
                objectName: "LineSeries"
                width: 400

                signal qmlReceiveLineSeries(real X,real Y)
                onQmlReceiveLineSeries:
                {
                    console.log("onQmlReceiveLineSeries:"+x+","+y)
                    new XYPoint(x = X, y = Y)
                }
            }
        }*/
    }

    Rectangle
    {
        id: idGpsBox
        color: "white"
        x:Screen.width/4
        y:0
        width: 3*Screen.width/4
        height: 150;

        Text
        {
            id: idTxtTimestamp
            x: 0
            y: 0
            text: qsTr("Timestamp:")
            font.pixelSize: 18
            font.bold : true
            objectName: "txtTimestamp"

            TextInput
            {
                id: idTextInputTimestamp
                x: idTxtTimestamp.width
                y: 0
                text:"N.A."
                font.pixelSize: 14
                cursorVisible: false
                objectName: "txtInputTimestamp"

                signal qmlReceiveTimestamp(string timestamp)
                onQmlReceiveTimestamp:
                {
                    console.log("onQmlReceiveTimestamp:"+timestamp)
                    text = timestamp
                }
            }
        }
        Text
        {
            id: idTxtLatitude
            x: 0
            y: idTxtTimestamp.height
            text: qsTr("Latitude:")
            font.pixelSize: 18
            font.bold: true
            objectName: "txtLatitude"

            TextInput
            {
                id: idTextInputLatitude
                x: idTxtLatitude.width
                y: 0
                text:"N.A."
                font.pixelSize: 14
                cursorVisible: false
                objectName: "txtInputLatitude"

                signal qmlReceiveLatitude(string latitude)
                onQmlReceiveLatitude:
                {
                    console.log("onQmlReceiveLatitude:"+latitude)
                    text = latitude
                }
            }
        }
        Text
        {
            id: idTxtLongitude
            x: 0
            y: idTxtTimestamp.height + idTxtLatitude.height
            text: qsTr("Longitude:")
            font.pixelSize: 18
            font.bold: true
            objectName: "txtLongitude"

            TextInput
            {
                id: idTextInputLongitude
                x: idTxtLongitude.width
                y: 0
                text:"N.A."
                font.pixelSize: 14
                cursorVisible: false
                objectName: "txtInputLongitude"

                signal qmlReceiveLongitude(string longitude)
                onQmlReceiveLongitude:
                {
                    console.log("onQmlReceiveLongitude:"+longitude)
                    text = longitude
                }
            }
        }

        Text
        {
            id: idTxtAltitude
            x: 0
            y: idTxtTimestamp.height + idTxtLatitude.height+idTxtLongitude.height
            text: qsTr("Altitude:")
            font.pixelSize: 18
            font.bold: true
            objectName: "txtAltitude"

            TextInput
            {
                id: idTxtInputAltitude
                x: idTxtAltitude.width
                y: 0
                text: "0"
                font.pixelSize: 18
                cursorVisible: false
                objectName: "txtInputAltitude"
                signal qmlReceiveAltitude(string textIn)
                onQmlReceiveAltitude:
                {
                    console.log("onQmlReceiveAltitude:"+textIn)
                    text = textIn + " m"
                }
            }
        }

        Text
        {
            id: idTxtSpeed
            x: 0
            y: idTxtTimestamp.height + idTxtLatitude.height+idTxtLongitude.height+idTxtAltitude.height
            text: qsTr("Speed:")
            font.pixelSize: 24
            font.bold: true
            objectName: "txtSpeed"

            TextInput
            {
                id: idTxtInputSpeed
                x: idTxtSpeed.width
                y: 0
                text: "0 Km/h"
                font.pixelSize: 48
                cursorVisible: false
                objectName: "txtInputSpeed"

                signal qmlReceiveSpeed(string textIn)
                onQmlReceiveSpeed:
                {
                    console.log("onQmlReceiveSpeed:"+textIn)
                    text = textIn + " Km/h"
                }
            }
        }
    }


    Row
    {
        anchors.centerIn: parent
        spacing: 20

        PieChart
        {
            id: chartA
            width: 100; height: 100
            color: "red"
            name: "ChartA"
            objectName: "ChartA"
            onChartCleared: console.log("The chart has been cleared")
        }
        PieChart
        {
            id: chartB
            width: 100; height: 100
            color: chartA.color
            name: "ChartB"
            objectName: "ChartB"
        }
    }

    MouseArea
    {
        anchors.fill: parent
        /*onClicked: { chartA.color = "blue" }*/
        onClicked: chartA.clearChart()
    }

    /*ChartView
    {
        id: view
        LayoutItem.width: parent.width
        LayoutItem.height: 200

        Rectangle
        {
            id: rec
            x: 30
            y: 50
            width: 40
            height: 10
            color: "green"
        }
        ScatterSeries
        {
            id: series
            color: "black"
            XYPoint { x: 30; y: 50 }
            XYPoint { x: 50; y: 60 }
            XYPoint { x: 60; y: 50 }
            XYPoint { x: 70; y: 60 }
            axisX: ValueAxis
            {
                min: 0
                max: 100
            }
            axisY: ValueAxis
            {
                min: 0
                max: 100
            }
        }
    }*/

    Text
    {
        anchors { bottom: parent.bottom; horizontalCenter: parent.horizontalCenter; bottomMargin: 20 }
        text: "Click anywhere to clear the chart"
    }
}
