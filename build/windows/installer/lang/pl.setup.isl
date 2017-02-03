[Messages]
;InfoBefore page is used instead of license page because the GPL only concerns distribution, not use, and as such doesn't have to be accepted
WizardInfoBefore=Umowa licencyjna
AboutSetupNote=Instalator utworzony przez Jerneja Simon�i�a, jernej-gimp@ena.si%n%nObraz na stronie otwieraj�cej autorstwa Alexia_Death%nObraz na stronie zamykaj�cej autorstwa Jakuba Steinera
WinVersionTooLowError=Ta wersja programu GIMP wymaga systemu Windows XP z Service Pack 3 lub nowsz� wersj� systemu Windows.

[CustomMessages]
;shown before the wizard starts on development versions of GIMP
DevelopmentWarningTitle=Wersja rozwojowa
;DevelopmentWarning=To jest rozwojowa wersja programu GIMP. Niekt�re funkcje nie zosta�y jeszcze uko�czone, a ca�y program mo�e by� niestabilny. W razie wyst�pienia b��du przed skontaktowaniem si� z programistami nale�y sprawdzi�, czy nie zosta� on naprawiony w repozytorium git.%nTa wersja programu GIMP nie jest przeznaczona do codziennej pracy z powodu niestabilno�ci i mo�liwo�ci utraty danych. Kontynuowa� instalacj� mimo to?
DevelopmentWarning=To jest rozwojowa wersja instalatora programu GIMP. Nie zosta�a ona przetestowana tak dok�adnie, jak stabilna wersja, co mo�e powodowa� nieprawid�owe dzia�anie programu GIMP. Prosimy zg�asza� napotkane b��dy w systemie Bugzilla programu GIMP (komponent \"Installer\"):%n_https://bugzilla.gnome.org/enter_bug.cgi?product=GIMP%n%nKontynuowa� instalacj� mimo to?
DevelopmentButtonContinue=&Kontynuuj
DevelopmentButtonExit=Zako�cz

;XPSP3Recommended=Ostrze�enie: na komputerze uruchomiona jest nieobs�ugiwana wersja systemu Windows. Prosimy zaktualizowa� do co najmniej systemu Windows XP z Service Pack 3 przed zg�aszaniem problem�w.
SSERequired=Ta wersja programu GIMP wymaga procesora obs�uguj�cego instrukcje SSE.

Require32BPPTitle=Problem ustawie� ekranu
Require32BPP=Instalator wykry�, �e system Windows nie dzia�a w trybie wy�wietlania 32 bit�w g��bi kolor�w. Powoduje to problemy stabilno�ci programu GIMP. Zalecana jest zmiana g��bi kolor�w ekranu na 32 bity na piksel przed kontynuowaniem.
Require32BPPContinue=&Kontynuuj
Require32BPPExit=Za&ko�cz

InstallOrCustomize=Program GIMP jest gotowy do instalacji. Klikni�cie przycisku Zainstaluj spowoduje instalacj� u�ywaj�c domy�lnych ustawie�, a klikni�cie przycisku Dostosuj udost�pnia wi�cej mo�liwo�ci kontroli nad procesem instalacji.
Install=Za&instaluj
Customize=&Dostosuj

;setup types
TypeCompact=Instalacja podstawowa
TypeCustom=Instalacja u�ytkownika
TypeFull=Pe�na instalacja

;text above component description
ComponentsDescription=Opis
;components
ComponentsGimp=GIMP
ComponentsGimpDescription=GIMP i wszystkie domy�lne wtyczki
ComponentsDeps=Biblioteki wykonawcze
ComponentsDepsDescription=Biblioteki wykonawcze u�ywane przez program GIMP, w tym �rodowisko wykonawcze GTK+
ComponentsGtkWimp=Mechanizm MS-Windows dla biblioteki GTK+
ComponentsGtkWimpDescription=Natywny wygl�d programu GIMP
ComponentsCompat=Obs�uga starszych wtyczek
ComponentsCompatDescription=Instaluje biblioteki wymagane przez starsze wtyczki firm trzecich
ComponentsTranslations=T�umaczenia
ComponentsTranslationsDescription=T�umaczenia
ComponentsPython=J�zyk skryptowy Python
ComponentsPythonDescription=Umo�liwia u�ywanie wtyczek programu GIMP napisanych w j�zyku skryptowym Python.
ComponentsGhostscript=Obs�uga plik�w PostScript
ComponentsGhostscriptDescription=Umo�liwia programowi GIMP wczytywanie plik�w w formacie PostScript
;only when installing on x64 Windows
ComponentsGimp32=Obs�uga wtyczek 32-bitowych
ComponentsGimp32Description=Do��cza pliki wymagane, aby u�ywa� wtyczki 32-bitowe.%nWymagane do obs�ugi j�zyka Python.

;additional installation tasks
AdditionalIcons=Dodatkowe ikony:
AdditionalIconsDesktop=&Utworzenie ikony na pulpicie
AdditionalIconsQuickLaunch=Utworzenie ikony na pasku &szybkiego uruchamiania

RemoveOldGIMP=Usuni�cie poprzedniej wersji programu GIMP

;%1 is replaced by file name; these messages should never appear (unless user runs out of disk space at the exact right moment)
ErrorChangingEnviron=Wyst�pi� problem podczas aktualizowania �rodowiska programu GIMP w %1. Je�li wyst�pi� b��dy podczas wczytywania wtyczek, to nale�y odinstalowa� i ponownie zainstalowa� program GIMP.
ErrorExtractingTemp=B��d podczas wypakowywania plik�w tymczasowych.
ErrorUpdatingPython=B��d podczas aktualizowania informacji o interpreterze j�zyka Python.
ErrorReadingGimpRC=Wyst�pi� b��d podczas aktualizowania %1.
ErrorUpdatingGimpRC=Wyst�pi� b��d podczas aktualizowania pliku konfiguracji %1 programu GIMP.

;displayed in Explorer's right-click menu
OpenWithGimp=Edytuj za pomoc� GIMP

;file associations page
SelectAssociationsCaption=Wyb�r powi�za� plik�w
SelectAssociationsExtensions=Rozszerzenia:
SelectAssociationsInfo1=Prosz� wybra� typy plik�w do powi�zania z programem GIMP
SelectAssociationsInfo2=Spowoduje to otwieranie wybranych plik�w w programie GIMP po podw�jnym klikni�ciu ich w Eksploratorze.
SelectAssociationsSelectAll=Zaznacz &wszystkie
SelectAssociationsUnselectAll=Odznacz w&szystkie
SelectAssociationsSelectUnused=Zaznacz &nieu�ywane

;shown on summary screen just before starting the install
ReadyMemoAssociations=Typy plik�w do powi�zania z programem GIMP:

RemovingOldVersion=Usuwanie poprzedniej wersji programu GIMP:
;%1 = version, %2 = installation directory
;ran uninstaller, but it returned an error, or didn't remove everything
RemovingOldVersionFailed=GIMP %1 nie mo�e zosta� zainstalowany w miejscu obecnie zainstalowanej wersji, a automatyczne odinstalowanie poprzedniej wersji si� nie powiod�o.%n%nProsz� samodzielnie usun�� poprzedni� wersj� programu GIMP przed zainstalowaniem tej wersji w katalogu %2 lub wybra� instalacj� u�ytkownika i poda� inny katalog instalacji.%n%nInstalator zostanie zako�czony.
;couldn't find an uninstaller, or found several uninstallers
RemovingOldVersionCantUninstall=GIMP %1 nie mo�e zosta� zainstalowany w miejscu obecnie zainstalowanej wersji, a instalator nie mo�e ustali� sposobu automatycznego usuni�cia poprzedniej wersji.%n%nPrzed zainstalowaniem tej wersji w katalogu %2 prosz� usun�� poprzedni� wersj� programu GIMP i wszystkie dodatki zainstalowane przez u�ytkownika lub wybra� instalacj� u�ytkownika i poda� inny katalog instalacji.%n%nInstalator zostanie zako�czony.

RebootRequiredFirst=Pomy�lnie usuni�to poprzedni� wersj� programu GIMP, ale system Windows musi zosta� ponownie uruchomiony przed kontynuowaniem instalacji.%n%nPo ponownym uruchomieniu komputera instalator zostanie kontynuowany, kiedy administrator si� zaloguje.

;displayed if restart settings couldn't be read, or if the setup couldn't re-run itself
ErrorRestartingSetup=Wyst�pi� b��d podczas ponownego uruchamiania instalatora. (%1)

;displayed while the files are being extracted; note the capitalisation!
Billboard1=Prosimy pami�ta�: program GIMP jest wolnym oprogramowaniem.%n%nZapraszamy do odwiedzenia witryny
;www.gimp.org (displayed between Billboard1 and Billboard2)
Billboard2=zawieraj�cej darmowe aktualizacje.

SettingUpAssociations=Ustawianie powi�za� plik�w...
SettingUpPyGimp=Ustawianie �rodowiska dla rozszerzenia j�zyka Python programu GIMP...
SettingUpEnvironment=Ustawianie �rodowiska programu GIMP...
SettingUpGimpRC=Ustawianie konfiguracji programu GIMP dla obs�ugi wtyczek 32-bitowych...

;displayed on last page
LaunchGimp=Uruchomienie programu GIMP

;shown during uninstall when removing add-ons
UninstallingAddOnCaption=Usuwanie dodatku

InternalError=Wewn�trzny b��d (%1).

;used by installer for add-ons (currently only help)
DirNotGimp=Program GIMP nie jest zainstalowany w wybranym katalogu. Kontynuowa� mimo to?
