#Requires -Version 5.1
<#
.SYNOPSIS
    Удаляет лишние локальные Docker-образы и опционально сжимает виртуальный диск Docker Desktop (WSL2).

.DESCRIPTION
    Скрипт рассчитан на хост с GitLab Runner под Windows 11 и Docker Desktop (бэкенд WSL2).

    Этап «образы» (по умолчанию включен):
      1) docker image prune -f — снимает висячие слои (<none>), если не задан -SkipDanglingPrune.
      2) docker images — для каждого тега сравнивается поле REPOSITORY с наборами regex: совпало — образ
         сохраняется, иначе выполняется docker rmi repo:tag.
      3) docker system df — краткая сводка по данным внутри демона Docker.

    По умолчанию сохраняются образы с REPOSITORY, похожим на официальные базы: ubuntu, debian, fedora,
    docker (включая теги dind), alpine, busybox (в т.ч. вид docker.io/library/...), а также
    registry.gitlab.com/gitlab-org/release-cli. Все остальное (частные registry, CI-образы и т.д.) удаляется.

    Ограничения: docker rmi не удалит образ, пока его использует контейнер — в консоли будет ошибка.
    Удаление образов освобождает место внутри файла docker_data.vhdx, но размер .vhdx на диске Windows
    сам не уменьшается — для этого нужен этап -CompactDockerDataVhdx.

    Этап «сжатие VHDX» (-CompactDockerDataVhdx):
      Корректно останавливает Docker Desktop, выполняет wsl --shutdown и Optimize-VHD -Mode Full для
      docker_data.vhdx, чтобы файл на NTFS стал меньше. Требует запуска PowerShell от администратора и
      установленного модуля Hyper-V (компонент Windows). После сжатия Docker Desktop нужно запустить вручную.

    Поддержка ShouldProcess: -WhatIf и -Confirm влияют на docker prune/rmi и на вызов Optimize-VHD.

.PARAMETER KeepRepositoryRegex
    Массив регулярных выражений. Если REPOSITORY образа совпадает с любым из них — образ не удаляется.
    Значения по умолчанию задают «базовые» официальные образы и GitLab release-cli.

.PARAMETER ExtraKeepPattern
    Дополнительные regex для REPOSITORY (зеркала, mcr.microsoft.com и т.д.). Объединяются с KeepRepositoryRegex.

.PARAMETER SkipDanglingPrune
    Не выполнять docker image prune -f перед перебором образов.

.PARAMETER CompactDockerDataVhdx
    После этапа образов (или вместо него при -SkipImagePrune) выполнить сжатие VHDX Docker.
    Без прав администратора этап будет пропущен с предупреждением.

.PARAMETER DockerDataVhdxPath
    Полный путь к файлу виртуального диска. По умолчанию:
    $env:LOCALAPPDATA\Docker\wsl\disk\docker_data.vhdx

.PARAMETER SkipImagePrune
    Пропустить очистку образов (docker prune/rmi/df). Имеет смысл только вместе с -CompactDockerDataVhdx,
    иначе скрипт завершится с предупреждением.

.PARAMETER DockerQuitWaitSeconds
    Максимальное время ожидания корректного выхода Docker Desktop после --quit (по умолчанию 90).

.PARAMETER WslShutdownWaitSeconds
    Пауза в секундах после wsl --shutdown перед Optimize-VHD (по умолчанию 15).

.INPUTS
    None. Параметры только из командной строки.

.OUTPUTS
    None. Информация выводится в консоль через Write-Host / Write-Warning.

.NOTES
    Имя файла: docker-prune-keep-bases.ps1
    Требования: Docker CLI в PATH; для -CompactDockerDataVhdx — админ, Hyper-V, Docker Desktop + WSL2.
    Документация (Markdown): docs/ru/CI_SCRIPTS.md и docs/en/CI_SCRIPTS.md — раздел 7 (якорь #docker-prune-runner-windows)

    Справка в консоли (из корня репозитория):
      Get-Help .\scripts\ci\docker-prune-keep-bases.ps1 -Full
      Get-Help .\scripts\ci\docker-prune-keep-bases.ps1 -Parameter CompactDockerDataVhdx

.LINK
    https://learn.microsoft.com/powershell/module/hyper-v/optimize-vhd

.EXAMPLE
    Get-Help .\scripts\ci\docker-prune-keep-bases.ps1 -Full

    Показать полную встроенную справку (из этого блока).

.EXAMPLE
    .\scripts\ci\docker-prune-keep-bases.ps1 -WhatIf

    Показать, какие образы были бы сняты (docker rmi), без удаления.

.EXAMPLE
    .\scripts\ci\docker-prune-keep-bases.ps1 -Confirm

    Запрос подтверждения перед каждым docker rmi и перед Optimize-VHD.

.EXAMPLE
    .\scripts\ci\docker-prune-keep-bases.ps1 -ExtraKeepPattern '^mcr\.microsoft\.com/'

    Дополнительно не удалять образы, чей REPOSITORY начинается с mcr.microsoft.com/

.EXAMPLE
    .\scripts\ci\docker-prune-keep-bases.ps1 -ExtraKeepPattern @('^registry\.internal\.lan/', '^public\.ecr\.aws/')

    Несколько дополнительных шаблонов «оставить».

.EXAMPLE
    .\scripts\ci\docker-prune-keep-bases.ps1 -SkipDanglingPrune

    Только снять теги по правилам, без предварительного docker image prune -f.

.EXAMPLE
    # Очистка образов и сжатие VHDX — PowerShell «От имени администратора»:
    .\scripts\ci\docker-prune-keep-bases.ps1 -CompactDockerDataVhdx

.EXAMPLE
    .\scripts\ci\docker-prune-keep-bases.ps1 -CompactDockerDataVhdx -DockerQuitWaitSeconds 120 -WslShutdownWaitSeconds 20

    Сжатие диска с увеличенными таймаутами ожидания Docker и WSL.

.EXAMPLE
    .\scripts\ci\docker-prune-keep-bases.ps1 -SkipImagePrune -CompactDockerDataVhdx

    Только сжать docker_data.vhdx (образы уже чистили вручную или ранее).
#>
[CmdletBinding(SupportsShouldProcess)]
param(
  [string[]] $KeepRepositoryRegex = @(
    '^(docker\.io/library/)?(ubuntu|debian|fedora|docker|alpine|busybox)$'
    '^registry\.gitlab\.com/gitlab-org/release-cli$'
  ),
  [string[]] $ExtraKeepPattern = @(),
  [switch] $SkipDanglingPrune,
  [switch] $CompactDockerDataVhdx,
  [string] $DockerDataVhdxPath = $(Join-Path $env:LOCALAPPDATA 'Docker\wsl\disk\docker_data.vhdx'),
  [switch] $SkipImagePrune,
  [int] $DockerQuitWaitSeconds = 90,
  [int] $WslShutdownWaitSeconds = 15
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

if ($SkipImagePrune -and -not $CompactDockerDataVhdx) {
  Write-Warning "Указан -SkipImagePrune без -CompactDockerDataVhdx — нечего выполнять."
  exit 0
}

function Test-Administrator {
  $id = [Security.Principal.WindowsIdentity]::GetCurrent()
  $p = New-Object Security.Principal.WindowsPrincipal($id)
  return $p.IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
}

function Test-KeepRepository {
  param([string] $Repository)
  foreach ($p in ($KeepRepositoryRegex + $ExtraKeepPattern)) {
    if ($Repository -match $p) { return $true }
  }
  return $false
}

function Stop-DockerDesktopForCompact {
  param([int] $MaxWaitSeconds)
  $exe = Join-Path $env:ProgramFiles 'Docker\Docker\Docker Desktop.exe'
  if (-not (Test-Path -LiteralPath $exe)) {
    Write-Warning "Не найден $exe — попытка завершить процессы Docker по имени."
  } else {
    Start-Process -FilePath $exe -ArgumentList '--quit' -WindowStyle Hidden -ErrorAction SilentlyContinue | Out-Null
  }
  $deadline = (Get-Date).AddSeconds($MaxWaitSeconds)
  while ((Get-Date) -lt $deadline) {
    $left = @(
      Get-Process -Name 'Docker Desktop' -ErrorAction SilentlyContinue
      Get-Process -Name 'com.docker.backend' -ErrorAction SilentlyContinue
    )
    if (-not $left) { return }
    Start-Sleep -Seconds 2
  }
  Write-Warning "Docker не завершился за $MaxWaitSeconds с. Принудительное завершение основных процессов."
  @('Docker Desktop', 'com.docker.backend', 'docker-desktop') | ForEach-Object {
    Get-Process -Name $_ -ErrorAction SilentlyContinue | Stop-Process -Force -ErrorAction SilentlyContinue
  }
}

function Invoke-DockerDataVhdxCompact {
  param([string] $VhdxPath)

  if (-not (Test-Administrator)) {
    Write-Warning "Сжатие VHDX пропущено: запустите PowerShell от имени администратора с -CompactDockerDataVhdx."
    return
  }

  if (-not (Test-Path -LiteralPath $VhdxPath)) {
    Write-Warning "Файл не найден: $VhdxPath — сжатие пропущено."
    return
  }

  if (-not (Get-Module -ListAvailable -Name Hyper-V)) {
    Write-Warning "Модуль Hyper-V не установлен (включите компонент Hyper-V) — Optimize-VHD недоступен. Используйте compact через diskpart вручную."
    return
  }
  Import-Module Hyper-V -ErrorAction Stop

  $before = (Get-Item -LiteralPath $VhdxPath).Length
  Write-Host "Сжатие VHDX (до: $([math]::Round($before/1GB, 2)) GiB): $VhdxPath" -ForegroundColor Yellow
  Write-Host "Будут остановлены Docker Desktop и WSL (wsl --shutdown)." -ForegroundColor Yellow

  if (-not $PSCmdlet.ShouldProcess($VhdxPath, 'Optimize-VHD (compact)')) {
    return
  }

  Stop-DockerDesktopForCompact -MaxWaitSeconds $DockerQuitWaitSeconds
  Start-Sleep -Seconds 3

  & wsl.exe --shutdown 2>&1 | ForEach-Object { Write-Host $_ }
  Start-Sleep -Seconds $WslShutdownWaitSeconds

  try {
    Optimize-VHD -Path $VhdxPath -Mode Full -ErrorAction Stop
  } catch {
    Write-Error "Optimize-VHD не удался (файл занят или нет прав). Закройте Docker вручную, выполните wsl --shutdown и повторите. Сообщение: $_"
    return
  }

  $after = (Get-Item -LiteralPath $VhdxPath).Length
  $saved = $before - $after
  Write-Host "Готово. Файл VHDX: $([math]::Round($after/1GB, 2)) GiB (освобождено на уровне файла ~ $([math]::Round($saved/1GB, 2)) GiB)." -ForegroundColor Green
  Write-Host "Запустите Docker Desktop снова вручную." -ForegroundColor Cyan
}

if (-not $SkipImagePrune) {
  if (-not (Get-Command docker -ErrorAction SilentlyContinue)) {
    Write-Error "Команда docker не найдена в PATH. Установите Docker Desktop / CLI и повторите."
  }

  Write-Host "=== docker-prune-keep-bases (образы) ===" -ForegroundColor Cyan

  if (-not $SkipDanglingPrune) {
    if ($PSCmdlet.ShouldProcess('dangling images', 'docker image prune -f')) {
      docker image prune -f
    }
  }

  $jsonLines = @(docker images --format '{{json .}}' 2>&1)
  if ($LASTEXITCODE -ne 0) {
    Write-Error "docker images завершился с ошибкой: $($jsonLines -join "`n")"
  }

  $toRemove = New-Object System.Collections.Generic.List[string]
  foreach ($line in $jsonLines) {
    if ([string]::IsNullOrWhiteSpace($line)) { continue }
    $obj = $line | ConvertFrom-Json
    $repo = [string] $obj.Repository
    $tag  = [string] $obj.Tag
    if ($repo -eq '<none>' -or $tag -eq '<none>') { continue }
    if (Test-KeepRepository -Repository $repo) { continue }
    $ref = "${repo}:${tag}"
    [void] $toRemove.Add($ref)
  }

  if ($toRemove.Count -eq 0) {
    Write-Host "Удалять нечего (все образы совпали с правилами «оставить» или список пуст)." -ForegroundColor Green
  } else {
    Write-Host "Будет снято тегов (docker rmi): $($toRemove.Count)" -ForegroundColor Yellow
    foreach ($ref in $toRemove) {
      if ($PSCmdlet.ShouldProcess($ref, 'docker rmi')) {
        docker rmi $ref 2>&1 | ForEach-Object { Write-Host $_ }
      }
    }
  }

  if (Get-Command docker -ErrorAction SilentlyContinue) {
    Write-Host "Использование данных Docker (внутри демона):" -ForegroundColor Cyan
    docker system df
  }
}

if ($CompactDockerDataVhdx) {
  Write-Host "=== docker-prune-keep-bases (сжатие docker_data.vhdx) ===" -ForegroundColor Cyan
  Invoke-DockerDataVhdxCompact -VhdxPath $DockerDataVhdxPath
}
