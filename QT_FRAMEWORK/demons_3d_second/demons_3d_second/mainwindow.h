#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include<string>
#include <QtWidgets/QMainWindow>
#include<QtWidgets/QMenubar>
#include<QtWidgets/QMenu>
#include<QtWidgets/QAction>
#include<QtWidgets/QMenubar>
#include<QtWidgets/QToolBar>
#include<QtWidgets/QMenubar>
#include<QtWidgets/QMenubar>
#include"rawvolumewidget.h"
#include"PropertyListWidget.h"
#include"SettingGLWidget.h"
#include"ConsoleWidget.h"
#include"GLWindow.h"
#include<unordered_map>
#include"TransferfunWidget.h"


using namespace std;
class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	static const unsigned int maxNumRecentFiles_ = 10;
	// to do 
	// current work folder 

	QToolBar* basicToolbar_; // toorbar

	//dock widgets;

	// menu actions
	std::unordered_map<std::string, QAction*> actions_;
	RawVolumeWidget* rawVW;

	//
	// Menus and tool bars
	//

	// menus
	QMenuBar* menu_;
	QMenu* fileMenu_;
	QMenu* viewMenu_;
	QMenu* toolsMenu_;
	QMenu* optionsMenu_;
	QMenu* ShaderMenu_;
	QMenu* Customize_;
	QMenu* helpMenu_;
	

	// tool bars
	QToolBar* fileToolBar_;
	QToolBar* viewToolBar_;
	QToolBar* toolsToolBar_;

	// toolwindow;

	PropertyListWidget* proplist;
	SettingGLWidget* settings;
	OPENGL::GLWindow* GL;
	OPENGL::GLWindow* GL2;
	ConsoleWidget* consolewindow;



	// actions
	QAction* workspaceNewAction_;
	QAction* workspaceOpenAction_;
	QAction* workspaceSaveAction_;
	QAction* workspaceSaveAsAction_;
	QAction* workspaceSaveCopyAsAction_;

	QAction* aboutAction_;
	QAction* helpFirstStepsAct_;
	QAction* helpNetworkEditorAct_;
	QAction* helpAnimationAct_;
	QAction* helpTutorialSlidesAct_;
	QAction* importNetworkAction_;
	QAction* exportNetworkAction_;
	QAction* showShortcutPreferencesAction_;
	QAction* quitAction_;

	QAction* rebuildShadersAction_;
	//QAction* enterWhatsThisAction_;
	QAction* loadLastWorkspaceAct_;

	QAction* modeApplicationAction_;
	QAction* modeDevelopmentAction_;

	QAction* screenshotAction_;




	QList<QAction*> recentFileActs_;
    private slots:
      void saveWorkspaceAs();
      void newWorkspace();
      void about();
      void showproperty();
      void showopengl();
      void createcontex();
public:

	void initialize();
	void createActions();
	void createMenus();
	void createToolBars();

	/// Create all tool windows. Has to be called after tgt::initGL() and initCanvas().
	void createToolWindows();

public:
	
	MainWindow(QWidget *parent = 0);
	~MainWindow();
};

#endif // MAINWINDOW_H
