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
#include <QThread>
#include <QProgressBar>
#include <mutex>
#include <list>
#include "filedownloader.h"
#include "themewidget.h"
#include "theme.h"
#include "scrollareacontent.h"
#include "scrollarea.h"
#include "formparameters.h"
#include "types.h"
#include "unzipper.h"
#include "dialogimporturl.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void makeProgressBar();
	bool loadConfigurationFile();
	void checkOutputExistence();
	void importAllThemes();
    void createScrollAreas();
	void importAllThemesThreaded();
	Theme *importOneTheme(const QDir &dir);

	bool saveConfigurationFile();
	void resetDefaultThemeWidget();
	void openTheme(QString str);

	AppParameters *parameters();

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
    std::vector<Theme *> m_extraThemes;

	ThemeWidget *m_defaultThemeWidget;
	std::vector<ThemeWidget *> m_extraThemeWidgets;

	QProgressBar	*m_progressBar;

	static void clearLayout(QLayout *layout);
	void initJson(bool forceReset = false);
	void downloadDefault();
	void makeTheme();
	void resetTheme();
	std::vector<Theme *>::iterator findTheme(const QString &name);
	bool themeFolderIsValid(const QDir &dir);

signals:
	void progressUpdateRequired(int newValue);
	void messageUpdateRequired(const QString &message, int timeout = 0);
	void defaultThemeWidgetCreationRequired();
	void extraThemeWidgetCreationOrUpdateRequired(Theme *theme);
	void openThemeRequired(QDir dir);
	void updateFromThemesDirRequired();

private slots:
	void enableAllWidgets();
	void disableAllWidgets();
	void setAllWidgetsEnabled(bool b);
	void updateFromThemesDir();
	void on_openThemeRequired(QDir dir);
	void createDefaultThemeWidget();
	ThemeWidget *createOrUpdateOneExThemeWidget(Theme *theme);
	void createAllExtraThemeWidgets();
	void loadJsonFromInternet();
	void on_actionDownload_triggered();
	void on_actionOpen_triggered();
	void on_actionOpen_Zip_triggered();
	void on_actionExport_triggered();
	void on_actionSave_triggered();
	void on_actionMake_theme_triggered();
	void on_actionReset_triggered();
	void on_actionParameters_triggered();
	void on_parametersChanged(AppParameters newParameters);
	void on_actionImport_From_Url_triggered();
	void on_urlProvided(QString name, QString urlStr);
};
#endif // MAINWINDOW_H
