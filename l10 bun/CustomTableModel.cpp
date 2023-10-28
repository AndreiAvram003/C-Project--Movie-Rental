#include "CustomTableModel.h"

QVariant CustomTableModel::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int col = index.column();

	if (role == Qt::DisplayRole) {
		if (col == 0)
			return QString::fromStdString(to_string(product_list[row].get_id()));
		else if (col == 1)
			return QString::fromStdString(product_list[row].get_titlu());
		else if (col == 2)
			return QString::fromStdString(product_list[row].get_gen());
		else if (col == 3)
			return QString::fromStdString(product_list[row].get_actor());
		else if(col == 4)
			return QString::fromStdString(to_string(product_list[row].get_an()));

	}
	return QVariant();
}

QVariant CustomTableModel::headerData(int section, Qt::Orientation orientation, int role) const {

	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		switch (section) {
		case 0:
			return QString("ID");
		case 1:
			return QString("Titlu");
		case 2:
			return QString("Gen");
		case 3:
			return QString("Actor");
		case 4:
			return QString("An");
		}
	}

	return QVariant();
}