#include <iostream>
#include <thread>
#include <filesystem>

#include <QLayout>
#include <QThread>
#include <QMessageBox>
#include <MeshViewer/MainViewerWidget.h>
#include <MeshViewer/InteractiveViewerWidget.h>

#include <MeshParamWidget.h>

using namespace std::literals;
namespace fs = std::filesystem;

// 自定义功能都放这里
void MainViewerWidget::Custom() {
    
}

MainViewerWidget::MainViewerWidget(QWidget* _parent/* =0 */)
    :loadmeshsuccess(false)
{
    InitViewerWindow();
}

MainViewerWidget::~MainViewerWidget(void)
{
}

void MainViewerWidget::InitViewerWindow(void)
{
    CreateViewerDialog();
    CreateParamWidget();

    QHBoxLayout* main_layout = new QHBoxLayout();
    main_layout->addWidget(meshparamwidget);
    main_layout->addWidget(meshviewerwidget, 1);
    this->setLayout(main_layout);
}

Mesh& MainViewerWidget::mesh() {
    return meshviewerwidget->get_mesh();
}

void MainViewerWidget::CreateParamWidget(void)
{
    meshparamwidget = new MeshParamWidget();
    connect(meshparamwidget, SIGNAL(PrintInfoSignal()), meshviewerwidget, SLOT(PrintMeshInfo()));
    Custom();
}

void MainViewerWidget::CreateViewerDialog(void)
{
    meshviewerwidget = new InteractiveViewerWidget(NULL);
    meshviewerwidget->setAcceptDrops(true);
    connect(meshviewerwidget, SIGNAL(LoadMeshOKSignal(bool, QString)), SLOT(LoadMeshFromInner(bool, QString)));
}

void MainViewerWidget::OpenMeshGUI(const QString & fname)
{
    if (fname.isEmpty() || !meshviewerwidget->LoadMesh(fname.toStdString()))
    {
        QString msg = "Cannot read mesh from file:\n '" + fname + "'";
        QMessageBox::critical(NULL, windowTitle(), msg);
    }
    else
    {
        loadmeshsuccess = true;
        // emit(haveLoadMesh(fname));
    }
}

void MainViewerWidget::SaveMeshGUI(const QString & fname)
{
    if (fname.isEmpty() || !meshviewerwidget->SaveMesh(fname.toStdString()))
    {
        QString msg = "Cannot read mesh from file:\n '" + fname + "'";
        QMessageBox::critical(NULL, windowTitle(), msg);
    }
}

void MainViewerWidget::LoadMeshFromInner(bool OK, QString fname)
{
    loadmeshsuccess = OK;
    // emit(haveLoadMesh(fname));
    // TODO 这个函数似乎没什么用
}

void MainViewerWidget::Open(void)
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open mesh file"),
        tr("./model"),
        tr("Mesh Files (*.obj *.off *.ply *.stl);;"
        "OFF Files (*.off);;"
        "OBJ Files (*.obj);;"
        "PLY Files (*.ply);;"
        "STL Files (*.stl);;"
        "All Files (*)"));
    if (!fileName.isEmpty())
    {
        OpenMeshGUI(fileName);
    }
}

void MainViewerWidget::Save(void)
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save mesh file"),
        tr("untitled.obj"),
        tr("OBJ Files (*.obj);;"
        "OFF Files (*.off);;"
        "PLY Files (*.ply);;"
        "STL Files (*.stl);;"
        "All Files (*)"));
    if (!fileName.isEmpty())
    {
        SaveMeshGUI(fileName);
    }
}

void MainViewerWidget::ClearMesh(void)
{
    if (loadmeshsuccess)
    {
        loadmeshsuccess = false;
        meshviewerwidget->Clear();
    }
}

void MainViewerWidget::Screenshot(void)
{
    meshviewerwidget->ScreenShot();
}

void MainViewerWidget::ShowPoints(void)
{
    meshviewerwidget->SetDrawMode(InteractiveViewerWidget::POINTS);
}

void MainViewerWidget::ShowWireframe(void)
{
    meshviewerwidget->SetDrawMode(InteractiveViewerWidget::WIREFRAME);
}

void MainViewerWidget::ShowHiddenLines(void)
{
    meshviewerwidget->SetDrawMode(InteractiveViewerWidget::HIDDENLINES);
}

void MainViewerWidget::ShowFlatLines(void)
{
    meshviewerwidget->SetDrawMode(InteractiveViewerWidget::FLATLINES);
}

void MainViewerWidget::ShowFlat(void)
{
    meshviewerwidget->SetDrawMode(InteractiveViewerWidget::FLAT);
}

void MainViewerWidget::ShowSmooth(void)
{
    meshviewerwidget->SetDrawMode(InteractiveViewerWidget::SMOOTH);
}

void MainViewerWidget::Lighting(bool b)
{
    meshviewerwidget->EnableLighting(b);
}

void MainViewerWidget::DoubleSideLighting(bool b)
{
    meshviewerwidget->EnableDoubleSide(b);
}

void MainViewerWidget::ShowBoundingBox(bool b)
{
    meshviewerwidget->SetDrawBoundingBox(b);
}

void MainViewerWidget::ShowBoundary(bool b)
{
    meshviewerwidget->SetDrawBoundary(b);
}

void MainViewerWidget::ResetView(void)
{
    meshviewerwidget->ResetView();
}

void MainViewerWidget::ViewCenter(void)
{
    meshviewerwidget->ViewCenter();
}

void MainViewerWidget::CopyRotation(void)
{
    meshviewerwidget->CopyRotation();
}

void MainViewerWidget::LoadRotation(void)
{
    meshviewerwidget->LoadRotation();
}
