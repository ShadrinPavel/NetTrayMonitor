# NetTrayMonitor 🚀

*[English version below](#english-version)*

**Легковесный портабельный монитор интернет-трафика для системного трея Windows.**

## 📌 Описание
Программа создана для мониторинга **реальной** скорости интернет-соединения в реальном времени. Виджет аккуратно встраивается в панель задач (слева от системного трея) и динамически подстраивается под ширину текста.

**Версия:** 1.0.0  
**Автор:** Павел Шадрин (pavel.shadrin@gmail.com)  
**Дата создания:** 09.08.2026 г.  

## ⚙️ Особенности
*   **Минимальная нагрузка:** Нулевое потребление процессора, работа напрямую через Win32 API и GDI.
*   **Portable:** Программа не требует установки, не оставляет следов и не прописывается в системный реестр.
*   **Совместимость:** Поддержка всех разрядностей ОС Windows (x86 / x64), начиная с Windows 7 и заканчивая Windows 11.
*   **Умная фильтрация:** Отслеживает только внешний интернет-трафик (маршрут к шлюзу по умолчанию). Игнорирует внутренний локальный трафик виртуальных машин (Hyper-V, WSL 2, Docker) и петлевые интерфейсы.
*   **Сетевой стандарт (Base-10):** Автоматическое округление данных в телекоммуникационном формате (1000 Kb/s автоматически переводится в 1.0 Mb/s).
*   **Адаптивный дизайн:** Прозрачный фон, инверсия цветов в зависимости от светлой/тёмной темы ОС, динамическая ширина окна для предотвращения обрезания текста.

## ⚖️ Лицензия и Отказ от ответственности (Disclaimer)
Распространяется **бесплатно** на правах **"AS IS"** (как есть). 

> **⚠️ ВНИМАНИЕ:** Исходный код ядра программы намеренно обфусцирован (подвергнут лексическому искажению и сжатию). Это сделано для защиты логики работы программы от несанкционированного изменения. Автор не несет ответственности за любые прямые или косвенные убытки, возникшие в результате использования данной программы.

---

<a name="english-version"></a>
# NetTrayMonitor 🚀

**A lightweight, portable internet traffic monitor for the Windows system tray.**

## 📌 Description
Designed to monitor the **real** internet connection speed in real-time. The widget is neatly embedded into the taskbar (to the left of the system tray) and dynamically adjusts to the text width.

**Version:** 1.0.0  
**Author:** Pavel Shadrin (pavel.shadrin@gmail.com)  
**Date:** August 9, 2026  

## ⚙️ Features
*   **Minimal Footprint:** Zero CPU consumption, runs directly via Win32 API and GDI.
*   **Portable:** Requires no installation, leaves no traces, and makes no system registry entries.
*   **Compatibility:** Supports all Windows architectures (x86 / x64), from Windows 7 up to Windows 11.
*   **Smart Filtering:** Tracks only external internet traffic (route to the default gateway). Ignores internal local traffic from virtual machines (Hyper-V, WSL 2, Docker) and loopback interfaces.
*   **Network Standard (Base-10):** Automatic data rounding in telecommunication format (1000 Kb/s is automatically converted to 1.0 Mb/s).
*   **Adaptive Design:** Transparent background, automatic color inversion based on the OS light/dark theme, dynamic window width to prevent text clipping.

## ⚖️ License and Disclaimer
Distributed **for free** on an **"AS IS"** basis.

> **⚠️ WARNING:** The core source code of the program is intentionally obfuscated (subjected to lexical mangling and compression). This is done to protect the program's logic from unauthorized modification. The author is not liable for any direct or indirect damages arising from the use of this software.

---
*Created by Pavel Shadrin | 2026*
