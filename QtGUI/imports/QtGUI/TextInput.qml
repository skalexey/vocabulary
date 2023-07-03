import QtQuick
import QtQuick.Controls

Item {
    property var model
    property string text

    height: childrenRect.height

    Label {
        id: label
        objectName: "label"
    }

    TextField {
        text: parent.text
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

        QtObject {
            id: local
            property bool ignoreChanges: false;
        }
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
    }
}
