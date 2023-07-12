import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
	id: dialog
	title: qsTr("Title")
    property int originalHeight
    property int originalWidth

    property var onShow: function() {
        console.log("Dialog.onShow default handler");
    }
    property var show: function() {
        visible = true;
        onShow();
    }

    property var onDestroy: function() {
        console.log("Dialog.onDestroy default handler");
    }

    onClosed: function() {
        console.log("Dialog.onClosed default handler");
    }

    closePolicy: Popup.NoAutoClose
    modal: true // Default value. Overridden from C++.
    anchors.centerIn: parent
    
    Item {
        id: test
        height: childrenRect.height
        width: childrenRect.width

        ColumnLayout {
            id: mainLayout
            objectName: "content"
            Layout.maximumWidth: 400
        
        }
        property int previousWidth: 0
        property int previousHeight: 0

        onHeightChanged: function() {
            var deltaHeight = height - previousHeight;
            previousHeight = height
            dialog.height += deltaHeight
        }
        onWidthChanged: function() {
            var deltaWidth = width - previousWidth
            dialog.width += deltaWidth
            previousWidth = width
        } 
    }
    Component.onCompleted : {
        originalWidth = width;
        originalHeight = height;
    }
}

/*##^##
Designer {
	D{i:0;formeditorZoom:0.9}D{i:2}D{i:3}D{i:1}
}
##^##*/
