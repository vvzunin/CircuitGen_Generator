(function () {
  "use strict";

  const I18N = {
    ru: {
      tagline: "Документация модулей проекта",
      uiLangLabel: "Язык интерфейса",
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
    },
    en: {
      tagline: "Project module documentation",
      uiLangLabel: "Interface language",
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
    },
  };

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

  function mergeCatalog(registry, manifest) {
    const deployed = new Map((manifest.modules || []).map((m) => [m.id, m]));
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
    card.innerHTML = "<h2></h2><p class=\"desc\"></p><div class=\"meta\"></div><div class=\"links\"></div>";
    card.querySelector("h2").textContent = name;
    card.querySelector(".desc").textContent = desc;

    const links = card.querySelector(".links");

    if (planned || !man) {
      const badge = document.createElement("span");
      badge.className = "badge planned";
      badge.textContent = t("planned");
      links.appendChild(badge);
      if (reg.repo) {
        const repo = document.createElement("a");
        repo.href = reg.repo;
        repo.target = "_blank";
        repo.rel = "noopener";
        repo.textContent = "GitHub";
        links.appendChild(repo);
      }
      return card;
    }

    const meta = card.querySelector(".meta");
    const parts = [];
    if (man.version) parts.push(t("version") + ": " + man.version);
    if (man.builtAt) parts.push(t("built") + ": " + man.builtAt);
    meta.textContent = parts.join(" · ");

    const fmt = man.formats || {};
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

    if (man.repo || reg.repo) {
      const repo = document.createElement("a");
      repo.href = man.repo || reg.repo;
      repo.target = "_blank";
      repo.rel = "noopener";
      repo.textContent = "GitHub";
      links.appendChild(repo);
    }

    return card;
  }

  let manifestBase = "";

  async function loadJson(url) {
    const res = await fetch(url, { cache: "no-store" });
    if (!res.ok) throw new Error(res.status + " " + url);
    return res.json();
  }

  async function init() {
    const status = document.getElementById("status");
    const grid = document.getElementById("modules");
    const updatedEl = document.getElementById("updated-at");
    const langSelect = document.getElementById("ui-lang");

    langSelect.value = uiLang;
    langSelect.addEventListener("change", () => {
      uiLang = langSelect.value;
      localStorage.setItem("circuitgen-docs-ui-lang", uiLang);
      applyUiStrings();
      init();
    });

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
      manifestBase = manifest.baseUrl || "";
      if (manifest.updatedAt) {
        updatedEl.textContent = manifest.updatedAt;
        updatedEl.dateTime = manifest.updatedAt;
      }

      const items = mergeCatalog(registry, manifest);
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
