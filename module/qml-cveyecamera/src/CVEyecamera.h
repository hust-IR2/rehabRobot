#ifndef CVEYECAMERA_H
#define EYECAMERA_H

#include <QQuickItem>
#include "CVCamera.h"
/**
 * @brief Add some image process function about eye into CVCamera class.
 */
class CVEyeCamera : public CVCamera
{
Q_OBJECT
    Q_DISABLE_COPY(CVEyeCamera)
    Q_PROPERTY(QPoint leftTop
               READ getLeftTop
               WRITE setLeftTop
               NOTIFY LeftTopChanged)
    Q_PROPERTY(QPoint rightDown
               READ getRightDown
               WRITE setRightDown
               NOTIFY RightDownChanged)
    Q_PROPERTY(QPoint pupilCenter
               READ getPupilCenter
               WRITE setPupilCenter
               NOTIFY PupilCenterChanged)

public:
    CVEyeCamera(QQuickItem* parent = 0);
    QPoint getLeftTop();
    void setLeftTop(QPoint);
    QPoint getRightDown();
    void setRightDown(QPoint);
    QPoint getPupilCenter();
    void setPupilCenter(QPoint);
signals:
    void RightDownChanged();
    void LeftTopChanged();
    void PupilCenterChanged();
public slots:
    void cvImageProcess();
private:
    QPoint leftTop;
    QPoint rightDown;
    QPoint pupilCenter;
    cv::Point cvPupilCenter;
};
#endif // CVEYECAMERA_H
