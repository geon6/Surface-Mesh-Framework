#pragma once

#include <string>
#include <unordered_map>

#include <QWidget>
#include <QtGui>
#include <QtWidgets>
#include <QSlider>
#include <QSpinBox>
#include <QGroupBox>
#include <QVBoxLayout>

class MeshParamWidget : public QWidget
{
    Q_OBJECT

public:
    MeshParamWidget(QWidget *parent = 0);
    ~MeshParamWidget(void);
private:
    void CreateTabWidget(void);
    void CreateLayout(void);
signals:
    void PrintInfoSignal();

private:
    QTabWidget *twParam;
    QWidget *wParam;
    QScrollArea *saParam;
    QPushButton *pbPrintInfo;

public:
    // 自己的按钮
    //  -------------   去噪相关 Begin   -------------
    QPushButton *button_add_noise;
    QPushButton *button_smoothing_filtering;
    QPushButton *button_smoothing_diffusion_flow;
    int smoothing_m{1};
    QSpinBox *spinbox_smoothing;
    //  -------------   去噪相关 End   ---------------

    //  -------------   参数化 Begin   -------------
    QPushButton *button_tutte;
    QPushButton *button_tutte_square;
    QPushButton *button_tutte_triangle;
    QPushButton *button_tutte_hexagon;
    QPushButton *button_aes;
    QPushButton *button_my; 
    QPushButton *button_show_my_iter;
    //  -------------   参数化 End   ---------------

    //  -------------   简化 Begin   -------------
    QPushButton *button_qem;
    int qem_t{1};
    QSpinBox* spinbox_qem;
    //  -------------   简化 End   ---------------

    //  -------------   修复 Begin   -------------
    // Delaunay??
    //  -------------   修复 End   ---------------

    //  -------------   变形 Begin   -------------
    //  -------------   变形 End   ---------------

    //  -------------   细分 Begin   -------------
    //  -------------   细分 End   ---------------
};
