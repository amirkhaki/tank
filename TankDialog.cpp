//
// Created by amir on 7/13/23.
//

#include "TankDialog.h"
#include <QFormLayout>
#include <QPushButton>
#include <qspinbox.h>

TankDialog::TankDialog(QWidget *parent)
		: QDialog(parent) {
	setWindowTitle("Create Tank");

	movementSpeedEdit = new QSpinBox;
	rotationSpeedEdit = new QSpinBox;
	shootCooldownEdit = new QSpinBox;
	healthEdit = new QSpinBox;
	bulletPowerSpin = new QSpinBox;
	bulletSpeedSpin = new QSpinBox;
	name = new QLineEdit;


	bulletPowerSpin->setMinimum(1);
	bulletPowerSpin->setMaximum(5);
	bulletSpeedSpin->setMinimum(1);
	bulletSpeedSpin->setMaximum(3);
	movementSpeedEdit->setMinimum(1);
	movementSpeedEdit->setMaximum(5);
	rotationSpeedEdit->setMaximum(3);
	rotationSpeedEdit->setMinimum(1);
	healthEdit->setMinimum(100);
	healthEdit->setMaximum(150);

	auto *layout = new QFormLayout;
	layout->addRow("Name:", name);
	layout->addRow("Movement Speed:", movementSpeedEdit);
	layout->addRow("Rotation Speed:", rotationSpeedEdit);
	layout->addRow("Shoot Cooldown:", shootCooldownEdit);
	layout->addRow("Health:", healthEdit);
	layout->addRow("Bullet Power:", bulletPowerSpin);
	layout->addRow("Bullet Speed:", bulletSpeedSpin);

	auto *cancelButton = new QPushButton("Cancel");
	auto *okButton = new QPushButton("OK");

	connect(cancelButton, &QPushButton::clicked, this, &TankDialog::reject);
	connect(okButton, &QPushButton::clicked, this, &TankDialog::accept);

	layout->addWidget(cancelButton);
	layout->addWidget(okButton);

	setLayout(layout);
}

TankInfo TankDialog::getTankInfo() const {
	TankInfo tankInfo;
	tankInfo.movementSpeed = movementSpeedEdit->text().toDouble();
	tankInfo.rotationSpeed = rotationSpeedEdit->text().toDouble();
	tankInfo.shootCooldown = shootCooldownEdit->text().toLongLong();
	tankInfo.health = healthEdit->text().toLongLong();
	tankInfo.bulletPower = bulletPowerSpin->value();
	tankInfo.bulletSpeed = bulletSpeedSpin->value();
	tankInfo.name = name->text();
	return tankInfo;
}
