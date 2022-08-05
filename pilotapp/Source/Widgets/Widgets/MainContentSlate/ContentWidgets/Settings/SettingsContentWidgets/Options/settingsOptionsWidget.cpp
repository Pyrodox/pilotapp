#include "settingsOptionsWidget.h"

#include <QMessageBox>
#include <QFrame>

#include "../../../../../../../Backend/Utilities/utilities.h"
#include "../../../../../../../Backend/Communication/dataManager.h"

//

settingsOptionsWidget::settingsOptionsWidget(QWidget* parent){
    //utilities::setPaletteColor(this, QPalette::Background, Qt::blue);

    setupLayout();
    renderContent();
}

settingsOptionsWidget::~settingsOptionsWidget(){
}

//

void settingsOptionsWidget::setupLayout(){
    vBoxLayout = new QVBoxLayout(this);

    vBoxLayout->setContentsMargins(0, 0, 0, 0);
    vBoxLayout->setSpacing(0);

    //

    scrollArea = new QScrollArea(this);

    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScroller::grabGesture(scrollArea, QScroller::LeftMouseButtonGesture);

    utilities::setPaletteColor(scrollArea, QPalette::Background, Qt::black);

    vBoxLayout->addWidget(scrollArea);

    //

    scrollAreaContentWidget = new QWidget(scrollArea);

    utilities::setPaletteColor(scrollAreaContentWidget, QPalette::Background, Qt::black);

    scrollArea->setWidget(scrollAreaContentWidget);

    //

    scrollAreaContentLayout = new QVBoxLayout(scrollAreaContentWidget);

    scrollAreaContentWidget->setLayout(scrollAreaContentLayout);

    scrollAreaContentLayout->setContentsMargins(scrollAreaContentPadding, scrollAreaContentPadding/2, scrollAreaContentPadding + scrollAreaContentPadding/2, scrollAreaContentPadding/2);
    scrollAreaContentLayout->setSpacing(scrollAreaContentPadding);
}

void settingsOptionsWidget::renderContent(){
    renderBoatKernel();
    renderCommunicationsManager();
    renderCommunicationsThread();
    renderLeftContentSlate();
    renderMapSettings();
    renderMap();
    renderDivider();
    renderBottomActions();
}

//

void settingsOptionsWidget::renderBoatKernel(){

    boatKernelSettingsWidget = new QWidget(this);
    scrollAreaContentLayout->addWidget(boatKernelSettingsWidget);

    //

    boatKernelLayout = new QVBoxLayout(boatKernelSettingsWidget);
    boatKernelLayout->setContentsMargins(0, 0, 0, 0);

    //

    boatKernelLabel = new QLabel(boatKernelSettingsWidget);
    boatKernelLabel->setText("Boat Kernel");
    boatKernelLabel->setAlignment(Qt::AlignLeft);

    QFont boatKernelLabelFont = boatKernelLabel->font();
    boatKernelLabelFont.setPixelSize(headerLabelFontSize);
    boatKernelLabelFont.setBold(true);
    boatKernelLabel->setFont(boatKernelLabelFont);
    
    boatKernelLayout->addWidget(boatKernelLabel);

    //

    voltageRangeLabel = new QLabel(boatKernelSettingsWidget);
    voltageRangeLabel->setFrameStyle(QFrame::Plain);
    voltageRangeLabel->setText("Min/Max Voltage");
    voltageRangeLabel->setAlignment(Qt::AlignRight);

    QFont voltageRangeLabelFont = voltageRangeLabel->font();
    voltageRangeLabelFont.setPixelSize(subHeaderLabelFontSize);
    voltageRangeLabel->setFont(voltageRangeLabelFont);

    boatKernelLayout->addWidget(voltageRangeLabel);

    //

    voltageBoxLayout = new QHBoxLayout();
    voltageBoxLayout->setContentsMargins(0, 0, 0, 0);
    voltageBoxLayout->setSpacing(horizontalPadding);

    boatKernelLayout->addLayout(voltageBoxLayout);

    //

    minVoltageRangeLabel = new QLabel(boatKernelSettingsWidget);
    minVoltageRangeLabel->setAlignment(Qt::AlignHCenter);
    minVoltageRangeLabel->setFixedWidth(30);
    minVoltageRangeLabel->setText(QString::number(boatDataPack::minPossibleVoltage)); //need backend changes

    voltageBoxLayout->addWidget(minVoltageRangeLabel);

    //

    RangeSlider* minMaxVoltageSlider = new RangeSlider(Qt::Horizontal, RangeSlider::DoubleHandles, boatKernelSettingsWidget);
    minMaxVoltageSlider->SetRange(boatDataPack::minPossibleVoltage, boatDataPack::maxPossibleVoltage); //TODO: needs preference manager integration
    minMaxVoltageSlider->SetUpperValue(boatDataPack::maxPossibleVoltage);
    minMaxVoltageSlider->SetLowerValue(boatDataPack::minPossibleVoltage);

    voltageBoxLayout->addWidget(minMaxVoltageSlider);

    //

    maxVoltageRangeLabel = new QLabel(boatKernelSettingsWidget);
    maxVoltageRangeLabel->setAlignment(Qt::AlignHCenter);
    maxVoltageRangeLabel->setFixedWidth(30);
    maxVoltageRangeLabel->setText(QString::number(boatDataPack::maxPossibleVoltage)); //need backend changes

    voltageBoxLayout->addWidget(maxVoltageRangeLabel);
}

void settingsOptionsWidget::renderCommunicationsManager(){

    communicationsSettingsWidget = new QWidget(this);
    scrollAreaContentLayout->addWidget(communicationsSettingsWidget);
   
    //

    communicationsLayout = new QVBoxLayout(communicationsSettingsWidget);
    communicationsLayout->setContentsMargins(0, 0, 0, 0);

    //

    communicationsLabel = new QLabel(communicationsSettingsWidget);
    //communicationsLabel->setStyleSheet("font-weight: bold; font-size: 20px");
    communicationsLabel->setText("Communications");
    communicationsLabel->setAlignment(Qt::AlignLeft);

    QFont communicationsLabelFont = communicationsLabel->font();
    communicationsLabelFont.setPixelSize(headerLabelFontSize);
    communicationsLabelFont.setBold(true);
    communicationsLabel->setFont(communicationsLabelFont);

    communicationsLayout->addWidget(communicationsLabel);

    //

    ipcSubAddressLabel = new QLabel(communicationsSettingsWidget);
    ipcSubAddressLabel->setFrameStyle(QFrame::Plain);
    ipcSubAddressLabel->setText("IPC IP Address");
    ipcSubAddressLabel->setAlignment(Qt::AlignRight);

    communicationsLayout->addWidget(ipcSubAddressLabel);

    //

    QLineEdit* ipcSubAddressNumericalInput = new TouchNumericalLineEdit(communicationsSettingsWidget);
    ipcSubAddressNumericalInput->setAlignment(Qt::AlignRight);
    ipcSubAddressNumericalInput->setFixedWidth(300);

    communicationsLayout->addWidget(ipcSubAddressNumericalInput);

    //

    ipcSubPortLabel = new QLabel(communicationsSettingsWidget);
    ipcSubPortLabel->setFrameStyle(QFrame::Plain);
    ipcSubPortLabel->setText("IPC Port");
    ipcSubPortLabel->setAlignment(Qt::AlignRight);

    communicationsLayout->addWidget(ipcSubPortLabel);

    //

    QLineEdit* ipcSubPortNumericalInput = new TouchNumericalLineEdit(communicationsSettingsWidget);
    ipcSubPortNumericalInput->setAlignment(Qt::AlignRight);
    ipcSubPortNumericalInput->setFixedWidth(300);
    
    communicationsLayout->addWidget(ipcSubPortNumericalInput);

    //

    scriptPairAddressLabel = new QLabel(communicationsSettingsWidget);
    scriptPairAddressLabel->setFrameStyle(QFrame::Plain);
    scriptPairAddressLabel->setText("Script Pair Address");
    scriptPairAddressLabel->setAlignment(Qt::AlignRight);

    communicationsLayout->addWidget(scriptPairAddressLabel);

    //
    
    QLineEdit* scriptPairAddressNumericalInput = new TouchNumericalLineEdit(communicationsSettingsWidget);
    scriptPairAddressNumericalInput->setAlignment(Qt::AlignRight);
    scriptPairAddressNumericalInput->setFixedWidth(300);
    
    communicationsLayout->addWidget(scriptPairAddressNumericalInput);

    //

    scriptPairPortLabel = new QLabel(communicationsSettingsWidget);
    scriptPairPortLabel->setFrameStyle(QFrame::Plain);
    scriptPairPortLabel->setText("Script Pair Address");
    scriptPairPortLabel->setAlignment(Qt::AlignRight);

    communicationsLayout->addWidget(scriptPairPortLabel);

    //
    
    QLineEdit* scriptPairPortNumericalInput = new TouchNumericalLineEdit(communicationsSettingsWidget);
    scriptPairPortNumericalInput->setAlignment(Qt::AlignRight);
    scriptPairPortNumericalInput->setFixedWidth(300);
    
    communicationsLayout->addWidget(scriptPairPortNumericalInput);    
}

void settingsOptionsWidget::renderCommunicationsThread(){
    commsThreadLayout = new QVBoxLayout(this);
    commsThreadLayout->setContentsMargins(0, 0, 0, 0);
    commsThreadLayout->setAlignment(Qt::AlignRight);
    auto leftLayout = new QVBoxLayout(this);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setAlignment(Qt::AlignLeft);

    scrollAreaContentLayout->addLayout(leftLayout);
    scrollAreaContentLayout->addLayout(commsThreadLayout);

    communicationsThreadLabel = new QLabel(this);
    //communicationsThreadLabel->setStyleSheet("font-weight: bold; font-size: 20px");
    communicationsThreadLabel->setText("Communications Thread");
    communicationsThreadLabel->setAlignment(Qt::AlignLeft);

    QFont communicationsThreadLabelFont = communicationsThreadLabel->font();
    communicationsThreadLabelFont.setPixelSize(headerLabelFontSize);
    communicationsThreadLabelFont.setBold(true);
    communicationsThreadLabel->setFont(communicationsThreadLabelFont);

    leftLayout->addWidget(communicationsThreadLabel);

    //

    loopTimeoutLabel = new QLabel(this);
    loopTimeoutLabel->setFrameStyle(QFrame::Plain);
    loopTimeoutLabel->setText("Loop Timeout");
    loopTimeoutLabel->setAlignment(Qt::AlignRight);

    commsThreadLayout->addWidget(loopTimeoutLabel);

    QLineEdit* loopTimeoutNumericalInput = new TouchNumericalLineEdit(this);
    loopTimeoutNumericalInput->setAlignment(Qt::AlignRight);
    loopTimeoutNumericalInput->setFixedWidth(300);

    commsThreadLayout->addWidget(loopTimeoutNumericalInput);


    stopThreadLabel = new QLabel(this);
    stopThreadLabel->setFrameStyle(QFrame::Plain);
    stopThreadLabel->setText("Stop Thread");
    stopThreadLabel->setAlignment(Qt::AlignRight);

    commsThreadLayout->addWidget(stopThreadLabel);

    QLineEdit* stopThreadNumericalInput = new TouchNumericalLineEdit(this);
    stopThreadNumericalInput->setAlignment(Qt::AlignRight);
    stopThreadNumericalInput->setFixedWidth(300);

    commsThreadLayout->addWidget(stopThreadNumericalInput);
}

void settingsOptionsWidget::renderLeftContentSlate(){
    leftContentSlateLayout = new QVBoxLayout(this);
    leftContentSlateLayout->setContentsMargins(0, 0, 0, 0);
    leftContentSlateLayout->setAlignment(Qt::AlignRight);
    auto leftLayout = new QVBoxLayout(this);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setAlignment(Qt::AlignLeft);

    scrollAreaContentLayout->addLayout(leftLayout);
    scrollAreaContentLayout->addLayout(leftContentSlateLayout);

    leftContentSlateLabel = new QLabel(this);
    //leftContentSlateLabel->setStyleSheet("font-weight: bold; font-size: 20px");
    leftContentSlateLabel->setText("Left Content Slate");
    leftContentSlateLabel->setAlignment(Qt::AlignLeft);

    QFont leftContentSlateLabelFont = leftContentSlateLabel->font();
    leftContentSlateLabelFont.setPixelSize(headerLabelFontSize);
    leftContentSlateLabelFont.setBold(true);
    leftContentSlateLabel->setFont(leftContentSlateLabelFont);

    leftLayout->addWidget(leftContentSlateLabel);

    speedometerUnitsLabel = new QLabel(this);
    speedometerUnitsLabel->setFrameStyle(QFrame::Plain);
    speedometerUnitsLabel->setText("Speedometer Units");
    speedometerUnitsLabel->setAlignment(Qt::AlignRight);

    leftContentSlateLayout->addWidget(speedometerUnitsLabel);

    QLineEdit* speedometerUnitsNumericalInput = new QLineEdit(this);
    speedometerUnitsNumericalInput->setAlignment(Qt::AlignRight);
    speedometerUnitsNumericalInput->setFixedWidth(300);

    leftContentSlateLayout->addWidget(speedometerUnitsNumericalInput);
}

void settingsOptionsWidget::renderMapSettings(){
    mapSettingsLayout = new QVBoxLayout(this);
    mapSettingsLayout->setContentsMargins(0, 0, 0, 0);
    //mapSettingsLayout->setAlignment(Qt::AlignRight);
    auto leftLayout = new QVBoxLayout(this);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setAlignment(Qt::AlignLeft);

    scrollAreaContentLayout->addLayout(leftLayout);
    scrollAreaContentLayout->addLayout(mapSettingsLayout);

    mapSettingsLabel = new QLabel(this);
    //mapSettingsLabel->setStyleSheet("font-weight: bold; font-size: 20px");
    mapSettingsLabel->setText("Map Settings");
    mapSettingsLabel->setAlignment(Qt::AlignLeft);

    QFont mapSettingsLabelFont = mapSettingsLabel->font();
    mapSettingsLabelFont.setPixelSize(headerLabelFontSize);
    mapSettingsLabelFont.setBold(true);
    mapSettingsLabel->setFont(mapSettingsLabelFont);

    leftLayout->addWidget(mapSettingsLabel);

    maxCoordPrecisionLabel = new QLabel(this);
    maxCoordPrecisionLabel->setFrameStyle(QFrame::Plain);
    maxCoordPrecisionLabel->setText("Max Coordinate Precision");
    maxCoordPrecisionLabel->setAlignment(Qt::AlignRight);

    mapSettingsLayout->addWidget(maxCoordPrecisionLabel);

    maxCoordPrecisionLayout = new QHBoxLayout();
    maxCoordPrecisionLayout->setContentsMargins(0, 0, 0, 0);
    maxCoordPrecisionLayout->setSpacing(horizontalPadding);

    mapSettingsLayout->addLayout(maxCoordPrecisionLayout);

    leftMaxCoordPrecisionLabel = new QLabel(this);
    leftMaxCoordPrecisionLabel->setFixedWidth(30);
    leftMaxCoordPrecisionLabel->setText("0"); //need backend changes

    maxCoordPrecisionLayout->addWidget(leftMaxCoordPrecisionLabel);

    RangeSlider* maxCoordPrecisionSlider = new RangeSlider(Qt::Horizontal, RangeSlider::RightHandle, this);
    maxCoordPrecisionSlider->SetRange(0, 100);
    maxCoordPrecisionSlider->SetUpperValue(100);
    maxCoordPrecisionSlider->SetLowerValue(0);

    maxCoordPrecisionLayout->addWidget(maxCoordPrecisionSlider);

    rightMaxCoordPrecisionLabel = new QLabel(this);
    rightMaxCoordPrecisionLabel->setFixedWidth(30);
    rightMaxCoordPrecisionLabel->setText("100"); //need backend changes

    maxCoordPrecisionLayout->addWidget(rightMaxCoordPrecisionLabel);
}

void settingsOptionsWidget::renderMap(){
    mapLayout = new QVBoxLayout(this);
    mapLayout->setContentsMargins(0, 0, 0, 0);
    mapLayout->setAlignment(Qt::AlignRight);
    auto leftLayout = new QVBoxLayout(this);
    leftLayout->setContentsMargins(0, 0, 0, 0);
    leftLayout->setAlignment(Qt::AlignLeft);

    scrollAreaContentLayout->addLayout(leftLayout);
    scrollAreaContentLayout->addLayout(mapLayout);

    mapLabel = new QLabel(this);
    //mapLabel->setStyleSheet("font-weight: bold; font-size: 20px");
    mapLabel->setText("Map");
    mapLabel->setAlignment(Qt::AlignLeft);

    QFont mapLabelFont = mapLabel->font();
    mapLabelFont.setPixelSize(headerLabelFontSize);
    mapLabelFont.setBold(true);
    mapLabel->setFont(mapLabelFont);

    leftLayout->addWidget(mapLabel);

    buoyMarkerSizeLabel = new QLabel(this);
    buoyMarkerSizeLabel->setFrameStyle(QFrame::Plain);
    buoyMarkerSizeLabel->setText("Buoy Marker Size");
    buoyMarkerSizeLabel->setAlignment(Qt::AlignRight);

    mapLayout->addWidget(buoyMarkerSizeLabel);

    QLineEdit* buoyMarkerSizeNumericalInput = new TouchNumericalLineEdit(this);
    buoyMarkerSizeNumericalInput->setAlignment(Qt::AlignRight);
    buoyMarkerSizeNumericalInput->setFixedWidth(300);

    mapLayout->addWidget(buoyMarkerSizeNumericalInput);

    boatMarkerSizeLabel = new QLabel(this);
    boatMarkerSizeLabel->setFrameStyle(QFrame::Plain);
    boatMarkerSizeLabel->setText("Boat Marker Size");
    boatMarkerSizeLabel->setAlignment(Qt::AlignRight);

    mapLayout->addWidget(boatMarkerSizeLabel);

    QLineEdit* boatMarkerSizeNumericalInput = new TouchNumericalLineEdit(this);
    boatMarkerSizeNumericalInput->setAlignment(Qt::AlignRight);
    boatMarkerSizeNumericalInput->setFixedWidth(300);

    mapLayout->addWidget(boatMarkerSizeNumericalInput);

    mapCacheDataLabel = new QLabel(this);
    mapCacheDataLabel->setFrameStyle(QFrame::Plain);
    mapCacheDataLabel->setText("Map Cache Data");
    mapCacheDataLabel->setAlignment(Qt::AlignRight);

    mapLayout->addWidget(mapCacheDataLabel);

    QLineEdit* mapCacheDataNumericalInput = new QLineEdit(this);
    mapCacheDataNumericalInput->setAlignment(Qt::AlignRight);
    mapCacheDataNumericalInput->setFixedWidth(300);

    mapLayout->addWidget(mapCacheDataNumericalInput);
}

void settingsOptionsWidget::renderDivider(){
    QFrame* divider = new QFrame(this);

    divider->setContentsMargins(0, 0, 0, 0);
    divider->setFrameShape(QFrame::HLine);
    divider->setFrameShadow(QFrame::Sunken);

    scrollAreaContentLayout->addWidget(divider);
}

void settingsOptionsWidget::renderBottomActions(){
    bottomActionsLayout = new QHBoxLayout();

    bottomActionsLayout->setContentsMargins(0, 0, 0, 0);
    bottomActionsLayout->setSpacing(horizontalPadding);

    scrollAreaContentLayout->addLayout(bottomActionsLayout);
    
    //

    saveOptionsButton = new QPushButton(this);

    saveOptionsButton->setText("Save Options");

    QFont saveOptionsButtonFont = saveOptionsButton->font();
    saveOptionsButtonFont.setPixelSize(bottomActionsFontSize);
    saveOptionsButton->setFont(saveOptionsButtonFont);

    utilities::setPaletteColor(saveOptionsButton, QPalette::ButtonText, Qt::white);

    bottomActionsLayout->addWidget(saveOptionsButton);

    //

    exitButton = new QPushButton(this);

    exitButton->setText("Close App");
    //exitButton->setContentsMargins(10, 0, 10, 0);
    
    QFont exitButtonFont = exitButton->font();
    exitButtonFont.setPixelSize(bottomActionsFontSize);
    exitButton->setFont(exitButtonFont);

    utilities::setPaletteColor(exitButton, QPalette::ButtonText, Qt::white);

    //vBoxLayout->setAlignment(Qt::AlignLeft);
    bottomActionsLayout->addWidget(exitButton);

    connect(exitButton, &QPushButton::released, this, &settingsOptionsWidget::handleExit);
}

//

void settingsOptionsWidget::handleExit(){
    QMessageBox b;
    b.setText("Close App");
    b.setInformativeText("Are you sure?");
    b.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    b.setDefaultButton(QMessageBox::Yes);

    if (b.exec() == QMessageBox::Yes)
        utilities::findMainWindow()->closeApplication();
}