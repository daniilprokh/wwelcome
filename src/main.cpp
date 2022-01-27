#include "welcome_window.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QStyle>

int main(int argc, char* argv[]) {
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));

	QCoreApplication::setOrganizationName("Prokhorov Daniil");
	QCoreApplication::setOrganizationDomain("https://github.com/daniilprokh");
	QCoreApplication::setApplicationName("WelcomeWindow");
	
	QApplication app(argc,argv);

	WelcomeWindow welcome_window;
	//welcome_window.setWindowFlag(Qt::SplashScreen);
	welcome_window.setGeometry(
		QStyle::alignedRect(
			Qt::LeftToRight,
			Qt::AlignCenter,
			welcome_window.size(),
			app.desktop()->availableGeometry()
		)
	);
	welcome_window.show();

	return app.exec();
}