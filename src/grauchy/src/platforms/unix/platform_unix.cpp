#include "platform_unix.h"
#include <globalshortcutmanager.h>
#include <QDebug>

PlatformUnix::PlatformUnix(int& argc, char** argv) 
    : PlatformBase(argc, argv)
{

} 

bool PlatformUnix::setHotkey(const QKeySequence& key, QObject* receiver, const char* slot)
{
    GlobalShortcutManager::disconnect(_currentHotkey, receiver, slot);
    GlobalShortcutManager::connect(key, receiver, slot);
    _currentHotkey = key;
    qDebug() << key << GlobalShortcutManager::isConnected(key);
    return GlobalShortcutManager::isConnected(key);
}

#if 0
#include <QtGui>
#include <QApplication>
#include <X11/Xlib.h>
#include <QFileIconProvider>





PlatformUnix::PlatformUnix(int& argc, char** argv) :
        
{
    /*
        instance = new LimitSingleInstance(TEXT("Local\\{ASDSAD0-DCC6-49b5-9C61-ASDSADIIIJJL}"));

        // Create local and global application mutexes so that installer knows when
        // Launchy is running
        localMutex = CreateMutex(NULL,0,_T("LaunchyMutex"));
        globalMutex = CreateMutex(NULL,0,_T("Global\\LaunchyMutex"));
        */
    icons = new UnixIconProvider();

//    init(argc,argv);
//        alpha.reset();
  //      icons->reset();
}


/*
shared_ptr<QApplication> PlatformUnix::init(int & argc, char** argv)
{        
    //    QApplication * app = new QApplication(*argc, argv);
    shared_ptr<QApplication> app(new MyApp(argc, argv));
    icons = new UnixIconProvider();

//    icons.reset( (QFileIconProvider *) new UnixIconProvider());
    return app;
}
*/
PlatformUnix::~PlatformUnix()
{ 
    GlobalShortcutManager::clear();
//    delete icons;
}

QList<Directory> PlatformUnix::getDefaultCatalogDirectories() {
    QList<Directory> list;
    const char *dirs[] = { "/usr/share/applications/",
			   "/usr/local/share/applications/",
			   "/usr/share/gdm/applications/",
			   "/usr/share/applications/kde/",
			   "~/.local/share/applications/"};
    QStringList l;
    l << "*.desktop";
    
    for(int i = 0; i < 5; i++)
	list.append(Directory(dirs[i],l,false,false,100));

    list.append(Directory("~",QStringList(),true,false,0));
    
    return list;
}


QHash<QString, QList<QString> > PlatformUnix::getDirectories() {
    QHash<QString, QList<QString> > out;
    QDir d;
    d.mkdir(QDir::homePath() + "/.launchy");
    
    out["skins"] += qApp->applicationDirPath() + "/skins";
    out["skins"] += QDir::homePath() + "/.launchy/skins";
    out["skins"] += SKINS_PATH;

    out["plugins"] += qApp->applicationDirPath() + "/plugins";
    out["plugins"] += QDir::homePath() + "/.launchy/plugins";
    out["plugins"] += PLUGINS_PATH;

    out["config"] += QDir::homePath() + "/.launchy";
    out["portableConfig"] += qApp->applicationDirPath();
    
    if (QFile::exists(out["skins"].last() + "/Default"))
	out["defSkin"] += out["skins"].last() + "/Default";
    else
      out["defSkin"] += out["skins"].first() + "/Default";

    out["platforms"] += qApp->applicationDirPath();
    out["platforms"] += PLATFORMS_PATH;

    return out;
}


/*
bool PlatformUnix::CreateAlphaBorder(QWidget* w, QString ImageName)
{
//   if (alpha)
//	delete alpha;
  
    if (ImageName == "")
	ImageName = alphaFile;
    alphaFile = ImageName;
    alpha.reset( new AlphaBorder(w, ImageName) ); 
    return true;
}
*/
bool PlatformUnix::supportsAlphaBorder() const
{
    /* @@@
     *
    return QX11Info::isCompositingManagerRunning();
    */
    return true;
}

//Q_EXPORT_PLUGIN2(platform_unix, PlatformUnix)


void PlatformUnix::alterItem(CatItem* item) {
    if (!item->fullPath.endsWith(".desktop", Qt::CaseInsensitive))
	return;

    QString locale = QLocale::system().name();
    
    

    QFile file(item->fullPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	return;

    QString name = "";
    QString icon = "";
    QString exe = "";
    while(!file.atEnd()) {
	QString line = QString::fromUtf8(file.readLine());
	
	if (line.startsWith("Name[" + locale, Qt::CaseInsensitive)) 
	    name = line.split("=")[1].trimmed();
	

	else if (line.startsWith("Name=", Qt::CaseInsensitive)) 
	    name = line.split("=")[1].trimmed();

	else if (line.startsWith("Icon", Qt::CaseInsensitive))
	    icon = line.split("=")[1].trimmed();
	else if (line.startsWith("Exec", Qt::CaseInsensitive))
	    exe = line.split("=")[1].trimmed();	
    }
    if (name.size() >= item->shortName.size() - 8) {
	item->shortName = name;
	item->lowName = item->shortName.toLower();
    }

    // Don't index desktop items wthout icons
    if (icon.trimmed() == "")
        return;


    /* fill in some specifiers while we have the info */
    exe.replace("%i", "--icon " + icon);
    exe.replace("%c", name);
    exe.replace("%k", item->fullPath);

    QStringList allExe = exe.trimmed().split(" ",QString::SkipEmptyParts);
    if (allExe.size() == 0 || allExe[0].size() == 0 )
            return;
    exe = allExe[0];
    allExe.removeFirst();
    //    exe = exe.trimmed().split(" ")[0];

    
    /* if an absolute or relative path is supplied we can just skip this
       everything else should be checked to avoid picking up [unwanted]
       stuff from the working directory - if it doesnt exsist, use it anyway */
    if(!exe.contains(QRegExp("^.?.?/"))){
        foreach(QString line, QProcess::systemEnvironment()) {
            if (!line.startsWith("Path", Qt::CaseInsensitive))
                continue;

            QStringList spl = line.split("=");
            QStringList spl2 = spl[1].split(":");
            foreach(QString dir, spl2) {
                QString tmp = dir + "/" + exe;
                if (QFile::exists(tmp)) {
                    exe = tmp;
                    break;
                }
            }
            break;
        }
    }
    
    
    item->fullPath = exe + " " + allExe.join(" ");

    // Cache the icon for this desktop file
    //shared_ptr<UnixIconProvider> u(dynamic_pointer_cast<UnixIconProvider>(icons));
//    shared_ptr<UnixIconProvider> u((UnixIconProvider*) icons.get());
    
    //icon = u->getDesktopIcon(file.fileName(), icon);
    icon = ((UnixIconProvider*)icons)->getDesktopIcon(file.fileName(), icon);

    QFileInfo inf(icon);
    if (!inf.exists()) {
        qDebug() << "couldn't find icon for" << icon << item->fullPath;
        return;
    }

    item->icon = icon;

    file.close();
    return;
}


QString PlatformUnix::expandEnvironmentVars(QString txt)
{
	QStringList list = QProcess::systemEnvironment();
	txt.replace('~', "$HOME$");
	QString delim("$");
	QString out = "";
	int curPos = txt.indexOf(delim, 0);
	if (curPos == -1) return txt;

	while(curPos != -1)
	{
		int nextPos = txt.indexOf("$", curPos+1);
		if (nextPos == -1) 
		{
			out += txt.mid(curPos+1);
			break;
		}
		QString var = txt.mid(curPos+1, nextPos-curPos-1);
		bool found = false;
		foreach(QString s, list)
		{
			if (s.startsWith(var, Qt::CaseInsensitive))
			{
				found = true;
				out += s.mid(var.length()+1);
				break;
			}			
		}
		if (!found)
			out += "$" + var;
		curPos = nextPos;
	}
	return out;
}


// Create the application object
QApplication* createApplication(int& argc, char** argv)
{
        return new PlatformUnix(argc, argv);
}
#endif
