[Messages]
;InfoBefore page is used instead of license page because the GPL only concerns distribution, not use, and as such doesn't have to be accepted
WizardInfoBefore=Acuerdo de Licencia
AboutSetupNote=Instalaci�n creada por Jernej Simon�i�, jernej-gimp@ena.si%n%nImagen en la p�gina de inicio de la Instalaci�n por Alexia_Death%nImagen en la p�gina final de la Instalaci�n por Jakub Steiner
WinVersionTooLowError=Esta versi�n de GIMP requiere Windows XP con Service Pack 3, o una versi�n m�s reciente de Windows.

[CustomMessages]
;shown before the wizard starts on development versions of GIMP
DevelopmentWarningTitle=Versi�n de Desarrollo
;DevelopmentWarning=Esta es una versi�n de desarrollo de GIMP. Como tal, algunas caracter�sticas est�n incompletas y pueden ser inestables. Si usted encuentra alg�n problema, primero verifique que no haya sido solucionado en el GIT antes de contactar a los desarrolladores.%nEsta versi�n de GIMP no est� orientada a trabajo diario o a ambientes de producci�n, ya que puede ser inestable y podr�a perder su trabajo. �Desea continuar con la instalaci�n de todos modos?
DevelopmentWarning=Esta es una versi�n de desarrollo del instalador de GIMP. No ha sido probado tan profundamente como el instalador estable, lo que puede resultar en que GIMP no funcione apropiadamente. Por favor reporte cualquier problema que usted encuentre en el bugzilla de GIMP (Installer component):%n_https://bugzilla.gnome.org/enter_bug.cgi?product=GIMP%n%n�Desea continuar con la instalaci�n de todos modos?
DevelopmentButtonContinue=&Continuar
DevelopmentButtonExit=&Salir

;XPSP3Recommended=Aviso: usted est� ejecutando una versi�n no soportada de Windows. Por favor actualice al menos a Windows XP con Service Pack 3 antes de reportar alg�n problema.
SSERequired=Esta versi�n de GIMP requiere un procesador que soporte instrucciones SSE.

Require32BPPTitle=Problema con la configuraci�n de v�deo de su pantalla
Require32BPP=El instalador ha detectado que su Windows no se est� ejecutando a 32 bits por p�xel de profundidad de color. Se sabe que esto puede causar problemas de estabilidad al GIMP, por lo que se le recomienda que cambie la profundidad de color de la configuraci�n de v�deo de su pantalla a 32BPP antes de continuar.
Require32BPPContinue=&Continuar
Require32BPPExit=&Salir

InstallOrCustomize=GIMP est� listo para ser instalado. Haga clic en el bot�n Instalar para instalar usando la configuraci�n por defecto, o haga clic en el bot�n Personalizar si desea un mayor control sobre lo que va a instalar.
Install=&Instalar
Customize=&Personalizar

;setup types
TypeCompact=Instalaci�n Compacta
TypeCustom=Instalaci�n Personalizada
TypeFull=Instalaci�n Completa

;text above component description
ComponentsDescription=Descripci�n
;components
ComponentsGimp=GIMP
ComponentsGimpDescription=GIMP y todos los plug-ins por defecto
ComponentsDeps=Bibliotecas Run-time
ComponentsDepsDescription=Bibliotecas Run-time usadas por GIMP, incluyendo bibliotecas Run-time del Entorno GTK+
ComponentsGtkWimp=Motor(Engine) MS-Windows para GTK+
ComponentsGtkWimpDescription=Aspecto nativo de Windows para GIMP
ComponentsCompat=Soporte para plug-ins antiguos
ComponentsCompatDescription=Instala bibliotecas requeridas por plug-ins antiguos de terceros
ComponentsTranslations=Traducciones
ComponentsTranslationsDescription=Traducciones
ComponentsPython=Python scripting
ComponentsPythonDescription=Le permite usar plug-ins de GIMP escritos en el lenguaje interpretado Python.
ComponentsGhostscript=Soporte para PostScript
ComponentsGhostscriptDescription=Permite a GIMP abrir archivos PostScript
;only when installing on x64 Windows
ComponentsGimp32=Soporte para plug-ins de 32-bit
ComponentsGimp32Description=Incluye archivos necesarios para usar plug-ins de 32-bit.%nRequerido para soportar Python.

;additional installation tasks
AdditionalIcons=Iconos adicionales:
AdditionalIconsDesktop=Crear un icono de acceso directo en el &Escritorio
AdditionalIconsQuickLaunch=Crear un icono de acceso directo en la barra de Inicio &R�pido

RemoveOldGIMP=Elimina versi�n anterior de GIMP

;%1 is replaced by file name; these messages should never appear (unless user runs out of disk space at the exact right moment)
ErrorChangingEnviron=Ocurri� un problema al actualizar el ambiente de GIMP en %1. Si encuentra alg�n error cargando los plug-ins, pruebe desinstalar y reinstalar GIMP.
ErrorExtractingTemp=Error al extraer los archivos temporales.
ErrorUpdatingPython=Error al actualizar la informaci�n del int�rprete de Python.
ErrorReadingGimpRC=Ocurri� un problema al actualizar %1.
ErrorUpdatingGimpRC=Ocurri� un problema al actualizar el archivo de configuraci�n de GIMP %1.

;displayed in Explorer's right-click menu
OpenWithGimp=Editar con GIMP

;file associations page
SelectAssociationsCaption=Seleccione la asociaci�n de archivos
SelectAssociationsExtensions=Extensiones:
SelectAssociationsInfo1=Seleccione los tipos de archivo que desea asociar con GIMP
SelectAssociationsInfo2=Esto har� que los tipos de archivo seleccionados se abran con GIMP cuando haga doble clic sobre ellos en el Explorador.
SelectAssociationsSelectAll=Seleccionar &Todos
SelectAssociationsUnselectAll=Deseleccionar T&odos
SelectAssociationsSelectUnused=Seleccionar los no &Utilizados

;shown on summary screen just before starting the install
ReadyMemoAssociations=Tipos de archivo que se asociar�n con GIMP:

RemovingOldVersion=Eliminando versi�n anterior de GIMP:
;%1 = version, %2 = installation directory
;ran uninstaller, but it returned an error, or didn't remove everything
RemovingOldVersionFailed=GIMP %1 no se puede instalar sobre la versi�n de GIMP instalado actualmente, y la desinstalaci�n autom�tica de la versi�n antigua ha fallado.%n%nPor favor desinstale la versi�n anterior de GIMP usted mismo antes de instalar esta versi�n en %2, o seleccione Instalaci�n Personalizada y escoja otra carpeta de instalaci�n.%n%nEl instalador se cerrar� ahora.
;couldn't find an uninstaller, or found several uninstallers
RemovingOldVersionCantUninstall=GIMP %1 no se puede instalar sobre la versi�n de GIMP instalado actualmente, y el instalador no pudo determinar como eliminar la versi�n antigua autom�ticamente.%n%nPor favor desinstale la versi�n anterior de GIMP y todos sus complementos(add-ons) usted mismo antes de instalar esta versi�n en %2, o seleccione Instalaci�n Personalizada y escoja otra carpeta de instalaci�n.%n%nEl instalador se cerrar� ahora.

RebootRequiredFirst=La versi�n anterior de GIMP se elimin� satisfactoriamente, pero Windows necesita reiniciar antes de que el instalador pueda continuar.%n%nDespu�s de reiniciar su computadora, el instalador continuar� la pr�xima vez que un administrador inicie sesi�n en el sistema.

;displayed if restart settings couldn't be read, or if the setup couldn't re-run itself
ErrorRestartingSetup=Ocurri� un problema al reiniciar el instalador. (%1)

;displayed while the files are being extracted; note the capitalisation!
Billboard1=Recuerde: GIMP es Software Libre.%n%nPor favor visite
;www.gimp.org (displayed between Billboard1 and Billboard2)
Billboard2=para obtener actualizaciones gratuitas.

SettingUpAssociations=Estableciendo la asociaci�n de archivos...
SettingUpPyGimp=Estableciendo el entorno para las extensiones en Python de GIMP...
SettingUpEnvironment=Estableciendo el entorno de GIMP...
SettingUpGimpRC=Estableciendo la configuraci�n de GIMP para el soporte de plug-ins de 32-bit...

;displayed on last page
LaunchGimp=Iniciar GIMP

;shown during uninstall when removing add-ons
UninstallingAddOnCaption=Eliminando complementos(add-ons)

InternalError=Error interno (%1).

;used by installer for add-ons (currently only help)
DirNotGimp=GIMP no parece estar instalado en el directorio seleccionado. �Desea continuar de todos modos?
