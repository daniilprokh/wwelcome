#ifndef WELCOME_WINDOW
#define WELCOME_WINDOW

#include "settings_widget.h"

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QPixmap>
#include <QUrl>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class WelcomeWindow; }
QT_END_NAMESPACE

class WelcomeWindow : public QMainWindow {
	Q_OBJECT
public:
	WelcomeWindow(QMainWindow* parent = nullptr);
	~WelcomeWindow();
public slots:
	void setSettings();
protected:
	void closeEvent(QCloseEvent* event) override;
	void showEvent(QShowEvent* event) override;
private:
	QPixmap background_;
	QUrl song_url_;
	SettingsWidget settings_widget_;

	std::shared_ptr<QGraphicsScene> scene_{ new QGraphicsScene() };

	std::unique_ptr<QMediaPlayer> player_{ new QMediaPlayer() };
	std::unique_ptr<Ui::WelcomeWindow> ui_;
};

#endif // !WELCOME_WINDOW