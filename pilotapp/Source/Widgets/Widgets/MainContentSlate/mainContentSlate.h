#ifndef MAIN_CONTENT_SLATE_H_
#define MAIN_CONTENT_SLATE_H_

#include <QWidget>

#include <QPalette>
#include <QHBoxLayout>

#include "ContentWidgets/Map/mapWidget.h"
#include "ContentWidgets/Settings/settingsWidget.h"

class mainContentSlateWidget : public QWidget {
	Q_OBJECT

private:
	QHBoxLayout* mapLayout;
	mapWidget* map;

	void setupMapWidget();

public:
	mainContentSlateWidget(QWidget* parent = nullptr);
	~mainContentSlateWidget();

	void updateToWidgetIndex(int index);
};

#endif // !MAIN_CONTENT_SLATE_H_