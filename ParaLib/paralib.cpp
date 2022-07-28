#include "paralib.h"

namespace ParaLib
{
	ParaCommon::ParaCommon(QWidget* parent) : QObject(parent)
	{
	}

	int ParaCommon::returnInt()
	{
		return 42;
	}
}


