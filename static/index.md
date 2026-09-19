# О проекте

Прошивка [ESPHome](https://esphome.io) для ESP8266 (D1 mini): шлюз между Home Assistant и контроллером умного дома по UART. Управляет освещением и водяным клапаном и получает от контроллера их состояние.

Исходный код и описание протокола — в [репозитории на GitHub](https://github.com/vaninanton/esphome-gauhartas204).

# Установка

Кнопка ниже устанавливает последнюю версию прошивки на устройство по USB прямо из браузера (Chrome или Edge на компьютере).

<esp-web-install-button manifest="manifest.json"></esp-web-install-button>

<script type="module" src="https://unpkg.com/esp-web-tools@10/dist/web/install-button.js?module"></script>

После установки устройство поднимет точку доступа для настройки Wi‑Fi. Дальнейшие обновления приходят по воздуху: Home Assistant покажет их в карточке устройства.
