#include <welcome_window.h>
#include <ui_welcome_window.h>

#include <QCloseEvent>
#include <QDebug>
#include <QSettings>

WelcomeWindow::WelcomeWindow(QMainWindow* parent) : QMainWindow(parent),
	ui_(new Ui::WelcomeWindow){
	ui_->setupUi(this);

	connect(ui_->action_settings, &QAction::triggered, this, &WelcomeWindow::setSettings);
	connect(ui_->action_quit, &QAction::triggered, this, &WelcomeWindow::close);

	setWindowIcon(QIcon(":icon/resources/icon.png"));

	QSettings settings("Prokhorov Daniil", "WelcomeWindow");
	settings.beginGroup("WelcomeWindow");
	player_->setMedia(settings.value("audio", QUrl("qrc:/audio/resources/default.mp3")).toUrl());
	background_ = settings.value("image", QPixmap(":image/resources/default.png")).value<QPixmap>();
	QSize window_size(settings.value("size", QSize(800, 600)).toSize());
	settings.endGroup();

	setFixedSize(window_size);
	ui_->graphics_view->setScene(scene_.get());
	ui_->graphics_view->show();
	
	player_->setVolume(25);
	player_->play();
}

WelcomeWindow::~WelcomeWindow() {
	
}

void WelcomeWindow::closeEvent(QCloseEvent* event) {
	if(settings_widget_.isWindow()) {
		settings_widget_.close();
	}

	event->accept();
}

void WelcomeWindow::showEvent(QShowEvent* event) {
	QMainWindow::showEvent(event);

	scene_->addPixmap(background_.scaled(ui_->graphics_view->size()));
	scene_->update();
}

void WelcomeWindow::setSettings() {
	if (!settings_widget_.isActiveWindow()) {
		settings_widget_.show();
	}
}