[Messages]
;InfoBefore page is used instead of license page because the GPL only concerns distribution, not use, and as such doesn't have to be accepted
WizardInfoBefore=Licensaftale
AboutSetupNote=Installationen er lavet af Jernej Simon�i�, jernej-gimp@ena.si%n%nBilledet p� �bningssiden er lavet af Alexia_Death%nBilledet p� afslutningssiden er lavet af Jakub Steiner
WinVersionTooLowError=Denne version af GIMP kr�ver Windows XP med Service Pack 3, eller en nyere version af Windows.

[CustomMessages]
;shown before the wizard starts on development versions of GIMP
DevelopmentWarningTitle=Development version
;DevelopmentWarning=This is a development version of GIMP. As such, some features aren't finished, and it may be unstable. If you encounter any problems, first verify that they haven't already been fixed in GIT before you contact the developers.%nThis version of GIMP is not intended for day-to-day work, as it may be unstable, and you could lose your work. Do you wish to continue with installation anyway?
DevelopmentWarning=Dette er en development version af installationsprogrammet til GIMP. Det er ikke blevet testet lige s� meget som det stabile installationsprogram, hvilket kan resultere i at GIMP ikke virker korrekt. Rapport�r venligst de problemer du st�der p� i GIMP bugzilla (Installer komponent):%n_https://bugzilla.gnome.org/enter_bug.cgi?product=GIMP%n%n�nsker du alligevel at forts�tte installation?
DevelopmentButtonContinue=&Forts�t
DevelopmentButtonExit=Afslut

;XPSP3Recommended=Warning: you are running an unsupported version of Windows. Please update to at least Windows XP with Service Pack 3 before reporting any problems.
SSERequired=Denne version af GIMP kr�ver en processor der underst�tter SSE-instruktioner.

Require32BPPTitle=Problemer med sk�rmindstillinger
Require32BPP=Installationen har registreret at Windows sk�rmindstillinger ikke anvender 32-bits-per-pixel. Det er kendt for at skabe stabilitetsproblemer for GIMP, s� det anbefales at �ndre sk�rmens farvedybde til �gte farver (32 bit) f�r du forts�tter.
Require32BPPContinue=&Forts�t
Require32BPPExit=A&fslut

InstallOrCustomize=GIMP er nu klar til at blive installeret. Klik p� Installer nu-knappen for at installere med standardindstillingerne, eller klik p� Brugerdefineret-knappen hvis du �nsker at v�lge hvad der skal installeres.
Install=&Installer
Customize=&Brugerdefineret

;setup types
TypeCompact=Kompakt installation
TypeCustom=Brugerdefineret installation
TypeFull=Fuld installation

;text above component description
ComponentsDescription=Beskrivelse
;components
ComponentsGimp=GIMP
ComponentsGimpDescription=GIMP og alle standard plugins
ComponentsDeps=Afviklingsbiblioteker
ComponentsDepsDescription=Afviklingsbiblioteker som GIMP anvender, inklusiv GTK+ afviklingsmilj�
ComponentsGtkWimp=MS-Windows-motor til GTK+
ComponentsGtkWimpDescription=Standard Windows udseende til GIMP
ComponentsCompat=Underst�ttelse af gamle plugins
ComponentsCompatDescription=Installer biblioteker der kr�ves til gamle tredjeparts plugins
ComponentsTranslations=Overs�ttelser
ComponentsTranslationsDescription=Overs�ttelser
ComponentsPython=Python-scripting
ComponentsPythonDescription=Giver mulighed for at bruge GIMP-plug-ins som er skrevet i Python-scripting-sproget.
ComponentsGhostscript=PostScript underst�ttelse
ComponentsGhostscriptDescription=GIMP f�s mulighed for at indl�se PostScript-filer
;only when installing on x64 Windows
ComponentsGimp32=Underst�ttelse af 32-bit plugins
ComponentsGimp32Description=Inkludere filer der er n�dvendige for at anvende 32-bit plugins.%nP�kr�vet for underst�ttelse af Python.

;additional installation tasks
AdditionalIcons=Yderligere ikoner:
AdditionalIconsDesktop=Opret ikon p� &skrivebordet
AdditionalIconsQuickLaunch=Opret ikon i &Hurtig start

RemoveOldGIMP=Fjern forrige GIMP-version

;%1 is replaced by file name; these messages should never appear (unless user runs out of disk space at the exact right moment)
ErrorChangingEnviron=Der opstod et problem ved opdatering af GIMP's-milj� i %1. Hvis du f�r fejl ved indl�sning af plugins, s� pr�v at afinstallere og geninstaller GIMP.
ErrorExtractingTemp=Fejl ved udtr�kning af midlertidige data.
ErrorUpdatingPython=Fejl ved opdatering af Python-fortolker information.
ErrorReadingGimpRC=Der opstod en fejl ved opdatering af %1.
ErrorUpdatingGimpRC=Der opstod en fejl ved opdatering af GIMP's konfigurationsfil %1.

;displayed in Explorer's right-click menu
OpenWithGimp=Rediger i GIMP

;file associations page
SelectAssociationsCaption=V�lg filtilknytninger
SelectAssociationsExtensions=Filtyper:
SelectAssociationsInfo1=V�lg de filtyper som du have tilknyttet med GIMP
SelectAssociationsInfo2=Markerede filer �bnes i GIMP, n�r du dobbeltklikker p� dem i Stifinder.
SelectAssociationsSelectAll=V�lg &alle
SelectAssociationsUnselectAll=Frav�lg &alle
SelectAssociationsSelectUnused=V�lg &ubrugte

;shown on summary screen just before starting the install
ReadyMemoAssociations=Filtyper der skal tilknyttes GIMP:

RemovingOldVersion=Fjerner forrige version af GIMP:
;%1 = version, %2 = installation directory
;ran uninstaller, but it returned an error, or didn't remove everything
RemovingOldVersionFailed=GIMP %1 kan ikke installeres oven p� den GIMP-version der er installeret i �jeblikket, og automatisk afinstallation af gamle versioner mislykkedes.%n%nFjern venligst selv den forrige version af GIMP, f�r denne version installeres i %2, eller v�lg brugerdefineret installation, og v�lg en anden installationsmappe.%n%nInstallationen vil nu blive afsluttet.
;couldn't find an uninstaller, or found several uninstallers
RemovingOldVersionCantUninstall=GIMP %1 kan ikke installeres oven p� den GIMP-version der er installeret i �jeblikket, og installationen var ikke i stand til at fastsl� hvordan den gamle version kunne fjernes.%n%nFjern venligst selv den forrige version af GIMP og alle tilf�jelser, f�r denne version installeres i %2, eller v�lg brugerdefineret installation, og v�lg en anden installationsmappe.%n%nInstallationen vil nu blive afsluttet.

RebootRequiredFirst=Forrige GIMP-version blev fjernet, men Windows skal genstartes f�r installationen kan forts�tte.%n%nEfter computeren er blevet genstartet vil installationen forts�tte, n�ste gang en administrator logger p�.

;displayed if restart settings couldn't be read, or if the setup couldn't re-run itself
ErrorRestartingSetup=Der opstod en fejl ved genstart af installationen. (%1)

;displayed while the files are being extracted; note the capitalisation!
Billboard1=Husk: GIMP er fri software.%n%nBes�g venligst
;www.gimp.org (displayed between Billboard1 and Billboard2)
Billboard2=for gratis opdateringer.

SettingUpAssociations=Ops�tter filtilknytninger...
SettingUpPyGimp=Ops�tter milj� til GIMP Python-udvidelse...
SettingUpEnvironment=Ops�tter GIMP-milj�...
SettingUpGimpRC=Ops�tter GIMP-konfiguration til underst�ttelses af 32-bit plugin...

;displayed on last page
LaunchGimp=Start GIMP

;shown during uninstall when removing add-ons
UninstallingAddOnCaption=Fjerner add-on

InternalError=Intern fejl (%1).

;used by installer for add-ons (currently only help)
DirNotGimp=GIMP ser ikke ud til at v�re installeret i den angivne mappe. Forts�t alligevel?
