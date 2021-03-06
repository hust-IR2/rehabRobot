#include "CVEyeCamera.h"
#include <iostream>
#include "pupilDetect.h"
using namespace std;
CVEyeCamera::CVEyeCamera(QQuickItem* parent): CVCamera(parent)
{
    leftTop = QPoint(0, 0);
    rightDown = QPoint(0, 0);
    cvPupilCenter = cv::Point(0, 0);
    // Here we must use this function to set exportCvImage true, then can we get the signal.
    getCvImage().value<cv::Mat>();
    connect(this, SIGNAL(cvImageChanged()), this, SLOT(cvImageProcess()));
}

QPoint CVEyeCamera::getLeftTop()
{
    return this->leftTop;
}
void CVEyeCamera::setLeftTop(QPoint _leftTop)
{
    cout <<"leftTop(" << _leftTop.x() << " " << _leftTop.y() << ")" << endl;
    this->leftTop = _leftTop;
}

QPoint CVEyeCamera::getRightDown()
{
    return this->rightDown;
}

void CVEyeCamera::setRightDown(QPoint _rightDown)
{
    cout <<"rightDown(" << _rightDown.x() << " " << _rightDown.y() << ")" << endl;
    this->rightDown = _rightDown;
}

QPoint CVEyeCamera::getPupilCenter()
{
    return pupilCenter;
}

void CVEyeCamera::setPupilCenter(QPoint center)
{
    pupilCenter = center;
    cvPupilCenter = cv::Point(center.x(), center.y());
}

void CVEyeCamera::cvImageProcess()
{
    cv::Mat image = getCvImage().value<cv::Mat>().clone();
    cv::Rect roi = cv::Rect(leftTop.x(), leftTop.y(), rightDown.x() - leftTop.x(), rightDown.y() - leftTop.y());
    cv::Mat pupilTemplate = cv::imread("pupilTemplate.jpg", 0);
    float scale = 0.9;
    monoPupilDetect(image, roi, cvPupilCenter, pupilTemplate, scale);
    pupilCenter = QPoint(cvPupilCenter.x, cvPupilCenter.y);
    // std::cout <<"device id: " << this->getDevice() << "    center:" << cvPupilCenter << std::endl;
    // cv::rectangle(image, roi,cv::Scalar(0,0,255),3);
    // cv::imshow("image", image);
    // cv::waitKey(1);
}
