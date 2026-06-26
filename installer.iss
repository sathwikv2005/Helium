#define VersionFile FileOpen("VERSION")
#define MyAppVersion Trim(FileRead(VersionFile))
#expr FileClose(VersionFile)

#define MyAppName "Helium"
#define MyAppPublisher "Sathwik Vemula"

[Setup]
AppId={{C8E1C7A2-9D62-4A6F-BE8E-7D6E7A1E6F01}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}

DefaultDirName={autopf}\Helium
DefaultGroupName=Helium

OutputDir=release
OutputBaseFilename=Helium-v{#MyAppVersion}-Setup

Compression=lzma2
SolidCompression=yes
WizardStyle=modern

ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible

UninstallDisplayIcon={app}\helium.exe

[Tasks]
Name: "addtopath"; Description: "Add Helium to PATH"; Flags: checkedonce
Name: "desktopicon"; Description: "Create a desktop shortcut"

[Files]
Source: "dist\helium.exe"; DestDir: "{app}"; Flags: ignoreversion

; Source: "stdlib\*"; DestDir: "{app}\stdlib"; Flags: ignoreversion recursesubdirs createallsubdirs
; Source: "examples\*"; DestDir: "{app}\examples"; Flags: ignoreversion recursesubdirs createallsubdirs

Source: "he.bat"; DestDir: "{app}"; Flags: ignoreversion
Source: "LICENSE.md"; DestDir: "{app}"; Flags: ignoreversion
Source: "README.md"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Helium"; Filename: "{app}\helium.exe"
Name: "{group}\Uninstall Helium"; Filename: "{uninstallexe}"
Name: "{autodesktop}\Helium"; Filename: "{app}\helium.exe"; Tasks: desktopicon

[Code]

const
  EnvironmentKey = 'Environment';

procedure AddPath(Path: string);
var
  Paths: string;
begin
  if not RegQueryStringValue(HKEY_CURRENT_USER, EnvironmentKey, 'Path', Paths) then
    Paths := '';

  if Pos(';' + UpperCase(Path) + ';', ';' + UpperCase(Paths) + ';') = 0 then
  begin
    if (Paths <> '') and (Paths[Length(Paths)] <> ';') then
      Paths := Paths + ';';

    Paths := Paths + Path;
    RegWriteStringValue(HKEY_CURRENT_USER, EnvironmentKey, 'Path', Paths);
  end;
end;

procedure RemovePath(Path: string);
var
  Paths: string;
  Search: string;
  P: Integer;
begin
  if RegQueryStringValue(HKEY_CURRENT_USER, EnvironmentKey, 'Path', Paths) then
  begin
    Search := ';' + UpperCase(Path);
    P := Pos(Search, ';' + UpperCase(Paths));

    if P > 0 then
    begin
      Delete(Paths, P, Length(Path) + 1);
      RegWriteStringValue(HKEY_CURRENT_USER, EnvironmentKey, 'Path', Paths);
    end;
  end;
end;

procedure RefreshEnvironment;
var
  ResultCode: Integer;
begin
  Exec(
    ExpandConstant('{sys}\setx.exe'),
    'HELIUM_REFRESH 1',
    '',
    SW_HIDE,
    ewWaitUntilTerminated,
    ResultCode
  );
end;

procedure CurStepChanged(CurStep: TSetupStep);
begin
  if (CurStep = ssPostInstall) and WizardIsTaskSelected('addtopath') then
  begin
    AddPath(ExpandConstant('{app}'));
    RefreshEnvironment;
  end;
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
begin
  if CurUninstallStep = usPostUninstall then
  begin
    RemovePath(ExpandConstant('{app}'));
    RefreshEnvironment;
  end;
end;