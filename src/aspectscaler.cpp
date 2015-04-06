#include "aspectscaler.h"
#include "ui_aspectscaler.h"
#include <algorithm>

AspectScaler::AspectScaler(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AspectScaler)
{
    ui->setupUi(this);
    connect(ui->EditWidth, SIGNAL(textChanged(QString)), ui->CalculatedWidth, SLOT(setText(QString)));
    connect(ui->EditWidth, SIGNAL(textEdited(QString)), this, SLOT(NewW(QString)));

    connect(ui->EditHeight, SIGNAL(textChanged(QString)), ui->CalculatedHeight, SLOT(setText(QString)));
    connect(ui->EditHeight, SIGNAL(textEdited(QString)), this, SLOT(NewH(QString)));

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(updateAspectScale(int)));
}

char* toCharP(const QString& inpu)
{
    QByteArray ba = inpu.toLatin1();
    char* c_str = ba.data();
    return c_str ;
}

AspectScaler::~AspectScaler()
{
    delete ui;
}

void AspectScaler::NewW(QString str)
{
    int newValue = std::max(str.toInt(), ui->EditHeight->text().toInt());
    int newMaximum = newValue * 2;

    ui->horizontalSlider->setMaximum(newMaximum);
    ui->horizontalSlider->setValue(newValue);
}
void AspectScaler::NewH(QString str)
{
    int newValue = std::max(str.toInt(), ui->EditWidth->text().toInt());
    int newMaximum = newValue * 2 ;

    ui->horizontalSlider->setMaximum(newMaximum);
    ui->horizontalSlider->setValue(newValue);
}

void AspectScaler::updateAspectScale(int value)
{
    double newWidth, newHeight ;

    if (ui->EditHeight->text().toInt() < ui->EditWidth->text().toInt() )
    {
        newHeight =  value / ( ui->EditWidth->text().toDouble() / ui->EditHeight->text().toDouble() ) ;
        newWidth = value ;
    }else if (ui->EditHeight->text().toInt() > ui->EditWidth->text().toInt())
    {
        newWidth = value / ( ui->EditHeight->text().toDouble() / ui->EditWidth->text().toDouble() ) ;
        newHeight = value ;
    }else if (ui->EditHeight->text().toInt() == ui->EditWidth->text().toInt())
    {
        newWidth = value ;
        newHeight = value ;
    }

    ui->CalculatedHeight->setNum(newHeight);
    ui->CalculatedWidth->setNum(newWidth);

}

void AspectScaler::on_ButtonNext_clicked()
{
    // progress the slider until we find a value that generates two whole numbers
    for (int i = ui->horizontalSlider->value() ; i != ui->horizontalSlider->maximum() ; i++)
    {
        ui->horizontalSlider->setSliderPosition(i + 1);

        double height = ui->CalculatedHeight->text().toDouble();
        double width = ui->CalculatedWidth->text().toDouble();

        if ( height == static_cast<int>(height) && width == static_cast<int>(width) )
            break;
    }
}

void AspectScaler::on_ButtonPrev_clicked()
{
    // progress the slider backwards until we find a value that generates two whole numbers
    for (int i = ui->horizontalSlider->value() ; i != 0 ; i--)
    {
        ui->horizontalSlider->setSliderPosition(i - 1);

        double height = ui->CalculatedHeight->text().toDouble();
        double width = ui->CalculatedWidth->text().toDouble();

        if ( height == static_cast<int>(height) && width == static_cast<int>(width) )
            break;
    }
}
