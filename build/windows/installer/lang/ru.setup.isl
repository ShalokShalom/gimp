[Messages]
;InfoBefore page is used instead of license page because the GPL only concerns distribution, not use, and as such doesn't have to be accepted
WizardInfoBefore=������������ ����������
AboutSetupNote=��������� ������ ��������� Jernej Simoncic, jernej-gimp@ena.si%n%n����� ����������� � ������ ��������� Alexia_Death%n����� ����������� � ����� ��������� Jakub Steiner
WinVersionTooLowError=��� ���� ������ GIMP ��������� Windows XP � ������� ���������� 3 (Service Pack 3), ��� ����� ����������� ������ Windows.

[CustomMessages]
;shown before the wizard starts on development versions of GIMP
DevelopmentWarningTitle=��������������� ������
;DevelopmentWarning=��� ��������������� ������ GIMP. ��������� ������� �� ��������, � ��� ����� �������� �����������. ���� � ��� ��������� �����-���� ��������, ������� ���������, ��� ��� ��� �� ���� ���������� � GIT, ������ ��� ��������� � ��������������.%n��� ������ GIMP �� ������������� ��� ������������ ������, ��� ��� ��� ����� �������� �����������, � �� ������ �������� ���� ������. �� ������ ���������� ���������?
DevelopmentWarning=��� ��������������� ������ GIMP. ��� �� ���� �������������� ��� ��, ��� ���������� ������, � ���������� GIMP ����� �� �������� ������� �������. ������ ��� �������� � ��������� ��������� � GIMP bugzilla (��������� Installer):%n_https://bugzilla.gnome.org/enter_bug.cgi?product=GIMP%n%n�� ������ ���������� ���������?
DevelopmentButtonContinue=&�����
DevelopmentButtonExit=&�����

;XPSP3Recommended=��������: �� ����������� ���������������� ������ Windows. ����������, �������� � �� Windows XP � ������� ���������� 3 (Service Pack 3), ������ ��� �������� � ���������.
SSERequired=���� ������ GIMP ��������� ��������� � ���������� ���������� SSE.

Require32BPPTitle=�������� � ����������� �������
Require32BPP=��������� ��������� ����������, ��� ���� Windows ������ �������� � ��������� ������������� �� 32 ����. ��������, ��� ��� ����� ������� ������������ ������ GIMP, ������� ������������� ������� �������� ������������� �� 32 ���� � ���������� �������, ������ ��� ����������.
Require32BPPContinue=&�����
Require32BPPExit=&�����

InstallOrCustomize=GIMP ����� � ���������. ������� ���������� ��� ��������� � ����������� �� ���������, ��� ��������� ��� ������ �����������.
Install=&����������
Customize=&���������

;setup types
TypeCompact=���������� ���������
TypeCustom=���������� ���������
TypeFull=������ ���������

;text above component description
ComponentsDescription=��������
;components
ComponentsGimp=GIMP
ComponentsGimpDescription=GIMP � ��� ����������� �������
ComponentsDeps=���������� ������� ����������
ComponentsDepsDescription=���������� ������� ���������� ��� GIMP, ������� ��������� ������� ���������� GTK+
ComponentsGtkWimp=������ MS-Windows ��� GTK+
ComponentsGtkWimpDescription=��������������� ������� ��� ��� GIMP
ComponentsCompat=��������� ������ ��������
ComponentsCompatDescription=��������� ���������, ����������� ��� ������ ��������� ��������
ComponentsTranslations=�����������
ComponentsTranslationsDescription=�����������
ComponentsPython=������������� �� Python
ComponentsPythonDescription=������������ ������ �������� GIMP, ���������� �� ����� Python.
ComponentsGhostscript=��������� PostScript
ComponentsGhostscriptDescription=������������ �������� ������ PostScript � GIMP
;only when installing on x64 Windows
ComponentsGimp32=��������� 32-������ ��������
ComponentsGimp32Description=�������� �����, ����������� ��� ������������� 32-������ ��������.%n���������� ��� ��������� Python.

;additional installation tasks
AdditionalIcons=�������������� ������:
AdditionalIconsDesktop=������� ������ �� &������� �����
AdditionalIconsQuickLaunch=������� ������ � &������ �������� �������

RemoveOldGIMP=������� ���������� ������ GIMP

;%1 is replaced by file name; these messages should never appear (unless user runs out of disk space at the exact right moment)
ErrorChangingEnviron=�������� �������� ��� ���������� ��������� GIMP � %1. ���� �� �������� ������ ��� �������� ��������, ���������� ������� � ������ ���������� GIMP.
ErrorExtractingTemp=������ ��� ���������� ��������� ������.
ErrorUpdatingPython=������ ���������� ���������� �������������� Python.
ErrorReadingGimpRC=�������� ������ ��� ���������� %1.
ErrorUpdatingGimpRC=�������� ������ ��� ���������� ����� �������� GIMP %1.

;displayed in Explorer's right-click menu
OpenWithGimp=�������� � GIMP

;file associations page
SelectAssociationsCaption=����� �������� ����������
SelectAssociationsExtensions=����������:
SelectAssociationsInfo1=�������� ���� ������, ������� ����� ������������� � GIMP
SelectAssociationsInfo2=��� �������� ��������� ��������� ����� � GIMP �� �������� ������ � ����������.
SelectAssociationsSelectAll=&������� ���
SelectAssociationsUnselectAll=&����� ���
SelectAssociationsSelectUnused=������� &��������������

;shown on summary screen just before starting the install
ReadyMemoAssociations=���� ������, ������� ����� ������������� � GIMP:

RemovingOldVersion=�������� ���������� ������ GIMP:
;%1 = version, %2 = installation directory
;ran uninstaller, but it returned an error, or didn't remove everything
RemovingOldVersionFailed=GIMP %1 �� ����� ���� ���������� ������ ��� ������������� ������ GIMP, � �������������� �������� ������ ������ �� �������.%n%n����������, ������� ���������� ������ GIMP �������, ������ ��� ������������� ��� ������ � %2, ��� ������� ��������� � ������, � �������� ������ ����� ��� ���������.%n%n������ ��������� ����� ��������.
;couldn't find an uninstaller, or found several uninstallers
RemovingOldVersionCantUninstall=GIMP %1 �� ����� ���� ���������� ������ ��� ������������� ������ GIMP, � ��������� ��������� �� ����� ����������, ��� ������� ���������� ������ �������������.%n%n����������, ������� ���������� ������ GIMP � ��� ���������� �������, ������ ��� ������������� ��� ������ � %2, ��� ������� ��������� � ������, � �������� ������ ����� ��� ���������.%n%n������ ��������� ����� ��������.

RebootRequiredFirst=���������� ������ GIMP ������� �������, �� ���������� ������������� Windows ����� ������������ ���������.%n%n����� ������������ ���������� ��������� ����� ����������, ��� ������ ����� ������������ � ������� �������������� ����� � �������.

;displayed if restart settings couldn't be read, or if the setup couldn't re-run itself
ErrorRestartingSetup=�������� ������ ��� ����������� ��������� ���������. (%1)

;displayed while the files are being extracted; note the capitalisation!
Billboard1=�������: GIMP �������� ��������� ����������� ������������.%n%n����������, ��������
;www.gimp.org (displayed between Billboard1 and Billboard2)
Billboard2=��� ���������� ����������.

SettingUpAssociations=��������� �������� ����������...
SettingUpPyGimp=��������� ��������� ��� ���������� GIMP Python...
SettingUpEnvironment=��������� ��������� GIMP...
SettingUpGimpRC=��������� �������� GIMP ��� ��������� 32-������ ��������...

;displayed on last page
LaunchGimp=��������� GIMP

;shown during uninstall when removing add-ons
UninstallingAddOnCaption=�������� ����������

InternalError=���������� ������ (%1).

;used by installer for add-ons (currently only help)
DirNotGimp=�������, GIMP �� ��� ���������� � ��������� �������. �� ����� ����������?
