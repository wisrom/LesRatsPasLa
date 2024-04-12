#include "GameView.h"
#include <QDebug>

GameView::GameView(FishingRun* sFishingRun, QWidget* parent) : fishingRun(sFishingRun) {

	// Créer une scène
	scene = new QGraphicsScene(this);
	setScene(scene);

	cellSize = qMin(this->size().width() / numCols, this->size().height() / numRows);

	// Parcourir toutes les lignes et colonnes pour créer la grille
	for (int row = 0; row < numRows; ++row) {
		for (int col = 0; col < numCols; ++col) {
			// Calculer les coordonnées du coin supérieur gauche de la cellule
			qreal x = col * cellSize;
			qreal y = row * cellSize;

			QPixmap waterPixmap(waterImgPath);
			QGraphicsPixmapItem* cell = new QGraphicsPixmapItem;
			cell->setPixmap(waterPixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio));
			cell->setPos(x, y);
			scene->addItem(cell);
			cells.append(cell);
		}
	}

	QPixmap playerImg(playerImgPath);
	fish = scene->addPixmap(playerImg);
	scaleImg(playerImg, fish);
	fish->setPos(0, 0);

	Position fishPosition;
	for (Fish fish : fishingRun->getCurrentSession()->fishs)
	{
		fishPosition = fish.getPosition();

		QPixmap fishPixmap(bubbleImgPath);
		QGraphicsPixmapItem* fishImg = new QGraphicsPixmapItem;
		fishImg->setPixmap(fishPixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio));
		fishImg->setPos(fishPosition.x * cellSize, fishPosition.y * cellSize);
		scaleImg(fishPixmap, fishImg);
		scene->addItem(fishImg);
		fishsToGet.append(fishImg);
	}

	
}

void GameView::removeFishToGet()
{
	std::vector<Fish> capturedFishsLocal = fishingRun->getCurrentSession()->capturedFishs;
	std::vector<Fish> fishsLocal = fishingRun->getCurrentSession()->fishs;

	for (int i = 0; i < fishsToGet.count(); i++) {
		for (int ii = 0; ii < capturedFishsLocal.size(); ii++)
		{
			if (fishsToGet[i]->pos().x() / cellSize == capturedFishsLocal[ii].getPosition().x && fishsToGet[i]->pos().y() / cellSize == capturedFishsLocal[ii].getPosition().y) {
				scene->removeItem(fishsToGet[i]);
				fishsToGet.removeOne(fishsToGet[i]);
			}
		}
	}
}

void GameView::changeImageFish() {
	if (fishingRun->getCurrentSession()->getNearFish().getIsCapturing()) {
		QPixmap fishPixmap(fishImgPath);
		Position pos = fishingRun->getCurrentSession()->player.getPosition();
		for (int i = 0; i < fishsToGet.size(); i++)
		{
			if (fishsToGet[i]->pos().x() / cellSize == pos.x && fishsToGet[i]->pos().y() / cellSize == pos.y) {
				fishsToGet[i]->setPixmap(fishPixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio));
				isDifferent.x = pos.x;
				isDifferent.y = pos.y;
			}
		}
	}
	else {
		QPixmap fishPixmap(bubbleImgPath);
		for (int i = 0; i < fishsToGet.size(); i++)
		{
			if (fishsToGet[i]->pos().x() / cellSize == isDifferent.x && fishsToGet[i]->pos().y() / cellSize == isDifferent.y) {
				fishsToGet[i]->setPixmap(fishPixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio));
				std::vector<Fish> lstFishs = fishingRun->getCurrentSession()->fishs;
				for (int i = 0; i < lstFishs.size(); i++)
				{
					if (lstFishs[i].getPosition().x == isDifferent.x && lstFishs[i].getPosition().y == isDifferent.y) {
						fishingRun->getCurrentSession()->fishs[i].setIsCapturing(false);
					}
				}
			}
		}

	}
}

void GameView::resizeLbl(QLabel* lbl)
{
	lbls.append(lbl);
}

void GameView::scaleImg(QPixmap imagePath, QGraphicsPixmapItem* pixmapItem) {
	pixmapItem->setPixmap(imagePath.scaled(cellSize, cellSize, Qt::KeepAspectRatio));
}

GameView::~GameView() {}

void GameView::resizeEvent(QResizeEvent* event) {
	ResizeGrid(event);
	QPixmap playerImg(playerImgPath);
	scaleImg(playerImg, fish);
	if (lbls.size() != 0) {
		for (QLabel* lbl : lbls) {
			int fontSize = qMin(event->size().width(), event->size().height()) / 10; // Taille de police basée sur la taille de la fenêtre
			lbl->setStyleSheet(QString("QLabel { font-size: %1px; }").arg(fontSize)); // Mettre à jour la taille de la police
		}
	}

	// Resize fish to get
	std::vector<Fish> lstFish = fishingRun->getCurrentSession()->fishs;
	Position fishPosition;
	QPixmap fishImg(bubbleImgPath);
	for (int i = 0; i < fishsToGet.count(); i++)
	{
		fishPosition = lstFish[i].getPosition();
		fishsToGet[i]->setPos(fishPosition.x * cellSize, fishPosition.y * cellSize);
		scaleImg(fishImg, fishsToGet[i]);
	}
}

void GameView::refreshFishDisplay()
{
	Position fishPosition;

	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < fishsToGet.count(); i++)
		{
			scene->removeItem(fishsToGet[i]);
			fishsToGet.removeOne(fishsToGet[i]);
		}
	}
	
	for (Fish fish : fishingRun->getCurrentSession()->fishs)
	{
		fishPosition = fish.getPosition();

		QPixmap fishPixmap(bubbleImgPath);
		QGraphicsPixmapItem* fishImg = new QGraphicsPixmapItem;
		fishImg->setPixmap(fishPixmap.scaled(cellSize, cellSize, Qt::KeepAspectRatio));
		fishImg->setPos(fishPosition.x * cellSize, fishPosition.y * cellSize);
		scaleImg(fishPixmap, fishImg);
		scene->addItem(fishImg);
		fishsToGet.append(fishImg);
	}
}

void GameView::ResizeGrid(QResizeEvent* event) {
	cellSize = qMin(event->size().width() / numCols, event->size().height() / numRows);
	QPixmap waterImg(waterImgPath);

	for (int row = 0; row < numRows; ++row) {
		for (int col = 0; col < numCols; ++col) {
			qreal x = col * cellSize;
			qreal y = row * cellSize;

			QGraphicsPixmapItem* cell = cells.at(row * numCols + col);
			cell->setPos(x, y);
			cell->setPixmap(waterImg.scaled(cellSize, cellSize, Qt::KeepAspectRatio));
		}
	}
}

void GameView::refreshMove(FishingRun* fishingRun)
{
	Position playerPosition = fishingRun->getCurrentSession()->player.getPosition();
	if (playerPosition.x > numCols - 1) {
		Position position = { numCols - 1, playerPosition.y };
		fishingRun->getCurrentSession()->player.setPosition(position);

	}
	if (playerPosition.y > numRows - 1) {
		Position position = { playerPosition.x, numRows - 1 };
		fishingRun->getCurrentSession()->player.setPosition(position);

	}
	if (playerPosition.y < 0) {
		Position position = { playerPosition.x, 0 };
		fishingRun->getCurrentSession()->player.setPosition(position);
	}
	if (playerPosition.x < 0) {
		Position position = { 0, playerPosition.y };
		fishingRun->getCurrentSession()->player.setPosition(position);
	}
	Position playerPosition2 = fishingRun->getCurrentSession()->player.getPosition();

	fish->setPos(playerPosition2.x * cellSize, playerPosition2.y * cellSize);
}
