param (
    [Parameter(Mandatory=$true, HelpMessage="Введите версию (например: 1.3.0)")]
    [string]$NewVersion,
    [Parameter(Mandatory=$false)]
    [string]$ReleaseNotes = "Автоматический релиз Монитора с исправлениями и улучшениями."
)
Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'
$baseDir = $PSScriptRoot
$exePath = "C:\PORTABLE\NetTrayMonitor\NetTrayMonitor.exe"
$newZipPath = Join-Path $baseDir "NetTrayMonitor_v${NewVersion}.zip"
$stageDir = Join-Path $baseDir "stage_zip"
$ghExe = "c:\PORTABLE\GitHub_CLI\gh.exe"

Write-Host "========================================" -ForegroundColor Cyan
Write-Host " STARTING AUTOMATED RELEASE v$NewVersion" -ForegroundColor Cyan
Write-Host "========================================" -ForegroundColor Cyan

Write-Host "[1/4] Упаковка портативного ZIP-архива..."
if (Test-Path $newZipPath) { Remove-Item $newZipPath -Force }
if (Test-Path $stageDir) { Remove-Item $stageDir -Recurse -Force }
New-Item -Type Directory -Path $stageDir | Out-Null
Copy-Item $exePath -Destination $stageDir
if (Test-Path "$baseDir\README.md") { Copy-Item "$baseDir\README.md" -Destination $stageDir }
if (Test-Path "$baseDir\LICENSE") { Copy-Item "$baseDir\LICENSE" -Destination $stageDir }
Compress-Archive -Path "$stageDir\*" -DestinationPath $newZipPath -Force
Remove-Item $stageDir -Recurse -Force

Write-Host "[2/4] Фиксация изменений в Git..."
Set-Location $baseDir
& git add .
$ErrorActionPreference = 'Continue'
$gitStatus = & git status --porcelain
$ErrorActionPreference = 'Stop'
if (-not [string]::IsNullOrWhiteSpace($gitStatus)) {
    & git commit -m "Release v$NewVersion" | Out-Null
}

Write-Host "[3/4] Отправка (Push) на GitHub..."
$ErrorActionPreference = 'Continue'
& git push origin main 2>&1 | Out-Null
$ErrorActionPreference = 'Stop'

Write-Host "[4/4] Создание релиза на GitHub..."
$notesFile = Join-Path $baseDir "temp_notes.txt"
[System.IO.File]::WriteAllText($notesFile, $ReleaseNotes, [System.Text.Encoding]::UTF8)
$ErrorActionPreference = 'Continue'
& $ghExe release create "v$NewVersion" $newZipPath --title "NetTrayMonitor v$NewVersion" --notes-file $notesFile 2>&1 | Out-Null
$ErrorActionPreference = 'Stop'
Remove-Item $notesFile -Force

Write-Host "========================================" -ForegroundColor Green
Write-Host " SUCCESS: Релиз v$NewVersion успешно опубликован!" -ForegroundColor Green
Write-Host "========================================" -ForegroundColor Green
Write-Host "Нажмите любую клавишу для выхода..."
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")

