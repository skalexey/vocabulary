import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
	property var model
	property string text

	height: childrenRect.height
	width: layout.width
	
	RowLayout {
		id: layout
		spacing: 8  // Adjust the spacing as needed
	
		Label {
			id: label
			objectName: "label"
			Layout.alignment: Qt.AlignVCenter
		}

		TextField {
			property var textToEdit
			property var onDefocus: function() {
				console.log("EditField.onDefocus default handler");
			}
			property var onNewValue: function(val) {
				console.log("EditField.onNewValue(" + val + ") default handler");
				model.onNewValue(val);
			}
			property var edit: function(val) {
				forceActiveFocus();
				text = val;
			}

			text: parent.text
			Layout.alignment: Qt.AlignVCenter
			id: input
			objectName: "input"
			placeholderText: qsTr("Enter text")
			Keys.onReturnPressed: focus = false;
			Keys.onEnterPressed: focus = false;
			Keys.onEscapePressed: function() {
				local.ignoreChanges = true;
				focus = false;
				local.ignoreChanges = false;
			}
			onFocusChanged: function() {
				if (!focus)
				{
					if (!local.ignoreChanges)
						onNewValue(text);
					onDefocus();
				}
			}

			QtObject {
				id: local
				property bool ignoreChanges: false;
			}
		}
	}
}
