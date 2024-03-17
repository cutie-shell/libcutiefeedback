#pragma once
#include <QtQuick>

class Feedback : public QObject {
	Q_OBJECT
	Q_PROPERTY(QString profile READ profile WRITE setProfile NOTIFY profileChanged)
    public:
	Feedback(QObject *parent = 0);

	~Feedback();

	Q_INVOKABLE uint trigger(QString appId, QString event,
				QVariantMap hints, int timeout);
	Q_INVOKABLE void end(uint id);

	QString profile();
	void setProfile(QString profile);

	static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);

	signals:
	void ended(uint id, uint reason);
	void profileChanged(QString profile);

	private slots:
	void onFeedbackEnded(uint id, uint reason);
	void onPropertiesChanged(QString iface, QMap<QString, QVariant> updated,
				 QStringList invalidated);
};
