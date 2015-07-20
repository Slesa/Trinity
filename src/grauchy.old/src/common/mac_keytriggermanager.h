#ifndef MAC_KEYTRIGGERMANAGER_H
#define MAC_KEYTRIGGERMANAGER_H

#include <QObject>
#include <Carbon/Carbon.h>

class MacKeyTrigger;

class MacKeyTriggerManager : public QObject
{
public:
    static MacKeyTriggerManager* instance();

    void addTrigger(MacKeyTrigger* trigger);
    void removeTrigger(MacKeyTrigger* trigger);

private:
    MacKeyTriggerManager();

    static pascal OSStatus hotKeyHandler(EventHandlerCallRef /*nextHandler*/, EventRef theEvent, void* userData);

    void activated(int id);

    static MacKeyTriggerManager* _instance;
    QList<MacKeyTrigger*> _triggers;

	typedef struct
	{
		short kchrID;
		Str255 KCHRname;
		short transtable[256];
	} Ascii2KeyCodeTable;

	enum {
		kTableCountOffset = 256 + 2,
		kFirstTableOffset = 256 + 4,
		kTableSize        = 128
	};

    static EventHandlerUPP _hot_key_function;
    static Ascii2KeyCodeTable _key_codes;

private:
    static OSStatus initAscii2KeyCodeTable(Ascii2KeyCodeTable* ttable);
    static OSStatus validateAscii2KeyCodeTable(Ascii2KeyCodeTable* ttable, Boolean* wasChanged);
    static short asciiToKeyCode(Ascii2KeyCodeTable* ttable, short asciiCode);

//	static char keyCodeToAscii(short virtualKeyCode)

private:
	struct Qt_Mac_Keymap
	{
		int qt_key;
		int mac_key;
	};

	static Qt_Mac_Keymap qt_keymap[];

public:
    static bool convertKeySequence(const QKeySequence& ks, quint32* _key, quint32* _mod);
};

#endif // MAC_KEYTRIGGER_H
