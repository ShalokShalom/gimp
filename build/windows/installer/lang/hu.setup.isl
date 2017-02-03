[Messages]
;InfoBefore page is used instead of license page because the GPL only concerns distribution, not use, and as such doesn't have to be accepted
WizardInfoBefore=Licencmeg�llapod�s
AboutSetupNote=A telep�t�t Jernej Simoncic, jernej-gimp@ena.si k�sz�tette%n%nA telep�t� kezd�lapj�n l�that� k�pet Alexia_Death k�sz�tette%nA telep�t� utols� lapj�n l�that� k�pet Jakub Steiner k�sz�tette
WinVersionTooLowError=A GIMP ezen verzi�ja a Windows Windows XP Service Pack 3 vagy �jabb verzi�j�t ig�nyli.

[CustomMessages]
;shown before the wizard starts on development versions of GIMP
DevelopmentWarningTitle=Fejleszt�i verzi�
;DevelopmentWarning=Ez a GIMP fejleszt�i verzi�ja. Mint ilyen, egyes funkci�k nincsenek befejezve; tov�bb� a program instabil is lehet. Ha probl�m�t tapasztal, ellen�rizze hogy nincs-e m�r jav�tva Git-ben, miel�tt megkeresi a fejleszt�ket.%nA GIMP ezen verzi�j�t nem napi szint� haszn�latra sz�njuk, mivel instabil lehet �s emiatt elvesz�thet adatokat. Mindenk�pp folytatja a telep�t�st?
DevelopmentWarning=Ez a GIMP telep�t�j�nek fejleszt�i verzi�ja. Nincs annyira tesztelve, mint a stabil telep�t�, emiatt a GIMP hib�san m�k�dhet. A tapasztalt hib�kat a GIMP Bugzill�ba jelentse (az Installer �sszetev� al�):%n_https://bugzilla.gnome.org/enter_bug.cgi?product=GIMP%n%nMindenk�pp folytatja a telep�t�st?
DevelopmentButtonContinue=&Folytat�s
DevelopmentButtonExit=Kil�p�s

;XPSP3Recommended=Figyelem: a Windows nem t�mogatott verzi�j�t futtatja. Friss�tsen legal�bb a Windows XP Service Pack 3 kiad�sra a probl�m�k bejelent�se el�tt.
SSERequired=A GIMP ezen verzi�ja az SSE utas�t�sokat t�mogat� processzort ig�nyel.

Require32BPPTitle=Probl�ma a kijelz�be�ll�t�sokkal
Require32BPP=A telep�t� azt �szlelte, hogy a Windows nem 32 bites sz�nm�lys�g� m�dban fut. Ez a GIMP-nek stabilit�si probl�m�kat okoz, �gy javasoljuk, hogy a folytat�s el�tt �ll�tsa a sz�nm�lys�get 32 bitesre.
Require32BPPContinue=&Folytat�s
Require32BPPExit=&Kil�p�s

InstallOrCustomize=A GIMP imm�r k�sz a telep�t�sre. Kattintson a Telep�t�s gombra az alap�rtelmezett be�ll�t�sokkal val� telep�t�shez, vagy a Szem�lyre szab�s gombra, ha m�dos�tani szeretn� a telep�tend� �sszetev�k list�j�t.
Install=&Telep�t�s
Customize=&Szem�lyre szab�s

;setup types
TypeCompact=Kompakt telep�t�s
TypeCustom=Egy�ni telep�t�s
TypeFull=Teljes telep�t�s

;text above component description
ComponentsDescription=Le�r�s
;components
ComponentsGimp=GIMP
ComponentsGimpDescription=A GIMP �s minden alap b�v�tm�nye
ComponentsDeps=Fut�sidej� programk�nyvt�rak
ComponentsDepsDescription=A GIMP �ltal haszn�lt fut�sidej� programk�nyvt�rak, bele�rtve a GTK+ k�rnyezetet
ComponentsGtkWimp=MS-Windows motor a GTK+-hoz
ComponentsGtkWimpDescription=Nat�v Windows megjelen�s a GIMP-hez
ComponentsCompat=R�gi b�v�tm�nyek t�mogat�sa
ComponentsCompatDescription=R�gi k�ls� b�v�tm�nyekhez sz�ks�ges programk�nyvt�rak telep�t�se
ComponentsTranslations=Ford�t�sok
ComponentsTranslationsDescription=Ford�t�sok
ComponentsPython=Python parancsf�jlok
ComponentsPythonDescription=Lehet�v� teszi Python nyelven �rt GIMP b�v�tm�nyek haszn�lat�t.
ComponentsGhostscript=PostScript t�mogat�s
ComponentsGhostscriptDescription=A GIMP bet�ltheti a PostScript f�jlokat
;only when installing on x64 Windows
ComponentsGimp32=32 bites b�v�tm�nyek t�mogat�sa
ComponentsGimp32Description=A 32 bites b�v�tm�nyek t�mogat�s�hoz sz�ks�ges f�jlok.%nSz�ks�ges a Python t�mogat�shoz.

;additional installation tasks
AdditionalIcons=Tov�bbi ikonok:
AdditionalIconsDesktop=&Asztali ikon l�trehoz�sa
AdditionalIconsQuickLaunch=&Gyorsind�t� ikon l�trehoz�sa

RemoveOldGIMP=Kor�bbi GIMP verzi� elt�vol�t�sa

;%1 is replaced by file name; these messages should never appear (unless user runs out of disk space at the exact right moment)
ErrorChangingEnviron=Hiba t�rt�nt a GIMP k�rnyezet�nek friss�t�sekor ebben: %1. Ha hiba�zeneteket kap a b�v�tm�nyek bet�lt�sekor, akkor pr�b�lja meg elt�vol�tani �s �jratelep�teni a GIMP-et.
ErrorExtractingTemp=Hiba az ideiglenes adatok kibont�sakor.
ErrorUpdatingPython=Hiba a Python �rtelmez� inform�ci�inak friss�t�sekor.
ErrorReadingGimpRC=Hiba t�rt�nt a k�vetkez� friss�t�sekor: %1.
ErrorUpdatingGimpRC=Hiba t�rt�nt a GIMP be�ll�t�f�jlj�nak friss�t�sekor: %1.

;displayed in Explorer's right-click menu
OpenWithGimp=Szerkeszt�s a GIMP-pel

;file associations page
SelectAssociationsCaption=V�lasszon f�jlt�rs�t�sokat
SelectAssociationsExtensions=Kiterjeszt�sek:
SelectAssociationsInfo1=V�lassza ki a GIMP-hez t�rs�tand� f�jlt�pusokat
SelectAssociationsInfo2=Ennek hat�s�ra a kijel�lt t�pus� f�jlok a GIMP-ben ny�lnak meg, amikor dupl�n kattint r�juk az Int�z�ben.
SelectAssociationsSelectAll=�sszes &kijel�l�se
SelectAssociationsUnselectAll=Kijel�l�s &t�rl�se
SelectAssociationsSelectUnused=T�&bbi kijel�l�se

;shown on summary screen just before starting the install
ReadyMemoAssociations=A GIMP-hez t�rs�tand� f�jlt�pusok:

RemovingOldVersion=A GIMP kor�bbi verzi�j�nak elt�vol�t�sa:
;%1 = version, %2 = installation directory
;ran uninstaller, but it returned an error, or didn't remove everything
RemovingOldVersionFailed=A GIMP %1 nem telep�thet� a jelenlegi GIMP verzi� f�l�, �s a r�gi verzi� automatikus elt�vol�t�sa meghi�sult.%n%nT�vol�tsa el a GIMP kor�bbi verzi�j�t, miel�tt ezt a verzi�t ide telep�ti: %2, vagy v�lassza az Egy�ni telep�t�st �s v�lasszon m�sik telep�t�si mapp�t.%n%nA telep�t� most kil�p.
;couldn't find an uninstaller, or found several uninstallers
RemovingOldVersionCantUninstall=A GIMP %1 nem telep�thet� a jelenlegi GIMP verzi� f�l�, �s a telep�t� nem tudta meg�llap�tani, hogyan t�vol�that� el a r�gi verzi� automatikusan.%n%nT�vol�tsa el a GIMP kor�bbi verzi�j�t �s a b�v�tm�nyeket, miel�tt ezt a verzi�t ide telep�ti: %2, vagy v�lassza az Egy�ni telep�t�st �s v�lasszon m�sik telep�t�si mapp�t.%n%nA telep�t� most kil�p.

RebootRequiredFirst=A GIMP kor�bbi verzi�ja sikeresen elt�vol�tva, de a Windowst �jra kell ind�tani, miel�tt a telep�t�s folytat�dhatna.%n%nA sz�m�t�g�p �jraind�t�sa �s egy adminisztr�tor bejelentkez�se ut�n a telep�t� fut�sa folytat�dik.

;displayed if restart settings couldn't be read, or if the setup couldn't re-run itself
ErrorRestartingSetup=Hiba t�rt�nt a Telep�t� �jraind�t�sakor. (%1)

;displayed while the files are being extracted; note the capitalisation!
Billboard1=Ne feledje: A GIMP szabad szoftver.%n%nFriss�t�sek�rt keresse fel a
;www.gimp.org (displayed between Billboard1 and Billboard2)
Billboard2=oldalt.

SettingUpAssociations=F�jlt�rs�t�sok be�ll�t�sa...
SettingUpPyGimp=K�rnyezet be�ll�t�sa a GIMP Python kiterjeszt�s�hez...
SettingUpEnvironment=A GIMP k�rnyezet�nek be�ll�t�sa...
SettingUpGimpRC=A GIMP be�ll�t�sa a 32 bites b�v�tm�nyek t�mogat�s�hoz...

;displayed on last page
LaunchGimp=A GIMP ind�t�sa

;shown during uninstall when removing add-ons
UninstallingAddOnCaption=B�v�tm�ny elt�vol�t�sa

InternalError=Bels� hiba (%1).

;used by installer for add-ons (currently only help)
DirNotGimp=A GIMP nem tal�lhat� a kijel�lt k�nyvt�rban. Mindenk�pp folytatja?
