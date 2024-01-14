#include "my_text_editor.h"
#include <QKeyEvent>
#include <QDebug>

void MyTextEditor::setCompletedCommand(const QString &command) {
    this->setPlainText(command);
    this->moveCursor(QTextCursor::End); // Move cursor to end of text
}
