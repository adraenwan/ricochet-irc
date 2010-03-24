#include "ChatWidget.h"
#include <QBoxLayout>
#include <QTextEdit>
#include <QLineEdit>

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent)
{
	QBoxLayout *layout = new QVBoxLayout(this);
	layout->setMargin(0);

	createTextArea();
	layout->addWidget(textArea);

	createTextInput();
	layout->addWidget(textInput);
}

void ChatWidget::createTextArea()
{
	textArea = new QTextEdit;
	textArea->setReadOnly(true);
	textArea->setFrameStyle(QFrame::NoFrame);
}

void ChatWidget::createTextInput()
{
	textInput = new QLineEdit;
}