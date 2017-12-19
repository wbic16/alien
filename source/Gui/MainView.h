﻿#pragma once
#include <QMainWindow>

#include "Model/Api/Definitions.h"

#include "Definitions.h"

namespace Ui {
	class MainView;
}

class MainView
	: public QMainWindow
{
	Q_OBJECT

public:
	MainView(QWidget * parent = nullptr);
	virtual ~MainView();

	virtual void init(MainModel* model, MainController* controller, Serializer* serializer);
	virtual void refresh();

	virtual void setupEditors(SimulationController* controller, DataController* manipulator, Notifier* notifier);
	virtual InfoController* getInfoController() const;

private:
	void connectWidget();
	void setupMenu();
	void setupTheme();

	Q_SLOT void onSetEditorMode();
	Q_SLOT void onRunClicked(bool run);
	Q_SLOT void onStepForward();
	Q_SLOT void onStepBackward();
	Q_SLOT void onMakeSnapshot();
	Q_SLOT void onRestoreSnapshot();
	Q_SLOT void onZoomInClicked();
	Q_SLOT void onZoomOutClicked();
	Q_SLOT void onNewSimulation();
	Q_SLOT void onSaveSimulation();
	Q_SLOT void onLoadSimulation();
	Q_SLOT void onEditSimulationParameters();
	Q_SLOT void onLoadSimulationParameters();
	Q_SLOT void onSaveSimulationParameters();
	Q_SLOT void onEditSymbolTable();
	Q_SLOT void onLoadSymbolTable();
	Q_SLOT void onSaveSymbolTable();

	void updateZoomFactor();

	Ui::MainView* ui = nullptr;
	VisualEditController* _visualEditor = nullptr;
	MainModel* _model = nullptr;
	MainController* _controller = nullptr;
	Serializer* _serializer = nullptr;
	ActionHolder* _actions = nullptr;

	DataEditController* _dataEditor = nullptr;
	ToolbarController* _toolbar = nullptr;
	InfoController* _infoController = nullptr;
};
