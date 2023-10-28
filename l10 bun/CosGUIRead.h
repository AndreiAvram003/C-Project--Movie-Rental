#pragma once
#include "observer.h"
#include "service.h"
#include <qwidget.h>
#include <qpainter.h>
#include <random>
#include <cmath>

#define RECTANGLE_MAX_DIM 100

class CartCRUDRead : public QWidget, public Observer {

private:
	Cos& cos;

public:
	CartCRUDRead(Cos& cos);

	void update() override;

	void paintEvent(QPaintEvent* event) override;

	~CartCRUDRead() {
		this->cos.removeObserver(this);
	}
};