import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts

Item {
	id: dialog_root
	height: dialog.height
	width: dialog.width
	property bool modal: true
	property string title: ""

	Dialog {
		id: dialog
		objectName: "dialog"
		title: dialog_root.title

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
		modal: dialog_root.modal // Default value. Overridden from C++.
		// anchors.centerIn: parent
		
		height: childrenRect.height
		width: childrenRect.width

		ColumnLayout {
			id: mainLayout
			objectName: "content"
			Layout.maximumWidth: 250
		}
	}

	MouseArea {
		id: mouse_area
		property real startX
		property real startY
		height: dialog.height + 100
		width: dialog.width + 100
		x: dialog.x - 50
		y: dialog.y - 50

		drag.target: dialog_root

		onPressed: (mouse)=> {
			startX = mouse.x;
			startY = mouse.y;
		}

		onPositionChanged: (mouse)=> {
			var newX = dialog_root.x + (mouse.x - startX);
			var newY = dialog_root.y + (mouse.y - startY);
			dialog_root.x = newX;
			dialog_root.y = newY;
		}
	}
}
/*##^##
Designer {
	D{i:0;formeditorZoom:0.9}D{i:2}D{i:3}D{i:1}
}
##^##*/
