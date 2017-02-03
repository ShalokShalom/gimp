[Messages]
;InfoBefore page is used instead of license page because the GPL only concerns distribution, not use, and as such doesn't have to be accepted
WizardInfoBefore=Contrat de licence utilisateur final
AboutSetupNote=Installateur r�alis� par Jernej Simon�i�, jernej-gimp@ena.si%n%nImage d'accueil de l'installateur par Alexia_Death%nImage de fin de l'installateur par Jakub Steiner
WinVersionTooLowError=Cette version de GIMP requiert Windows XP Service Pack 3, ou sup�rieur.

[CustomMessages]
;shown before the wizard starts on development versions of GIMP
DevelopmentWarningTitle=Version de d�veloppement
;DevelopmentWarning=This is a development version of GIMP. As such, some features aren't finished, and it may be unstable. If you encounter any problems, first verify that they haven't already been fixed in GIT before you contact the developers.%nThis version of GIMP is not intended for day-to-day work, as it may be unstable, and you could lose your work. Do you wish to continue with installation anyway?
DevelopmentWarning=Ceci est une version de d�veloppement de l'installateur GIMP. Elle a moins �t� test�e que l'installateur stable, ce qui peut causer des dysfonctionnements de GIMP. Veuillez rapporter les probl�mes rencontr�s dans le bugzilla GIMP (composant: "Installer"):%n_https://bugzilla.gnome.org/enter_bug.cgi?product=GIMP%n%nSouhaitez-vous tout de m�me poursuivre l'installation�?
DevelopmentButtonContinue=&Continuer
DevelopmentButtonExit=Quitter

;XPSP3Recommended=Warning: you are running an unsupported version of Windows. Please update to at least Windows XP with Service Pack 3 before reporting any problems.
SSERequired=Cette version de GIMP requiert un processeur prenant en charger les instructions SSE.

Require32BPPTitle=Probl�me de param�tres d'affichage
Require32BPP=L'installateur a d�tect� que Windows ne s'ex�cute pas en affichage 32 bits par pixel. C'est une cause connue d'instabilit� de GIMP, nous vous recommandons de changer la profondeur d'affichage de couleurs en 32BPP avant de poursuivre.
Require32BPPContinue=&Continuer
Require32BPPExit=&Quitter

InstallOrCustomize=GIMP est pr�t � �tre install�. Cliquez sur le bouton � Installer � pour utiliser les param�tres par d�faut, ou sur � Personnaliser � pour choisir plus finement ce qui sera install�.
Install=&Installer
Customize=&Personnaliser

;setup types
TypeCompact=Installation compacte
TypeCustom=Installation personnalis�e
TypeFull=Installation compl�te

;text above component description
ComponentsDescription=Description
;components
ComponentsGimp=GIMP
ComponentsGimpDescription=GIMP et tous les greffons par d�faut
ComponentsDeps=Biblioth�ques d'ex�cution
ComponentsDepsDescription=Biblioth�ques d'ex�cution utilis�es par GIMP, y compris l'environnement d'ex�cution GTK+
ComponentsGtkWimp=Moteur GTK+ pour Windows
ComponentsGtkWimpDescription=Apparence native pour Windows
ComponentsCompat=Prise en charge des anciens greffons
ComponentsCompatDescription=Installe les biblioth�ques requises par d'anciens greffons
ComponentsTranslations=Traductions
ComponentsTranslationsDescription=Traductions
ComponentsPython=Prise en charge des scripts Python
ComponentsPythonDescription=Prise en charge des greffons GIMP �crits en langage Python
ComponentsGhostscript=Prise en charge de PostScript
ComponentsGhostscriptDescription=Permet le chargement de fichiers PostScript dans GIMP
;only when installing on x64 Windows
ComponentsGimp32=Gestion des greffons 32 bits
ComponentsGimp32Description=Inclut les fichiers n�cessaires � l'utilisation de greffons 32 bits.%nRequis pour la prise en charge de Python.

;additional installation tasks
AdditionalIcons=Ic�nes additionnelles:
AdditionalIconsDesktop=Cr�er une ic�ne sur le &bureau
AdditionalIconsQuickLaunch=Cr�er une ic�ne dans la barre de lancement &rapide

RemoveOldGIMP=Supprimer les versions ant�rieures de GIMP

;%1 is replaced by file name; these messages should never appear (unless user runs out of disk space at the exact right moment)
ErrorChangingEnviron=Une erreur s'est produite lors de la mise � jour de l'environnement de GIMP dans %1. Si des erreurs surviennent au chargement des greffons, tentez de d�sinstaller puis r�installer GIMP.
ErrorExtractingTemp=Erreur durant l'extraction de donn�es temporaires.
ErrorUpdatingPython=Erreur durant la mise � jour de l'interpr�teur Python.
ErrorReadingGimpRC=Erreur de mise � jour du fichier %1.
ErrorUpdatingGimpRC=Erreur de mise � jour du fichier %1 de configuration de GIMP.

;displayed in Explorer's right-click menu
OpenWithGimp=Modifier avec GIMP

;file associations page
SelectAssociationsCaption=S�lectionner les extensions � associer
SelectAssociationsExtensions=Extensions:
SelectAssociationsInfo1=S�lectionner les extensions de fichiers � associer � GIMP
SelectAssociationsInfo2=En double-cliquant dans l'Explorateur Windows, les fichiers portant ces extensions s'ouvriront dans GIMP.
SelectAssociationsSelectAll=&S�lectionner toutes
SelectAssociationsUnselectAll=&D�s�lectionner toutes
SelectAssociationsSelectUnused=S�lectionner les &inutilis�es

;shown on summary screen just before starting the install
ReadyMemoAssociations=Types de fichiers � associer � GIMP:

RemovingOldVersion=D�sinstallation de la version pr�c�dente de GIMP:
;%1 = version, %2 = installation directory
;ran uninstaller, but it returned an error, or didn't remove everything
RemovingOldVersionFailed=La d�sinstallation automatique de votre version de GIMP actuelle a �chou�, et GIMP %1 ne peut l'�craser.%n%nVeuillez d�sinstaller manuellement l'ancienne version de GIMP et relancez l'installation dans %2, ou choisissez l'option d'installation personnalis�e et un dossier de destination diff�rent.%n%nL'installateur va � pr�sent s'arr�ter.
;couldn't find an uninstaller, or found several uninstallers
RemovingOldVersionCantUninstall=La m�thode de d�sinstallation automatique de votre version de GIMP actuelle n'a pu �tre d�termin�e, et GIMP %1 ne peut �craser votre version de GIMP actuelle.%n%nVeuillez d�sinstaller manuellement l'ancienne version de GIMP et ses greffons avant de retenter une instalation dans %2, ou choisissez une installation personnalis�e et un dossier de destination diff�rent.%n%nL'installateur va � pr�sent s'arr�ter.

RebootRequiredFirst=Votre version pr�c�dente de GIMP a �t� supprim�e avec succ�s, mais Windows requiert un red�marrage avant de poursuivre l'installation.%n%nApr�s le red�marrage, l'installation reprendra � la connexion d'un administrateur.

;displayed if restart settings couldn't be read, or if the setup couldn't re-run itself
ErrorRestartingSetup=L'installateur a rencontr� une erreur au red�marrage. (%1)

;displayed while the files are being extracted; note the capitalisation!
Billboard1=GIMP est un Logiciel Libre.%n%nVisitez
;www.gimp.org (displayed between Billboard1 and Billboard2)
Billboard2=pour des mises � jour gratuites.

SettingUpAssociations=Associations des extensions de fichiers...
SettingUpPyGimp=Configuration de l'environnement d'extension de GIMP en Python...
SettingUpEnvironment=Configuration de l'environnement GIMP...
SettingUpGimpRC=Configuration de la gestion des greffons 32 bits...

;displayed on last page
LaunchGimp=Ex�cuter GIMP

;shown during uninstall when removing add-ons
UninstallingAddOnCaption=Suppression de l'extension

InternalError=Erreur interne (%1).

;used by installer for add-ons (currently only help)
DirNotGimp=GIMP ne semble pas �tre install� dans le dossier s�lectionn�. Souhaitez vous continuer�?
