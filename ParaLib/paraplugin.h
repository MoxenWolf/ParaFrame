#pragma once

#include <QObject>

class ParaPlugin  : public QObject
{
	Q_OBJECT

public:
	ParaPlugin(QObject *parent);
	~ParaPlugin();
};
