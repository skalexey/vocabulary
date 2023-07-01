import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Dialog {
	id: dialog
	title: qsTr("Title")

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

    Component.onCompleted : {
        originalWidth = width;
        originalHeight = height;
    }

    closePolicy: Popup.NoAutoClose
    modal: true
    anchors.centerIn: parent

    height: childrenRect.height
    width: childrenRect.width

    ColumnLayout {
        id: mainLayout
        objectName: "content"
    }
}

/*##^##
Designer {
	D{i:0;formeditorZoom:0.9}D{i:2}D{i:3}D{i:1}
}
##^##*/
