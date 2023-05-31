﻿
#include<G4VSensitiveDetector.hh>
#ifndef ExG4DetectorSD_h
#define ExG4DetectorSD_h 1
   class G4Step;
   class G4TouchableHistory;
   /// Класс определения чувствительной области детектора
   class ExG4DetectorSD: public G4VSensitiveDetector
     {
     private:
       //Создадим гистограмму в которую запишем распределение
       //энергии протонов
       //Число бинов (интервалов в гистограмме)
       static const int NOBINS = 400;
       //Максимальная энергия в гистограмме
       const double HIST_MAX;
       //Минимальная энергия в гистограмме
       const double HIST_MIN;
       //Объявляем саму гистограмму
       int histogram[NOBINS];
       //Постоим также угол, на который рассеялся протон
      int histogram_angle[NOBINS];
      
     public:
        //Контструктор, в нем обнуляем гистограммы
        ExG4DetectorSD(G4String name);
        //Декструктор, в нем выведем гистограммы в файл
        //Вывод данных в файл лучше делать здесь чем в ProcessHits, так как
        //вызов деструктора происходит в конце работы программы,
        //а если записывать в процессе моделирования, то значительное
        //время будет тратится на ожидание записи в файл. А это относительно
        //медленная процедура и занимает много времени и в результате
        //моделирование будет занимать больше времени чем нужно.
        ~ExG4DetectorSD();
        //Когда частица попадает в этот чувствительный объем, тогда на каждом
        //её шаге моделирования вызывается эта функция.
        //В ней мы получаем и собираем информацию о состоянии
        //частицы и ее треке
        G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
     };
#endif /* SENSITIVEDETECTOR */