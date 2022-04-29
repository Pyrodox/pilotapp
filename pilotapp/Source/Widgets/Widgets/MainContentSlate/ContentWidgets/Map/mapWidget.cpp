#include "mapWidget.h"

#include "../../../../../Backend/Utilities/utilities.h"

#include <ArcGISRuntimeEnvironment.h>
#include <Map.h>
#include <MapGraphicsView.h>
#include <Viewpoint.h>
#include <Point.h>
#include <QFile>
#include <vector>
#include <sstream>
#include <string>
//#include <QDir>

using namespace Esri::ArcGISRuntime;

mapWidget::mapWidget(QWidget* parent){
	utilities::setPaletteColor(this, QPalette::Background, Qt::black);

	//

	hBoxLayout = new QHBoxLayout(this);
	hBoxLayout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(hBoxLayout);

	arcGISMap = new Map(Basemap::imageryWithLabels(this), this);
	arcGISMapView = new MapGraphicsView(arcGISMap, this);

	hBoxLayout->addWidget(arcGISMapView);

	//

	setMapCenter(parseMapData(readMapFile()));
}

mapWidget::~mapWidget(){
}

//

QString mapWidget::readMapFile(){
	QFile mapFile("navcenter.txt");
	
	if (mapFile.open(QIODevice::ReadOnly | QIODevice::Text)){
		QString data = mapFile.readAll();
	   	qDebug() << "Opened map data file (navcenter.txt) - " << data;
	   	return data;
	}
	
	qInfo() << "No map data file found (navcenter.txt)";
	return "";
}

Viewpoint mapWidget::parseMapData(QString raw){
	std::string r = raw.toStdString();
	
	std::vector<std::string> sArray;
	std::stringstream stream(r);

	while (stream.good()){
		std::string substr;
		getline(stream, substr, ',');
		sArray.push_back(substr);
	}

	/*for (std::string i : sArray){
		qDebug() << QString::fromStdString(i);
	}*/

	if (sArray.size() != 3){
		qFatal("Map data is invalid");
		return Viewpoint();
	}

	double latitude = std::stod(sArray[0]), longitude = std::stod(sArray[1]), scale = std::stod(sArray[2]); // default scale is 100000.0
	
	Point centerPoint(longitude, latitude, SpatialReference::wgs84());

	return Viewpoint(centerPoint, scale);
}

void mapWidget::setMapCenter(Viewpoint center){
	this->arcGISMapView->setViewpoint(center);
}