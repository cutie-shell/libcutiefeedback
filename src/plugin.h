#pragma once
#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>

#include "cutiefeedback.h"

class CutieFeedbackPlugin : public QQmlExtensionPlugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid FILE
			  "cutiefeedback.json")
    public:
	explicit CutieFeedbackPlugin()
	{
	}

	void registerTypes(const char *uri) override;
};