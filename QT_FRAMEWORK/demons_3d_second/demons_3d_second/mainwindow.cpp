#include "mainwindow.h"
#include"QtWidgets/qmessagebox.h"
#include"QtWidgets/QFileDialog"
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{

	setMinimumHeight(1000);
	setMinimumWidth(1500);
	//setPaletteBackgroundColor(Qt::black);
	//setAutoFillBackground(true);
	this->setStyleSheet("MainWindow{background:'#E6E6FA';}");
	
	//this->setProperty("windowOpacity", 0.9);
	//this->setStyleSheet("background:transparent");
	setWindowIcon(QIcon("./resources/icons/inviwo_dark.png"));
	createToolWindows();
	createActions();
	createMenus();
	createToolBars();

	
}



void MainWindow::initialize()
{
	 // opengl context
}


void MainWindow::createActions()
{
	// Workspace
	workspaceNewAction_ = new QAction(QIcon("./resources/icons/new.png"), tr("&New Workspace"), this);
	workspaceNewAction_->setShortcut(QKeySequence::New);
	connect(workspaceNewAction_, SIGNAL(triggered()), this, SLOT(newWorkspace()));

	workspaceOpenAction_ = new QAction(QIcon("./resources/icons/open.png"), tr("&Open Workspace..."), this);
	workspaceOpenAction_->setShortcut(QKeySequence::Open);
	connect(workspaceOpenAction_, SIGNAL(triggered()), this, SLOT(openWorkspace()));

	workspaceSaveAction_ = new QAction(QIcon("./resources/icons/save.png"), tr("&Save Workspace"), this);
	workspaceSaveAction_->setShortcut(QKeySequence::Save);
	connect(workspaceSaveAction_, SIGNAL(triggered()), this, SLOT(saveWorkspace()));

	workspaceSaveAsAction_ = new QAction(QIcon("./resources/icons/saveas.png"), tr("Save Workspace &As..."), this);
	connect(workspaceSaveAsAction_, SIGNAL(triggered()), this, SLOT(saveWorkspaceAs()));
	

	workspaceSaveCopyAsAction_ = new QAction(tr("Save Workspace &Copy As..."), this);
	connect(workspaceSaveCopyAsAction_, SIGNAL(triggered()), this, SLOT(saveWorkspaceCopyAs()));

	screenshotAction_ = new QAction(tr("Save Workspace &Copy As..."), this);
	connect(screenshotAction_, SIGNAL(triggered()), this, SLOT(ScreenShot()));

	//view


	//tool
	screenshotAction_ = new QAction(QIcon("./resources/icons/screenshot.png"), "&Screenshot", this);
	screenshotAction_->setData(0);

	aboutAction_ = new QAction(QIcon("./resources/icons/about.png"), tr("&About MVG..."), this);
	connect(aboutAction_, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
	menu_ = menuBar();

	//menu_->setAutoFillBackground(true);
	//
	// File menu
	//
	fileMenu_ = menu_->addMenu(tr("&File"));
	fileMenu_->addAction(workspaceNewAction_);
	fileMenu_->addAction(workspaceOpenAction_);
	fileMenu_->addAction(workspaceSaveAction_);
	fileMenu_->addAction(workspaceSaveAsAction_);
	fileMenu_->addAction(workspaceSaveCopyAsAction_);

	

	//
	// View menu
	//
	viewMenu_ = menu_->addMenu(tr("&View"));

	viewMenu_->addAction(settings->toggleViewAction());
	viewMenu_->addAction(proplist->toggleViewAction());
	viewMenu_->addAction(consolewindow->toggleViewAction());

	/*modeDevelopmentAction_ = new QAction(QIcon(":/voreenve/icons/development-mode.png"),
		tr("&Development Mode"), this);
	modeDevelopmentAction_->setCheckable(true);
	modeDevelopmentAction_->setShortcut(tr("F3"));

	modeApplicationAction_ = new QAction(QIcon(":/voreenve/icons/visualization-mode.png"),
		tr("&Application Mode"), this);
	modeApplicationAction_->setCheckable(true);
	modeApplicationAction_->setShortcut(tr("F4"));

	QActionGroup* guiModeGroup = new QActionGroup(this);
	guiModeGroup->addAction(modeApplicationAction_);
	guiModeGroup->addAction(modeDevelopmentAction_);
	modeApplicationAction_->setChecked(true);
	connect(guiModeGroup, SIGNAL(triggered(QAction*)), this, SLOT(guiModeChanged()));

	viewMenu_->addAction(modeDevelopmentAction_);
	viewMenu_->addAction(modeApplicationAction_);
	viewMenu_->addSeparator();*/


	// tools
	toolsMenu_ = menu_->addMenu(tr("&Tools"));
	
	QMenu* screenshotMenu = new QMenu(this);
	screenshotMenu->addAction(screenshotAction_);
	

	//
	// Shader Menu
	//
	ShaderMenu_ = menu_->addMenu(tr("&GLSL Shader"));


	//
	// Help Menu
	//
	helpMenu_ = menu_->addMenu(tr("&Help"));
	
	
	helpMenu_->addAction(aboutAction_);
	
	


}

void MainWindow::createToolBars()
{


	// file toolbar
	fileToolBar_ = addToolBar(tr("File"));
	
	fileToolBar_->setObjectName("file-toolbar");
	fileToolBar_->addAction(workspaceNewAction_);
	fileToolBar_->addAction(workspaceOpenAction_);
	fileToolBar_->addAction(workspaceSaveAction_);
	
	// view toolbar
	viewToolBar_ = addToolBar(tr("View"));

	/*viewToolBar_->setObjectName("view-toolbar");
	QLabel* label = new QLabel(tr("   View  "));
	label->setObjectName("toolBarLabel");
	viewToolBar_->addWidget(label);

	viewToolBar_->addAction(modeDevelopmentAction_);
	viewToolBar_->addAction(modeApplicationAction_);
	viewToolBar_->addSeparator();*/

	
	// tools toolbar
	toolsToolBar_ = addToolBar(tr("Tools"));

	//toolsToolBar_->setObjectName("tools-toolbar");
	//label = new QLabel(tr("   Tools "));
	//label->setObjectName("toolBarLabel");
	//toolsToolBar_->addWidget(label);
	//toolsToolBar_->addAction(rebuildShadersAction_);
	//toolsToolBar_->addAction(screenshotAction_);


}

void MainWindow::newWorkspace()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("open model image"), ".", tr(" Model File(*.txt)"));

	if (fileName == nullptr) //must add this line of code to make sure filename is not empty;

	{
		QMessageBox::warning(this, "error message", "you do not open a file");
		return;
	}
	string filename = fileName.toStdString();

	
}


void MainWindow::saveWorkspaceAs()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("open model image"), ".", tr(" Model File(*.txt)"));

	if (fileName == nullptr) //must add this line of code to make sure filename is not empty;

	{
		QMessageBox::warning(this, "error message", "you do not open a file");
		return;
	}
	string filename = fileName.toStdString();


}


void MainWindow::createToolWindows()
{
	proplist = new PropertyListWidget(this);
	addDockWidget(Qt::LeftDockWidgetArea, proplist);
	settings = new SettingGLWidget(this);
	addDockWidget(Qt::RightDockWidgetArea, settings);
	GL = new OPENGL::GLWindow(this);
	setCentralWidget(GL);
	consolewindow = new ConsoleWidget(this);
	addDockWidget(Qt::BottomDockWidgetArea, consolewindow);
	connect(settings->bt1, SIGNAL(clicked()), this, SLOT(createcontex()));

}


MainWindow::~MainWindow()
{

}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About Application"),
		tr("The <b>Application</b> example demonstrates how to "
		"write modern GUI applications using Qt, with a menu bar, "
		"toolbars, and a status bar."));
}


void MainWindow::showproperty()
{

}
void MainWindow::showopengl()
{

}


void MainWindow::createcontex()
{
	QDialog* dig = new QDialog(this);

	//dig->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);

	dig->setWindowTitle("result");
	dig->setMinimumHeight(450);
	dig->setMinimumWidth(600);


	//OPENGL::GLWindow*GL2 = new OPENGL::GLWindow(this);
	TransferfunWidget* t1 = new TransferfunWidget(dig);
	QVBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(t1);

	dig->setLayout(layout);
	dig->show();


}