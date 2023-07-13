//
// Created by amir on 7/13/23.
//

#ifndef GAME_TANKDIALOG_H
#define GAME_TANKDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <qlineedit.h>
#include <qspinbox.h>
#include "MainWindow.h"
struct TankInfo;

class TankDialog : public QDialog
{
Q_OBJECT

public:
	explicit TankDialog(QWidget *parent = nullptr);

	[[nodiscard]] TankInfo getTankInfo() const;

private:
	QSpinBox *movementSpeedEdit;
	QSpinBox *rotationSpeedEdit;
	QSpinBox *shootCooldownEdit;
	QSpinBox *healthEdit;
	QSpinBox *bulletPowerSpin;
	QSpinBox *bulletSpeedSpin;
	QLineEdit* name;
};

#endif //GAME_TANKDIALOG_H
