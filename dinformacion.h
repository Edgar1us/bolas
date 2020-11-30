#ifndef _DINFORMACION_H
#define _DINFORMACION_H

#include <QDialog>
#include <QLabel>
#include <QVector>


class DInformacion : public QDialog{
    public:
        DInformacion(int numBolas, int ancho, int alto, QWidget * parent = nullptr);

        QLabel * etTituloNumero;
        QLabel * etTituloTamanyo;
        QLabel * etValorNumero;
        QLabel * etValorTamanyo;


        void establecerTamanyo(int anchura, int altura); 

};

#endif