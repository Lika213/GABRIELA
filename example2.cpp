﻿                                         
#include "G4RunManager.hh" // RunManager, класс из ядра Geant4,
//должен быть включен обязательно
#include "G4UImanager.hh" // Менеджер взаимодействия с пользователем
#include "ExG4DetectorConstruction01.hh" // Конструкция и структура детектора,
//должна определяться пользователем
#include "ExG4PhysicsList.hh" 
#include "FTFP_BERT.hh"// Подключение физического листа из Geant4, где определяется
// используемые физические процессы и частицы
#include "ExG4ActionInitialization01.hh" // Пользовательский класс
//для задания начального источника частиц
//Если используется интерфейс пользователя то включаем визуализацию
#include "G4VisExecutive.hh"//Визуализация
#include "G4UIExecutive.hh"//Выбор соответствующего интерфейса пользователя


int main(int argc,char** argv)
{
// Создание класса G4RunManager, он контролирует выполнение программы и
// управляет событиями (запуском начальных частиц) при запуске проекта
G4RunManager* runManager = new G4RunManager;
// Установка обязательных инициализирующих классов
// Создание геометрии, материала детектора и мишени
// т.е. моделируемой установки
runManager->SetUserInitialization(new ExG4DetectorConstruction01);
// Создание физического листа - набора моделируемых частиц и физических процессов
// которые используются в данном моделировании.
// Используется готовый физический лист из Geant4
runManager->SetUserInitialization(new ExG4PhysicsList);
// Объявление начальных частиц (параметры пучка) и
// подключение прочих классов, используемых
// для получения данных о частицах в процессе моделирования
runManager->SetUserInitialization(new ExG4ActionInitialization01);
// Инициализация ядра Geant4
runManager->Initialize();
// Объявления менеджера визуализации
//G4VisManager* visManager = new G4VisExecutive;
// Инициализация менеджера визуализации
//visManager->Initialize();
// Получение указателя на менеджера взаимодействия с пользователем
// нужен, что бы можно было отправлять команды в проект
G4UImanager* UImanager = G4UImanager::GetUIpointer();
// Проверяем или были переданы через командную сроку параметры
if ( argc == 1 ) {//Если через командную строку ничего не передавалось
// То устанавливаем  интерактивный режим

G4UIExecutive* ui = new G4UIExecutive(argc, argv);//Создание интерфейса пользователя
UImanager->ApplyCommand("/control/execute vis.mac");
//Параметры отображения берем из заранее подготовленного
// файла vis.mac
ui->SessionStart();//Запуск интерфейса пользователя
delete ui;//Удаление интерфейса пользователя

}
else {
// Если были переданы параметры, по включаем пакетный режим
G4String command = "/control/execute ";//Записываем в строковую переменную
// команду выполнить
G4String fileName = argv[1];//Имя файла из командной строки при запуске проекта
// Мы считаем, что первым параметром было передано имя файла с командами для запуска
// проекта в пакетном режиме
UImanager->ApplyCommand(command+fileName);//Выполнение команды
}
// Окончание работы, вызов деструктора (удаление) G4RunManager
delete runManager;
return 0;
}
