
[![tag](https://img.shields.io/github/v/tag/mambaru/wfcroot.svg?sort=semver)](https://github.com/mambaru/wfcroot/tree/master)
[![Build Status](https://github.com/mambaru/wfcroot/workflows/C++%20CI/badge.svg?branch=master)](https://github.com/mambaru/wfcroot/tree/master)
[![Build Status](https://github.com/mambaru/wfcroot/workflows/C++%20CI/badge.svg?branch=mambaru)](https://github.com/mambaru/wfcroot/tree/mambaru)
[![Build Status](https://travis-ci.com/mambaru/wfcroot.svg?branch=master)](https://travis-ci.com/mambaru/wfcroot)
[![Build Status](https://travis-ci.com/mambaru/wfcroot.svg?branch=mambaru)](https://travis-ci.com/mambaru/wfcroot)
[![codecov](https://codecov.io/gh/mambaru/wfcroot/branch/master/graph/badge.svg)](https://codecov.io/gh/mambaru/wfcroot)


* Репозитарий на [github.com](https://github.com/mambaru/wfcroot).
* Документация [doxygen](https://mambaru.github.io/wfcroot/index.html).
* Отчет [coverage](https://mambaru.github.io/wfcroot/cov-report/index.html)

# Общая информация

Фреймворк позволяет за короткое время разработать высокопроизводительный демон, работающий по протоколу JSON-RPC, который может также, в асинхронном режиме, взаимодействовать с другими сервисами. Пропускная способность системы на одном хосте может достигать 100 тысяч JSON-RPC сообщений в секунду. Фреймворк избавляет программиста от необходимости взаимодействовать с сетевой подсистемой, а реализация JSON-RPC происходит на декларативном уровне, что позволяет сконцентрироваться исключительно на прикладной логике. Система конфигурации позволяет настроить демон для работы с различными профилями нагрузки. Например большие тяжелы запросы, очень много мелких запросов с коротким временем ответа или же смесь их, большой поток сообщений по одному каналу.

Большая часть функционала фремворка подключается в виде пакетов модулей. Из "коробки" [wfcroot](https://github.com/mambaru/wfcroot) вы получаете:
- [Модули ядра](https://github.com/mambaru/wfc_core):
  - *startup*
  - *config*
  - *core*
  - *logger*
  - *workflow*
- [Работа с сетью](https://github.com/mambaru/wfc_io):
  - *server-tcp*
  - *server-udp*
  - *client-tcp*
  - *io-queue*
- [Поддержка JSON-RPC](https://github.com/mambaru/wfc_jsonrpc):
  - *jsonrpc-queue
  - *jsonrpc-broker
  - *jsonrpc-repli
  - *jsonrpc-hub
  - *jsonrpc-batch
  - *jsonrpc-backlog
