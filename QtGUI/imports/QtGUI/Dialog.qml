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

	onClosed: function() {
        console.log("Dialog.onClosed default handler");
	}

	modal: true
	x: 200 // parent.width / 2 - width / 2
	y: 200 // parent.height / 2 - height / 2
	width: 300
	height: 220

    ColumnLayout {
        objectName: "content"
        width: parent.width;
        height: parent.height
	}
}

/*##^##
Designer {
	D{i:0;formeditorZoom:0.9}D{i:2}D{i:3}D{i:1}
}
##^##*/
