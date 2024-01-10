#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QVector>
#include <QRandomGenerator>
#include <cmath>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QInputDialog>
#include <QMessageBox>



class GraphView : public QGraphicsView {
public:
    GraphView(QWidget *parent = nullptr) : QGraphicsView(parent) {
        scene = new QGraphicsScene(this);
        setScene(scene);
        setRenderHint(QPainter::Antialiasing, true);
    }

    void drawGraph(int numNodes, double density) {
        // Clear the previous scene
        scene->clear();

        QVector<QPointF> nodePositions = calculateCircularNodePositions(numNodes);

        for (int i = 0; i < numNodes; ++i) {
            QGraphicsEllipseItem *node = new QGraphicsEllipseItem(-nodeRadius, -nodeRadius, 2 * nodeRadius, 2 * nodeRadius);
            node->setPos(nodePositions[i]);

            QBrush brush(Qt::blue);
            QPen pen(Qt::black);
            node->setBrush(brush);
            node->setPen(pen);

            scene->addItem(node);


            QGraphicsTextItem *label = new QGraphicsTextItem(QString::number(i + 1));
            label->setPos(nodePositions[i].x() - label->boundingRect().width() / 2,
                          nodePositions[i].y() - label->boundingRect().height() / 2);


            QFont font = label->font();
            font.setBold(true);
            label->setFont(font);


            label->setDefaultTextColor(Qt::white);

            scene->addItem(label);
        }

        // Draw edges based on density
        for (int i = 0; i < numNodes; ++i) {
            for (int j = i + 1; j < numNodes; ++j) {
                if (QRandomGenerator::global()->generateDouble() < density) {
                    QGraphicsLineItem *edge = new QGraphicsLineItem(nodePositions[i].x(), nodePositions[i].y(),
                                                                    nodePositions[j].x(), nodePositions[j].y());

                    // Set color and appearance
                    QPen pen(Qt::gray);
                    edge->setPen(pen);

                    scene->addItem(edge);
                }
            }
        }
    }
    void drawGraphWithoutEdges(int numNodes);

private:
    QVector<QPointF> calculateCircularNodePositions(int numNodes) {
        QVector<QPointF> positions;

        double angleIncrement = 2 * M_PI / numNodes;

        for (int i = 0; i < numNodes; ++i) {
            double x = circleRadius * std::cos(i * angleIncrement);
            double y = circleRadius * std::sin(i * angleIncrement);
            positions.append(QPointF(x, y));
        }

        return positions;
    }

    QGraphicsScene *scene;
    const double nodeRadius = 15.0;
    const double circleRadius = 150.0;  // Adjust the circle radius as needed
};

void GraphView::drawGraphWithoutEdges(int numNodes) {
    // Clear the previous scene
    scene->clear();

    QVector<QPointF> nodePositions = calculateCircularNodePositions(numNodes);

    // Draw nodes with numeric labels
    for (int i = 0; i < numNodes; ++i) {
        QGraphicsEllipseItem *node = new QGraphicsEllipseItem(-nodeRadius, -nodeRadius, 2 * nodeRadius, 2 * nodeRadius);
        node->setPos(nodePositions[i]);

        // Set color and appearance
        QBrush brush(Qt::blue);
        QPen pen(Qt::black);
        node->setBrush(brush);
        node->setPen(pen);

        scene->addItem(node);

        // Add numeric label inside the node
        QGraphicsTextItem *label = new QGraphicsTextItem(QString::number(i + 1));
        label->setPos(nodePositions[i].x() - label->boundingRect().width() / 2,
                      nodePositions[i].y() - label->boundingRect().height() / 2);

        // Set label font to bold
        QFont font = label->font();
        font.setBold(true);
        label->setFont(font);

        // Set label color
        label->setDefaultTextColor(Qt::white);

        scene->addItem(label);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setStyleSheet("QGroupBox { border: 2px solid #777; border-radius: 5px; margin-top: 1ex;background-color: lightblue; }");

    graphView = new GraphView();
    lineEditNumNodes = findChild<QLineEdit *>("lineEdit");
    lineEditDensity = findChild<QLineEdit *>("lineEdit_2");
}

MainWindow::~MainWindow()
{
    delete ui;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}



void MainWindow::on_pushButton_clicked()
{
    bool ok;
    int numNodes = lineEditNumNodes->text().toInt(&ok);
    double density = lineEditDensity->text().toDouble(&ok);

    if (!ok) {
        // Conversion failed, handle the error (e.g., show a message box)
        QMessageBox::warning(this, tr("Input Error"), tr("Invalid input for number of nodes or density."));
        return;
    }
    graphView->drawGraph(numNodes, density);
    graphView->showMaximized();
}



void MainWindow::on_pushButton_2_clicked()
{
    bool ok;
    int numNodes = lineEditNumNodes->text().toInt(&ok);
    graphView->drawGraphWithoutEdges(numNodes);
    graphView->showMaximized();
}

