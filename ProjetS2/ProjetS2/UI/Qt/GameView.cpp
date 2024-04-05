#include "GameView.h"
#include <QDebug>


GameView::GameView(QWidget* parent) {
	// Créer une scène
	scene = new QGraphicsScene(this);
	setScene(scene);

	// Taille de chaque cellule de la grille

	// Nombre de lignes et de colonnes dans la grille
	/*int numRows = scene->height() / cellSize;
	int numCols = scene->width() / cellSize;*/
	int numRows = 20;
	int numCols = 20;
	int cellSize = qMin(this->size().width() / numCols, this->size().height() / numRows);

	// Parcourir toutes les lignes et colonnes pour créer la grille
	for (int row = 0; row < numRows; ++row) {
		for (int col = 0; col < numCols; ++col) {
			// Calculer les coordonnées du coin supérieur gauche de la cellule
			qreal x = col * cellSize;
			qreal y = row * cellSize;

			// Ajouter un rectangle représentant une cellule de la grille
			QGraphicsRectItem* cell = scene->addRect(x, y, cellSize, cellSize);
			cell->setPen(QPen(Qt::black));  // Pas de contour pour les cellules
			cell->setBrush(Qt::red); // Pas de couleur de remplissage
			cells.append(cell);
		}
	}

	QGraphicsEllipseItem* fish = scene->addEllipse(0, 0, 50, 50);
	fish->setBrush(Qt::blue);
	fish->setPos(0, 0);
	//connect(this, &GameView::resizeEvent, this, &GameView::ResizeGrid); // Connexion de l'événement de redimensionnement
}

GameView::~GameView() {}

void GameView::resizeEvent(QResizeEvent* event) {
	ResizeGrid(event);
	QGraphicsView::resizeEvent(event);
}

// Slot pour redimensionner la grille
void GameView::ResizeGrid(QResizeEvent* event) {
	int numCols = 20;
	int numRows = 20;
	int cellSize = qMin(event->size().width() / numCols, event->size().height() / numRows);

	for (int row = 0; row < numRows; ++row) {
		for (int col = 0; col < numCols; ++col) {
			qreal x = col * cellSize;
			qreal y = row * cellSize;

			QGraphicsRectItem* cell = cells.at(row * numCols + col); // Récupérer la cellule de la liste
			cell->setRect(x, y, cellSize, cellSize);
		}
	}
}
