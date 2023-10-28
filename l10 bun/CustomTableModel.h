#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Film.h"
using namespace std;

class CustomTableModel : public QAbstractTableModel {
private:
	vector <Film> product_list;

public:

	CustomTableModel(const vector<Film>& product_list) : product_list{ product_list } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return int(product_list.size());
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 5;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	void setProduct(const vector<Film>& new_list) {

		product_list = new_list;
		emit layoutChanged();
	}
};