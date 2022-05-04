#ifndef POWER_WIDGET_H_
#define POWER_WIDGET_H_

#include <QWidget>
#include "../../contentWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QResizeEvent>

class powerWidget : public ContentWidget{
    Q_OBJECT

private:
    QHBoxLayout* mainContentHLayout;

    QVBoxLayout* powerSourceVLayout;
    QLabel* powerSourceIconLabel;

    //

    QVBoxLayout* dataStackVLayout;
    
    QHBoxLayout* dataValueHLayout;
    QLabel* voltageValueLabel;
    QLabel* currentValueLabel;

    QHBoxLayout* dataLabelHLayout;
    QLabel* voltageLabelLabel;
    QLabel* currentLabelLabel;

    void renderContent();

    void resizeEvent(QResizeEvent*);
public:
    powerWidget(QWidget* parent = nullptr);
    ~powerWidget();
};

#endif