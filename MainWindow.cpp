//
// Created by amir on 7/13/23.
//

#include "MainWindow.h"
#include "Scene.h"
#include "MapCreator.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QSlider>
#include <QLabel>
#include <qapplication.h>
#include <qdialog.h>
#include <qevent.h>
#include <qnamespace.h>
#include <random>
#include <QDir>
#include <QListWidget>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
		: QMainWindow(parent) {
	createMainMenu();
}

void MainWindow::showPlayerInputs() {
	if (tanks.empty()) {
		QMessageBox::critical(this, "Error", "No tanks available.");
		return;
	}
	QDir mapsDirectory(mapsDirectoryPath); // Replace with the actual directory path
	mapsDirectory.setFilter(QDir::Files);
	mapsDirectory.setNameFilters(QStringList() << "*.map");
	QStringList mapFiles = mapsDirectory.entryList();
	if (mapFiles.empty()) {
		QMessageBox::critical(this, "Error", "No maps available.");
		return;
	}
	auto *playerInputDialog = new QDialog(this);
	playerInputDialog->setWindowTitle("Player Inputs");

	auto *layout = new QVBoxLayout(playerInputDialog);

	QList<QComboBox *> playerTankComboBoxes;
	playerInputs.clear();
	playerKeyListWidgets.clear();
	for (int i = 0; i < numPlayers; ++i) {
		auto *nameLabel = new QLabel("Player " + QString::number(i + 1) + " Name:");
		auto *nameLineEdit = new QLineEdit;
		playerInputs.append(nameLineEdit);

		auto *tankLabel = new QLabel("Player " + QString::number(i + 1) + " Tank:");
		auto *tankComboBox = new QComboBox;
		for (const auto &tank: tanks) {
			tankComboBox->addItem(tank.name);
		}
		playerTankComboBoxes.append(tankComboBox);

		auto *controlsLabel = new QLabel("Player " + QString::number(i + 1) + " Controls:");
		auto *keyListWidget = new QListWidget;
		auto *upKeyItem = new QListWidgetItem("Up: ");
		auto *downKeyItem = new QListWidgetItem("Down: ");
		auto *leftKeyItem = new QListWidgetItem("Left: ");
		auto *rightKeyItem = new QListWidgetItem("Right: ");
		auto *shootKeyItem = new QListWidgetItem("Shoot: ");
		keyListWidget->addItem(upKeyItem);
		keyListWidget->addItem(downKeyItem);
		keyListWidget->addItem(leftKeyItem);
		keyListWidget->addItem(rightKeyItem);
		keyListWidget->addItem(shootKeyItem);
		playerKeyListWidgets.append(keyListWidget);

		layout->addWidget(nameLabel);
		layout->addWidget(nameLineEdit);
		layout->addWidget(tankLabel);
		layout->addWidget(tankComboBox);
		layout->addWidget(controlsLabel);
		layout->addWidget(keyListWidget);
	}

	auto *mapLabel = new QLabel("Select Map:");
	auto *mapComboBox = new QComboBox;

	auto *playButton = new QPushButton("Play");

	// Populate the mapComboBox with the available map files
	mapComboBox->addItems(mapFiles);

	layout->addWidget(mapLabel);
	layout->addWidget(mapComboBox);
	layout->addWidget(playButton);

	connect(playButton, &QPushButton::clicked, [=]() {
		playerNames.clear();
		std::vector<int> selectedTanks;
		QList<Player::Controls> playerControls;
		for (int i = 0; i < numPlayers; ++i) {
			playerNames << playerInputs[i]->text();
			selectedTanks.push_back(playerTankComboBoxes[i]->currentIndex());
			Player::Controls controls = {};
			auto *keyListWidget = playerKeyListWidgets[i];
			controls.up = keyListWidget->item(0)->data(Qt::UserRole).toInt();
			controls.down = keyListWidget->item(1)->data(Qt::UserRole).toInt();
			controls.left = keyListWidget->item(2)->data(Qt::UserRole).toInt();
			controls.right = keyListWidget->item(3)->data(Qt::UserRole).toInt();
			controls.shoot = keyListWidget->item(4)->data(Qt::UserRole).toInt();
			playerControls.append(controls);
		}
		QString selectedMap = mapComboBox->currentText();

		playerControls.clear();
		playerControls.append({Qt::Key_W, Qt::Key_S, Qt::Key_A, Qt::Key_D, Qt::Key_Space});
		playerControls.append({Qt::Key_Up, Qt::Key_Down, Qt::Key_Left, Qt::Key_Right, Qt::Key_K});

		startGame(selectedMap, selectedTanks, playerControls); // Call the startGame function

		playerInputDialog->accept(); // Close the dialog after starting the game
	});
	class KeyCaptureFilter : public QObject {
	public:
		explicit KeyCaptureFilter(QListWidgetItem *item) : item(item) {}

	protected:
		bool eventFilter(QObject *obj, QEvent *event) override {
			if (event->type() == QEvent::KeyPress && typeid(*obj) == typeid(*item)) {
				auto *keyEvent = dynamic_cast<QKeyEvent *>(event);
				auto key = static_cast<Qt::Key>(keyEvent->key());
				item->setData(Qt::UserRole, QVariant::fromValue(key));
				item->setText(item->text() + QKeySequence(key).toString());
				return true;
			}

			return QObject::eventFilter(obj, event);
		}

	private:
		QListWidgetItem *item;
	};

	// Apply event filter to the key list widgets
	for (QListWidget *keyListWidget: playerKeyListWidgets) {
		for (int i = 0; i < keyListWidget->count(); ++i) {
			QListWidgetItem *item = keyListWidget->item(i);
			item->setFlags(item->flags() | Qt::ItemIsEditable);
			item->setData(Qt::UserRole, QVariant::fromValue(Qt::Key_unknown) );

			auto *filter = new KeyCaptureFilter(item);
			keyListWidget->installEventFilter(filter);
		}
	}
	playerInputDialog->exec();
}

static inline void rtrim(std::string &s, unsigned char c) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [c](unsigned char ch) {
		return ch != 47;
	}).base(), s.end());
}

void MainWindow::startGame(const QString &selectedMap, const std::vector<int> &selectedTanks,
                           QList<Player::Controls> playerControls) {
	auto *scene = new Scene();
	auto path = mapsDirectoryPath.toStdString();
	rtrim(path, PATH_SEPARATOR);

	path += PATH_SEPARATOR;
	path += selectedMap.toStdString();
	MapCreator map(path, scene, 0, 53);
	map.create();
	std::vector<std::pair<int, int>> positions;
	auto emptyPositions = map.getEmptyIndexes();
	if (emptyPositions.size() < numPlayers) {
		QMessageBox::critical(this, "Error", "Not enough empty positions in the map.");
		return;
	}
	std::sample(emptyPositions.begin(), emptyPositions.end(), std::back_inserter(positions), numPlayers,
	            std::mt19937{std::random_device{}()});
	for (int i = 0; i < numPlayers; ++i) {
		auto *player = new Player(playerNames[i], tanks[selectedTanks[i]], playerControls[i]);
		player->setPos(positions[i].second * OBJECT_PIXEL_WIDTH, positions[i].first * OBJECT_PIXEL_HEIGHT);
		scene->addItem(player);
		scene->addPlayer(player);
	}
	auto *view = new QGraphicsView(scene);
	view->setFixedSize(map.getMapSize().first, map.getMapSize().second);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setCentralWidget(view);


	for (const auto &playerName: playerNames) {
		for (auto &player: players) {
			if (player->name == playerName) {
				player->winCount++;
				break;
			}
		}
	}
}

void MainWindow::showSettings() {
	auto settingsDialog = new QDialog(this);
	settingsDialog->setWindowTitle("Settings");

	auto *layout = new QVBoxLayout(settingsDialog);

	auto *frameRateLabel = new QLabel("Frame Rate:");
	auto *frameRateSlider = new QSlider(Qt::Horizontal);
	frameRateSlider->setRange(30, 120);
	frameRateSlider->setTickInterval(10);
	frameRateSlider->setSingleStep(10);

	auto *directoryLabel = new QLabel("Maps Directory:");
	auto *directoryLineEdit = new QLineEdit;

	auto *applyButton = new QPushButton("Apply");
	layout->addWidget(frameRateLabel);
	layout->addWidget(frameRateSlider);
	layout->addWidget(directoryLabel);
	layout->addWidget(directoryLineEdit);
	layout->addWidget(applyButton);

	connect(frameRateSlider, &QSlider::valueChanged, frameRateLabel, [frameRateLabel](int value) {
		frameRateLabel->setNum(value);
	});

	connect(applyButton, &QPushButton::clicked, [=]() {
		// Retrieve the directory path from the QLineEdit
		mapsDirectoryPath = directoryLineEdit->text();

		// Use the directoryPath as needed in your application
		// ...

		settingsDialog->accept(); // Close the dialog after applying the settings
	});
	settingsDialog->exec();
}


void MainWindow::createTank() {
	TankDialog dialog(this);
	if (dialog.exec() == QDialog::Accepted) {
		TankInfo tankInfo = dialog.getTankInfo();
		tanks.append(tankInfo);
	}
}

void MainWindow::createMainMenu() {
	auto *playButton = new QPushButton("Play", this);
	auto *settingsButton = new QPushButton("Settings", this);
	auto *createTankButton = new QPushButton("Create Tank", this);
	auto *exitButton = new QPushButton("Exit", this);

	connect(playButton, &QPushButton::clicked, this, &MainWindow::showPlayerInputs);
	connect(settingsButton, &QPushButton::clicked, this, &MainWindow::showSettings);
	connect(createTankButton, &QPushButton::clicked, this, &MainWindow::createTank);
	connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);

	auto *layout = new QVBoxLayout;
	layout->addWidget(playButton);
	layout->addWidget(settingsButton);
	layout->addWidget(createTankButton);
	layout->addWidget(exitButton);

	auto *centralWidget = new QWidget(this);
	centralWidget->setLayout(layout);
	setCentralWidget(centralWidget);

}

