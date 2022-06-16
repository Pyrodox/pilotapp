#include "settingsOptionsWidget.h"

#include "../../../../../../../Backend/Utilities/utilities.h"

//

settingsOptionsWidget::settingsOptionsWidget(QWidget* parent){
    //utilities::setPaletteColor(this, QPalette::Background, Qt::blue);

    //

    vBoxLayout = new QVBoxLayout(this);

    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    vBoxLayout->setSpacing(0);

    //

    renderContent();

}

settingsOptionsWidget::~settingsOptionsWidget(){

}

//

void settingsOptionsWidget::renderContent(){
    exitButton = new QPushButton(this);

    exitButton->setText("Close App");
    //exitButton->setContentsMargins(10, 0, 10, 0);
    
    QFont exitButtonFont = exitButton->font();
    exitButtonFont.setPixelSize(12);
    exitButton->setFont(exitButtonFont);

    utilities::setPaletteColor(exitButton, QPalette::ButtonText, Qt::white);

    //vBoxLayout->setAlignment(Qt::AlignLeft);
    vBoxLayout->addWidget(exitButton, 0, Qt::AlignHCenter);

    connect(exitButton, &QPushButton::released, this, &settingsOptionsWidget::handleExit);
}

void settingsOptionsWidget::handleExit(){
    utilities::findMainWindow()->closeApplication();
}