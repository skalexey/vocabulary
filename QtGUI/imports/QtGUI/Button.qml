import QtQuick
import QtQuick.Controls


Button {
    property var model
    onClicked: function(mouse) {
        model.buttonClicked();
    }
}

/*##^##
Designer {
	D{i:0;formeditorZoom:0.9}D{i:2}D{i:3}D{i:1}
}
##^##*/
