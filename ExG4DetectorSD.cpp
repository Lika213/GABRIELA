// ********************************************************************
/*
#include<G4Step.hh>
// Для работы с файлами
#include<fstream>
// Для работы с покотками ввода и вывода
#include<iostream>
// Подключаем систему едениц измерения, что бы пользоваться еденицами cm, MeV.
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "ExG4DetectorSD.hh"
#include "G4TrackStatus.hh"   
// Используем пространство имен std, что бы не писать много где std::
using namespace std;
ExG4DetectorSD::ExG4DetectorSD(G4String name) : G4VSensitiveDetector(name),
HIST_MAX(2010 * keV),// Инициализация верхней границы
HIST_MIN(0 * keV)// Инициализация нижней границы
{
    // Обнуляем гистограммы
    for (int i = 0; i < NOBINS; i++) {
        histogram[i] = 0;
    }
}
G4bool ExG4DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
   {
    // Получаем кинетическую энергии частицы с предыдущего шага, т.е. начальную
    // кинетическую энегрию перед текущим шагом
    double energy = step->GetPreStepPoint()->GetKineticEnergy();
    double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
    if(step->GetTrack()->GetKineticEnergy() == 0){
         // Определяем индекс (номер) бина гистограммы энергии
         int index = int(floor((energy-HIST_MIN)/bin_width));
         // Добавляем +1 в соответствующий бин
         if(index >= 0 && index < NOBINS)
           histogram[index]++;
     // Так как мы хотим только измерить параметры частиц после прохождения
     // мишени и не интересуемся дальнейшей их судьбой в детекторе, то их убиваем -
     // устанавливаем статус остановлено и уничтожено (fStopAndKill)
     step->GetTrack()->SetTrackStatus(fStopAndKill);
    //step->GetTrack()->GetTrackID();
     return true;
   }
ExG4DetectorSD::~ExG4DetectorSD()
{
    // В деструкторе выводим гистограммы в файлы
    // Открываем файл (существующий файл полностью перезаписывается)
    std::ofstream file("spectrum.dat");
    // Вычисляем ширину бина
    double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
    // Выводим гистограмму
    for(int i = 0; i<NOBINS; i++)
    {
        // Вычисляем энергию
        double energy = i*bin_width + HIST_MIN;
        // Выводим в файл
        file << std::setw(15) << energy/keV << " "
             << std::setw(15) << histogram[i] << std::endl;
    }
    // Закрываем файл
    file.close();
    

}
*/
// ********************************************************************

#include<G4Step.hh>
// Для работы с файлами
#include<fstream>
// Для работы с покотками ввода и вывода
#include<iostream>
// Подключаем систему едениц измерения, что бы пользоваться еденицами cm, MeV.
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "ExG4DetectorSD.hh"

#include "G4SteppingManager.hh"
#include "G4VProcess.hh"
#include "G4ParticleTypes.hh"
// Используем пространство имен std, что бы не писать много где std::
using namespace std;
// Конструктор чувствительной области, по умолчанию инициализируем нижнюю и верхнюю
// границы гистограммы в 0 и 50 МэВ
ExG4DetectorSD::ExG4DetectorSD(G4String name) : G4VSensitiveDetector(name),
HIST_MAX(1310 * keV),// Инициализация верхней границы
HIST_MIN(0 * keV)// Инициализация нижней границы
{
    // Обнуляем гистограммы
    for (int i = 0; i < NOBINS; i++) {
        histogram[i] = 0;
        histogram_angle[i] = 0;
    }
}
//Вызывается на каждом шаге моделирования частицы, когда она попадает в этот чувствительный объем
G4bool ExG4DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
    //auto analysisManager = G4AnalysisManager::Instance();
    // Получаем кинетическую энергии частицы с предыдущего шага, т.е. начальную
    // кинетическую энегрию перед текущим шагом
   //double energy = step->GetPreStepPoint()->GetKineticEnergy();
    double energy = step->GetPreStepPoint()->GetKineticEnergy();
   //double energy = step->GetPostStepPoint()->GetTotalEnergy();
    // Вычисляем ширину бина (интерва) гистограммы
    double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
    //double it = 0.;

    G4Track* aTrack = step->GetTrack();
    //const G4VProcess* process = step->GetPostStepPoint()->GetProcessDefinedStep();
    //G4String processName = process->GetProcessName();
   // fRunAction->CountProcesses(processName); //count processes
    G4StepPoint* postStepPoint = step->GetPostStepPoint();
    
    /////////const G4VProcess* CurrentProcess = postStepPoint->GetProcessDefinedStep();
    //G4int parent_ID = aTrack->GetParentID();
   //////// //if (CurrentProcess != 0) {
        /////////const G4String& StepProcessName = CurrentProcess->GetProcessName();
       // G4String volumePos = aTrack->GetNextVolume()->GetName();
       G4double ParentID = step->GetTrack()->GetParentID();
       double KIN = step->GetPostStepPoint()->GetKineticEnergy();
        //if ((StepProcessName == "compt") && (TrackID == 1))
        //if (StepProcessName == "phot" && ParentID == 0)
       if (KIN == 0 && ParentID == 0) {
       //if (StepProcessName == "phot" ) {

            //it = it + 1;
            
            // if (processName == "compt") //return;

                // if (StepProcessName == "phot"){
             //if (step->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName() == "phot") {
                 // Определяем индекс (номер) бина гистограммы энергии
            int index = int(floor((energy - HIST_MIN) / bin_width));
            // Добавляем +1 в соответствующий бин
            if (index >= 0 && index < NOBINS)
                histogram[index]++;
       
            double ener = step->GetTotalEnergyDeposit();
            //double angle = ang.angle(*centerVector);
            //double bin_width_ang = (3.14) / NOBINS;
            double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
            // Получаем номер бина
            //index = int(floor((angle) / bin_width_ang));
             index = int(floor((ener - HIST_MIN) / bin_width));
            // Заполняем гистограмму
            if (index >= 0 && index < NOBINS)
                histogram_angle[index]++;
        }
    //}
    // Так как мы хотим только измерить параметры частиц после прохождения
    // мишени и не интересуемся дальнейшей их судьбой в детекторе, то их убиваем -
    // устанавливаем статус остановлено и уничтожено (fStopAndKill)
  //step->GetTrack()->SetTrackStatus(fStopAndKill);
  //G4cout  << it << G4endl;
    return true;
   
}

ExG4DetectorSD::~ExG4DetectorSD()
{
    // В деструкторе выводим гистограммы в файлы
    // Открываем файл (существующий файл полностью перезаписывается)
    std::ofstream file("spectrum.dat");
    // Вычисляем ширину бина
    double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
    // Выводим гистограмм
    for (int i = 0; i < NOBINS; i++)
    {
        // Вычисляем энергию
        double energy = i * bin_width + HIST_MIN;
        // Выводим в файл
        file << std::setw(15) << energy / keV << " "
            << std::setw(15) << histogram[i] << std::endl;
    }
    // Закрываем файл
    file.close();
    // Открываем файл для вывода гистограммы углового распределения
    file.open("prekin.dat");
    // Вычисляем ширину бина
   // bin_width = (3.14) / NOBINS;
    bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
    // Выводим гистограмму
    for (int i = 0; i < NOBINS; i++)
    {
        // Вычисляем угол
        double ener = i * bin_width + HIST_MIN;;
        // Выводим в файл
        file << std::setw(15) << ener / keV << " "
            << std::setw(15) << histogram_angle[i] << std::endl;
    }
    // Закрываем файл
    file.close();
}
