
// Подключаем необходимые заголовочные файлы
#include "ExG4PrimaryGeneratorAction01.hh"
// Подключаем необходимы заголовочные файлы
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
// Источник частиц
#include "G4ParticleGun.hh"
// Таблица указателей на данные частиц
#include "G4ParticleTable.hh"
// Данные частиц
#include "G4ParticleDefinition.hh"
// Подключаем систему едениц измерения, что бы пользоваться еденицами cm, MeV.
#include "G4SystemOfUnits.hh"
// Генератор случайных чисел
#include "Randomize.hh"
#include "G4RandomDirection.hh"

///
/// \brief ExG4PrimaryGeneratorAction01::ExG4PrimaryGeneratorAction01 Формирование начального пучка.
/// Класс, в котором описывается положение, тип, энергия, направление вылета
/// и распределение начальных частиц
///
ExG4PrimaryGeneratorAction01::ExG4PrimaryGeneratorAction01()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0), 
  fEnvelopeBox(0),
  fAngle(180 * degree)
{
  // Данные, которые здесь задаются после могут быть изменены через команды в mac файле,
  // или в консольном режиме.
  // По умолчанию у источника частиц поставим 1 частицу
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // Получаем встроеную в Geant4 таблицу частиц
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  // Ищем частицу, в нашем случае протон
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  // Устанавливаем полученную частицу в качестве испускаемого типа начальных частиц в источнике
  fParticleGun->SetParticleDefinition(particle);
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
  //fParticleGun->SetParticleEnergy(700.0*keV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, 0.0));
}

/// Деструктор, удаляем созданный в конструкторе экземпляр класса источника G4ParticleGun
/// для очистки памяти
ExG4PrimaryGeneratorAction01::~ExG4PrimaryGeneratorAction01()
{
  // удаляем созданный в конструкторе экземпляр класса источника G4ParticleGun
  delete fParticleGun;
}

/// Эта функция вызывается в начале каждого события и генерирует начальные частицы.
/// Определенные здесь условия переписывают команды из файла mac и команды из
/// консольного режима.
void ExG4PrimaryGeneratorAction01::GeneratePrimaries(G4Event* anEvent)
{
  // Для избежания зависимости этого класса от класса DetectorConstruction,
  // мы получаем ссылку на объем детектора через класс G4LogicalVolumeStore
  
  G4double envSizeXY = 0;
  G4double envSizeZ = 0;
  // Проверяем или ссылка на fEnvelopeBox пустая
  if (!fEnvelopeBox)
  {
     // Если пустая, то получаем ссылку на объем детектора
    G4LogicalVolume* envLV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("Detector");
    if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  }
  // Получаем размеры объема, предполагается что, стороны по x и y одинаковы
  if ( fEnvelopeBox ) {
    envSizeXY = fEnvelopeBox->GetXHalfLength()*2.;
    envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
  }  
  else  {//Если ссылка на fEnvelopeBox пустая, выдаем предупреждение
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n"; 
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("B1PrimaryGeneratorAction::GeneratePrimaries()",
     "MyCode0002",JustWarning,msg);
  }
  // Задаем координаты где будет источник начальных частиц
  //G4double x0 = 0;
  //G4double y0 = 0;
  // Устанавливаем в положение -10 см, 0 означает цент мирового объема
  //G4double z0 = 0;
  // Команда устанавливает позицию источника начальных частиц
  G4double cosTheta = 1. - (1. - cos(fAngle)) * G4UniformRand();

  G4double phi = 360 * degree * G4UniformRand();

  G4double sinTheta = std::sqrt(1. - cosTheta * cosTheta);
  G4double ux = sinTheta * std::cos(phi),
      uy = sinTheta * std::sin(phi),
      uz = cosTheta;

 fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux, uy, uz));
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
  // Генерируем первичное событие
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
