#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>
#include <QScrollBar>
#include <QFileDialog>
#include <QMessageBox>
#include <mutex>
#include <QThread>
#include <QProgressBar>
#include "filedownloader.h"
#include "themewidget.h"
#include "theme.h"
#include "scrollareacontent.h"
#include "scrollarea.h"
#include "formparameters.h"
#include "types.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void downloadAllImages();
	void downloadAllColours();
	void downloadAll();

	void makeProgressBar();
	bool setActionIcons();
	bool loadConfigurationFile();
	void checkOutputExistence();
	void loadAllThemes();
    void createScrollAreas();
	void createAllExtraThemeWidgets();

	bool saveConfigurationFile();
	void resetDefaultThemeWidget();

	AppParameters *parameters();
	void notifyThemesPathChanged();
	void notifyParametersChanged();

private:
	Ui::MainWindow *ui;
	FileDownloader *m_fd;
	QJsonDocument	m_configJson;
	AppParameters	m_parameters;
	QString			m_pixmapRelativePath;
	QDir			m_defaultThemePath;
	QFile			m_configFile;

	Theme			m_defaultTheme;
	Theme			m_outputTheme;
	std::vector<Theme> m_extraThemes;

	ThemeWidget *m_defaultThemeWidget;
	std::vector<ThemeWidget *> m_extraThemeWidgets;

	QProgressBar	*m_progressBar;

	static void clearLayout(QLayout *layout);
	void initJson(bool forceReset = false);
	void downloadDefault();
	void makeTheme();
	void resetTheme();

	void setAllWidgetsEnabled(bool b);

private slots:
	void loadJsonFromInternet(QUrl url);
	void on_actionDownload_triggered();
	void on_actionOpen_triggered();
	void on_actionExport_triggered();
	void on_actionSave_triggered();
	void on_actionMake_theme_triggered();
	void on_actionReset_triggered();
	void on_actionParameters_triggered();
};
#endif // MAINWINDOW_H
