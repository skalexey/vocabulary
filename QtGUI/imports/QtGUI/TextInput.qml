import QtQuick
import QtQuick.Controls

Item {
    Label {
        id: label
    }

    TextField {
        property var textToEdit
        property var model
        property var onDefocus: function() {
            console.log("EditField.onDefocus default handler");
        }
        property var onNewValue: function(val) {
            console.log("EditField.onNewValue(" + val + ") default handler");
            if (model)
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
        width: textToEdit ? Math.max(100, textToEdit.width * 1.4) : width
        height: textToEdit ? textToEdit.height * 1.4 : height
        x: textToEdit ? textToEdit.x : x
        y: textToEdit ? textToEdit.y : y
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
