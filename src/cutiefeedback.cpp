#include "cutiefeedback.h"
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>

Feedback::Feedback(QObject *parent)
	: QObject(parent)
{
	QDBusConnection::sessionBus().connect(
		"org.sigxcpu.Feedback", "/org/sigxcpu/Feedback", "org.sigxcpu.Feedback", "FeedbackEnded", this,
		SLOT(onFeedbackEnded(uint, uint)));
	QDBusConnection::sessionBus().connect(
		"org.sigxcpu.Feedback", "/org/sigxcpu/Feedback", "org.freedesktop.DBus.Properties", "PropertiesChanged", this,
		SLOT(onPropertiesChanged(QString, QVariantMap, QStringList)));
}

Feedback::~Feedback()
{
}

uint Feedback::trigger(QString appId, QString event,
				QVariantMap hints, int timeout)
{
	QDBusReply<uint> idReply =
		QDBusInterface("org.sigxcpu.Feedback",
			       "/org/sigxcpu/Feedback",
			       "org.sigxcpu.Feedback",
			       QDBusConnection::sessionBus())
			.call("TriggerFeedback", appId, event, hints, timeout);
	return idReply.isValid() ? idReply.value() : 0;
}

void Feedback::end(uint id)
{
	QDBusInterface("org.sigxcpu.Feedback",
				"/org/sigxcpu/Feedback",
				"org.sigxcpu.Feedback",
				QDBusConnection::sessionBus())
		.call("EndFeedback", id);
}

QString Feedback::profile()
{
	QDBusReply<QString> profileReply =
		QDBusInterface("org.sigxcpu.Feedback",
			       "/org/sigxcpu/Feedback",
			       "org.freedesktop.DBus.Properties",
			       QDBusConnection::sessionBus())
			.call("Get", "org.sigxcpu.Feedback", "Profile");
	return profileReply.isValid() ? profileReply.value() : QString();
}

void Feedback::setProfile(QString profile)
{
	QDBusInterface("org.sigxcpu.Feedback",
				"/org/sigxcpu/Feedback",
				"org.freedesktop.DBus.Properties",
				QDBusConnection::sessionBus())
		.call("Set", "org.sigxcpu.Feedback", "Profile", profile);
}

void Feedback::onFeedbackEnded(uint id, uint reason)
{
	emit ended(id, reason);
}

void Feedback::onPropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated)
{
	Q_UNUSED(invalidated);
	if (iface == "org.sigxcpu.Feedback") {
		if (updated.contains("Profile")) {
			emit profileChanged(qdbus_cast<QString>(updated.value("Profile")));
		}
	};
}

QObject *Feedback::provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
	Q_UNUSED(scriptEngine);
	return new Feedback(engine);
}
