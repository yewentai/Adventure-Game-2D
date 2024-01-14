#ifndef MY_TEXT_EDITOR_H
#define MY_TEXT_EDITOR_H

#include <QApplication>
#include <QPlainTextEdit>
#include <QKeyEvent>
#include <QObject>
#include <QDebug>

class MyTextEditor : public QPlainTextEdit {
    Q_OBJECT

            signals:
            void enterKeyPressed(QString);

    void tabKeyPressed(QString);

public
    slots:
            void setCompletedCommand(
    const QString &command
    );

public:
    MyTextEditor(QWidget *parent = nullptr)
            : QPlainTextEdit(parent) {
    }

protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_Tab) {
            emit tabKeyPressed(this->toPlainText());
        } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
            emit enterKeyPressed(this->toPlainText());
            this->clear();
        } else {
            QPlainTextEdit::keyPressEvent(event);
        }
    }
};

#endif // MY_TEXT_EDITOR_H
