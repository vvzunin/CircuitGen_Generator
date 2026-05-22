# Публикация документации (Synology NAS)

Этот процесс одинаков для **Graph**, **Generator** и **Parameters** (каталог `scripts/docs/` синхронизируется). В каждом репозитории задание GitLab **`docs`** выполняет `scripts/ci/docs.sh`, затем `scripts/docs/deploy-synology.sh`.

**English:** [DEPLOY.md](../en/DEPLOY.md)

## Публичный URL и структура

Портал публикуется по адресу `DOCS_PUBLIC_BASE_URL` (переменная CI, например `https://vvzunin.me/docs/CircuitGen`):

```
CircuitGen/
├── index.html, portal.js, portal.css   # UI портала (ru/en)
├── manifest.json                       # схема v2 — все модули и каналы документации
├── modules-registry.json               # каталог: репозитории, Docker, планируемые модули
└── modules/
    └── <slug>/                         # graph | generator | parameters | …
        ├── versions.json               # индекс: main + релизные теги
        └── versions/
            ├── main/                   # актуальная документация с ветки по умолчанию
            │   ├── meta.json
            │   ├── pdf/{ru,en}.pdf
            │   └── html/{ru,en}/…
            └── v1.6.0/                 # снимок с пайплайна по Git-тегу
                ├── meta.json
                └── …
```

**Устаревшая раскладка** `modules/<slug>/meta.json` (без `versions/`) портал по-прежнему читает как канал **main**.

## Каналы версий

| Пайплайн | `DOCS_VERSION_CHANNEL` | Что заменяется на NAS |
|----------|------------------------|------------------------|
| Ветка по умолчанию (`main`) | `main` | только `modules/<slug>/versions/main/` |
| Git-тег (`v1.6.0`, …) | точное имя тега | только `modules/<slug>/versions/v1.6.0/` |

Канал определяется в `scripts/docs/nas-docs-names.sh`: `resolve_docs_version_channel` использует `CI_COMMIT_TAG`, если он задан, иначе выбирает `main`.

Старые релизные деревья **не удаляются** при выкладке нового тега. `versions.json` перечисляет все известные каналы (слияние NAS + локальная стадия).

## Задание CI `docs`

**Правила** (`.gitlab-ci.yml`):

- Всегда для **Git-тегов** (полная сборка документации и деплой на NAS для этого тега).
- На **ветке по умолчанию** при срабатывании `changes:` (исходники, `scripts/docs/**`, входы Doxygen, `scripts/ci/docs.sh` и т.д.).

**Скрипты:** `bash scripts/ci/docs.sh` → `bash scripts/docs/deploy-synology.sh`.

**Артефакты:** `docs_<tag>.tar.gz` или `docs_latest.tar.gz` (локальное дерево `build/docs`; не зависит от NAS).

**Стадия release:** `release-from-tag` создаёт только GitLab Release; на NAS документацию не выкладывает.

Для локального запуска без доступа к NAS задайте `NAS_DEPLOY_STRICT=false` после сборки документации.

## Переменные CI (на репозиторий)

| Переменная | Пример (Graph) | Описание |
|------------|----------------|----------|
| `NAS_URL` | `https://vvzunin.me:5001` | Базовый URL DSM / File Station API |
| `NAS_USER`, `NAS_PASS` | *(маскируются в CI/CD)* | Учётные данные File Station |
| `NAS_DOCS` | `/volume1/web/docs/CircuitGen` | Каталог назначения на NAS |
| `NAS_DEPLOY_STRICT` | `true` в CI | Завершать задание ошибкой, если нет учётных данных |
| `DOCS_MODULE_SLUG` | `graph` | Сегмент URL под `modules/` |
| `REPO_DOCS_NAME` | `Graph` | Отображаемое имя в `meta.json` |
| `DOCS_PDF_BASE_NAME` | `CircuitGenGraph` | Базовое имя собранного PDF |
| `DOCS_PUBLIC_BASE_URL` | `https://vvzunin.me/docs/CircuitGen` | Базовый URL в `manifest.json` / портале |

В Generator: `generator` / `CircuitGenGenerator`; в Parameters: `parameters` / `CircuitGenParameters`.

## Цепочка деплоя (скрипты)

| Скрипт | Назначение |
|--------|------------|
| `deploy-synology.sh` | Оркестратор: подготовка staging-каталога → ZIP → удаление целевого канала на NAS → загрузка → распаковка → обновление файлов портала |
| `stage-module-docs.sh` | Копирование `build/docs` в `modules/<slug>/versions/<channel>/` |
| `versions-index.sh` | Слияние удалённого `versions.json` со всеми `versions/*/meta.json` в staging-каталоге |
| `manifest-merge.sh` | Сборка `manifest.json` схема v2 (`channels[]` по модулям) из стадии + соседи с NAS |
| `nas-filestation-api.sh` | Auth v3, загрузка, распаковка, обход NAS, поддержка плоского `meta.json` |
| `nas-docs-names.sh` | Slug, имя PDF, канал версии, нормализация путей |
| `build-doxygen-lang-variants.sh` | Общий драйвер Doxygen (`docs.sh` / `build-docs.sh`) |
| `modules-registry.json` | Каталог портала: репозитории [hub.mos.ru](https://hub.mos.ru), `dockerDefaults`, `releaseTag` |
| `portal/*` | Статический портал; выбор версии на карточке; `versions.json` и `meta.json` по каналам |

**Параллельный CI:** пайплайны модулей могут идти одновременно. Каждое задание заменяет только каталог своего модуля и канала, затем добавляет в `manifest.json` **соседние модули**, найденные на NAS. Так устаревший manifest не удаляет ссылки, опубликованные другим модулем.

## Портал и ссылки Docker

- Переключатель языка (ru/en) — один обработчик `change` (без дублирования карточек).
- В карточке каждого модуля есть ссылки на HTML/PDF для обоих языков и выпадающий список версий, если каналов несколько.
- **Репозитории** — из `modules-registry.json` ([hub.mos.ru](https://hub.mos.ru), не GitHub).
- **Docker** dev/release по ОС (`ubuntu-22.04`, `ubuntu-24.04`, `fedora-43`):  
  `{registryHost}/{group}/{imageRepo}/{os}/{dev|release}:{tag}` (см. `dockerDefaults` в JSON каталога).

## Локальный запуск

```bash
bash scripts/ci/docs.sh          # или scripts/dev/build-docs.sh
export NAS_DEPLOY_STRICT=false   # без NAS, если нет учётных данных
bash scripts/docs/deploy-synology.sh
```

Имитация релизного канала:

```bash
export DOCS_VERSION_CHANNEL=v1.6.0
export CI_COMMIT_TAG=v1.6.0
bash scripts/docs/deploy-synology.sh
```

## Проверка без NAS

```bash
bash scripts/ci/test_deploy_mock.sh
```

Проверяет нормализацию путей, staging-структуру (`versions/<channel>/`), слияние `versions.json` для `main` и канала тега, manifest v2 и вызов `deploy-synology.sh` в `.gitlab-ci.yml`.

## Подключение нового модуля (7+)

1. Добавьте запись в `scripts/docs/modules-registry.json` (один и тот же файл хранится во всех репозиториях).
2. Задайте `DOCS_MODULE_SLUG`, `REPO_DOCS_NAME` и `DOCS_PDF_BASE_NAME` в задании `docs` в `.gitlab-ci.yml`.
3. Тот же `scripts/docs/deploy-synology.sh` (пути менять не нужно).

## См. также

- [SCRIPTS.md](SCRIPTS.md) — обзор каталогов и скриптов  
- [CI_SCRIPTS.md](CI_SCRIPTS.md) — `docs.sh` и NAS (§7)  
- [CI_PIPELINE.md](CI_PIPELINE.md) — правила стадии `docs`  
