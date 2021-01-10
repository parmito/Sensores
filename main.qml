import QtQuick 2.0
import QtQuick.Window 2.14
import QtLocation 5.6
import QtPositioning 5.6



Item {
    width: Screen.width; height: Screen.height

    Plugin {
       id: osmMapPlugin
       name: "osm"

       //provide the address of the tile server to the plugin
       PluginParameter {
          name: "osm.mapping.custom.host"
          value: "http://localhost/osm/"
       }

       /*disable retrieval of the providers information from the remote repository.
       If this parameter is not set to true (as shown here), then while offline,
       network errors will be generated at run time*/
       PluginParameter {
          name: "osm.mapping.providersrepository.disabled"
          value: true
       }
    }
    /*Map {
        anchors.fill: parent
        plugin: osmMapPlugin
        center: QtPositioning.coordinate(-23.8333,-46.7609)
        zoomLevel: 20
    }*/

   /*Map {
        anchors.fill: parent
        plugin: osmMapPlugin

        MapPolyline {
            line.width: 3
            line.color: 'green'
            path: [
                { latitude: -27, longitude: 153.0 },
                { latitude: -27, longitude: 154.1 },
                { latitude: -28, longitude: 153.5 },
                { latitude: -29, longitude: 153.5 }
            ]
        }
    }*/

    Map {
        id:mapa
        anchors.fill: parent
        plugin: osmMapPlugin
        center: QtPositioning.coordinate(-23.6370,-46.557)
        zoomLevel: 20

        MapPolyline {
            id:polyline
            line.width: 10
            line.color: 'deepskyblue'
        }
    }

    Connections {
    target: applicationData

    function onPathChanged(){
        console.log("The application data changed:"+applicationData.path)
        /*var path = polyline.path;*/
        polyline.addCoordinate(applicationData.path)
        mapa.center = applicationData.path
        }
    }
}
