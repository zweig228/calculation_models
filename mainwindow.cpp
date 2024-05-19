#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
};


MainWindow::~MainWindow()
{
    delete ui;
}

// Функция для вывода данных из kinematic_struct в QTextEdit
void displayKinematicData(const kinematic_struct& kinematic, QTextEdit* textEdit) {
    if (!textEdit) return;

    QString velocityStr = QString("Velocity: (%1, %2, %3)")
                              .arg(kinematic.velocity.x)
                              .arg(kinematic.velocity.y)
                              .arg(kinematic.velocity.z);
    QString positionStr = QString("Position: (%1, %2, %3)")
                              .arg(kinematic.position.x)
                              .arg(kinematic.position.y)
                              .arg(kinematic.position.z);
    // QString tActStr = QString("Time: %1").arg(kinematic.t_act);

    textEdit->clear();

    textEdit->append(velocityStr);
    textEdit->append(positionStr);
    // textEdit->append(tActStr);
}

// Функция для вывода данных из RingSegment в QTextEdit
void displayRingSegmentData(const RingSegment& ringSegment, QTextEdit* textEdit_2) {

    if (!textEdit_2) return;

    textEdit_2->clear();

    for (int i = 0; i <= ringSegment.num_segments; ++i) {
        QString segmentStr = QString("Segment %1: Alpha: %2, Length: %3")
                                 .arg(i + 1)
                                 .arg(ringSegment.alpha[i])
                                 .arg(ringSegment.length[i]);
        textEdit_2->append(segmentStr);
    }
}

void displayTime(const kinematic_struct& kinematic, QTextEdit* textEdit_3) {
    if (!textEdit_3) return;
    QString tActStr = QString("Time: %1").arg(kinematic.t_act);
    if (kinematic.t_act == 0) {
        // Выдача ошибки, например, с помощью QMessageBox
        QMessageBox::critical(nullptr, "Ошибка", "Некорректное значение времени.");
        return;
    }
    textEdit_3->clear();
    textEdit_3->append(tActStr);
}


void MainWindow::on_recount_button_clicked()
{

    recount_object_state(ring_object_manager.kinematic, ui->doubleSpinBox->value(), ui->mass_spinbox->value(), ui->air_temperature_spinbox->value(), ui->cross_sectional_area_spinbox->value());
    calculate_temperatures(ring_object_manager.kinematic, ui->radius_spinbox->value(), ui->step_spinbox->value());

    displayKinematicData(ring_object_manager.kinematic, ui->textEdit);

    displayRingSegmentData(ring_object_manager.ringSegment, ui->textEdit_2);

    displayTime(ring_object_manager.kinematic, ui->textEdit_3);
}


void MainWindow::on_initialization_button_clicked()
{
    readSegmentsFromFile("C:/Users/User/Desktop/build-calculation_models-Desktop_Qt_5_9_0_MinGW_32bit-Debug/segments.txt", ring_object_manager.segmentsData);
    ring_object_manager.ringSegment = convertSegmentsDataToRingSegment(ring_object_manager.segmentsData);
    Vector3D initial_position (ui->x_position_spinbox->value(), ui->y_position_spinbox->value(), ui->z_position_spinbox->value());
    object_state_initialization(ring_object_manager.kinematic, ui->zenith_angle_spinbox->value(), ui->azimuth_angle_spinbox->value(), ui->velocity_0_spinbox->value(), initial_position, ui->sea_height_position_spinbox->value());
}
