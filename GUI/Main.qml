import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Controls.Material

ApplicationWindow {
    id: root

    width: 760
    height: 560
    visible: true
    title: qsTr("UltralightWebCursor-GUI")

    Material.theme: Material.Dark
    Material.accent: "#3daee9"

    FontLoader {
        id: uiFont
        source: "file:///usr/share/fonts/noto/NotoSans-Regular.ttf"
    }

    font.family: uiFont.name !== "" ? uiFont.name : "Noto Sans"

    FolderDialog {
        id: themeUploadDialog
        title: qsTr("Choose Theme Folder")

        onAccepted: {
            backend.uploadTheme(selectedFolder.toLocalFile())
        }
    }

    Page {
        anchors.fill: parent

        background: Rectangle {
            color: "#181818"
        }

        header: ToolBar {
            height: 52

            background: Rectangle {
                color: "#202020"

                Rectangle {
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: 1
                    color: "#333333"
                }
            }

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 16
                anchors.rightMargin: 16

                TabBar {
                    id: tabBar
                    Layout.fillWidth: true

                    background: Rectangle {
                        color: "transparent"
                    }

                    TabButton {
                        text: qsTr("Theme")
                    }

                    TabButton {
                        text: qsTr("Blacklist")
                    }

                    TabButton {
                        text: qsTr("Setting")
                    }
                }

                ToolButton {
                    id: githubButton
                    Layout.preferredWidth: 40
                    Layout.preferredHeight: 40

                    contentItem: Image {
                        source: "assets/github.svg"
                        fillMode: Image.PreserveAspectFit
                        sourceSize.width: 24
                        sourceSize.height: 24
                    }

                    ToolTip.visible: hovered
                    ToolTip.text: qsTr("Open GitHub Repository")

                    onClicked: {
                        if (typeof backend.openGitHub === "function")
                            backend.openGitHub()
                        else
                            Qt.openUrlExternally("https://github.com/LuYishan-4/Cursor-animation")
                    }
                }
            }
        }

        StackLayout {
            anchors.fill: parent
            currentIndex: tabBar.currentIndex

            Item {
                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 14

                    Label {
                        text: qsTr("Current Theme")
                        font.bold: true
                        font.pixelSize: 18
                    }

                    ComboBox {
                        id: currentThemeBox
                        Layout.fillWidth: true
                        model: backend.themeList
                        currentIndex: backend.themeList.indexOf(backend.currentTheme)

                        onActivated: {
                            backend.useTheme(currentText)
                        }
                    }

                    Label {
                        text: qsTr("Installed Themes")
                        font.bold: true
                        font.pixelSize: 16
                    }

                    ListView {
                        id: themeList
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        spacing: 10
                        clip: true
                        model: backend.themeList

                        delegate: Rectangle {
                            width: themeList.width
                            height: 60
                            radius: 10
                            color: backend.currentTheme === modelData ? "#263b50" : "#242424"
                            border.width: 1
                            border.color: backend.currentTheme === modelData ? "#3daee9" : "#444444"

                            Behavior on color {
                                ColorAnimation {
                                    duration: 150
                                }
                            }

                            RowLayout {
                                anchors.fill: parent
                                anchors.margins: 10
                                spacing: 12

                                RadioButton {
                                    checked: backend.currentTheme === modelData

                                    onClicked: {
                                        backend.useTheme(modelData)
                                    }
                                }

                                Label {
                                    text: modelData
                                    Layout.fillWidth: true
                                    font.pixelSize: 14
                                }

                                Button {
                                    text: qsTr("Apply")
                                    onClicked: backend.useTheme(modelData)
                                }

                                Button {
                                    text: qsTr("Open")
                                    onClicked: backend.openThemeFolder(modelData)
                                }

                                Button {
                                    text: qsTr("Delete")
                                    onClicked: backend.removeTheme(modelData)
                                }
                            }
                        }
                    }

                    Button {
                        text: qsTr("Upload Theme")
                        Layout.alignment: Qt.AlignRight
                        onClicked: themeUploadDialog.open()
                    }
                }
            }
        }
    }
}