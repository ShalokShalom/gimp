[Messages]
;InfoBefore page is used instead of license page because the GPL only concerns distribution, not use, and as such doesn't have to be accepted
WizardInfoBefore=Acord de llic�ncia
AboutSetupNote=Instal�laci� creada per Jernej Simon�i�, jernej-gimp@ena.si%n%nImatge en la p�gina d'inici de la instal�laci� per Alexia_Death%nImatge en la p�gina final de la instal�laci� per Jakub Steiner
WinVersionTooLowError=Aquesta versi� del GIMP requereix Windows XP amb Service Pack 3, o una versi� m�s nova de Windows.

[CustomMessages]
;shown before the wizard starts on development versions of GIMP
DevelopmentWarningTitle=Versi� de desenvolupament
;DevelopmentWarning=Aquesta �s una versi� de desenvolupament del GIMP. Aix�, algunes caracter�stiques no estan acabades i pot ser inestable. Si trobeu qualsevol problema, verifiqueu primer que no ha estat resolt en el GIT abans de contactar amb els desenvolupadors.%nAquesta versi� del GIMP no est� orientada al treball diari , aix� pot ser inestable i podr�eu perdre la vostra feina. Voleu continuar amb la instal�laci� de totes maneres?
DevelopmentWarning=Aquesta �s una versi� de desenvolupament de l'instal�lador del GIMP. No ha estat provada tan com l'instal�lador estable, i aix� pot fer que el GIMP no funcioni correctament. Informeu de qualsevol problema que trobeu en el bugzilla del GIMP (Installer component):%n_https://bugzilla.gnome.org/enter_bug.cgi?product=GIMP%n%nVoleu continuar amb la instal�laci� de totes maneres?
DevelopmentButtonContinue=&Continua
DevelopmentButtonExit=Surt

;XPSP3Recommended=Av�s: Esteu executant una versi� no suportada de Windows. Actualitzeu, com a m�nim, a Windows XP amb Service Pack 3 abans d'informar de qualsevol problema.
SSERequired=Aquesta versi� del GIMP requereix un processador que suporti instruccions SSE.

Require32BPPTitle=Hi ha un problema en la configuraci� de pantalla
Require32BPP=L'instal�lador ha detectat que el vostre Windows no s'est� executant en mode de visualitzaci� de 32 bits per p�xel. Aix� pot causar problemes d'estabilitat amb el GIMP, pel que es recomana canviar la profunditat de color de pantalla a 32 BPP abans de continuar.
Require32BPPContinue=&Continua
Require32BPPExit=S&urt

InstallOrCustomize=El GIMP ja est� llest per ser instal�lat. Cliqueu en el bot� Instal�la per instal�lar usant els par�metres per defecte o cliqueu el bot� Personalitza si us agrada un major control sobre el que voleu instal�lar.
Install=&Instal�la
Customize=&Personalitza

;setup types
TypeCompact=Instal�laci� compacta
TypeCustom=Instal�laci� personalitzada
TypeFull=Instal�laci� completa

;text above component description
ComponentsDescription=Descripci�
;components
ComponentsGimp=GIMP
ComponentsGimpDescription=GIMP i tots els connectors per defecte
ComponentsDeps=Biblioteques d'execuci�
ComponentsDepsDescription=Biblioteques d'execuci� usades pel GIMP, incl�s l'entorn d'execuci� GTK+
ComponentsGtkWimp=Motor MS-Windows per GTK+
ComponentsGtkWimpDescription=Aspecte natiu de Windows pel GIMP
ComponentsCompat=Suport per connectors vells
ComponentsCompatDescription=Instal�la les biblioteques necess�ries pels connectors vells de terceres parts
ComponentsTranslations=Traduccions
ComponentsTranslationsDescription=Traduccions
ComponentsPython=Python scripting
ComponentsPythonDescription=Us permet usar els connectors del GIMP escrits en llenguatge script de Python.
ComponentsGhostscript=Suport PostScript
ComponentsGhostscriptDescription= Permet al GIMP carregar fitxers PostScript
;only when installing on x64 Windows
ComponentsGimp32=Suport per connectors de 32-bit
ComponentsGimp32Description=Inclou els fitxers necessaris per usar els connectors de 32-bits.%nNecessaris pel suport de Python.

;additional installation tasks
AdditionalIcons=Icones addicionals:
AdditionalIconsDesktop=Crea una icona en l'&escriptori
AdditionalIconsQuickLaunch=Crea una icona d'acc�s &r�pid

RemoveOldGIMP=Elimina la versi� pr�via del GIMP.

;%1 is replaced by file name; these messages should never appear (unless user runs out of disk space at the exact right moment)
ErrorChangingEnviron=S'ha produ�t un error en actualitzar l'entorn del GIMP en %1. Si teniu qualsevol en carregar els connectors, proveu a desinstal�lar i tornar a instal�lar el GIMP.
ErrorExtractingTemp=S'ha produ�t un error en extreure les dades temporals.
ErrorUpdatingPython=S'ha produ�t un error en actualitzar la informaci� de l'int�rpret de Python.
ErrorReadingGimpRC=S'ha produ�t un error en actualitzar %1.
ErrorUpdatingGimpRC=S'ha produ�t un error en actualitzar el fitxer %1 de configuraci� del GIMP.

;displayed in Explorer's right-click menu
OpenWithGimp=Edita amb el GIMP

;file associations page
SelectAssociationsCaption=Seleccioneu les associacions dels fitxers
SelectAssociationsExtensions=Extensions:
SelectAssociationsInfo1=Seleccioneu els tipus de fitxers que voleu associar amb el GIMP
SelectAssociationsInfo2=Aix� far� que els tipus de fitxers seleccionats s'obrin amb el GIMP quan feu doble clic sobre ells en l'explorador.
SelectAssociationsSelectAll=Selecciona-ho &tot
SelectAssociationsUnselectAll=Desselecciona-ho t&ot
SelectAssociationsSelectUnused=Selecciona els no &usats

;shown on summary screen just before starting the install
ReadyMemoAssociations=Tipus de fitxer a associar amb el GIMP:

RemovingOldVersion=Removing previous version of GIMP:
;%1 = version, %2 = installation directory
;ran uninstaller, but it returned an error, or didn't remove everything
RemovingOldVersionFailed= El GIMP %1 no es pot instal�lar sobre la versi� del GIMP instal�lada actualment, i la desinstal�laci� autom�tica de la versi� antiga ha fallat.%n%nElimineu la versi� pr�via del GIMP abans d'instal�lar aquesta versi� en %2, o escolliu Instal�laci� personalitzada, i seleccioneu una carpeta d'instal�laci� diferent.%n%nL'instal�lador es tancar� ara.
;couldn't find an uninstaller, or found several uninstallers
RemovingOldVersionCantUninstall=El GIMP %1 no es pot instal�lar sobre la versi� del GIMP instal�lada actualment, i l'instal�lador no pot determinar com eliminar automaticament.%n%nElimineu la versi� pr�via del GIMP i qualsevol connector abans d'instal�lar aquesta versi� en %2, o escolliu Instal�laci� personalitzada, i seleccioneu una carpeta d'instal�laci� diferent.%n%nL'instal�lador es tancar� ara.

RebootRequiredFirst=La versi� pr�via del GIMP s'ha eliminat satisfact�riament, per� cal reiniciar Windows abans que l'instal�lador pugui continuar.%n%nDespr�s de reiniciar l'ordinador, l'instal�lador continuar� un cop un administrador obri sessi�.

;displayed if restart settings couldn't be read, or if the setup couldn't re-run itself
ErrorRestartingSetup=S'ha produ�t un error en reiniciar l'insta�lador. (%1)

;displayed while the files are being extracted; note the capitalisation!
Billboard1=Recordeu: El GIMP �s programari lliure.%n%nVisiteu
;www.gimp.org (displayed between Billboard1 and Billboard2)
Billboard2=per actualitzacions grat�ites.

SettingUpAssociations=S'estan configurant les associacions de fitxer...
SettingUpPyGimp=S'est� configurant l'entorn per l'extensi� Python del GIMP...
SettingUpEnvironment=S'est� configurant l'entorn del GIMP...
SettingUpGimpRC=S'est� configurant el GIMP pel suport de connectors de 32-bits...

;displayed on last page
LaunchGimp=Inicia el GIMP

;shown during uninstall when removing add-ons
UninstallingAddOnCaption=S'estan eliminant complements

InternalError=S'ha produ�t un error intern (%1).

;used by installer for add-ons (currently only help)
DirNotGimp=El GIMP no sembla instal�lar-se en el directori seleccionat. Voleu continuar de totes maneres?
