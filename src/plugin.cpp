#include "plugin.h"

void CutieFeedbackPlugin::registerTypes(const char *uri)
{
	qmlRegisterSingletonType<Feedback>(uri, 1, 0, "CutieFeedback",
					   &Feedback::provider);
}
