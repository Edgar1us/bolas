#include "dinformacion.h"
#include <QGridLayout>
#include <QVector>


DInformacion::DInformacion(int numBolas, int ancho, int alto, QWidget * parent) : QDialog(parent){

    QGridLayout *layout = new QGridLayout;

    etTituloNumero = new QLabel("Numero de bolas");
    etTituloTamanyo = new QLabel("Tanaño de la ventana");
    etValorNumero = new QLabel(QString::number(numBolas));
    QString cadena = QString::number(ancho) + " x " +
                     QString::number(alto);       
    etValorTamanyo = new QLabel(cadena);


    layout->addWidget(etTituloNumero,0,0);
    layout->addWidget(etValorNumero,0,1);
    layout->addWidget(etTituloTamanyo,1,0);
    layout->addWidget(etValorTamanyo,1,1);

    this->setLayout(layout);

    

}

void DInformacion::establecerTamanyo(int anchura, int altura){
        
        QString cadena = QString::number(anchura) + " x " +
                     QString::number(altura); 
        etValorTamanyo->setText(cadena);
}