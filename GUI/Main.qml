import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs


ApplicationWindow {
    id: root

    width: 520
    height: 360
    visible: true
    title: qsTr("UltralightWebCursor-GUI")


    FileDialog {
        id: htmlFileDialog
        title: qsTr("選擇 HTML 主題檔案")
        nameFilters: ["HTML files (*.html *.htm)"]
        onAccepted: {
            backend.htmlPath = htmlFileDialog.selectedFile.toString().replace("file://", "")
        }
    }

    FolderDialog {
        id: sdkFolderDialog
        title: qsTr("選擇 Ultralight SDK 資料夾")
        onAccepted: {
            backend.sdkPath = sdkFolderDialog.selectedFolder.toString().replace("file://", "")
        }
    }


    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 16

        Label {
            text: qsTr("CursorFX 游標特效設定")
            font.pixelSize: 20
            font.bold: true
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                text: qsTr("啟用特效")
                Layout.fillWidth: true
            }

            Switch {
                checked: backend.enabled
                onToggled: {
                    if(checked)
                        backend.enable()
                    else
                        backend.disable()
                }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4

            Label {
                text: qsTr("HTML 主題路徑")
                font.bold: true
            }

            RowLayout {
                Layout.fillWidth: true

                TextField {
                    id: htmlPathField
                    Layout.fillWidth: true
                    text: backend.htmlPath
                    placeholderText: qsTr("尚未設定")
                    onEditingFinished: backend.htmlPath = text

                    color: backend.pathExists(text) ? "black" : "red"
                }

                Button {
                    text: qsTr("瀏覽…")
                    onClicked: htmlFileDialog.open()
                }
            }

            Label {
                visible: htmlPathField.text.length > 0 && !backend.pathExists(htmlPathField.text)
                text: qsTr("⚠ 這個路徑目前不存在")
                color: "red"
                font.pixelSize: 11
            }
        }

        // --- SDK 路徑 ---
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4

            Label {
                text: qsTr("Ultralight SDK 路徑")
                font.bold: true
            }

            RowLayout {
                Layout.fillWidth: true

                TextField {
                    id: sdkPathField
                    Layout.fillWidth: true
                    text: backend.sdkPath
                    placeholderText: qsTr("尚未設定")
                    onEditingFinished: backend.sdkPath = text

                    color: backend.pathExists(text) ? "black" : "red"
                }

                Button {
                    text: qsTr("瀏覽…")
                    onClicked: sdkFolderDialog.open()
                }
            }

            Label {
                visible: sdkPathField.text.length > 0 && !backend.pathExists(sdkPathField.text)
                text: qsTr("⚠ 這個路徑目前不存在")
                color: "red"
                font.pixelSize: 11
            }
        }

        Item {
            Layout.fillHeight: true
        }

        Label {
            text: backend.statusMessage
            color: "gray"
            font.pixelSize: 12
        }

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            Button {
                text: qsTr("重新載入")
                onClicked: backend.reload()
            }

            Button {
                text: qsTr("重新載入 HTML")
                onClicked: backend.reloadHtml()
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: qsTr("儲存")
                onClicked: backend.save()
            }

            Button {
                text: qsTr("儲存並套用")
                highlighted: true
                onClicked: {
                    backend.save()
                    backend.reconfigureKWin()
                }
            }
        }
    }
}
