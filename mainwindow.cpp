#include "mainwindow.h"
#include "math.h"
#include "bola.h"
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <QBrush>
#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
        resize(400, 200);
        Bola::vidaInicial=100;
        temporizador = new QTimer();
        temporizador->setInterval(100);
        temporizador->setSingleShot(false);
        temporizador->start();

        connect(temporizador, SIGNAL(timeout()),
                this, SLOT(slotRepintar()));


        inicializarBolas();
        incializarMenus();
        dInformacion = NULL;

}

void MainWindow::inicializarBolas(){
        for (int i = 0; i < 20; i++){
              bolas.append(new Bola(random()%width(),
                                random()%height(),
                                ((4 + random()%50 / 50.1) - 0.5),
                                ((4 + random()%50 / 50.1) - 0.5)));
        }
        
        bolaJugador = new Bola(100,100,0,0);
        bolaJugador->color = QColor("black");
        
}

void MainWindow::incializarMenus(){
        
        QMenu * menuFichero = menuBar()->addMenu("Fichero");
        
        accionDInformacion = new QAction("Informacion basica", this);
        //accionDInformacion->setIcon(QIcon("./images/buscar.jpg"));
        //accionDInformacion->setShortcut(QKeySequence(tr("Ctrl+d")));
        accionDInformacion->setStatusTip("Obtener informacion basica");
        accionDInformacion->setToolTip("Obtener informacion basica");
        connect(accionDInformacion, SIGNAL(triggered()),
                this, SLOT(slotDInformacion()));

        menuFichero->addAction(accionDInformacion);
        
}






/* EVENTOS **********************************************************/

void MainWindow::paintEvent(QPaintEvent * evento){
        QPainter pintor(this);
        
        for (int i = 0; i < bolas.size(); i++){
                bolas.at(i)->pintar(pintor);
                //pintor.drawText(bolas.at(i)->posicionX - 10, bolas.at(i)->posicionY - 20, QString::number(bolas.at(i)->vida));

                int ancho = bolas.at(i)->diametro;
                float anchoVerde = ((float)bolas.at(i)->vida / bolas.at(i)->vidaInicial) * (float)ancho;
                float anchoRojo = (ancho - (float)anchoVerde);
                pintor.setBrush(Qt::green);
                pintor.drawRect(bolas.at(i)->posicionX, bolas.at(i)->posicionY, anchoVerde, 3);
                pintor.setBrush(Qt::red);
                pintor.drawRect(bolas.at(i)->posicionX + anchoVerde, bolas.at(i)->posicionY, anchoRojo, 3);
                
        }

        bolaJugador->pintar(pintor);
        //pintor.drawText(bolaJugador->posicionX - 10, bolaJugador->posicionY - 20, QString::number(bolaJugador->vida));

        int ancho = bolaJugador->diametro;
        float anchoVerde = ((float)bolaJugador->vida / bolaJugador->vidaInicial) * (float)ancho;
        float anchoRojo = (ancho - (float)anchoVerde);
        pintor.setBrush(Qt::green);
        pintor.drawRect(bolaJugador->posicionX, bolaJugador->posicionY, anchoVerde, 3);
        pintor.setBrush(Qt::red);
        pintor.drawRect(bolaJugador->posicionX + anchoVerde, bolaJugador->posicionY, anchoRojo, 3);
       
        
}

void MainWindow::mousePressEvent(QMouseEvent * event){
        inicialMouseClickX = event()->x();
        inicialMouseClickY = event()->y();
}

void MainWindow::mouseReleaseEvent(QMouseEvent * event){
        
}

void MainWindow::keyPressEvent(QKeyEvent * evento){

        if ( evento->key() == Qt::Key_Up){
                bolaJugador->velY = bolaJugador->velY - 0.05;
        }
        if ( evento->key() == Qt::Key_Down){
                bolaJugador->velY = bolaJugador->velY + 0.05;
        }
        if ( evento->key() == Qt::Key_Left){
                bolaJugador->velX = bolaJugador->velX - 0.05;
        }
        if ( evento->key() == Qt::Key_Right){
                bolaJugador->velX = bolaJugador->velX + 0.05;
        }
        

}

/* SLOTS **********************************************************/

void MainWindow::slotRepintar(){
        for (int i = 0; i < bolas.size(); i++){
                bolas.at(i)->moverBola(width(), height());         
        }
        
        for (int i = 0; i < bolas.size(); i++){
                for (int j = 0; j < bolas.size(); j++){
                       if (bolas.at(i) != bolas.at(j)){
                               if(bolas.at(i)->choca(bolas.at(j))){
                                       bolas.at(i)->vida--;
                                       bolas.at(j)->vida--;
                               }
                       }
                }
                
        }

        for (int i = 0; i < bolas.size(); i++){
                if (bolaJugador->choca(bolas.at(i)))
                {
                        bolaJugador->vida--;
                        bolas.at(i)->vida--;
                }
        }        
        
        bolaJugador->moverBola(width(), height());

        update();
}

void MainWindow::slotDInformacion(){
        if (dInformacion == NULL){
                dInformacion = new DInformacion(
                        bolas.size(),
                        0/*width()*/,
                        0/*height()*/

                );
        }
        
        dInformacion->establecerTamanyo(width(), height());

        dInformacion->show();
}

/*****************************************************************************************************************/
