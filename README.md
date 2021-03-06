# Raspberry - Synesthesia Vision
[![License](https://img.shields.io/badge/LICENSE-The%20Unlicense-green?style=flat-square)](/LICENSE)  [![Version](https://img.shields.io/badge/VERSION-DEBUG%20--%20demonstrable-yellow?style=flat-square)](https://github.com/averov90/RaspberryPi-SyneVis_Proj/releases)
### :small_orange_diamond: [English version](/README-eng.md)
Данный проект в конечном своём виде представляет из себя устройство следующей комплектации:
- Raspberry Pi (с установленным Raspbian, библиотеками, и, собственно, программой)
- Raspicam (1080p)
- Sonar sensor (HC-SR04)
- 2 кнопки
- подсветка
- вибромотор

**ВНИМАНИЕ:** Это - экспериментальный проект, создание которого было вызвано моим желанием поэкспериментировать с Google-API, Raspberry Pi, а так же некоторыми новыми для меня концепциями (например, зрение через слух). НЕ СТОИТ расценивать его как реальный прототип или практически применимое устройство! Данный девайс был создан исключительно в развлекательных целях, а область проблемы, "решаемой" устройством была выбрана исходя из компонентов, вызывавших у меня желание поэкспериментировать (тот же Google Vision API). Если вы будете внимательны, то не обнаружите, например, ни каких-либо алгоритмов анализа изображения (для определения цвета в простейшем случае было бы уместно для начала определить контуры по градиентам, а затем - оперировать с цетрами масс и площадями контуров, а так же смещением относительно центра кадра), ни нейросети (которую, кстати, в случае данного проекта, будь он и прототипом, - использовать вообще незачем). Это потому, что в данном проекте такой необходимости небыло, ведь целью было не создание прототипа, а эксперимент с компонентами, который удался.

### *Данный проект был создан на основе: [Synesthesia Vision](https://github.com/averov90/Synesthesia-Vision).*

*P.S. Сейчас уже это устройство разобрано и случилось так, что последняя версия кода осталась на нём и была утеряна после форматирования sd-карты. Это выяснилось относительно недавно. Поэтому выложенный мною код хоть и является рабочим, не является законченным в плане функциональности (совместной работы блоков), т.е. не дописан тот код, который создаёт "конечный автомат" из блоков и управляет им (кстати, дописать этот код не сложно - т.к. все принципиальные моменты уже реализованы и дописывание перешло в разряд рутинных задач). Сами же блоки в этой версии, разумеется, уже готовы. Если кого-то этот эксперимент заинтересует и он захочет дописать его до конечного состояния, буду рад принять Pull request.*
