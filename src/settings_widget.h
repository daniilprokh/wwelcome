#ifndef SETTINGS_WIDGET
#define SETTINGS_WIDGET

#include <QWidget>
#include <QUrl>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class SettingsWidget; }
QT_END_NAMESPACE

class SettingsWidget : public QWidget {
	Q_OBJECT
public slots:
	void applyDefaultSettings();
	void applySettings();
	void chooseAudio();
	void chooseImage();
public:
	SettingsWidget(QWidget* parent = nullptr);
	~SettingsWidget();
private:
	std::unique_ptr<Ui::SettingsWidget> ui_;
};

#endif // SETTINGS_WIDGET!