#include "CosGUIRead.h"

CartCRUDRead::CartCRUDRead(Cos& cos) : cos{ cos } {
    cos.addObserver(this);
    repaint();
}

void CartCRUDRead::paintEvent(QPaintEvent* event) {

    QPainter g{ this };
    g.setPen(Qt::red);

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> x_coord(0, this->width());
    std::uniform_int_distribution<> y_coord(0, this->height());
    std::uniform_int_distribution<> width(15, RECTANGLE_MAX_DIM);
    std::uniform_int_distribution<> height(15, RECTANGLE_MAX_DIM);

    int z_coord = 1000;
    int p_coord = 150;

    for (const auto& prod : this->cos.get_all()) {
        g.drawPie(x_coord(mt), y_coord(mt), width(mt), height(mt), z_coord, p_coord);

    }
}

void CartCRUDRead::update() {
    repaint();
}