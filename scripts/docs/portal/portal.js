(function () {
  "use strict";

  const I18N = {
    ru: {
      tagline: "Документация модулей проекта",
      uiLangLabel: "Язык интерфейса",
      docsVersionLabel: "Версия документации",
      updated: "Обновлено",
      loading: "Загрузка каталога…",
      loadError: "Не удалось загрузить manifest.json",
      planned: "Скоро",
      pdfRu: "PDF (RU)",
      pdfEn: "PDF (EN)",
      htmlRu: "HTML (RU)",
      htmlEn: "HTML (EN)",
      version: "Версия",
      built: "Сборка",
      repoLink: "Репозиторий",
      dockerDev: "Docker dev",
      dockerRelease: "Docker release",
      channelMain: "main (ветка)",
      channelRelease: "релиз",
    },
    en: {
      tagline: "Project module documentation",
      uiLangLabel: "Interface language",
      docsVersionLabel: "Documentation version",
      updated: "Updated",
      loading: "Loading catalog…",
      loadError: "Failed to load manifest.json",
      planned: "Coming soon",
      pdfRu: "PDF (RU)",
      pdfEn: "PDF (EN)",
      htmlRu: "HTML (RU)",
      htmlEn: "HTML (EN)",
      version: "Version",
      built: "Built",
      repoLink: "Repository",
      dockerDev: "Docker dev",
      dockerRelease: "Docker release",
      channelMain: "main (branch)",
      channelRelease: "release",
    },
  };

  let catalogRegistry = null;
  let manifestBase = "";

  const langSelect = document.getElementById("ui-lang");
  langSelect.addEventListener("change", () => {
    uiLang = langSelect.value;
    localStorage.setItem("circuitgen-docs-ui-lang", uiLang);
    init();
  });

  let uiLang = localStorage.getItem("circuitgen-docs-ui-lang") || "ru";

  function t(key) {
    return (I18N[uiLang] && I18N[uiLang][key]) || I18N.en[key] || key;
  }

  function applyUiStrings() {
    document.documentElement.lang = uiLang;
    document.querySelectorAll("[data-i18n]").forEach((el) => {
      const key = el.getAttribute("data-i18n");
      if (key) el.textContent = t(key);
    });
  }

  function absUrl(baseUrl, rel) {
    if (!rel) return null;
    const base = (baseUrl || "").replace(/\/$/, "");
    const path = String(rel).replace(/^\//, "");
    return base ? base + "/" + path : path;
  }

  function channelFromMeta(meta, channelId) {
    const base = "modules/" + meta.id + "/versions/" + channelId;
    return {
      id: channelId,
      kind: meta.docsKind || (channelId === "main" ? "branch" : "release"),
      label: meta.docsLabel || channelId,
      version: meta.version,
      builtAt: meta.builtAt,
      commit: meta.commit,
      ref: meta.ref,
      formats: {
        pdf: {
          ru: base + "/pdf/ru.pdf",
          en: base + "/pdf/en.pdf",
        },
        html: {
          ru: base + "/html/ru/",
          en: base + "/html/en/",
        },
      },
    };
  }

  function legacyChannelFromModule(man) {
    const base = man.basePath || "modules/" + man.id;
    return {
      id: "main",
      kind: "branch",
      label: "main",
      version: man.version,
      builtAt: man.builtAt,
      formats: man.formats || {},
    };
  }

  function normalizeModule(man) {
    if (!man) return null;
    if (Array.isArray(man.channels) && man.channels.length > 0) {
      return {
        id: man.id,
        name: man.name,
        repo: man.repo,
        docker: man.docker,
        defaultChannel: man.defaultChannel || man.channels[0].id,
        channels: man.channels,
      };
    }
    return {
      id: man.id,
      name: man.name,
      repo: man.repo,
      docker: man.docker,
      defaultChannel: "main",
      channels: [legacyChannelFromModule(man)],
    };
  }

  function channelLabel(ch) {
    if (ch.kind === "branch" || ch.id === "main") {
      return ch.label || t("channelMain");
    }
    return (ch.label || ch.id) + " (" + t("channelRelease") + ")";
  }

  function mergeManifestWithDeployed(registry, manifest, deployedById) {
    const byId = new Map();
    deployedById.forEach((entry, id) => {
      byId.set(id, normalizeModule(entry));
    });
    (manifest.modules || []).forEach((m) => {
      const norm = normalizeModule(m);
      if (!norm) return;
      if (byId.has(norm.id)) {
        const disk = byId.get(norm.id);
        const chMap = new Map();
        (disk.channels || []).forEach((c) => chMap.set(c.id, c));
        (norm.channels || []).forEach((c) => chMap.set(c.id, Object.assign({}, chMap.get(c.id), c)));
        norm.channels = [...chMap.values()].sort((a, b) => a.id.localeCompare(b.id));
        byId.set(norm.id, Object.assign({}, disk, norm, { channels: norm.channels }));
      } else {
        byId.set(norm.id, norm);
      }
    });
    const order = (registry.modules || []).map((m) => m.id);
    const extra = [...byId.keys()].filter((id) => !order.includes(id));
    const modules = [...order, ...extra].map((id) => byId.get(id)).filter(Boolean);
    return Object.assign({}, manifest, { modules: modules });
  }

  const DEFAULT_DOCKER_OS_LIST = ["ubuntu-22.04", "ubuntu-24.04", "fedora-43"];

  function normalizeReleaseTag(version, explicitTag) {
    if (explicitTag) {
      return String(explicitTag).startsWith("v") ? explicitTag : "v" + explicitTag;
    }
    if (!version) return "latest";
    return String(version).startsWith("v") ? version : "v" + version;
  }

  function resolveDockerImageLinks(reg, man, registry, channelId) {
    const channel = (man && man.channels || []).find((c) => c.id === channelId);
    const releaseTag = channel && channel.id !== "main" ? channel.id : null;

    if (man && man.docker && Array.isArray(man.docker.images) && man.docker.images.length) {
      return man.docker.images.flatMap(function (img) {
        return [
          { os: img.os, flavor: "dev", pull: img.dev && img.dev.pull, harborUrl: img.dev && img.dev.harborUrl },
          {
            os: img.os,
            flavor: "release",
            pull: img.release && img.release.pull,
            harborUrl: img.release && img.release.harborUrl,
          },
        ];
      }).filter(function (e) {
        return e.pull;
      });
    }

    const d = Object.assign({}, registry.dockerDefaults || {}, reg.docker || {});
    if (!d.imageRepo) return [];

    const host = d.registryHost || "vvzunin.me:5201";
    const group = d.group || "circuitgen";
    const osList = d.osList || DEFAULT_DOCKER_OS_LIST;
    const devTag = d.devTag || "main";
    const relTag = normalizeReleaseTag(channel && channel.version, releaseTag || d.releaseTag);
    const harborBase = (d.harborWebBase || "").replace(/\/$/, "");

    return osList.flatMap(function (os) {
      function entry(flavor, tag) {
        const pull = host + "/" + group + "/" + d.imageRepo + "/" + os + "/" + flavor + ":" + tag;
        const harborUrl = harborBase
          ? harborBase + "/" + encodeURIComponent(d.imageRepo + "/" + os + "/" + flavor) + "/artifacts-tab"
          : null;
        return { os: os, flavor: flavor, pull: pull, harborUrl: harborUrl };
      }
      return [entry("dev", devTag), entry("release", relTag)];
    });
  }

  function appendDockerLinks(links, reg, man, registry, channelId) {
    resolveDockerImageLinks(reg, man, registry, channelId).forEach(function (entry) {
      const a = document.createElement("a");
      a.className = "docker";
      const flavorLabel = entry.flavor === "dev" ? t("dockerDev") : t("dockerRelease");
      a.textContent = flavorLabel + " (" + entry.os + ")";
      if (entry.harborUrl) {
        a.href = entry.harborUrl;
        a.target = "_blank";
        a.rel = "noopener";
      }
      if (entry.pull) a.title = "docker pull " + entry.pull;
      links.appendChild(a);
    });
  }

  function appendDocLinks(links, channel) {
    const fmt = channel.formats || {};
    const pairs = [
      ["pdfRu", fmt.pdf && fmt.pdf.ru],
      ["pdfEn", fmt.pdf && fmt.pdf.en],
      ["htmlRu", fmt.html && fmt.html.ru],
      ["htmlEn", fmt.html && fmt.html.en],
    ];
    pairs.forEach(([labelKey, rel]) => {
      const href = absUrl(manifestBase, rel);
      if (!href) return;
      const a = document.createElement("a");
      a.href = href;
      a.textContent = t(labelKey);
      if (labelKey.startsWith("html")) a.target = "_blank";
      links.appendChild(a);
    });
  }

  function mergeCatalog(registry, manifest) {
    const deployed = new Map((manifest.modules || []).map((m) => [m.id, normalizeModule(m)]));
    const order = (registry.modules || []).map((m) => m.id);
    const extra = (manifest.modules || [])
      .filter((m) => !order.includes(m.id))
      .map((m) => m.id);
    const ids = [...order, ...extra];

    return ids.map((id) => {
      const reg = (registry.modules || []).find((m) => m.id === id) || { id };
      const man = deployed.get(id);
      const planned = reg.planned === true && !man;
      return { reg, man, planned };
    });
  }

  function renderCardContent(card, item, selectedChannelId) {
    const { reg, man, planned } = item;
    const links = card.querySelector(".links");
    const meta = card.querySelector(".meta");
    const versionRow = card.querySelector(".version-row");
    links.innerHTML = "";
    versionRow.innerHTML = "";

    if (planned || !man || !man.channels || man.channels.length === 0) {
      versionRow.hidden = true;
      const badge = document.createElement("span");
      badge.className = "badge planned";
      badge.textContent = t("planned");
      links.appendChild(badge);
      if (reg.repo) {
        const repo = document.createElement("a");
        repo.href = reg.repo;
        repo.target = "_blank";
        repo.rel = "noopener";
        repo.textContent = t("repoLink");
        links.appendChild(repo);
      }
      if (catalogRegistry) appendDockerLinks(links, reg, man, catalogRegistry, "main");
      return;
    }

    let channelId = selectedChannelId || man.defaultChannel || man.channels[0].id;
    let channel = man.channels.find((c) => c.id === channelId);
    if (!channel) {
      channelId = man.channels[0].id;
      channel = man.channels[0];
    }

    if (man.channels.length > 1) {
      versionRow.hidden = false;
      const label = document.createElement("label");
      label.setAttribute("for", "doc-ver-" + man.id);
      label.textContent = t("docsVersionLabel") + ": ";
      const select = document.createElement("select");
      select.id = "doc-ver-" + man.id;
      select.className = "doc-version-select";
      man.channels.forEach((ch) => {
        const opt = document.createElement("option");
        opt.value = ch.id;
        opt.textContent = channelLabel(ch);
        if (ch.id === channelId) opt.selected = true;
        select.appendChild(opt);
      });
      select.addEventListener("change", () => {
        card.dataset.selectedChannel = select.value;
        renderCardContent(card, item, select.value);
      });
      versionRow.appendChild(label);
      versionRow.appendChild(select);
    } else {
      versionRow.hidden = true;
    }

    const parts = [];
    if (channel.version) parts.push(t("version") + ": " + channel.version);
    if (channel.builtAt) parts.push(t("built") + ": " + channel.builtAt);
    meta.textContent = parts.join(" · ");

    appendDocLinks(links, channel);

    const repoUrl = reg.repo || man.repo;
    if (repoUrl) {
      const repo = document.createElement("a");
      repo.href = repoUrl;
      repo.target = "_blank";
      repo.rel = "noopener";
      repo.textContent = t("repoLink");
      links.appendChild(repo);
    }

    if (catalogRegistry) appendDockerLinks(links, reg, man, catalogRegistry, channelId);
  }

  function formatCard(item) {
    const { reg, man, planned } = item;
    const name =
      (reg.name && (reg.name[uiLang] || reg.name.en || reg.name.ru)) ||
      (man && man.name && (man.name[uiLang] || man.name.en)) ||
      reg.id;
    const desc =
      (reg.description &&
        (reg.description[uiLang] || reg.description.en || reg.description.ru)) ||
      "";

    const card = document.createElement("article");
    card.className = "module-card" + (planned ? " planned" : "");
    card.innerHTML =
      '<h2></h2><p class="desc"></p><div class="version-row" hidden></div><div class="meta"></div><div class="links"></div>';
    card.querySelector("h2").textContent = name;
    card.querySelector(".desc").textContent = desc;

    if (man && man.defaultChannel) {
      card.dataset.selectedChannel = man.defaultChannel;
    }

    renderCardContent(card, item, card.dataset.selectedChannel);
    return card;
  }

  async function loadJson(url) {
    const res = await fetch(url, { cache: "no-store" });
    if (!res.ok) throw new Error(res.status + " " + url);
    return res.json();
  }

  async function discoverModule(reg) {
    const id = reg.id;

    try {
      const vindex = await loadJson("modules/" + id + "/versions.json");
      const channels = [];
      let firstMeta = null;
      for (const ch of vindex.channels || []) {
        try {
          const meta = await loadJson("modules/" + id + "/versions/" + ch.id + "/meta.json");
          if (!firstMeta) firstMeta = meta;
          channels.push(channelFromMeta(meta, ch.id));
        } catch (_err) {
          /* channel tree missing on disk */
        }
      }
      if (channels.length > 0) {
        return {
          id: id,
          name: (firstMeta && firstMeta.name) || reg.name,
          repo: (firstMeta && firstMeta.repo) || reg.repo,
          docker: firstMeta && firstMeta.docker,
          defaultChannel: vindex.defaultChannel || "main",
          channels: channels,
        };
      }
    } catch (_err) {
      /* no versions.json */
    }

    try {
      const meta = await loadJson("modules/" + id + "/meta.json");
      if (meta.docsChannel) {
        return {
          id: id,
          name: meta.name || reg.name,
          repo: meta.repo || reg.repo,
          docker: meta.docker,
          defaultChannel: meta.docsChannel,
          channels: [channelFromMeta(meta, meta.docsChannel)],
        };
      }
      return normalizeModule({
        id: meta.id,
        name: meta.name,
        repo: meta.repo,
        docker: meta.docker,
        version: meta.version,
        builtAt: meta.builtAt,
        basePath: "modules/" + id,
        formats: {
          pdf: {
            ru: "modules/" + id + "/" + meta.formats.pdf.ru,
            en: "modules/" + id + "/" + meta.formats.pdf.en,
          },
          html: {
            ru: "modules/" + id + "/" + meta.formats.html.ru,
            en: "modules/" + id + "/" + meta.formats.html.en,
          },
        },
      });
    } catch (_err) {
      return null;
    }
  }

  async function discoverDeployedModules(registry) {
    const byId = new Map();
    await Promise.all(
      (registry.modules || []).map(async (reg) => {
        const mod = await discoverModule(reg);
        if (mod) byId.set(reg.id, mod);
      })
    );
    return byId;
  }

  async function init() {
    const status = document.getElementById("status");
    const grid = document.getElementById("modules");
    const updatedEl = document.getElementById("updated-at");
    langSelect.value = uiLang;
    applyUiStrings();
    status.textContent = t("loading");
    status.className = "status";
    grid.hidden = true;
    grid.innerHTML = "";

    try {
      const [registry, manifest] = await Promise.all([
        loadJson("modules-registry.json"),
        loadJson("manifest.json"),
      ]);
      catalogRegistry = registry;
      const deployedById = await discoverDeployedModules(registry);
      const effectiveManifest = mergeManifestWithDeployed(registry, manifest, deployedById);

      manifestBase = effectiveManifest.baseUrl || manifest.baseUrl || "";
      if (effectiveManifest.updatedAt) {
        updatedEl.textContent = effectiveManifest.updatedAt;
        updatedEl.dateTime = effectiveManifest.updatedAt;
      }

      const items = mergeCatalog(registry, effectiveManifest);
      items.forEach((item) => grid.appendChild(formatCard(item)));
      status.hidden = true;
      grid.hidden = false;
    } catch (err) {
      console.error(err);
      status.textContent = t("loadError");
      status.className = "status error";
    }
  }

  init();
})();
