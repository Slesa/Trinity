#ifndef MAC_KEYTRIGGER_H
#define MAC_KEYTRIGGER_H

#include "globalshortcutmanager.h"

// TODO:
//  - don't invoke hotkey if there is a modal dialog?
//  - do multi-mapping, like the x11 version

class MacKeyTrigger
{
public:
	virtual ~MacKeyTrigger() {}
	virtual void activate() = 0;
	virtual bool isAccepted(int id) const = 0;
};

#endif
