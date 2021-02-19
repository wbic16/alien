﻿#include <QTimer>

#include "MainController.h"
#include "GeneralInfoController.h"
#include "Settings.h"
#include "StringHelper.h"

GeneralInfoController::GeneralInfoController(QObject * parent)
	: QObject(parent)
	, _oneSecondTimer(new QTimer(this))
{
	connect(_oneSecondTimer, &QTimer::timeout, this, &GeneralInfoController::oneSecondTimerTimeout);
}

void GeneralInfoController::init(QLabel * infoLabel, MainController* mainController)
{
	_infoLabel = infoLabel;
	_mainController = mainController;
    _oneSecondTimer->stop();
    _oneSecondTimer->start(1000);
    _rendering = Rendering::Vector;
}

void GeneralInfoController::increaseTimestep()
{
	++_tpsCounting;
	updateInfoLabel();
}

void GeneralInfoController::setZoomFactor(double factor)
{
	_zoomFactor = factor;
	updateInfoLabel();
}

void GeneralInfoController::setRendering(Rendering value)
{
    _rendering = value;
    updateInfoLabel();
}

void GeneralInfoController::oneSecondTimerTimeout()
{
	_tps = _tpsCounting;
	_tpsCounting = 0;
	updateInfoLabel();
}

void GeneralInfoController::updateInfoLabel()
{
    QString renderModeString;
    QString renderModeColorString;
    if (Rendering::Pixel == _rendering) {
        renderModeString = "pixel";
        renderModeColorString = "<font color = #FFB080>";
    } else if (Rendering::Vector == _rendering) {
        renderModeString = "vector";
        renderModeColorString = "<font color = #B0FF80>";
    } else if (Rendering::Item == _rendering) {
        renderModeString = "item";
        renderModeColorString = "<font color = #80B0FF>";
    } else {
        THROW_NOT_IMPLEMENTED();
    }

    auto timestepString = StringHelper::generateFormattedIntString(_mainController->getTimestep(), true);
    auto tpsString = StringHelper::generateFormattedIntString(_tps, true);

    QString colorTextStart = "<font color = " + Const::CellEditTextColor1.name() + ">";
    QString colorDataStart = "<font color = " + Const::CellEditDataColor1.name() + ">";
    QString colorEnd = "</font>";

	QString renderingString = colorTextStart + "Render style: " +  colorEnd + renderModeColorString + "<b>" + renderModeString + "</b>" + colorEnd;

    auto separator = QString("<br/>");  
    auto infoString = renderingString + separator + colorTextStart + "Zoom level: &nbsp;&nbsp;" + colorEnd + colorDataStart
        + QString("%1x").arg(_zoomFactor) + colorEnd + separator + colorTextStart + "Time step: " + colorEnd
        + colorDataStart + "&nbsp;&nbsp;&nbsp;" + timestepString + colorEnd + separator + colorTextStart + "TPS: " + colorEnd
        + colorDataStart + QString("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;") + tpsString + colorEnd;
	_infoLabel->setText(infoString);
}