#ifndef MAP_WIDGET_H_
#define MAP_WIDGET_H_

#include <vector>
#include <QWidget>
#include <QHBoxLayout>
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkDiskCache>
#include <QGeoView/QGVMap.h>
#include <QGeoView/QGVLayerGoogle.h>

class mapWidget : public QWidget{
    Q_OBJECT

private:

    QHBoxLayout* hBoxLayout = nullptr;

    QGVMap* mapView = nullptr;
    QGVLayer* mapLayer = nullptr;

    QNetworkAccessManager* mapNet = nullptr;

    const QString mapCachePath = "mapCache";
    QNetworkDiskCache* mapCache = nullptr;

    double boatLat = 0;
    double boatLon = 0;

    void setupMapView();

    /*QString readMapFile();
    Esri::ArcGISRuntime::Viewpoint parseMapData(QString raw);
    void setMapCenter(Esri::ArcGISRuntime::Viewpoint center); */

    /*void setupMapFromMmpk();

    void renderGraphics(Esri::ArcGISRuntime::GraphicsOverlay* overlay, bool shouldOnlyRenderBoat = false);
    Esri::ArcGISRuntime::Graphic* drawPoint(Esri::ArcGISRuntime::GraphicsOverlay* overlay, double lat, double lon, QColor pointColor = Qt::blue, QColor outlineColor = Qt::white);

    std::vector<std::pair<double, double>> loadBuoyCoordinates();*/

public:
    mapWidget(QWidget* parent = nullptr);
    ~mapWidget();

public slots:
    void updateBoatLocation(double lat, double lon);
};

#endif