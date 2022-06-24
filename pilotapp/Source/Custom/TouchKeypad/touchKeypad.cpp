#include "touchKeypad.h"

#include "../TouchInputWidgets/TouchNumericalLineEdit/touchNumericalLineEdit.h"
#include "../../Backend/Utilities/utilities.h"
#include "../../MainWindow.h"

#include <QDebug>
#include <QPushButton>
#include <QKeyEvent>

//

touchKeypad* touchKeypad::instance = nullptr;

touchKeypad::touchKeypad(QWidget* parent) : QWidget(parent){
    //this->setObjectName("touchKeypad");
    this->setGeometry(0, 0, this->width, this->height);
    this->hide();

    utilities::setWidgetRoundedCorner(this, cornerRadius, {});
    utilities::setPaletteColor(this, QPalette::Background, backgroundColor);

    //

    renderContent();
}

touchKeypad::~touchKeypad(){
}

touchKeypad* touchKeypad::getInstance(){
    if (touchKeypad::instance == nullptr){
        touchKeypad::instance = new touchKeypad(utilities::findMainWindow());
    }
    return touchKeypad::instance;
}

//

void touchKeypad::renderContent(){
    gridLayout = new QGridLayout(this);

    gridLayout->setContentsMargins(padding, 0, padding, 0);
    gridLayout->setSpacing(0);

    //

    /*QPushButton* b = new QPushButton(this);

    b->setText("Close");

    connect(b, &QPushButton::clicked, this, &touchKeypad::closeKeypad);

    gridLayout->addWidget(b);*/

    //

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            int n = (i * 3) + j + 1;
            
            QPushButton* b = new QPushButton(this);

            b->setText(QString::number(n));

            gridLayout->addWidget(b, i, j);
        }
    }

    //

    QPushButton* zeroButton = new QPushButton(this);

    zeroButton->setText("0");

    gridLayout->addWidget(zeroButton, 3, 1);

    //

    QPushButton* backButton = new QPushButton(this);

    backButton->setText("⬅");

    gridLayout->addWidget(backButton, 3, 0);

    //

    QPushButton* exitButton = new QPushButton(this);

    exitButton->setText("⬇");

    gridLayout->addWidget(exitButton, 3, 2);
}

void touchKeypad::closeKeypad(){
    this->hide();
    if (inputWidget)
        inputWidget->clearFocus();
}

void touchKeypad::afterShowSetup(QObject* inputobj){
    inputWidget = qobject_cast<QWidget*>(inputobj);
}

//

bool touchKeypad::eventFilter(QObject* obj, QEvent* event){
    if (qobject_cast<TouchNumericalLineEdit*>(obj) && event->type() == QEvent::FocusIn){
        //qInfo() << "keypad open";
        utilities::findMainWindow()->showTouchKeypad();
        afterShowSetup(obj);
    }
    return QWidget::eventFilter(obj, event);
}

// https://stackoverflow.com/a/11185022/

void touchKeypad::mouseMoveEvent(QMouseEvent* event){
    if (event->buttons() & Qt::LeftButton){
        this->move(mapToParent(event->pos() - mouseEventOffset));
        
        // to ensure pad stays within bounds

        QPoint p = this->pos();
        p.setX(p.x() + (width / 2));
        p.setY(p.y() + (height / 2));

        //qInfo() << "pos = " << p; 

        p.setX(std::max(std::min(p.x(), MainWindow::windowWidth), 0));
        p.setY(std::max(std::min(p.y(), MainWindow::windowHeight), 0));

        //qInfo() << "adj pos = " << p;
        
        p.setX(p.x() - (width / 2));
        p.setY(p.y() - (height / 2));
        this->move(p);
    }
}

void touchKeypad::mousePressEvent(QMouseEvent* event){
    mouseEventOffset = event->pos();
}

//

void touchKeypad::buttonPress(int num){

}

QSize touchKeypad::getSize(){
    return QSize(width, height);
}
