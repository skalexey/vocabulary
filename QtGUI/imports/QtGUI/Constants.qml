pragma Singleton
import QtQuick 6.2
import QtQuick.Studio.Application

QtObject {
    readonly property int width: 550
    readonly property int height: 450

    property string relativeFontDirectory: "fonts"

    /* Edit this comment to add your custom font */
    readonly property font font: Qt.font({
                                             family: Qt.application.font.family,
                                             pixelSize: Qt.application.font.pixelSize
                                         })
    readonly property font largeFont: Qt.font({
                                                  family: Qt.application.font.family,
                                                  pixelSize: Qt.application.font.pixelSize * 1.6
                                              })

    readonly property color backgroundColorLight: "#c2c2c2"
    readonly property color backgroundColorDark: "#333333"
    readonly property color backgroundColor: backgroundColorDark


    property StudioApplication application: StudioApplication {
        fontPath: Qt.resolvedUrl("../../content/" + relativeFontDirectory)
    }
}
