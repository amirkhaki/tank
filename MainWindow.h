//
// Created by amir on 7/13/23.
//

#ifndef GAME_MAINWINDOW_H
#define GAME_MAINWINDOW_H

// check if win32 or win64
#if defined(_WIN32) || defined(_WIN64)
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

#include <QMainWindow>
#include <QList>
#include <QVBoxLayout>
#include <QLineEdit>
#include <qdialog.h>
#include <QListWidget>
#include "TankDialog.h"
#include "Player.h"


class MainWindow : public QMainWindow {
Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);

private slots:

	void showPlayerInputs();

	void startGame(const QString &selectedMap, const std::vector<int> &selectedTanks, QList<Player::Controls> controls);

	void showSettings();

	void createTank();

private:
	void createMainMenu();

	QList<QString> playerNames;
	QList<Player *> players; // Store the list of players
	QList<TankInfo> tanks;
	QList<QLineEdit *> playerInputs;
	const int numPlayers = 2;

	QString mapsDirectoryPath;
	QList<QListWidget *> playerKeyListWidgets;

};


#endif //GAME_MAINWINDOW_H
