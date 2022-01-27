#include "settings_widget.h"
#include "ui_settings_widget.h"

#include <QDesktopWidget>
#include <QFileDialog>
#include <QSettings>

SettingsWidget::SettingsWidget(QWidget* parent) : QWidget(parent),
	ui_(new Ui::SettingsWidget) {
	ui_->setupUi(this);

	connect(ui_->b_default, &QPushButton::clicked, this, &SettingsWidget::applyDefaultSettings);
	connect(ui_->b_apply, &QPushButton::clicked, this, &SettingsWidget::applySettings);
	connect(ui_->b_default, &QPushButton::clicked, this, &SettingsWidget::applySettings);
	connect(ui_->tb_audio_path, &QToolButton::clicked, this, &SettingsWidget::chooseAudio);
	connect(ui_->tb_image_path, &QToolButton::clicked, this, &SettingsWidget::chooseImage);

	setWindowIcon(QIcon(":icon/resources/icon.png"));

	QSize screen_size(QApplication::desktop()->screen()->size());
	ui_->sb_horizontal->setMaximum(screen_size.width());
	ui_->sb_vertical->setMaximum(screen_size.height());

	QSettings settings("Prokhorov Daniil", "WelcomeWindow");

	settings.beginGroup("WelcomeWindow");
	QSize size(settings.value("size", QSize(800, 600)).value<QSize>());
	settings.endGroup();

	ui_->sb_horizontal->setValue(size.width());
	ui_->sb_vertical->setValue(size.height());

	settings.beginGroup("SettingsWidget");
	ui_->le_audio_path->setText(settings.value("audio_path", "").toString());
	ui_->le_image_path->setText(settings.value("image_path", "").toString());
	ui_->cb_autostart->setChecked(settings.value("autostart", false).toBool());
	settings.endGroup();
}

SettingsWidget::~SettingsWidget() {

}

void SettingsWidget::applyDefaultSettings() {
	QSettings settings("Prokhorov Daniil", "WelcomeWindow");

	settings.beginGroup("WelcomeWindow");
	settings.remove("audio");
	settings.remove("image");
	settings.remove("size");
	settings.endGroup();

	settings.beginGroup("SettingsWidget");
	settings.remove("audio_path");
	settings.remove("image_path");
	settings.remove("autostart");
	settings.endGroup();

	settings.sync();

	ui_->le_audio_path->setText("");
	ui_->le_image_path->setText("");

	QSize size(QSize(800, 600));
	ui_->sb_horizontal->setValue(size.width());
	ui_->sb_vertical->setValue(size.height());

#ifdef _WIN32
	QSettings boot("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
	boot.remove("WelcomeWindow");
#endif // _WIN32

	close();
}

void SettingsWidget::applySettings() {
	QString audio_path(ui_->le_audio_path->text());
	QString image_path(ui_->le_image_path->text());

	QUrl audio_url(QUrl::fromLocalFile(audio_path));
	QPixmap image(image_path);

	QSize size(QSize(ui_->sb_horizontal->value(), ui_->sb_vertical->value()));
	bool is_autostart(ui_->cb_autostart->isChecked());

	QSettings settings("Prokhorov Daniil", "WelcomeWindow");

	settings.beginGroup("WelcomeWindow");
	if (!audio_url.isEmpty()) {
		settings.setValue("audio", audio_url);
	}
	if (!image.isNull()) {
		settings.setValue("image", image);
	}
	settings.setValue("size", size);
	settings.endGroup();

	settings.beginGroup("SettingsWidget");
	settings.setValue("audio_path", audio_path);
	settings.setValue("image_path", image_path);
	settings.setValue("autostart", is_autostart);
	settings.endGroup();

	settings.sync();

#ifdef _WIN32
	QSettings boot("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
	if (is_autostart) {
		boot.setValue("WelcomeWindow", QCoreApplication::applicationFilePath().replace('/', '\\'));
	}
	else {
		boot.remove("WelcomeWindow");
	}
#endif // _WIN32

	close();
}

void SettingsWidget::chooseImage() {
	ui_->le_image_path->setText(
		QFileDialog::getOpenFileName(nullptr, QString::fromLocal8Bit("Выбрать изображении"), "", QString::fromLocal8Bit("Изображение (*.png)"))
	);
}

void SettingsWidget::chooseAudio() {
	ui_->le_audio_path->setText(
		QFileDialog::getOpenFileName(nullptr, QString::fromLocal8Bit("Выбрать аудиофайл"), "", QString::fromLocal8Bit("Aудиофайл (*.mp3)"))
	);
}